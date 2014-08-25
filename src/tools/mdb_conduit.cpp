/**
 * Copyright (c) 2014 Charles J. Ezell III.
 *
 * This program is free software: you can redistribute it and/or  modify
 * it under the terms of the GNU Affero General Public License, version 3,
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * As a special exception, the copyright holders give permission to link the
 * code of portions of this program with the OpenSSL library under certain
 * conditions as described in each individual source file and distribute
 * linked combinations including the program with the OpenSSL library. You
 * must comply with the GNU Affero General Public License in all respects for
 * all of the code used other than as permitted herein. If you modify file(s)
 * with this exception, you may extend this exception to your version of the
 * file(s), but you are not obligated to do so. If you do not wish to do so,
 * delete this exception statement from your version. If you delete this
 * exception statement from all source files in the program, then also delete
 * it in the license file.
 */


#include "aggregate.h"

#include <algorithm>
#include <exception>
#include <fstream>
#include <sstream>
#include <vector>

#include <boost/filesystem/operations.hpp>
#include <boost/program_options.hpp>

#include <mongo/db/json.h>


using namespace std;
using mongo::BSONObj;
namespace fs = boost::filesystem;
namespace po = boost::program_options;

enum class InputFormat {
      JSON,
      BSON
};

//Converts a json array into bson.
BSONObj convertJsonArrayToBson(const string& json) {
   //Ugh.  fromjson() doesn't support top-level arrays?
   //This is annoying but I'm not concerned about JSON input performance.
   string rawJson("{\"w\":");
   rawJson.append(json);
   rawJson.append("}");

   //TODO: return better errors for the user than just:
   //code FailedToParse: FailedToParse: Expecting '{': offset:0 of:[{$match:{v:1}}]
   auto wrapped(mongo::fromjson(rawJson)),
            result(wrapped.getField("w").Obj());

   return result.getOwned();
}

//Read a file into a string.  No JSON validation is performed.
string loadSmallFile(const fs::path& path) {
   ifstream file(path.native());
   return string(istreambuf_iterator<char>(file),
      istreambuf_iterator<char>());
}

BSONObj readSmallBsonFile(const fs::path& path) {
   //Temp, just for testing.
   //Based off of BSONTool::processFile().
   //Going to rewrite this to use a memmapped file
   //and wrap it all in BsonFileDocumentSource.

   ifstream file(path.native());
   vector<char> data(fs::file_size(path));

    copy(istreambuf_iterator<char>(file),
      istreambuf_iterator<char>(), data.begin());

   mongo::BSONArrayBuilder b;

   char* p(&data[0]),
            *end(p + data.size());

   while(p < end) {
      size_t objsize(0);

      if((p+4) < end) {
         memcpy(&objsize, p, 4);
      }
      else {
         stringstream ss;
         const size_t offset(p - &data[0]);

         ss << "Unexpected end of BSON file '" << path.native()
               << "' at " << offset << " bytes.";

         throw runtime_error(ss.str());
      }

      if(objsize > mongo::BSONObjMaxUserSize) {
         stringstream ss;
         const size_t offset(p - &data[0]);

         ss << "BSON file '" << path.native()
               << "' appears to be corrupt near " << offset << " bytes.";

         throw runtime_error(ss.str());
      }

      BSONObj temp(p);
      b.append(temp);

      p += objsize;
   }

   return b.obj();
}

BSONObj loadFile(const InputFormat format, const fs::path& path) {
   BSONObj result;

   switch(format) {
      case InputFormat::BSON:
         return readSmallBsonFile(path);

      case InputFormat::JSON:
         return convertJsonArrayToBson(loadSmallFile(path));

      default:
         throw runtime_error("Unknown format for '" + path.native() + "': somebody screwed up.");
   }
}

InputFormat getInputFormat(const string& desc, const string& format) {
   if("bson" == format) {
      return InputFormat::BSON;
   }
   else if("json" == format) {
      return InputFormat::JSON;
   }
   else {
      throw logic_error("Unknown " + desc + " format: '" + format + "'");
   }
}

void getInputFormats(
   const string& formatSpec,
   InputFormat& pipelineFormat,
   InputFormat& dataFormat) {

   auto delimIdx(formatSpec.find('-'));

   if(string::npos == delimIdx || formatSpec.size() < delimIdx+1) {
      throw logic_error("Invalid format: '" + formatSpec + "'");
   }

   pipelineFormat = getInputFormat(
      "pipeline", formatSpec.substr(0, delimIdx));

   dataFormat  = getInputFormat("data", formatSpec.substr(delimIdx+1));
}

void conflicting_options(
   const po::variables_map& variables,
   const string& opt1,
   const string& opt2) {

   bool opt1Set(variables.count(opt1) && !variables[opt1].defaulted()),
            opt2Set(variables.count(opt2) && !variables[opt2].defaulted());

   if (opt1Set && opt2Set) {
      throw logic_error(
         string("Conflicting options '") + opt1 + "' and '" + opt2 + "'.");
   }
}

int main(int argc, char** argv, char** env) {

   try {
      po::options_description options("Options");
      options.add_options()
          ("help", "Show usage")
          ("eval,e", po::value<string>(), "A JSON pipeline to evaluate.")
          ("pipeline,p", po::value<fs::path>(), "The path to a pipeline to evaluate.")
          ("data,d", po::value<fs::path>()->required(), "The path to a data file to run the pipeline on.")
          ("format,f", po::value<string>()->default_value("bson-bson"), "Specifies the input and output format for --pipeline and --data, respectively.  One of: bson-bson, json-json, json-bson, bson-json.")
      ;

      po::positional_options_description p;
      p.add("data", -1);

      po::variables_map variables;
      po::store(po::command_line_parser(argc, argv).
             options(options).positional(p).run(),  variables);

      conflicting_options(variables, "eval", "pipeline");

      po::notify(variables);

      if (variables.count("help")) {
          cout << options << "\n";
          return 0;
      }

      InputFormat pipelineFormat, dataFormat;
      getInputFormats(
         variables["format"].as<string>(),
         pipelineFormat,
         dataFormat
      );

      BSONObj data, pipeline;

      if (variables.count("eval")) {
         auto pipelineJson(variables["eval"].as<string>());

         pipeline = convertJsonArrayToBson(pipelineJson);
      }
      else if(variables.count("pipeline")) {
         auto path(variables["pipeline"].as<fs::path>());

         pipeline = loadFile(pipelineFormat, path);
      }
      else {
         throw logic_error("You must provide a pipeline via either --eval or\
            --pipeline.");
      }

      if (variables.count("data")) {
         auto path(variables["data"].as<fs::path>());

         data = loadFile(dataFormat, path);
      }
      else {
         //TODO: it might be nice to have a pipeline validation mode.
         throw logic_error("You must provide a data file.");
      }

      mdb::Aggregate conduit(pipeline);

      mongo::BSONObjBuilder result;
      conduit(data, result);

      string jsonResult(result.obj().jsonString());

      cout << jsonResult << '\n';

      return 0;
   }
   catch(exception& e) {
      std::cerr << e.what() << '\n';
      return 1;
   }
}

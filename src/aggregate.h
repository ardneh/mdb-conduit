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

#pragma once

#include <memory>                  //TODO: use boost unique_ptr for portability.
//#include <vector>                          //For writeExplainOps().

//Needed for verify(), massert(), uasset() for all of the bson stuff.
//TODO: see if those can be disabled via a define or find out what specific
//headers I need to include.
#include <mongo/pch.h>

#include <mongo/bson/bsonobjbuilder.h>
//#include <mongo/db/pipeline/value.h> //For writeExplainOps().


namespace mongo {
   class DocumentSource;
   class ExpressionContext;
}

//Warning: API completely unstable.
//I want to try to prevent the average user to have to mix mdb:; and mongo::
//but also do not want things to get too confusing.
//Todo: mdb->conduit?
namespace mdb {

   //For user convenience.
   using boost::intrusive_ptr;
   using mongo::BSONObj;
   using mongo::BSONObjBuilder;
   using mongo::Status;

   //Performs one-time initialization.
   //Call this before creating an Aggregate instance.
   //You can safely pass nullptr for argv and envp.
   Status intialize_module(
      const int argc,
      const char** argv,
      const char** envp);

   //Cleanup.  Do not create any Aggregate instances after calling this.
   Status deinitalize_module();

   //Constructs an aggregation pipeline to be used to transform a stream
   //of data.
   //This may well end up getting renamed Conduit or MdbPipeline.
   class Aggregate {
      public:

         //Construct an aggregator for the given bson-encoded-pipeline array.
         Aggregate(const BSONObj& pipeline);
         virtual ~Aggregate();

         //Run the pipeline against data and store the results in result.
         void operator()(const BSONObj& data, BSONObjBuilder& result);

         //Run the pipeline against the documents provided by source and
         //store the results in result.
         void operator()(
            intrusive_ptr<mongo::DocumentSource> source,
            BSONObjBuilder& result);

         //Provide access to the context for creating document sources.
         intrusive_ptr<mongo::ExpressionContext> getContext() const;

         //bool isExplain() const;
         //vector<Value> writeExplainOps() const;

      protected:
         void prepareSource(
            intrusive_ptr<mongo::DocumentSource> source);

      private:

            //Prevent basic clients from having to pull in / know anything about
            //the internals of mongo pipelines.
            struct Impl;
            std::unique_ptr<Impl> impl;
   };

} //namespace mdb.

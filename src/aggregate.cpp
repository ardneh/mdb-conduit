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

#include <exception>

#include <mongo/base/initializer.h>
#include <mongo/bson/bsonobj.h>                       //intrusive_ptr_add_ref().
#include <mongo/db/pipeline/document_source.h>  //intrusive_ptr_add_ref().
#include <mongo/db/pipeline/expression_context.h>
#include <mongo/db/pipeline/pipeline.h>

#include "db/interrupt_status_noop.h"


using namespace mongo;

namespace mdb {

   Status intialize_module(const int argc,  const char** argv, const char ** envp) {
      return runGlobalInitializers(argc, argv, envp);
   }

   Status deinitalize_module() {
      return Status(ErrorCodes::OK, "");
   }

   struct Aggregate::Impl {
      //If this is going to be the only thing in here, then get rid of Impl.
      intrusive_ptr<Pipeline> pipeline;
   };

   Aggregate::Aggregate(const BSONObj& pipeline)
   : impl(new Aggregate::Impl()) {

      //The Pipeline class expects to receive a command, so build one.
      BSONObjBuilder bldr;
      bldr.appendArray("pipeline", pipeline);

      intrusive_ptr<ExpressionContext> ctx(
         new ExpressionContext(InterruptStatusNoop::status,
            NamespaceString("mdb-conduit")));

      std::string errmsg;
      impl->pipeline = Pipeline::parseCommand(errmsg, bldr.obj(), ctx);

      if (!impl->pipeline.get()) {
         //TODO: throw UserException instead?
         throw std::runtime_error(errmsg);
      }
   }

   Aggregate::~Aggregate() {

   }

   /*void Aggregate::operator()(
      const BSONObj& data,
      BSONObjBuilder& result) {

      throw std::runtime_error("Aggregate() directly against bson isn't \
      implemented yet")
   }*/

   void Aggregate::operator()(
      intrusive_ptr<mongo::DocumentSource> source,
      BSONObjBuilder& result) {

      intrusive_ptr<Pipeline> pipeline(impl->pipeline);

      pipeline->addInitialSource(source);
      pipeline->stitch();
      pipeline->run(result);

      //TODO: remove the initialSource.  Need to do so for exceptions, too.
   }

   intrusive_ptr<mongo::ExpressionContext>
   Aggregate::getContext() const {
      return impl->pipeline->getContext();
   }

} //namespace mdb.

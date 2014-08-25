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

/** Misc notes:

   * DocumentSourceOut and DocumentSourceGeoNear 'implement'
      DocumentSourceNeedsMongod so they are not allowed right now.  I
      haven't looked much at MongodImplementation but we can
      probably support at least Geo and maybe our own version of $out (maybe
      a new file).
   * See db/commands/pipeline_command.cpp handleCursorCommand() and
      PipelineRunner for how to get result documents back as they are
      processed.

      //Streaming output pseudocode.
      boost::optional<BSONObj> getNextBson() {
         auto next = _pipeline->output()->getNext();
         if (next) {
            if (_includeMetaData) {
               return next->toBsonWithMetaData();
            }
            else {
               return next->toBson();
            }
         }

         return boost::none;
      }
 */


#include "mdb_pipeline.h"

#include <exception>

#include <mongo/base/initializer.h>
#include <mongo/bson/bsonobj.h>                       //intrusive_ptr_add_ref().
#include <mongo/db/pipeline/document_source.h>  //intrusive_ptr_add_ref().
#include <mongo/db/pipeline/expression_context.h>
#include <mongo/db/pipeline/pipeline.h>

#include "db/interrupt_status_noop.h"


using mongo::Status;
using mongo::BSONObj;
using mongo::BSONObjBuilder;


namespace conduit {

   Status intialize_module(int argc, char** argv, char** env) {
      //TODO: fix the missing logger global initializer that is causing this
      //             to fail.
      //TODO: determine whether this is even needed for what we are doing.
      //return mongo::runGlobalInitializers(argc, argv, env);

      return Status::OK();
   }

   Status deinitalize_module() {
      return Status::OK();
   }

   struct Pipeline::Impl {
      //If this is going to be the only thing in here, then get rid of Impl.
      MongoPipelinePtr pipeline;
   };

   Pipeline::Pipeline(const BSONObj& pipeline)
   : impl(new Pipeline::Impl()) {

      //The mongo::Pipeline class expects to receive a command, so build one.
      BSONObjBuilder bldr;
      bldr.appendArray("pipeline", pipeline);

      ExpressionContextPtr ctx(
         new ExpressionContext(mongo::InterruptStatusNoop::status,
            mongo::NamespaceString("mdb-conduit")));

      std::string errmsg;
      impl->pipeline = mongo::Pipeline::parseCommand(errmsg, bldr.obj(), ctx);

      if (!impl->pipeline.get()) {
         //TODO: throw UserException instead?
         throw std::runtime_error(errmsg);
      }
   }

   Pipeline::~Pipeline() {

   }

   void Pipeline::operator()(
      const BSONObj& data,
      BSONObjBuilder& result) {

      auto pipeline(impl->pipeline);

      auto source(mongo::DocumentSourceBsonArray::create(
         data,
         pipeline->getContext()));

      prepareSource(source);

      pipeline->run(result);
   }

   void Pipeline::operator()(
      DocumentSourcePtr source,
      BSONObjBuilder& result) {

      prepareSource(source);

      impl->pipeline->run(result);
   }

   ExpressionContextPtr Pipeline::getContext() const {
      return impl->pipeline->getContext();
   }

   void Pipeline::prepareSource(DocumentSourcePtr source) {
         auto pipeline(impl->pipeline);

         // These steps were pieced together from:
         //  PipelineD::prepareCursorSource(aggregator, pCtx);
         // TODO: I've skipped a bunch of steps like coalescing just to test this
         // out, put them back in.

         pipeline->addInitialSource(source);
         pipeline->stitch();
      }

} //namespace conduit.

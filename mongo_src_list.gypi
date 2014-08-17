{
"variables":{
"mongo_matcher_src_files": [
   #"<(LIB_DIR)/mongo/db/matcher/matcher.cpp",		 # Run time, pipeline.
   #"<(LIB_DIR)/mongo/db/matcher/expression_parser.cpp",		 # Run time, pipeline
   "<(LIB_DIR)/mongo/db/matcher/expression_array.cpp",
   #"<(LIB_DIR)/mongo/db/matcher/expression_array_test.cpp",
   "<(LIB_DIR)/mongo/db/matcher/expression.cpp",
   "<(LIB_DIR)/mongo/db/matcher/expression_geo.cpp",
   #"<(LIB_DIR)/mongo/db/matcher/expression_geo_test.cpp",
   "<(LIB_DIR)/mongo/db/matcher/expression_leaf.cpp",
   #"<(LIB_DIR)/mongo/db/matcher/expression_leaf_test.cpp",
   #"<(LIB_DIR)/mongo/db/matcher/expression_parser_array_test.cpp",
   "<(LIB_DIR)/mongo/db/matcher/expression_parser.cpp",
   "<(LIB_DIR)/mongo/db/matcher/expression_parser_geo.cpp",
   #"<(LIB_DIR)/mongo/db/matcher/expression_parser_geo_test.cpp",
   #"<(LIB_DIR)/mongo/db/matcher/expression_parser_leaf_test.cpp",
   #"<(LIB_DIR)/mongo/db/matcher/expression_parser_test.cpp",
   #"<(LIB_DIR)/mongo/db/matcher/expression_parser_text.cpp",
   #"<(LIB_DIR)/mongo/db/matcher/expression_parser_text_test.cpp",
   "<(LIB_DIR)/mongo/db/matcher/expression_parser_tree.cpp",
   #"<(LIB_DIR)/mongo/db/matcher/expression_parser_tree_test.cpp",
   #"<(LIB_DIR)/mongo/db/matcher/expression_test.cpp",
   "<(LIB_DIR)/mongo/db/matcher/expression_text.cpp",
   "<(LIB_DIR)/mongo/db/matcher/expression_tree.cpp",
   #"<(LIB_DIR)/mongo/db/matcher/expression_tree_test.cpp",
   "<(LIB_DIR)/mongo/db/matcher/expression_where.cpp",
   "<(LIB_DIR)/mongo/db/matcher/matchable.cpp",
   "<(LIB_DIR)/mongo/db/matcher/match_details.cpp",
   "<(LIB_DIR)/mongo/db/matcher/matcher.cpp",
   "<(LIB_DIR)/mongo/db/matcher/path.cpp",
   "<(LIB_DIR)/mongo/db/matcher/path_internal.cpp",
   #"<(LIB_DIR)/mongo/db/matcher/path_test.cpp",
],
"mongo_pipeline_src_files": [
   "<(LIB_DIR)/mongo/db/pipeline/accumulator_add_to_set.cpp",
   "<(LIB_DIR)/mongo/db/pipeline/accumulator_avg.cpp",
   "<(LIB_DIR)/mongo/db/pipeline/accumulator_first.cpp",
   "<(LIB_DIR)/mongo/db/pipeline/accumulator_last.cpp",
   "<(LIB_DIR)/mongo/db/pipeline/accumulator_min_max.cpp",
   "<(LIB_DIR)/mongo/db/pipeline/accumulator_push.cpp",
   "<(LIB_DIR)/mongo/db/pipeline/accumulator_sum.cpp",
   "<(LIB_DIR)/mongo/db/pipeline/dependencies.cpp",
   "<(LIB_DIR)/mongo/db/pipeline/document.cpp",
   "<(LIB_DIR)/mongo/db/pipeline/document_source.cpp",
   "<(LIB_DIR)/mongo/db/pipeline/document_source_bson_array.cpp",
   "<(LIB_DIR)/mongo/db/pipeline/document_source_command_shards.cpp",
   "<(LIB_DIR)/mongo/db/pipeline/document_source_cursor.cpp", # This pulled in a ton of stuff, including a bunch of server only things.  Try to get rid of it or split it up to client only bits.
   "<(LIB_DIR)/mongo/db/pipeline/document_source_geo_near.cpp",
   "<(LIB_DIR)/mongo/db/pipeline/document_source_group.cpp",
   "<(LIB_DIR)/mongo/db/pipeline/document_source_limit.cpp",
   "<(LIB_DIR)/mongo/db/pipeline/document_source_match.cpp",
   "<(LIB_DIR)/mongo/db/pipeline/document_source_merge_cursors.cpp",
   "<(LIB_DIR)/mongo/db/pipeline/document_source_out.cpp",
   "<(LIB_DIR)/mongo/db/pipeline/document_source_project.cpp",
   "<(LIB_DIR)/mongo/db/pipeline/document_source_redact.cpp",
   "<(LIB_DIR)/mongo/db/pipeline/document_source_skip.cpp",
   "<(LIB_DIR)/mongo/db/pipeline/document_source_sort.cpp",
   "<(LIB_DIR)/mongo/db/pipeline/document_source_unwind.cpp",
   "<(LIB_DIR)/mongo/db/pipeline/expression.cpp",
   "<(LIB_DIR)/mongo/db/pipeline/field_path.cpp",
   "<(LIB_DIR)/mongo/db/pipeline/pipeline.cpp",
   # "<(LIB_DIR)/mongo/db/pipeline/pipeline_d.cpp",  # Includes a bunch of server side stuff, try to not include it.
   "<(LIB_DIR)/mongo/db/pipeline/value.cpp",
],
"mongo_bson_src_files": [
   #"<(LIB_DIR)/mongo/bson/bsondemo/bsondemo.cpp",
   "<(LIB_DIR)/mongo/bson/mutable/document.cpp",
   "<(LIB_DIR)/mongo/bson/mutable/element.cpp",
   #"<(LIB_DIR)/mongo/bson/mutable/mutable_bson_algo_test.cpp",
   #"<(LIB_DIR)/mongo/bson/mutable/mutable_bson_test.cpp",
   #"<(LIB_DIR)/mongo/bson/mutable/mutable_bson_test_utils.cpp",
   "<(LIB_DIR)/mongo/bson/util/bson_extract.cpp",
   #"<(LIB_DIR)/mongo/bson/util/bson_extract_test.cpp",
   #"<(LIB_DIR)/mongo/bson/util/builder_test.cpp",
   #"<(LIB_DIR)/mongo/bson/bson_field_test.cpp",
   #"<(LIB_DIR)/mongo/bson/bson_obj_test.cpp",
   "<(LIB_DIR)/mongo/bson/bson_validate.cpp",
   #"<(LIB_DIR)/mongo/bson/bson_validate_test.cpp",
   #"<(LIB_DIR)/mongo/bson/bsonobjbuilder_test.cpp",
   "<(LIB_DIR)/mongo/bson/oid.cpp",
"<(LIB_DIR)/mongo/bson/optime.cpp",
],
"mongo_misc_src_files": [
#"<(LIB_DIR)/mongo/base/counter_test.cpp",
"<(LIB_DIR)/mongo/base/global_initializer.cpp",
"<(LIB_DIR)/mongo/base/global_initializer_registerer.cpp",
"<(LIB_DIR)/mongo/base/init.cpp",
"<(LIB_DIR)/mongo/base/initializer.cpp",
"<(LIB_DIR)/mongo/base/initializer_context.cpp",
"<(LIB_DIR)/mongo/base/initializer_dependency_graph.cpp",
#"<(LIB_DIR)/mongo/base/initializer_dependency_graph_test.cpp",
#"<(LIB_DIR)/mongo/base/initializer_test.cpp",
"<(LIB_DIR)/mongo/base/make_string_vector.cpp",
#"<(LIB_DIR)/mongo/base/owned_pointer_map_test.cpp",
#"<(LIB_DIR)/mongo/base/owned_pointer_vector_test.cpp",
"<(LIB_DIR)/mongo/base/parse_number.cpp",
#"<(LIB_DIR)/mongo/base/parse_number_test.cpp",
"<(LIB_DIR)/mongo/base/status.cpp",
#"<(LIB_DIR)/mongo/base/status_test.cpp",
"<(LIB_DIR)/mongo/base/string_data.cpp",
#"<(LIB_DIR)/mongo/base/string_data_test.cpp",
"<(LIB_DIR)/mongo/base/error_codes.cpp",
"<(LIB_DIR)/mongo/pch.cpp",
#"<(LIB_DIR)/mongo/platform/atomic_word_test.cpp",
"<(LIB_DIR)/mongo/platform/backtrace.cpp",
#"<(LIB_DIR)/mongo/platform/bits_test.cpp",
"<(LIB_DIR)/mongo/platform/posix_fadvise.cpp",
"<(LIB_DIR)/mongo/platform/process_id.cpp",
#"<(LIB_DIR)/mongo/platform/process_id_test.cpp",
"<(LIB_DIR)/mongo/platform/random.cpp",
#"<(LIB_DIR)/mongo/platform/random_test.cpp",
"<(LIB_DIR)/mongo/platform/strcasestr.cpp",
"<(LIB_DIR)/mongo/logger/console.cpp",
#"<(LIB_DIR)/mongo/logger/console_test.cpp",
"<(LIB_DIR)/mongo/logger/log_manager.cpp",
"<(LIB_DIR)/mongo/logger/log_severity.cpp",
#"<(LIB_DIR)/mongo/logger/log_test.cpp",
"<(LIB_DIR)/mongo/logger/logger.cpp",
"<(LIB_DIR)/mongo/logger/logstream_builder.cpp",
"<(LIB_DIR)/mongo/logger/message_event_utf8_encoder.cpp",
"<(LIB_DIR)/mongo/logger/message_log_domain.cpp",
"<(LIB_DIR)/mongo/logger/ramlog.cpp", # Includes util/mongoutils/html.h, trying to skip.  RamLog::get() needed at runtime.
"<(LIB_DIR)/mongo/logger/rotatable_file_manager.cpp", # Includes mongo/util/map_util.h, trying to skip.
#"<(LIB_DIR)/mongo/logger/rotatable_file_writer.cpp", # Part of rotatable_file_manager.cpp ?
#"<(LIB_DIR)/mongo/logger/rotatable_file_writer_test.cpp",
"<(LIB_DIR)/mongo/db/jsobj.cpp",
"<(LIB_DIR)/mongo/db/dbmessage.cpp",
"<(LIB_DIR)/mongo/db/query/lite_parsed_query.cpp",
"<(LIB_DIR)/mongo/util/intrusive_counter.cpp",
"<(LIB_DIR)/mongo/util/debug_util.cpp",
"<(LIB_DIR)/mongo/util/time_support.cpp",
#"<(LIB_DIR)/mongo/util/thread_name.cpp", 	# Causing linker errors.
"<(LIB_DIR)/mongo/util/hex.cpp",
"<(LIB_DIR)/mongo/util/concurrency/thread_name.cpp",
#"<(LIB_DIR)/mongo/util/net/message.cpp",		# Doesn't seem like we should need this.
#"<(LIB_DIR)/mongo/util/net/message_port.cpp",	# Doesn't seem like we should need this.

# Everything below was added to resolve missing symbol errors at runtime.
"<(LIB_DIR)/mongo/util/assert_util.cpp",		# DBException
"<(LIB_DIR)/mongo/util/stacktrace.cpp",		# Needed by DBException.
"<(LIB_DIR)/mongo/util/startup_test.cpp",		# StartupTest.
"<(LIB_DIR)/mongo/db/storage_options.cpp",	# storageGlobalParams
"<(LIB_DIR)/mongo/db/server_parameters.cpp",	# Needed by storage_options.cpp
#"<(LIB_DIR)/mongo/client/replica_set_monitor.cpp",	# Needed by storage_options.cpp
"<(LIB_DIR)/mongo/db/auth/action_type.cpp",		#
#"<(LIB_DIR)/mongo/db/auth/action_set.cpp",		#
"<(LIB_DIR)/mongo/client/dbclientcursor.cpp",	# DBClientCursor
"<(LIB_DIR)/mongo/client/connpool.cpp",		# pool
"<(LIB_DIR)/mongo/util/background.cpp",		# PeriodicTask
#"<(LIB_DIR)/mongo/util/net/ssl_manager.cpp",	# needed by background.cpp
"<(LIB_DIR)/mongo/client/dbclient.cpp",		#
"<(LIB_DIR)/mongo/db/query/type_explain.cpp",
"<(LIB_DIR)/mongo/client/sasl_client_authenticate.cpp",
"<(LIB_DIR)/mongo/util/util.cpp",		# PeriodicTask
#"<(LIB_DIR)/mongo/db/client.cpp",		#
#"<(LIB_DIR)/mongo/db/client_basic.cpp",		#
#"<(LIB_DIR)/mongo/db/commands.cpp",		# Load.
#"<(LIB_DIR)/mongo/db/lasterror.cpp",		# Load.
"<(LIB_DIR)/mongo/util/log.cpp",		# Load.
#"<(LIB_DIR)/mongo/db/repl/rs.cpp",		# Load.
#"<(LIB_DIR)/mongo/s/d_state.cpp",		# Load: shardingState
"<(LIB_DIR)/mongo/db/server_options.cpp",		# Load: serverGlobalOptions.
"<(LIB_DIR)/mongo/util/timer.cpp",		# Timer::_countsPerSecond
"<(LIB_DIR)/mongo/util/net/sock.cpp",		# vtable SocketException
"<(LIB_DIR)/mongo/db/json.cpp",    # fromjson()
"<(LIB_DIR)/mongo/util/base64.cpp",		# json.cpp
"<(LIB_DIR)/mongo/util/fail_point.cpp",		# FailPoint()
"<(LIB_DIR)/mongo/util/concurrency/spin_lock.cpp",  # SpinLock()
"<(LIB_DIR)/mongo/util/fail_point_service.cpp",		# Run time, dependency graph stuff.
"<(LIB_DIR)/mongo/util/fail_point_registry.cpp",		# Run time, dependency graph stuff.
"<(LIB_DIR)/mongo/db/field_ref.cpp",
]
}
}

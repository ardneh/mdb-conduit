// Hacks to get around missing symbols and things we will never need.

#include "mongo/pch.h"

#include <mongo/db/matcher/expression_parser.h>
#include <mongo/util/concurrency/threadlocal.h>		//TSP_DEFINE
#include <mongo/db/query/find_constants.h>  			//MaxBytesToReturnToClientAtOnce
#include <mongo/scripting/engine.h>							//globalScriptEngine


namespace mongo {
	// Yet another dynamic symbol failure (when using $sort).
	// This is defined in mongo/db/server_options_helpers.cpp providing my own
	// version
	// to avoid having to pull in even more libs.  Should move this somewhere else.
	bool isMongos() { return false; }

	// Yep, this is horrible. :)  It's defined as part of the mongos code
	// and I do not want to pull any more things in.
	struct VersionManager {};
	VersionManager versionManager;

	StatusWithMatchExpression (*weNeed_parse)(const BSONObj &) =
	    &MatchExpressionParser::parse;

	//To avoid linking in client.cpp which pulls in the kitchen sink.
	class Client {};
	TSP_DEFINE(Client, currentClient);

	const int32_t MaxBytesToReturnToClientAtOnce = 4 * 1024 * 1024;

	ScriptEngine* globalScriptEngine = 0;
}

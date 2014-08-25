* Lint.
* Coalesce and optimize the input pipeline.
* Make a _json aggregate hook that will take json as input and
  output json.
* Get rid of the extra `out` subdirectory in build.
* Make it extendable (DocumentSources, Pipeline, etc...).
*  Compile MongoDB's buildinfo.cpp and
   call compilerFlags() in bindings.gyp to get the compiler flags for the
   pipeline.
* Move compile the mongo code in its own target so different cflags can be
   used.
* Run as many of MongoDB's unit tests as possible.
* Develop an pipeline agnostic set of tests that can be used for this and munge.
*  Investigate what it would take for the bson builder / reader classes to
   handle json.
* Make it able to accept/return json or bson.
* Use thread pool instead of trying to make any part of the pipeline async,
  which is pretty much pointless because of $group and $sort).
* See if it would be easy to add a pipeline-version flag [2.4, 2.6].
* Use C++11 or, preferrably 14.
* Try to re-use MongoDB's pipeline test cases.
* Only include (build) the files we actually need from MongoDB (mostly in
  pipeline/).  document_source_cursor.h/cpp is causing us to pull in way more
  than we need.

This library makes [MongoDB's](http://mongodb.org) aggregation pipeline
(henceforce `pipeline`) available for use in in any C++ program.

Potential uses
--------------
* Provide a common API to query/transform data in an application (one DSL).
* Pre/post-processing of data returned by MongoDB.
* Test out ideas for new pipeline functionality.
* Profile pipeline operations more easily.

Examples
--------
* As a command.
  ```sh
   echo '[{v:5},{v:1},{v:3},{v:4},{v:2},{v:0}]' >> array.json
   mdb-conduit '[{$sort:{v:1}}]' -f "json-json"  array.json
  ```
* Programmatically.
  ```C++
   //Note: I haven't tried to compile this yet, but it should be close.  Sorry!

   #include <iostream>
   #include <src/mdb_pipeline.h>

   using namespace conduit;

   void printTransformedData(BSONObj pipeline, BSONObj data) {
      Pipeline conduit(pipeline);

      BSONObjBuilder result;
      conduit(data, result);

      cout << result.obj().jsonString());
   }
   ```
* See conduit_main() in src/tools/mdb_conduit.cpp for a full example.

Bindings
--------
NodeJS: https://www.npmjs.org/package/mdb-conduit

Disclaimers
-----------
* The build here is very bare bones and only tested on a newer install of
  Arch Linux.  I just to make sure it builds on its own.  My primary use
  for this right now is in a NodeJS module and node-gyp provides a bunch
  of useful defaults that I'm leaning on. It will get improved once I'm
  using this library more directly from C++ and Python.
* Full text search pulled in a bunch of stuff to read from the disk so I
  assume it will not work.  It's not something I anticipate needing any time
  soon so it's very low on the list of things to test/fix.
* Where expressions require a bunch of auth stuff.  I doubt they will work.
* This was initially put together as a very quick proof-of-concept so in it's
  current state it is not pretty.
* It is only going to build on `nix platforms for now.  "Linux" should work
  and OS X should be easy to make work if it does not already.

Build Requirements
------------------
* A bash compatible shell
* Git
* Python
* A C++11 capable compiler.

Development Build Steps
-----------------------
* Clone the source and cd into that directory.
* Configure.
  ```sh
  third_party/gyp/gyp --depth=. -f make --generator-output=./build/ mdb-conduit.gyp
  ```
* Build.  This should take ~5-6 minutes on a slower box.
  ```sh
  DEBUG=1 make -C build
* The `mdb-conduit` executable which allows you to run pipelines against bson
  or json files is placed in `build/out/Debug/mdb-conduit`.
  ```

Embedding
---------
If you are using GYP already, just add "<path-to-this-project>/mdb-conduit.gyp:mdb-conduit" to your
dependencies.  Otherwise, follow the development build steps and link with
the libs in `build/out/Debug/obj.target`.  Take a look at mdb-conduit.gyp as well as binding.gyp in
node-mdb-conduit.

License
-------
GNU Affero General Public License (AGPL), with the same exceptions as MongoDB:

  Most MongoDB source files (src/mongo folder and below) are made available under the terms of the
    GNU Affero General Public License (AGPL).  See individual files for
    details.

    As an exception, the files in the client/, debian/, rpm/,
    utils/mongoutils, and all subdirectories thereof are made available under
    the terms of the Apache License, version 2.0.

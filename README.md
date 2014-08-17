This library makes [MongoDB's](http://mongodb.org) aggregation pipeline
(henceforce `pipeline`) available for use in in any C++ program.

Potential uses
--------------
* Provide a common API to query/transform data in an application (one DSL).
* Pre/post-processing of data returned by MongoDB.
* Test out ideas for new pipeline functionality.
* Profile pipeline operations more easily.

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
* This is the first time I've used gyp, so I am certain I could be doing some
  things better there.  And now it looks like gyp is dead so I'm not going to
  put much effort into making the gyp files perfect.  Long live gn....
* This is also my first native node module so it's going to be rough.

Build Requirements
------------------
* A bash compatible shell
* Git
* Python
* The rest of the MongoDB build requirements?
*  See [Building MongoDB](http://www.mongodb.org/about/contributors/tutorial/build-mongodb-from-source/)

Using from C++
--------------
If you are using GYP already, just add "<path-to-this-project>/mdb-conduit.gyp:mdb-conduit" to your
dependencies.  Otherwise, follow the development build steps and link with
build/out/Debug/obj.target/libmdb-conduit.

Development Build Steps
-----------------------
* Clone the source and cd into that directory.
* Configure.
  ```sh
  third_party/gyp/gyp --depth=. -f make --generator-output=./build/ mdb-conduit.gyp
  ```
* Build.  This should take ~5-6 minutes on a slower box.
  ```sh
  make -C build
  ```

License
-------
GNU Affero General Public License (AGPL), with the same exceptions as MongoDB:

  Most MongoDB source files (src/mongo folder and below) are made available under the terms of the
    GNU Affero General Public License (AGPL).  See individual files for
    details.

    As an exception, the files in the client/, debian/, rpm/,
    utils/mongoutils, and all subdirectories thereof are made available under
    the terms of the Apache License, version 2.0.

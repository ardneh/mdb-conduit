#!/usr/bin/env bash

if [ ! -d third_party/mongo ]; then
	git clone -b v2.6 --depth 1 --single-branch https://github.com/mongodb/mongo third_party/mongo
fi

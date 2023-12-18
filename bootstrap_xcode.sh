#!/bin/bash

rm -rf build
cmake . -G "Xcode" -B build -DCMAKE_INSTALL_PREFIX=$(pwd)/build/install -DCMAKE_BUILD_TYPE=Debug -DCMAKE_OSX_DEPLOYMENT_TARGET=14.0

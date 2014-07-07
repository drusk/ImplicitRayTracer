#!/bin/sh

BUILD_DIR=build

if [ ! -d $BUILD_DIR ]; then
    mkdir $BUILD_DIR
fi
 
cd $BUILD_DIR

cmake ..
if [ $? -ne 0 ]; then
    echo "Aborting: cmake failed."
    exit 1
fi

make
if [ $? -ne 0 ]; then
    echo "Aborting: make failed."
    exit 1
fi

./ImplicitRayTracer

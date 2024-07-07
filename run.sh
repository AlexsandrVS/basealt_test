#!/bin/bash

# Check if the build directory exists
if [ ! -d "build" ]; then
  echo "Creating build directory..."
  mkdir build
else
  echo "The build directory already exists."
fi

# Change to the build directory
cd build

# Check if the build_lib directory exists
if [ ! -d "build_lib" ]; then
  echo "Creating build_lib directory..."
  mkdir build_lib
else
  echo "The build_lib directory already exists."
fi

# Check if the build_main directory exists
if [ ! -d "build_main" ]; then
  echo "Creating build_main directory..."
  mkdir build_main
else
  echo "The build_main directory already exists."
fi

# Move shared_lib and main directories into the build directory
cd ..
if [ -d "shared_lib" ]; then
  echo "Moving shared_lib directory to build..."
  mv shared_lib build/
else
  echo "shared_lib directory does not exist. Exiting..."
  exit 1
fi

if [ -d "main" ]; then
  echo "Moving main directory to build..."
  mv main build/
else
  echo "main directory does not exist. Exiting..."
  exit 1
fi

echo "All necessary directories are in place and files have been moved."

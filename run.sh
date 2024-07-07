#!/bin/bash

#./task/download_curl_nlohmann_lib.sh

# Check if the build directory exists
if [ ! -d "build" ]; then
  echo "Creating build directory..."
  mkdir build
else
  echo "The build directory already exists."
fi

# Move shared_lib into the build directory
if [ -d "shared_lib" ]; then
  echo "Moving shared_lib directory to build..."
  mv shared_lib build/
else
  echo "shared_lib directory does not exist. Exiting..."
fi

# Move shared_lib into the build directory
if [ -d "task" ]; then
  echo "Moving task directory to build..."
  mv task build/
else
  echo "task directory does not exist. Exiting..."
fi

# Change to the build directory
cd build

# Verify the presence of shared_lib and main directories in build directory
if [ -d "shared_lib" ]; then
  echo "shared_lib directory is in the build directory."
else
  echo "shared_lib directory was not successfully moved. Exiting..."
  exit 1
fi

# Verify the presence of shared_lib and main directories in build directory
if [ -d "task" ]; then
  echo "task directory is in the build directory."
else
  echo "task directory was not successfully moved. Exiting..."
  exit 1
fi

echo "All necessary directories are in place and files have been moved."

# Check if the build directory exists
if [ ! -d "build_lab" ]; then
  echo "Creating build_lab directory..."
  mkdir build_lab
else
  echo "The build_lab directory already exists."
fi

# Change to build_lib and build the shared_lib project
cd build_lib
echo "Building shared_lib project..."
cmake ../shared_lib
make

# Change back to build directory
cd ..

echo "All necessary directories are in place and projects have been built."

# Перейти в директорию task
cd task

if [ ! -d "build_task" ]; then
  echo "Creating build_task directory..."
  mkdir build_task
else
  echo "The build_task directory already exists."
fi

# Перейти в директорию build_task
cd build_task

if [ ! -d "Answer" ]; then
  echo "Creating Answer directory..."
  mkdir Answer
else
  echo "The Answer directory already exists."
fi

# Запуск cmake для сборки проекта из текущей директории (task)
cmake ..

# Запуск make для сборки проекта
make

echo "Start task"
./task
echo "Finish task"

echo -e "\n**************"
echo "* Completed! *"
echo -e "************** \n" 
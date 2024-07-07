#!/bin/bash

./task/download_curl_nlohmann_lib.sh

# Check if the build directory exists
if [ ! -d "build" ]; then
  echo "Creating build directory..."
  mkdir build
else
  echo "The build directory already exists."
fi

# Move shared_lib and main directories into the build directory
if [ -d "shared_lib" ]; then
  echo "Moving shared_lib directory to build..."
  mv shared_lib build/
else
  echo "shared_lib directory does not exist. Exiting..."
fi

if [ -d "main" ]; then
  echo "Moving main directory to build..."
  mv main build/
else
  echo "main directory does not exist. Exiting..."
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

if [ -d "main" ]; then
  echo "main directory is in the build directory."
else
  echo "main directory was not successfully moved. Exiting..."
  exit 1
fi

# Check if the build_lib directory exists
if [ ! -d "build_lib" ]; then
  echo "Creating build_lib directory..."
  mkdir build_lib
else
  echo "The build_lib directory already exists. Exiting..."
fi

# Check if the build_main directory exists
if [ ! -d "build_main" ]; then
  echo "Creating build_main directory..."
  mkdir build_main
else
  echo "The build_main directory already exists. Exiting..."
fi

echo "All necessary directories are in place and files have been moved."

# Change to build_main and build the main project
cd build_main
echo "Building main project..."
cmake ../main
make

# Change back to build directory
cd ..

# Change to build_lib and build the shared_lib project
cd build_lib
echo "Building shared_lib project..."
cmake ../shared_lib
make

echo "All necessary directories are in place and projects have been built."

cd ..
cd ..

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

# Запуск cmake для сборки проекта из текущей директории (task)
cmake ..

# Запуск make для сборки проекта
make

# Проверка, существует ли исполняемый файл main и его права доступа
if [ -x "../../build/build_main/main" ]; then
    echo "Executing main..."
    ../../build/build_main/main
else
    echo "Error: ../../build/build_main/main does not exist or is not executable"
    exit 1
fi


echo "Start task"
./task
echo "Finish task"

echo -e "\n**************"
echo "* Completed! *"
echo -e "************** \n" 
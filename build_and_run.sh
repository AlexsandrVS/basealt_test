#? chmod +x build_and_run.sh 
#! ./build_and_run.sh

echo "Building shared library..."
cd build_lib
cmake ../shared_lib
make

if [ $? -ne 0 ]; then
    echo "Error: Failed to build shared library."
    exit 1
fi

cd ..

echo "Building main application..."
cd build_main
cmake ../main
make

if [ $? -ne 0 ]; then
    echo "Error: Failed to build main application."
    exit 1
fi

cd ..

echo "Running main application..."
./build_main/main

echo -e "\n**************"
echo      "* Completed! *"
echo      "**************"
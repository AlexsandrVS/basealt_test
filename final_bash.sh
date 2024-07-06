#./build_and_run.sh

cd project_folder
mkdir build
cd build

cmake ..
make

mv build/task ..

./task

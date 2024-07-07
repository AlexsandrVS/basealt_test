./build_and_run.sh

mkdir build
cd build

cmake ..
make

echo -e "\nStart task. parsing json....\n"
./task
echo -e "\nDone!\n"

if [ -f "final_comparison_result.json" ]; then
    mv final_comparison_result.json ../final_comparison_result.json
    echo "File moved successfully."
else
    echo "File final_comparison_result.json does not exist."
fi

echo -e "\nTask successfully!\n"
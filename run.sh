#!/bin/bash

# Функция для запроса подтверждения от пользователя
# Function to ask for user confirmation
confirm() {
    while true; do
        read -p "$1 [y/n]: " yn
        case $yn in
            # Запустить скрипт
            # Run the script
            [Yy]*) ./download_curl_nlohmann_lib.sh; break ;;
            # Пропустить выполнение
            # Skip the execution
            [Nn]*) echo "Пропуск загрузки библиотек. / Skipping library download."; break ;; 
            # Неверный ввод
            # Invalid input
            *) echo "Пожалуйста, ответьте y или n. / Please answer y or n." ;; 
        esac
    done
}

# Запрос подтверждения для запуска скрипта
# Prompt user for confirmation to run the script
confirm "Скачать и установить библиотеки? / Download and install libraries?"

# Переход в каталог task и сборка проекта shared_lib
# Change to task directory and build the shared_lib project
cd task
echo "Сборка проекта shared_lib... / Building shared_lib project..."
cmake ../shared_lib
make

# Создание директории Answer, если она не существует
# Create Answer directory if it doesn't exist
if [ ! -d "Answer" ]; then
  echo "Создание директории Answer... / Creating Answer directory..."
  mkdir Answer
else
  echo "Директория Answer уже существует. / The Answer directory already exists."
fi

# Компиляция файла task.cpp и линковка с библиотекой fetch_and_save и curl
# Compile task.cpp and link with fetch_and_save and curl libraries
g++ -std=c++11 task.cpp -o task -L./ -Wl,-rpath=./ -lfetch_and_save -lcurl

# Запуск программы task
# Run the task program
echo "Запуск task / Start task"
./task
echo "Завершение task / Finish task"

# Завершение скрипта
# Script completion message
echo -e "\n**************"
echo "* Завершено! / Completed! *"
echo -e "************** \n"

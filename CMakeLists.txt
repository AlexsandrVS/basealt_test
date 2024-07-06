cmake_minimum_required(VERSION 3.0)
project(task)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Найдем и подключим библиотеку nlohmann/json
find_package(nlohmann_json 3.11.2 REQUIRED)

# Добавим исполняемый файл и укажем исходный файл main.cpp
add_executable(task task.cpp)

# Связать библиотеку nlohmann/json с нашим проектом
target_link_libraries(task PRIVATE nlohmann_json::nlohmann_json)

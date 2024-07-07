cmake_minimum_required(VERSION 3.0)
project(MainApp)

# Укажите путь к заголовочным файлам вашей разделяемой библиотеки
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../shared_lib)

# Добавьте исполняемый файл main.cpp
add_executable(main main.cpp)

# Убедитесь, что библиотека собрана перед сборкой main
add_library(fetch_and_save SHARED IMPORTED)
set_target_properties(fetch_and_save PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../build_lib/libfetch_and_save.so)

# Укажите библиотеку, которую нужно подключить
target_link_libraries(main PRIVATE fetch_and_save)
target_link_libraries(main PRIVATE curl)

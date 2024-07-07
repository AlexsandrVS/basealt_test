cmake_minimum_required(VERSION 3.0)
project(MainApp)

# Добавьте исполняемый файл main.cpp
add_executable(main main.cpp)

# Укажите путь к заголовочным файлам вашей разделяемой библиотеки
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../shared_lib)

# Убедитесь, что библиотека собрана перед сборкой main
add_library(fetch_and_save SHARED IMPORTED)
set_target_properties(fetch_and_save PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../build_lib/libfetch_and_save.so)

# Укажите библиотеку, которую нужно подключить
target_link_libraries(main PRIVATE fetch_and_save)
target_link_libraries(main PRIVATE curl)

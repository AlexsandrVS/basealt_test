cmake_minimum_required(VERSION 3.0)
project(MainApp)

# Добавьте исполняемый файл main.cpp
add_executable(main main.cpp)

# Укажите путь к заголовочным файлам вашей разделяемой библиотеки
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../shared_lib)

# Укажите путь к библиотеке и имя библиотеки, которую нужно подключить
target_link_libraries(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../build_lib/libfetch_and_save.so)
target_link_libraries(main PRIVATE curl)

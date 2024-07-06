cmake_minimum_required(VERSION 3.0)
project(MainApp)

# Добавьте исполняемый файл main.cpp
add_executable(main main.cpp)

# Укажите путь к заголовочным файлам вашей разделяемой библиотеки
target_include_directories(main PRIVATE ../shared_lib)

# Укажите путь к библиотеке и имя библиотеки, которую нужно подключить
target_link_directories(main PRIVATE ../build_lib)
target_link_libraries(main fetch_and_save curl)
target_link_libraries(main fetch_and_save)

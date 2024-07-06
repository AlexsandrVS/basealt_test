# Укажите минимально необходимую версию CMake
cmake_minimum_required(VERSION 3.0)
project(fetch_and_save)

# Укажите исходные файлы для вашей библиотеки
add_library(fetch_and_save SHARED fetch_and_save.cpp)

# Укажите директорию, в которой находятся заголовочные файлы вашей библиотеки
target_include_directories(fetch_and_save PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Укажите необходимые библиотеки, если они есть
target_link_libraries(fetch_and_save)

# Установка библиотеки в директорию установки
install(TARGETS fetch_and_save LIBRARY DESTINATION lib)
install(FILES fetch_and_save.h DESTINATION include)

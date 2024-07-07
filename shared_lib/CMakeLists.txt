cmake_minimum_required(VERSION 3.5)
project(fetch_and_save_lib)

# Определяем источник файлов
set(SOURCES
    fetch_and_save.cpp
)

# Генерируем динамическую библиотеку
add_library(fetch_and_save SHARED ${SOURCES})

# Добавляем флаг -fPIC для всех целей
set_property(TARGET fetch_and_save PROPERTY POSITION_INDEPENDENT_CODE ON)

cmake_minimum_required(VERSION 3.17)

project(Lab3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SOURCE main.cpp)		# Установка переменной со списком исходников для исполняемого файла

set(LIB pugixml/pugixml.cpp)			# Тоже самое, но для библиотеки

add_library(pugixml STATIC ${LIB})	# Создание статической библиотеки с именем foo

add_executable(main ${SOURCE}) # Создает исполняемый файл с именем main

target_link_libraries(main pugixml)		# Линковка программы с библиотекой
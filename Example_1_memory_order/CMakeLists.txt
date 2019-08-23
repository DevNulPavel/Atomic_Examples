cmake_minimum_required(VERSION 3.14)

set (PROJECT AtomicTest)
project(${PROJECT})

##### Компилятор #####
# Вариант с путями
# execute_process(COMMAND which clang OUTPUT_VARIABLE CLANG_PATH)
# execute_process(COMMAND which clang++ OUTPUT_VARIABLE CLANGXX_PATH)
# if(NOT ("${CLANG_PATH}" STREQUAL ""))
# Вариант поиска программы
find_program(CLANG_FOUND clang)
if(CLANG_FOUND)
	message("Clang will be used for compilation")
	set(CMAKE_C_COMPILER "clang")
	set(CMAKE_CXX_COMPILER "clang++")
	# Скрываем ворнинги на clang + цвета
	# set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -fno-omit-frame-pointer -Qunused-arguments")
	# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -fsanitize=address -fno-omit-frame-pointer -Qunused-arguments")
endif(CLANG_FOUND)

# Стандарт С++
#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_REQUIRED_FLAGS -std=c++11)
#remove_definitions(-std=c++14)
#remove_definitions(-std=gnu++14)
#add_definitions(-std=c++2a -fcoroutines-ts)

# Флаги
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -Wall -Wextra -std=c++11")

# Таргеты
add_executable(Order_1_Relaxed 			"src/Order_1_Relaxed.cpp")
add_executable(Order_2_Relaxed 			"src/Order_2_Relaxed.cpp")
add_executable(Order_3_AcquireRelease 	"src/Order_3_AcquireRelease.cpp")
add_executable(Order_4_AcquireRelease 	"src/Order_4_AcquireRelease.cpp")
add_executable(Order_5_AcquireRelease   "src/Order_5_AcquireRelease.cpp")

# Стандарт С++
#set_property(TARGET ${PROJECT} PROPERTY CXX_STANDARD 11)
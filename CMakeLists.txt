cmake_minimum_required(VERSION 3.10)
project(mprpc)

# set compile_commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set the compile mode
set(CMAKE_BUILD_TYPE "Debug")

# set the path of the executable and library
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# set the path of the header files
include_directories(${PROJECT_SOURCE_DIR}/src/include)
include_directories(${PROJECT_SOURCE_DIR}/src/util)


# set the path of the library
link_directories(${PROJECT_SOURCE_DIR}/lib)

# find the related packages
find_package(Protobuf 3.20.3 REQUIRED) # Protobuf
find_package(Boost REQUIRED) # PropertyTree
find_package(spdlog REQUIRED) # spdlog

if(Boost_FOUND)
    # ignore BOOST deprecated headers
    add_definitions("-DBOOST_ALLOW_DEPRECATED_HEADERS")
    add_definitions("-DBOOST_BIND_GLOBAL_PLACEHOLDERS")
    include_directories(${Boost_INCLUDE_DIRS})
endif()


add_subdirectory(src)
add_subdirectory(examples)
cmake_minimum_required(VERSION 3.10)
project(protobuf_test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Protobuf 3.20.3 REQUIRED)
message(STATUS "Using protobuf ${Protobuf_VERSION}")
message(STATUS "${Protobuf_INCLUDE_DIRS}")
message(STATUS "${PROTOBUF_LIBRARIES}")
message(STATUS "${Protobuf_PROTOC_EXECUTABLE}")

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ./protobuf/test.proto)

message(STATUS "${PROTO_SRCS}")
message(STATUS "${PROTO_HDRS}")

add_library(PROTOBUF ${PROTO_SRCS} ${PROTO_HDRS})

get_filename_component(PROTO_PATH ${PROTO_HDRS} DIRECTORY)
message(STATUS "${PROTO_PATH}")

include_directories(${PROTO_PATH})

aux_source_directory(./src DIR_SRCS)

add_executable(protobuf_test ${DIR_SRCS} ${PROTO_SRCS})

target_include_directories(protobuf_test PRIVATE ${Protobuf_INCLUDE_DIRS})
target_link_libraries(protobuf_test ${PROTOBUF_LIBRARIES} )
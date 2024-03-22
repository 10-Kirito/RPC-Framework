# find protobuf and generate cpp files and hpp files
protobuf_generate_cpp(USER_PROTO_SRCS USER_PROTO_HDRS ./protobuf/user.proto)
message(STATUS "${USER_PROTO_SRCS}")
message(STATUS "${USER_PROTO_HDRS}")
add_library(PROTOBUF ${USER_PROTO_SRCS} ${USER_PROTO_HDRS})

# include the directory of generated files
get_filename_component(USER_PROTO_PATH ${USER_PROTO_HDRS} DIRECTORY)
include_directories(${USER_PROTO_PATH})

add_subdirectory(callee)
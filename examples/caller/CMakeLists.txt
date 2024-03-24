aux_source_directory(. SRC_LIST)
add_executable(consumer ${SRC_LIST})

target_link_libraries(consumer ${PROTOBUF_LIBRARIES} PROTOBUF)
target_link_libraries(consumer mprpc)
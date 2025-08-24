set(SRC_LIST callfriendsservice.cc ../friend.pb.cc)
add_executable(consumer ${SRC_LIST})

target_link_libraries(consumer mprpc protobuf)
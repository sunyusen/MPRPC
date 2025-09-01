# 手动指定文件列表，静态定义
# 需要显式列出文件路径，文件变动时需要手动更新
# 适合文件列表较少且变化不频繁的场景
set(SRC_LIST callfriendsservice.cc ../friend.pb.cc)
add_executable(consumer ${SRC_LIST})

target_link_libraries(consumer mprpc protobuf)
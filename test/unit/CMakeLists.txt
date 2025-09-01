# test/unit/CMakeLists.txt

# 收集本目录下的所有测试源文件
# 基于文件系统实际内容，动态获取文件列表，
# 如果目录中的文件发生变化（如新增或删除文件），需要重新运行 CMake 以更新文件列表
# 适合文件名模式较为固定的场景
file(GLOB UNIT_TEST_SOURCES 
	${CMAKE_CURRENT_SOURCE_DIR}/test_*.cc
)

# 生成一个测试可执行文件
add_executable(unit_tests ${UNIT_TEST_SOURCES})

# # 让测试能找到你的头文件，顶层已经包含了
# target_include_directories(unit_tests PRIVATE
# 	${CMAKE_SOURCE_DIR}/src
# 	${CMAKE_SOURCE_DIR}/include
# )

# 链接依赖：
# - gtest_main: GoogleTest 入口(自带main函数)
# - mprpc: 你的RPC框架库
# - pthread: Linux线程库
target_link_libraries(unit_tests PRIVATE
	gtest_main
	pthread
	mprpc
)

# # 头文件
# target_include_directories(unit_tests PRIVATE
# 	${CMAKE_SOURCE_DIR}/src/include
# )

# 包含GoogleTest的CMake模块
# Google Test提供了一些辅助函数，通过include(GoogleTest)引入
include(GoogleTest)
# GoogleTest提供哦的函数，用于自动发现并注册测试用例
# 扫描目标unit_test中的Google Test测试用例，并将她们注册到CTest测试框架中，
# 这样你就可以使用ctest命令来运行这些测试
gtest_discover_tests(unit_tests)
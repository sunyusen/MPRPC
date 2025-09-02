# test/unit/CMakeLists.txt

# 收集本目录下的所有测试源文件
# 基于文件系统实际内容，动态获取文件列表，
# 如果目录中的文件发生变化（如新增或删除文件），需要重新运行 CMake 以更新文件列表
# 适合文件名模式较为固定的场景
file(GLOB BENCHMARK_SOURCES 
	${CMAKE_CURRENT_SOURCE_DIR}/benchmark_*.cc
)

# 生成一个测试可执行文件
add_executable(benchmark_tests ${BENCHMARK_SOURCES})

# # 让测试能找到你的头文件，顶层已经包含了
# target_include_directories(unit_tests PRIVATE
# 	${CMAKE_SOURCE_DIR}/src
# 	${CMAKE_SOURCE_DIR}/include
# )

# 链接依赖：
# - gtest_main: GoogleTest 入口(自带main函数)
# - mprpc: 你的RPC框架库
# - pthread: Linux线程库
target_link_libraries(benchmark_tests PRIVATE
	benchmark::benchmark
	pthread
	mprpc
)

# enable_testing() 顶层已经做了
add_test(NAME benchmark_tests COMMAND benchmark_tests)
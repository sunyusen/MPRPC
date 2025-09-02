# 设置cmake的最低版本和项目名称
cmake_minimum_required(VERSION 3.0)
project(mprpc)

# 引入FetchContent模块(用于方便地从外部获取依赖项的源代码，并将其集成到当前项目的构建中)
include(FetchContent)

# 声明一个外部依赖（下载gtest源码包）
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

# 为 Google Test（gtest）设置一个选项，强制使用共享的 C 运行时库
# Google Test 默认使用静态的 C 运行时库
# 如果你的项目使用共享的 C 运行时库（/MD 或 /MDd），而 Google Test 使用静态的运行时库，会导致运行时库冲突，进而引发链接错误或运行时问题。
# 设置 gtest_force_shared_crt ON 可以确保 Google Test 和你的项目使用相同的运行时库，避免这些问题
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# 下载并配置 Google Benchmark
FetchContent_Declare(
	googlebenchmark
	GIT_REPOSITORY https://github.com/google/benchmark.git
	GIT_TAG v1.5.4
)

# 用于下载并准备 google Test和goole benchmark
FetchContent_MakeAvailable(googletest googlebenchmark)

# 开启CTest（让ctest能发现并运行测试）
enable_testing()

set(CMAKE_BUILD_TYPE "Debug")  # 设置编译模式为Debug

set(CMAKE_CXX_STANDARD 11)  #强制使用C++11标准
set(CMAKE_CXX_STANDARD_REQUIRED ON)  #必须支持C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -gdwarf-4")

# 设置项目可执行文件输出的路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# 设置项目库文件输出的路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# 设置项目编译头文件搜索路径 -I
include_directories(${PROJECT_SOURCE_DIR}/src/include)
include_directories(${PROJECT_SOURCE_DIR}/example)
include_directories(/usr/local/protobuf/include)

link_directories(${PROJECT_SOURCE_DIR}/lib)
link_directories(/usr/local/protobuf/lib)

# 把test目录加入构建, 必须在include_directorires和link_directories之后,因为test目录需要用到这些设置
add_subdirectory(test)

add_subdirectory(src)
add_subdirectory(example)
#include <benchmark/benchmark.h>
#include <atomic>
#include <mutex>
#include <string>
#include <vector>
#include "mprpcapplication.h"
#include "mprpcchannel.h"
#include "user.pb.h"

// 启动命令


// 一次性初始化 Mprpc（模拟传入: 程序名 -i test.conf）
static void InitMprpcOnce() {
  static std::once_flag flag;
  std::call_once(flag, []{
	// 静音关闭ZK打印
    static std::string arg0 = "benchmark_tests";	//命名是否合理
    static std::string arg1 = "-i";
    static std::string arg2 = "test.conf";   // 按你的实际路径放
    static std::vector<char*> argv{ &arg0[0], &arg1[0], &arg2[0] };
    MprpcApplication::Init((int)argv.size(), argv.data());
  });
}

// 按你的用法：stub + nullptr controller
static bool DoLoginOnce(int id) {
  fixbug::UserServiceRpc_Stub stub(new MprpcChannel());
  fixbug::LoginRequest req;
  req.set_name("user"+std::to_string(id));
  req.set_pwd("123456");
  fixbug::LoginResponse rsp;
  stub.Login(nullptr, &req, &rsp, nullptr);  // 和你的示例一致

  // 以返回码为准做最轻量校验（避免 printf 干扰计时）
  return rsp.result().errcode() == 0;
}

static bool DoRegisterOnce(int id) {
  fixbug::UserServiceRpc_Stub stub(new MprpcChannel());
  fixbug::RegisterRequest req; req.set_id(id); req.set_name("u"+std::to_string(id)); req.set_pwd("123456");
  fixbug::RegisterResponse rsp;
  stub.Register(nullptr, &req, &rsp, nullptr);
  return rsp.result().errcode() == 0;
}

// ---------- 基准用例 ----------

// 单次 Login 延迟
static void BM_RPC_Login_Latency(benchmark::State& state) {
  //定义了一个静态的原子变量gid,初始值为0，用于生成唯一用户ID，保证线程安全
  static std::atomic<int> gid{0};	
  for (auto _ : state) {
    int id = gid.fetch_add(1, std::memory_order_relaxed);
    bool ok = DoLoginOnce(id);
	// 防止编译器优化
    benchmark::DoNotOptimize(ok);	
  }
  // 设置一个自定义计数器
  state.counters["req/iter"] = 1;
}
BENCHMARK(BM_RPC_Login_Latency)
  ->Unit(benchmark::kMicrosecond)
  ->Iterations(1000);

// 吞吐量
/*
吞吐量反映了在单位时间内，RPC 框架可以处理多少请求。
通常来说，我们关心的是 每秒请求数（QPS），它能直接展示框架的 负载能力。
*/
static void BM_RPC_Login_Throughput(benchmark::State& state) {
  static std::atomic<int> gid{0};
  for (auto _ : state) {
    int id = gid.fetch_add(1, std::memory_order_relaxed);
    bool ok = DoLoginOnce(id);
    benchmark::DoNotOptimize(ok);
  }
  state.SetItemsProcessed(state.iterations()); // 让输出显示 Items/s
}
BENCHMARK(BM_RPC_Login_Throughput)
  ->Unit(benchmark::kMicrosecond)
  ->Threads(1)->Threads(2)->Threads(4);


// 并发性
/*
并发性主要反映了 RPC 框架处理多个并发请求的能力。
测试 多线程 环境下的性能，模拟真实的高并发场景。
*/
static void BM_RPC_Login_Concurrency(benchmark::State& state) {
    static std::atomic<int> gid{0};
    for (auto _ : state) {
        int id = gid.fetch_add(1, std::memory_order_relaxed);
        bool ok = DoLoginOnce(id);  // 并发登录
        benchmark::DoNotOptimize(ok);
    }
    state.SetItemsProcessed(state.iterations());  // 每秒处理的请求数
}
BENCHMARK(BM_RPC_Login_Concurrency)
    ->Unit(benchmark::kMicrosecond)
    ->Threads(8);  // 使用多个线程模拟高并发



// 错误率
/*
测试框架在实际使用中，错误处理能力如何。
我们可以模拟一些错误场景（例如，超时、连接失败等），然后记录错误率。
*/
static void BM_RPC_Login_ErrorRate(benchmark::State& state) {
    static std::atomic<int> gid{0};
    int error_count = 0;
    for (auto _ : state) {
        int id = gid.fetch_add(1, std::memory_order_relaxed);
        bool ok = DoLoginOnce(id);
        if (!ok) {
            error_count++;  // 统计错误的请求数
        }
        benchmark::DoNotOptimize(ok);
    }
    state.counters["error_rate"] = error_count / static_cast<double>(state.iterations());
}
BENCHMARK(BM_RPC_Login_ErrorRate)
    ->Unit(benchmark::kMicrosecond)
    ->Iterations(1000);  // 设置循环次数


// 资源占用
/*
CPU 占用率：展示 RPC 框架在处理请求时的 CPU 消耗。
内存使用：展示 RPC 框架在运行时的内存消耗。
*/
//===================================================


// BENCHMARK_MAIN();

int main(int argc, char** argv) {
    InitMprpcOnce();  // 只在程序开始时初始化一次
    ::benchmark::Initialize(&argc, argv); // 初始化基准测试框架
    ::benchmark::RunSpecifiedBenchmarks();  // 运行指定的基准测试
    return 0;
}
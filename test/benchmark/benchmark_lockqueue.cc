// #include <benchmark/benchmark.h>	//引入Google Benchmark头文件,用于定义和运行性能测试
// #include "lockqueue.h"

// // 测试 LockQueue 的 Push 操作性能
// // benchmark::State：Benchmark 框架提供的一个类，用于管理测试的状态和迭代
// static void BM_LockQueue_Push(benchmark::State& state) {
// 	LockQueue<int> q;
// 	for (auto _ : state) {
// 		q.Push(42);
// 	}
// }
// BENCHMARK(BM_LockQueue_Push);	//注册BM_LockQueue_Push测试函数，使其能够被Benchmark框架识别和执行

// static void BM_LockQueue_Pop(benchmark::State& state) {
// 	LockQueue<int> q;
// 	q.Push(42);	 //预先填充一个元素，确保队列不为空

// 	for (auto _ : state) {
// 		int v = q.Pop();	//从队列中弹出一个元素
// 		benchmark::DoNotOptimize(v);
// 		q.Push(42);	//重新插入元素，保持队列大小稳定
// 	}

// 	benchmark::DoNotOptimize(q);	//防止编译器优化掉对队列的操作
// }
// BENCHMARK(BM_LockQueue_Pop);

// // BENCHMARK_MAIN();
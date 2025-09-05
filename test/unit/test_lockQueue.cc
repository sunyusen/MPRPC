// #include <gtest/gtest.h>
// #include <thread>
// #include <set>
// #include "lockqueue.h"

// // 验证 LockQueue 在单线程环境下的基本功能
// TEST(LockQueueTest, SingleThread) {
//     LockQueue<int> q;
//     q.Push(42);
//     int v = q.Pop();  // 接收返回值
//     EXPECT_EQ(v, 42);
// }

// // 验证 LockQueue 在多线程环境下的正确性
// TEST(LockQueueTest, MultiProducerSingleConsumer) {
//     LockQueue<int> q;
//     std::thread p1([&] { for (int i = 0; i < 1000; ++i) q.Push(i); });
//     std::thread p2([&] { for (int i = 1000; i < 2000; ++i) q.Push(i); });
// 	std::thread p3([&] { for (int i = 2000; i < 3000; ++i) q.Push(i); });
// 	std::thread p4([&] { for (int i = 3000; i < 4000; ++i) q.Push(i); });
// 	std::thread p5([&] { for (int i = 4000; i < 5000; ++i) q.Push(i); });

//     std::set<int> got;
//     std::thread c([&] {
//         for (int i = 0; i < 5000; ++i) {
//             int v = q.Pop();
//             got.insert(v);
//         }
//     });

//     p1.join();
//     p2.join();
// 	p3.join();
// 	p4.join();
// 	p5.join();
//     c.join();

//     EXPECT_EQ(got.size(), 5000u);  // 确保消费者消费了所有数据
// }

// // 多消费者测试
// TEST(LockQueueTest, MultiConsumer) {
//     LockQueue<int> q;
//     std::thread p([&] { 
//         for (int i = 0; i < 5000; ++i) q.Push(i); 
//     });

//     std::set<int> got;
//     std::mutex mtx;  // 使用互斥量来确保线程安全

//     // 两个消费者线程
//     std::thread c1([&] { 
//         for (int i = 0; i < 1000; ++i) {  // 每个消费者消费500个，总共消费1000个
//             int v = q.Pop();
//             std::lock_guard<std::mutex> lock(mtx);
//             got.insert(v);
//         }
//     });

//     std::thread c2([&] { 
//         for (int i = 1000; i < 2000; ++i) {  // 每个消费者消费500个，总共消费1000个
//             int v = q.Pop();
//             std::lock_guard<std::mutex> lock(mtx);
//             got.insert(v);
//         }
//     });

// 	std::thread c3([&] { 
//         for (int i = 2000; i < 3000; ++i) {  // 每个消费者消费500个，总共消费1000个
//             int v = q.Pop();
//             std::lock_guard<std::mutex> lock(mtx);
//             got.insert(v);
//         }
//     });

// 	std::thread c4([&] { 
//         for (int i = 3000; i < 4000; ++i) {  // 每个消费者消费500个，总共消费1000个
//             int v = q.Pop();
//             std::lock_guard<std::mutex> lock(mtx);
//             got.insert(v);
//         }
//     });

// 	std::thread c5([&] { 
//         for (int i = 4000; i < 5000; ++i) {  // 每个消费者消费500个，总共消费1000个
//             int v = q.Pop();
//             std::lock_guard<std::mutex> lock(mtx);
//             got.insert(v);
//         }
//     });

//     p.join();
//     c1.join();
//     c2.join();
// 	c3.join();
// 	c4.join();
// 	c5.join();

//     EXPECT_EQ(got.size(), 5000u);  // 确保每个元素都被消费
// }

// // 线程安全测试
// TEST(LockQueueTest, ThreadSafety) {
//     LockQueue<int> q;
//     std::atomic<int> count(0);

//     // 10 个生产者、10 个消费者
//     std::vector<std::thread> producers;
//     std::vector<std::thread> consumers;
    
//     for (int i = 0; i < 100; ++i) {
//         producers.push_back(std::thread([&] {
//             for (int j = 0; j < 1000; ++j) {
//                 q.Push(j);
//             }
//         }));

//         consumers.push_back(std::thread([&] {
//             for (int j = 0; j < 1000; ++j) {
//                 int v = q.Pop();
//                 count.fetch_add(1, std::memory_order_relaxed);
//             }
//         }));
//     }

//     for (auto& t : producers) t.join();
//     for (auto& t : consumers) t.join();

//     EXPECT_EQ(count.load(), 100000);  // 确保总共消费了1000次
// }

// // 性能测试（例如，测试大数据量下的 Push 和 Pop 性能）
// TEST(LockQueueTest, Performance) {
//     LockQueue<int> q;
//     auto start = std::chrono::high_resolution_clock::now();

//     // 多线程测试 100000 次 Push 和 Pop
//     std::thread p1([&] { for (int i = 0; i < 50000; ++i) q.Push(i); });
//     std::thread p2([&] { for (int i = 50000; i < 100000; ++i) q.Push(i); });

//     std::set<int> got;
//     std::thread c([&] {
//         for (int i = 0; i < 100000; ++i) {
//             int v = q.Pop();
//             got.insert(v);
//         }
//     });

//     p1.join();
//     p2.join();
//     c.join();

//     auto end = std::chrono::high_resolution_clock::now();
//     auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//     std::cout << "Time taken for 100000 operations: " << duration << " ms" << std::endl;

//     EXPECT_EQ(got.size(), 100000u);
// }

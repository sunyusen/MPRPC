#pragma once

#include "google/protobuf/service.h"
#include <memory>
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpConnection.h> // 添加缺失的头文件

class RpcProvider {
public:
	// 这里是框架提供给外部使用的，可以发布rpc方法的函数接口
		void NotifyService(google::protobuf::Service *service);

		// 启动rpc服务节点，开始提供rpc远程网络调用服务
		void Run();
	private:
		// 组合了EventLoop
		muduo::net::EventLoop m_eventLoop;

		// 新的socket连接回调
		void OnConnection(const muduo::net::TcpConnectionPtr&); // 使用完整的类型定义
		// 已建立连接用户的读写事件回调
		void OnMessage(const muduo::net::TcpConnectionPtr&, muduo::net::Buffer*, muduo::Timestamp); // 修正类型定义
};
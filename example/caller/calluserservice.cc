#include <iostream>
#include "mprpcapplication.h"
#include "../user.pb.h"
#include "mprpcchannel.h"

int main(int argc, char **argv)
{
	// 整个程序启动以后，想使用mprpc框架来享受rpc服务调用，一定要先调用框架的初始化函数（只初始化一次）
	MprpcApplication::Init(argc, argv);

	// 创建UserServiceRpc_Stub对象，用于调用远程的UserService服务，它是一个代理对象
	// UserServiceRpc_Stub是由protoc编译器根据user.proto文件生成的，这是自己写的方法
	// new MprpcChannel():创建一个MprpcChannel对象，作为RPC通信的信道。
	fixbug::UserServiceRpc_Stub stub(new MprpcChannel());	//MprpcChannel是处理RPC调用的底层逻辑
	stub.Login();	//RpcChannel->RpcChannel::callMethod	集中来做所有rpc方法调用的参数序列化和网络发送

	return 0;
}
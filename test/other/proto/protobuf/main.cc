#include "test.pb.h"
#include <iostream>
#include <string>
using namespace fixbug;

int f1(){
	// 封装了login请求对象的数据
	LoginRequest req;
	req.set_username("zhang_sna");
	req.set_pwd("123456");

	//对象数据序列化 =》 char*
	std::string send_str;
	if(req.SerializeToString(&send_str))
	{
		std::cout << send_str.c_str() << std::endl;
	}

	//从send_st反序列化一个login请求对象
	LoginRequest reqB;
	if(reqB.ParseFromString(send_str)){
		std::cout << "username: " << reqB.username() << std::endl;
		std::cout << "pwd: " << reqB.pwd() << std::endl;
	}
	else
	{
		std::cerr << "Failed to parse LoginRequest." << std::endl;
		return -1;
	}
	return 0;
}
int main()
{
	// 列表使用方式
	// LoginResponse rsp;
	// ResultCode *rc = rsp.mutable_result();
	// rc->set_errcode(1);
	// rc->set_errmsg("登录处理失败了");

	GetFriendListResponse req;
	ResultCode *rc = req.mutable_result();
	rc->set_errcode(0);

	User *user1 = req.add_friend_list();
	user1->set_name("zhang_san");
	user1->set_age(20);
	user1->set_sex(User::MAN);

	User *user2 = req.add_friend_list();
	user2->set_name("li_shi");
	user2->set_age(22);
	user2->set_sex(User::MAN);

	User *user3 = req.add_friend_list();
	user3->set_name("wan_wu");
	user3->set_age(18);
	user3->set_sex(User::WOMAN);

	std::cout << req.friend_list_size() << std::endl;

	return 0;
}



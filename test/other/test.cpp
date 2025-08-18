#include<iostream>
#include<string.h>
using namespace std;



int main(){
	char arr[] = {4, 3, 9, 9, 2, 0, 1, 5};
	char *str = arr;

	cout << sizeof(arr) << endl; // 输出数组的大小
	cout << sizeof(str) << endl; // 输出指针的大小
	cout << strlen(str) << endl; // 输出字符串的长度	
	return 0;
}
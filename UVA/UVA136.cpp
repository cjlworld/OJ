#include<cstdio>
#include<set>
#include<iostream>
#define LL long long
using namespace std;
//题意描述：丑数是一些因子只有2,3,5的数。
//数列1,2,3,4,5,6,8,9,10,12,15……写出了从小到大的前11个丑数，
//1属于丑数。现在请你编写程序，找出第1500个丑数是什么。
//没有输入
//输出：The 1500'th ugly number is <...>.（<...>为你找到的第1500个丑数） 
//注意：<...>是你找到的数，输出中没有尖括号； 2、输出完应换行。 
const int N=1500;
set<LL> S;
int main()
{
//	freopen("1.in","r",stdin);
	int cnt=0;
	int i,j;
	LL x,y,z;
	S.insert(1); 
	for(i=1;i<=1500;i++) {
		x=*S.begin();
		S.erase(S.begin());
		S.insert(2*x);
		S.insert(3*x);
		S.insert(5*x);
	}
	cout<<"The 1500'th ugly number is "<<x<<"."<<endl; 
	return 0;
}


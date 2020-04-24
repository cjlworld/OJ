#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
int main()
{
//	freopen("1.in","r",stdin);
	char c;
	int cnt=0;
	for(int i=1;i<=8;i++) {
		cin>>c;
		if(c=='1') cnt++;
	}
	cout<<cnt;
	return 0;
}


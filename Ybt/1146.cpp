#include<cstdio>
#include<cstring>
#include<iostream>
#define LL long long
using namespace std;
const int N=256;
char a[N];
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	scanf("%s",a+1);
	int len=strlen(a+1);
	for(i=1;i<=len/2;i++) {
		if(a[i]!=a[len-i+1]) {
			cout<<"no"<<endl;
			return 0;
		}
	}
	cout<<"yes"<<endl;
	return 0;
}


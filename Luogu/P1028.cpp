#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
//�����κδ���;
//��������߼���һ����Ȼ��,������Ȼ�����ܳ���ԭ����һ��;
//��������,�������˹�����д���,ֱ�������ټ���Ȼ��Ϊֹ.
const int N=1000+5;
unsigned long long f[N];
int n;
int main()
{
	scanf("%d",&n);
	int i,j;
	f[0]=1;
	for(i=1;i<=n;i++) {
		if(i&1) f[i]=f[i-1];
		else f[i]=f[i>>1]+f[i-1];
	}
	cout<<f[n];
	return 0;
}


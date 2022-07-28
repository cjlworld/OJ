#include<set>
#include<map>
#include<queue>
#include<stack>
#include<ctime>
#include<cmath>
#include<bitset>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=256,INF=1e9+5; 
int f[N][N]; // f[i][j] ��ʾ���䳤��Ϊi,������j������������������Ҫ���Ӽ���������

int Dp(int x,int k) // ����x��,��֤��x+1��һ����,��k������ 
{
	if(x==0) return 0; // x==0,��ô������,x==1 ��Ҫ��һ��, ������x���飬����x+1���顣 
	else if(k==1) return x;
	int &v=f[x][k];
	if(v!=-1) return v;
	v=INF;	
	for(int i=1;i<=x;i++) // ö���ӵ�¥�� 
		v=min(v,max(Dp(i-1,k-1),Dp(x-(i+1)+1,k))+1); // ˤ���ˣ�ûˤ�顣 
	return v; 
}

int main()
{
//	freopen("1.in","r",stdin);
	memset(f,-1,sizeof f);
	int x,k;
	while(cin>>x>>k) 
		cout<<Dp(x,k)<<endl;
	return 0;
}

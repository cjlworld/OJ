#include<set>
#include<map>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
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

// ��չ�򲢲鼯 
// �����߼���ϵ
// ���鼯���ÿ��Ԫ�ض���һ������
// Ԫ��A,B��ͬһ�����鼯�� <--> ���� A,B �����໥�Ƶ� (��Ҫ��ϵ)  
// (��Ҫ��ϵ����Գ��Ժʹ�����)
const int M=2e4+5;
struct Require
{
	int l,r;
	int k; // k=0, even ż���� ; k=1 , odd ������ 
}q[M];

vector<int> nums;
int getid(int x)
{
	return (int)(lower_bound(nums.begin(),nums.end(),x)-nums.begin())+1;
}

int n,m;
int get(int x,int k)
{
	return k*2*m+x;
}
int par[2*M];
int Find(int x)
{
	if(par[x]!=x) return par[x]=Find(par[x]);
	else return x;
}
void Join(int x,int y)
{
	x=Find(x),y=Find(y);
	par[x]=y;
}


int main()
{
//	freopen("1.in","r",stdin);
	int i,x,y;
	char opt[20];
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++) {
		scanf("%d%d%s",&q[i].l,&q[i].r,opt);
		if(!strcmp(opt,"even")) q[i].k=0;
		else q[i].k=1;
		nums.push_back(q[i].l-1),nums.push_back(q[i].r);
	}
	
	sort(nums.begin(),nums.end());
	nums.erase(unique(nums.begin(),nums.end()),nums.end());
	
	for(i=1;i<=4*m;i++) par[i]=i;
	
	for(i=1;i<=m;i++) {
		x=getid(q[i].l-1);
		y=getid(q[i].r);	
		// odd ---> S[r]-s[l-1] is odd
		// ---> S[r] is even and S[l-1] is odd
		// ---> or S[r] is odd and S[l-1] is even 
		if(q[i].k) { 
			if(Find(get(x,1))==Find(get(y,1))||Find(get(x,0))==Find(get(y,0))) {
				// �� x is odd �Ѿ����Ƴ� y is odd ��  x is even <--> y is even  
				// �������� 
				// ��Ϊ�ӱ߶��ǳɶԵģ����Բ��ÿ���̫��
				 break;
			}
			// ����
			Join(get(x,0),get(y,1));
			Join(get(x,1),get(y,0));
		}
		else {
			if(Find(get(x,0))==Find(get(y,1))||Find(get(x,1))==Find(get(y,0))) 
				break;
			Join(get(x,0),get(y,0));
			Join(get(x,1),get(y,1));
		}
	}
	printf("%d\n",i-1);
	return 0;
}


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

// 扩展域并查集 
// 处理逻辑关系
// 并查集里的每个元素都是一个命题
// 元素A,B在同一个并查集内 <--> 命题 A,B 可以相互推导 (充要关系)  
// (充要关系满足对称性和传递性)
const int M=2e4+5;
struct Require
{
	int l,r;
	int k; // k=0, even 偶数个 ; k=1 , odd 奇数个 
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
				// 若 x is odd 已经能推出 y is odd 或  x is even <--> y is even  
				// 不不符了 
				// 因为加边都是成对的，所以不用考虑太多
				 break;
			}
			// 符合
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


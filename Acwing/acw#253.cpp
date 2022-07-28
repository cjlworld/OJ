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

const int N=1e5+5;

int n,k;
struct Query
{
	int opt,x;
}q[N];

vector<int> nums;

struct Bits
{
	int c[N];
	inline int lowbit(int x) { return x&(-x); }
	void Update(int x,int y)
	{
		for(;x<=n;x+=lowbit(x)) 
			c[x]+=y;
	}
	int Sum(int x)
	{
		int res=0;
		for(;x>=1;x-=lowbit(x)) 
			res+=c[x];
		return res;	
	}
	int Fdkth(int x)
	{
		int i,pos=0;
		for(i=k;i>=0;i--) 
			if(pos+(1<<i)<=n&&x>c[pos+(1<<i)])
				pos+=(1<<i),x-=c[pos];
		return pos+1;
	}
}C;
int main()
{
	int i,opt,x;
	scanf("%d",&n);
	for(i=1;i<=n;i++) {
		scanf("%d%d",&q[i].opt,&q[i].x);
		if(q[i].opt!=4) nums.push_back(q[i].x); 
	}
	sort(nums.begin(),nums.end());
	nums.erase(unique(nums.begin(),nums.end()),nums.end());
	k=log2(nums.size());
	for(i=1;i<=n;i++) {
		opt=q[i].opt,x=q[i].x;
		if(opt!=4) x=(int)(upper_bound(nums.begin(),nums.end(),x)-nums.begin())+1; 
		// 下标从2开始 
		if(opt==1) C.Update(x,1);
		else if(opt==2) C.Update(x,-1);
		else if(opt==3) printf("%d\n",C.Sum(x-1)+1);
		else if(opt==4) printf("%d\n",nums[C.Fdkth(x)-2]);
		else if(opt==5) printf("%d\n",nums[C.Fdkth(C.Sum(x-1))-2]);
		else if(opt==6) printf("%d\n",nums[C.Fdkth(C.Sum(x)+1)-2]);
	}
	return 0;
}


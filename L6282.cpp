#include<cmath>
#include<cstdio>
#include<vector>
#include<iostream>
#define LL long long
using namespace std;
const int N=1e5+5;
const int SQ=1000;
int n;
int a[N];
vector<int> V[SQ];
struct block
{
	int siz,k;
	inline void Build()
	{
		int i,j;
		siz=sqrt(n);
		k=n/siz;
		if(n%siz>0) k++;
		for(i=1;i<=k;i++) 
			V[i].clear();
		for(i=1;i<=k;i++) 
			for(j=(i-1)*siz+1;j<=min(i*siz,n);j++) 
				V[i].push_back(a[j]);
		return;
	}
	inline void insert(int x,int y) //insert num 'y' in front of x
	{
		int i,j;
		int tmp=0,pos=0;
		for(i=1;i<=k;i++) {
			if(tmp+V[i].size()>=x) 
				break;
			tmp+=V[i].size(); 
		} 
		if(i>k) i=k;
		pos=x-tmp;
		V[i].insert(V[i].begin()+pos-1,y); //https://www.cnblogs.com/cappuccino/p/3794698.html
		return;
	} 
	inline int want(int x)
	{
		int i,j;
		int tmp=0,pos=0;
		for(i=1;i<=k;i++) {
			if(tmp+V[i].size()>=x) 
				break;
			tmp+=V[i].size(); 
		} 
		pos=x-tmp;
		return V[i][pos-1];
	}
}B;
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int opt,x,y,z;
	scanf("%d",&n);
	for(i=1;i<=n;i++) 
		scanf("%d",&a[i]);
	B.Build();
	for(i=1;i<=n;i++) {
		scanf("%d%d%d%d",&opt,&x,&y,&z);
		if(opt==0) B.insert(x,y);
		else printf("%d\n",B.want(y));
	}
	return 0;
}


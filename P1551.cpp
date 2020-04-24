#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
const int N=5000+5;
int n,m,p; //<=5000+5;
int par[N];
int Find(int x)
{
	if(x!=par[x]) return par[x]=Find(par[x]);
	return x;
}
inline void Join(int x,int y)
{
	int x_=Find(x);
	int y_=Find(y);
	if(x_==y_) return;
	par[x_]=y_;
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	scanf("%d%d%d",&n,&m,&p);
	for(i=1;i<=n;i++) 
		par[i]=i;
	for(i=1;i<=m;i++) {
		scanf("%d%d",&x,&y);
		Join(x,y);
	}
	for(i=1;i<=p;i++) {
		scanf("%d%d",&x,&y);
		if(Find(x)==Find(y)) puts("Yes");
		else puts("No");
	}
	return 0;
}


#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
const int N=2000+5;
int n,m;
int par[N];
int Find(int x)
{
	if(x!=par[x]) return par[x]=Find(par[x]);
	return x;
}
void Join(int x,int y)
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
	char opt;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n*2;i++) 
		par[i]=i;
	while(m--) {
		cin>>opt;
		scanf("%d%d",&x,&y);
		if(opt=='F') Join(x,y);
		else {
			Join(x+n,y);
			Join(y+n,x);
		}
	}
	int ans=0;
	for(i=1;i<=n;i++) 
		if(i==Find(i))
			ans++;
	cout<<ans;
 	return 0;
}


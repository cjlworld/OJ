#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define data d_d
struct data
{
	int x;
	int y;
	int w;
}a[1024];
int par[1024];
data b[1024];
int n,e;//n(城市数) e(边数)
bool cmp(data a,data b)
{
	return a.w<b.w;
}
int f(int x)
{
	return (par[x]==x) ? x : par[x]=f(par[x]);
}
void kru()
{
	int head=0,v=0;
	int x_,y_;
	sort(a+1,a+e+1,cmp);
	for(int i=1;i<=e;i++) {
		x_=f(a[i].x);
		y_=f(a[i].y);
		if(x_==y_) {
			v+=a[i].w;
			continue;
		}
		par[x_]=y_;
//		head++;
//		b[head].x=a[i].x;
//		b[head].y=a[i].y;
//		if(head==n-1) return;
	}
	cout<<v;
}

int main()
{
//	freopen("1.txt","r",stdin);
	cin>>n>>e;
	int i,j;
	for(i=1;i<=e;i++) scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].w); 
	for(i=1;i<=n;i++) par[i]=i;
	kru();
//	for(i=1;i<=n-1;i++) cout<<b[i].x<<" "<<b[i].y<<endl;
	
	return 0;
}

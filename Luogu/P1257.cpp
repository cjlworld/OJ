#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iomanip>
#define LL long long
using namespace std;
const int N=10000+5;
const double INF=(1e9+5)/1.0;
int n;
struct node
{
	double x,y; //<=1e4
}a[N];
inline bool cmp_x(const node &a,const node &b)
{
	return a.x<b.x;
}
inline bool cmp_y(const int &x,const int &y)
{
	return a[x].y>a[y].y;
}
double dist(int x,int y)
{
	return (double)sqrt((a[x].x-a[y].x)*(a[x].x-a[y].x)+(a[x].y-a[y].y)*(a[x].y-a[y].y));
}
int tmp[N];
double Merge(int l,int r)
{
	if(l==r) return INF;
	if(l+1==r) return dist(l,r);
	int mid=(l+r)>>1;
	double mdis=INF;
	mdis=min(mdis,Merge(l,mid));
	mdis=min(mdis,Merge(mid+1,r));
	memset(tmp,0,sizeof tmp);
	int cnt=0;
	for(int i=l;i<=r;i++) {
		if(a[i].x>a[mid].x-mdis&&a[i].x<a[mid].x+mdis) 
			tmp[++cnt]=i;
	}
	sort(tmp+1,tmp+cnt+1,cmp_y);
	for(int i=1;i<=cnt;i++) {
		for(int j=i+1;j<=cnt;j++) {
			if(fabs(a[tmp[j]].y-a[tmp[i]].y)>mdis) 
				break;
			mdis=min(mdis,dist(tmp[i],tmp[j]));
		}
	}
	return mdis;
}
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d",&n);
	int i,j;
	for(i=1;i<=n;i++)
		scanf("%lf%lf",&a[i].x,&a[i].y);
	sort(a+1,a+n+1,cmp_x);
	cout<<fixed<<setprecision(4)<<Merge(1,n);
	return 0;
}


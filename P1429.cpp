#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iomanip>
#define LL long long
namespace FastIO
{
template<class T>
inline void read(T &x)
{
	x=0;
	char c=getchar();
	bool sign=false;
	while(c<'0'||c>'9') {
		if(c=='-') sign=true;
		c=getchar();
	}
	while(c>='0'&&c<='9') {
		x=(x<<1)+(x<<3)+(c-'0');
		c=getchar();
	}
	if(sign) x=~x+1;
	return;
}
template<class T>
void print(T x)
{
	if(x<0) x=~x+1,putchar('-');
	if(x>9) print(x/10);
	putchar(x%10+48);
	return;
}
template<class T>
inline T max(const T &x,const T &y)
{
	if(x>y) return x;
	else return y;
}
template<class T>
inline T min(const T &x,const T &y)
{
	if(x>y) return y;
	else return x;
}
template<class T>
inline void swap(T &x,T &y)
{
	T temp=x; x=y; y=temp;
	return;
}
template<class T>
inline T abs(const T &x)
{
	if(x>0) return x;
	else return (-x);
}
LL pow(LL x,int k)
{
	LL res=1;
	while(k) {
		if(k&1) res=res*x;
		x=x*x; k>>=1;
	}
	return res;
}
LL quickpow(LL x,LL k,LL mod)
{
	LL res=1;
	while(k) {
		if(k&1) res=res*x%mod;
		x=x*x%mod; k>>=1;
	}
	return res%mod;
}
}
#define rint register int 
#define read(x) FastIO::read(x) 
#define print(x) FastIO::print(x)
#define min(x,y) FastIO::min(x,y) 
#define max(x,y) FastIO::max(x,y)
#define swap(x,y) FastIO::swap(x,y)
#define abs(x) FastIO::abs(x)
#define pow(x,y) FastIO::pow(x,y)
#define quickpow(x,y,z) FastIO::quickpow(x,y,z)
//=================================
using namespace std;
const int N=200000+5;
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
	int cnt=0;
	for(int i=l;i<=r;i++) {
		if(a[i].x>a[mid].x-mdis&&a[i].x<a[mid].x+mdis) 
			tmp[++cnt]=i;
	}
	sort(tmp+1,tmp+cnt+1,cmp_y);
	for(int i=1;i<=cnt;i++) {
		for(int j=i+1;j<=cnt;j++) {
			if(abs(a[tmp[j]].y-a[tmp[i]].y)>mdis) 
				break;
			mdis=min(mdis,dist(tmp[i],tmp[j]));
		}
	}
	return mdis;
}
int main()
{
	scanf("%d",&n);
	int i,j;
	for(i=1;i<=n;i++)
		scanf("%lf%lf",&a[i].x,&a[i].y);
	sort(a+1,a+n+1,cmp_x);
	cout<<fixed<<setprecision(4)<<Merge(1,n);
	return 0;
}
//memset 放递归和循环里反复调用，非常容易超时！！！ 

#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
template<class T>
inline T mac(const T &x,const T &y) 
{
	if(x>y) return x;
	return y;
}
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
//============================================
const int N=2e5+5;
const int INF=(-1u)>>1;
const int LogN=21;
int cat[LogN][N];
int Log[2*N];
int a[N];
int pos[2*N];
int n,m;
int len;
void Build(int now,int l,int r,int dep)
{
	if(l==r) {
		pos[l]=now;
		return;
	}
	int mid=(l+r)>>1;
	int i,j;
	int x=-INF,y,z;
	for(i=mid;i>=l;i--) {
		x=mac(x,a[i]);
		cat[dep][i]=x;
	}
	x=-INF;
	for(i=mid+1;i<=r;i++) {
		x=mac(x,a[i]);
		cat[dep][i]=x;
	}	
	Build(now<<1,l,mid,dep+1);
	Build(now<<1|1,mid+1,r,dep+1);
	return;
}
inline int query(int x,int y)
{
	if(x==y) return a[x];
	int z=Log[pos[x]]-Log[pos[x]^pos[y]]; //--??
	int tmp=mac(cat[z][x],cat[z][y]);
	return tmp;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	read(n); read(m);
	for(i=1;i<=n;i++) 
		read(a[i]);
	len=1;
	while(len<n) len=len<<1;
	Log[0]=-1;
	for(i=1;i<=(len<<1|1);i++)
		Log[i]=Log[i>>1]+1;

	Build(1,1,len,1);
	for(i=1;i<=m;i++) {
		read(x); read(y);
		printf("%d\n",query(x,y));
	}
	return 0;
}


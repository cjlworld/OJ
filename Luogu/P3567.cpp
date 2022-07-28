#include<vector>
#include<cstdio>
#include<iostream>
#include<algorithm>
#define LL long long
#define rint register int
using namespace std;
namespace FastIO
{
char c;
bool sign;
template<class T>
inline void read(T &x)
{
	x=0;
	sign=false;
	for(c=getchar();c<'0'||c>'9';c=getchar()) 
		if(c=='-') 
			sign=true;
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+(c&15);
	if(sign) x=~x+1;
 	return;
}
template<class T>
void print(T x)
{
	if(x<0) putchar('-'),x=~x+1;
	if(x>9) print(x/10);
	putchar(x%10+'0');
	return;
}
}
using FastIO::read;
using FastIO::print;
//================================================
const int N=5e5+5;
struct Node
{
	int lc,rc;
	int sum;
}hjt[32*N];
int cnt=0;
int root[N];
void insert(int &now,const int &pre,const int &key,const int &l,const int &r)
{
	hjt[now=++cnt]=hjt[pre];
	hjt[now].sum++;
	if(l==r) return;
	int mid=(l+r)>>1;
	if(key<=mid) insert(hjt[now].lc,hjt[pre].lc,key,l,mid);
	else insert(hjt[now].rc,hjt[pre].rc,key,mid+1,r);
	return;
}
int query(const int &L,const int &R,const int &l,const int &r,const int &lit) //(L,R]
{
	if(l==r) return l;
	int mid=(l+r)>>1;
	if(hjt[hjt[R].lc].sum-hjt[hjt[L].lc].sum>lit) 
		return query(hjt[L].lc,hjt[R].lc,l,mid,lit);
	else if(hjt[hjt[R].rc].sum-hjt[hjt[L].rc].sum>lit)
		return query(hjt[L].rc,hjt[R].rc,mid+1,r,lit);
	else return 0;
}
int a[N];
int n,m;
vector<int> v;
int main()
{
//	freopen("1.in","r",stdin);
	rint i;
	int x,y,z;
	read(n); read(m);
	for(i=1;i<=n;i++) {
		read(a[i]);
		v.push_back(a[i]);
	}
	sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
	for(i=1;i<=n;i++) 
		a[i]=(int)(lower_bound(v.begin(),v.end(),a[i])-v.begin())+1;
	for(i=1;i<=n;i++) 
		insert(root[i],root[i-1],a[i],1,v.size());
	while(m--) {
		read(x); read(y);
		z=query(root[x-1],root[y],1,v.size(),(y-x+1)>>1);
		if(z==0) puts("0");
		else print(v[z-1]),putchar('\n');
	}
	return 0;
}


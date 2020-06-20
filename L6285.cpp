#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define LL long long
#define rint register int 
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
using namespace std;
const int N=100000+5;
const int SQ=1000+5;
int n;
int a[N];
struct block
{
	int siz,k;
	int f[SQ][SQ];
	int L[SQ],R[SQ],F[N];
	int cnt[N];
	vector<int> c[N];
	inline void Build()
	{
		rint i,j;
		siz=pow(n,0.40);
		k=n/siz+(n%siz>0);
		for(i=1;i<=k;i++) {
			L[i]=R[i-1]+1;
			R[i]=i*siz;
		}
		for(i=1;i<=k;i++) 
			for(j=L[i];j<=R[i];j++) 
				F[j]=i;
		for(i=1;i<=n;i++) 
			c[a[i]].push_back(i);
		int max_cnt;
		for(i=1;i<=k;i++) {
			memset(cnt,0,sizeof cnt);
			max_cnt=0;
			for(j=L[i];j<=n;j++) {
				cnt[a[j]]++;
				if(f[i][F[j]]==0) f[i][F[j]]=f[i][F[j]-1]; 
				if(cnt[a[j]]>max_cnt||(cnt[a[j]]==max_cnt&&a[j]<f[i][F[j]])) {
					max_cnt=cnt[a[j]];
					f[i][F[j]]=a[j];
				}
			}
		}			
		return;
	}
	inline int count(const int &key,const int &x,const int &y)
	{
		return (int)(upper_bound(c[key].begin(),c[key].end(),y)-lower_bound(c[key].begin(),c[key].end(),x));
	}
	inline int query(const int &x,const int &y)
	{
		rint i;
		rint res=0,mx=0,tmp=0;
		if(F[x]==F[y]) {
			for(i=x;i<=y;i++) {
				tmp=count(a[i],x,y);
				if(tmp>mx||(tmp==mx&&a[i]<res)) {
					mx=tmp;
					res=a[i];
				} 
			}
			return res;
		}
		res=f[F[x]+1][F[y]-1];
		mx=count(res,x,y);
		for(i=x;i<=R[F[x]];i++) {
			tmp=count(a[i],x,y);
			if(tmp>mx||(tmp==mx&&a[i]<res)) {
				mx=tmp;
				res=a[i];
			} 
		}
		for(i=L[F[y]];i<=y;i++) {
			tmp=count(a[i],x,y);
			if(tmp>mx||(tmp==mx&&a[i]<res)) {
				mx=tmp;
				res=a[i];
			}
		}
		return res;
	}
}B;
vector<int> v;
int main()
{
//	freopen("1.in","r",stdin);
	rint i;
	int x,y;
	read(n);
	for(i=1;i<=n;i++) {
		read(a[i]);
		v.push_back(a[i]);
	}
	sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
	for(i=1;i<=n;i++) 
		a[i]=(int)(lower_bound(v.begin(),v.end(),a[i])-v.begin())+1;
	B.Build();
	for(i=1;i<=n;i++) {
		read(x); read(y);
		print(v[B.query(x,y)-1]); putchar('\n');
	}
	return 0;
}


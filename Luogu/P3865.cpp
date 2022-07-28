#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
const int N=1<<21;
template<class T>
inline void read(T &x)
{
	x=0;
	bool flag=false;
	char inc='\0';
	while(inc=getchar()) {
		if(inc=='-') flag=true;
		if(inc>='0'&&inc<='9') break;
	}
	while(inc>='0'&&inc<='9') {
		x=(x<<1)+(x<<3)+(inc-'0');
		inc=getchar();
	}
	if(flag) x=(~x)+1;
	return;
}
int Log[N];
int a[N];
int pos[N];
int n,m;
int len;
int cat[21][N];
void Build(int now,int d,int l,int r)
{
	if(l==r) { pos[l]=now; return; } 
	int mid=(l+r)>>1;
	int i,j;
	cat[d][mid]=a[mid];
	for(i=mid-1;i>=l;i--) 
		cat[d][i]=max(cat[d][i+1],a[i]);
	for(i=mid+1;i<=r;i++) 
		cat[d][i]=max(cat[d][i-1],a[i]);
	Build(now<<1,d+1,l,mid);
	Build(now<<1|1,d+1,mid+1,r);
	return;
}
inline int query(int l,int r)
{
	if(l==r) return a[l];
	int d=Log[pos[l]]-Log[pos[l]^pos[r]];
	return max(cat[d][l],cat[d][r]);
}
int main()
{
//	freopen("1.in","r",stdin);
	read(n);
	read(m);
	int l,r;
	int i,j;
	for(i=1;i<=n;i++) 
		read(a[i]);
	len=1;
	while(len<n) len<<=1;
	Log[0]=-1;
	for(i=1;i<=len<<1;i++) 
		Log[i]=Log[i>>1]+1;
	Build(1,1,1,len);
	while(m--) {
		read(l);
		read(r);
		printf("%d\n",query(l,r));
	}
	return 0;	
}

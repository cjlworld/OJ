#include<cstdio>
#include<iostream>
#define LL long long
#define rint register int
using namespace std;
const int N=1500+5;
const LL INF=1e14+5;
int one[N];
int ver[2*N],Next[2*N];
int tot=0;
inline void AddEdge(const int  &a,const int &b)
{
	tot++;
	Next[tot]=one[a];
	one[a]=tot;
	ver[tot]=b;
	return;
}
//==================================
int n;
LL a[N];
LL f[N][3]; 
/*
f[x][0] not put or see
f[x][1] not put but can be seen
f[x][2] put and see 
but the child trees of it must be able to be seen
*/
void Dp(int now,const int &fa)
{
	rint i,v;
	bool flag=false;
	LL tmp=INF;
	for(i=one[now];i>0;i=Next[i]) 
		if(ver[i]!=fa) 
			Dp(ver[i],now);
	for(i=one[now];i>0;i=Next[i]) {
		if(ver[i]==fa) 
			continue;
		v=ver[i];
		f[now][0]+=f[v][1];
		
		if(f[v][2]<=f[v][1]) {
			f[now][1]+=f[v][2];
			flag=true;
		}
		else f[now][1]+=f[v][1],tmp=min(tmp,f[v][2]-f[v][1]);
		
		f[now][2]+=min(min(f[v][0],f[v][1]),f[v][2]);
	}
	if(!flag) 
		f[now][1]+=tmp;
	f[now][2]+=a[now];
	if(f[now][1]<0||f[now][2]<0) 
		cerr<<"wrong"<<now<<endl;
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	rint i,j;
	int x,y,z;
	scanf("%d",&n);
	for(i=1;i<=n;i++) {
		scanf("%d",&x);
		scanf("%lld",&a[x]);
		scanf("%d",&z);
		for(j=1;j<=z;j++) {
			scanf("%d",&y);
			AddEdge(x,y);
			AddEdge(y,x);
		}
	}
	Dp(1,0); 
	printf("%lld\n",min(f[1][1],f[1][2]));
	return 0;
}


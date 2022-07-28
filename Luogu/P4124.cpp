#include<cstdio>
#include<cstring>
#include<iostream>
#define LL long long
#define rint register int
using namespace std;
const int N=13;
int dim[N];
LL f[N][N][2][2][N][2]; // f[now][sta][if exist "8"][if exist "4"][sta num times][haveit]
LL dfs(int now,int sta,int ex8,int ex4,int times,bool haveit,bool lit)
{
	if(now==0) return (haveit&&sta==0) ? 1 : 0;
	if(f[now][sta][ex8][ex4][times][haveit]!=-1&&(!lit)) 
		return f[now][sta][ex8][ex4][times][haveit];
	int maxn=(lit) ? dim[now-1] : 9;
	LL res=0;
	for(rint i=0;i<=maxn;i++) {
		if(ex8&&i==4) continue;
		if(ex4&&i==8) continue;
		if(i==sta) {
			if(times==2&&now>1) 
				res+=dfs(now-1,i,ex8|(i==8),ex4|(i==4),3,true,lit&&(i==maxn));
			else res+=dfs(now-1,i,ex8|(i==8),ex4|(i==4),times+1,haveit,lit&&(i==maxn));
		}
		else res+=dfs(now-1,i,ex8|(i==8),ex4|(i==4),1,haveit,lit&&(i==maxn));
	}
	if(!lit) f[now][sta][ex8][ex4][times][haveit]=res;
	return res;
}
LL prefix(LL x)
{
	memset(dim,0,sizeof dim);
	rint top=0;
	while(x>0) {
		dim[++top]=x%10;
		x/=10;
	}
	LL res=0;
	for(rint i=1;i<=dim[top];i++) 
		res+=dfs(top,i,(i==8),(i==4),1,false,(i==dim[top]));
	return res;
}
int main()
{
//	freopen("1.in","r",stdin);
	LL a,b;
	memset(f,-1,sizeof f);
	scanf("%lld%lld",&a,&b);
	LL ans=prefix(b);
	if(a>10000000000ll) //注意特判掉这种情况。 
		ans-=prefix(a-1);
	cout<<ans;
	return 0;
}


#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")

#include<bits/stdc++.h>

using namespace std;

const int INF=0x3f3f3f3f;
const int N=1000+5;

int n,p,m;
int a[N],f[N][N];

int main()
{
	scanf("%d%d%d",&n,&p,&m);
	for(int i=1;i<=n;i++) 
		scanf("%d",&a[i]);
	
	memset(f,0x3f,sizeof(f));
	for(int i=1;i<=p;i++) f[i][i]=0; 
	for(int i=1,x,y,z;i<=m;i++) {
		scanf("%d%d%d",&x,&y,&z);
		f[x][y]=min(f[x][y],z);
		f[y][x]=min(f[y][x],z);
	}
	
	for(int i,j,k=1;k<=p;k++) 
		for(i=1;i<=p;i++)
			for(j=1;j<=p;j++) 
				f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
	
	int ans=INF;
	for(int i=1;i<=p;i++) {
		int tmp=0;
		for(int j=1;j<=n;j++) {
			tmp+=f[i][a[j]];
			if(tmp>ans) break;
		}
		ans=min(ans,tmp);
	}
	printf("%d\n",ans); 
	return 0;
}


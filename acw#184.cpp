// TLE
#include<set>
#include<map>
#include<queue>
#include<stack>
#include<ctime>
#include<cmath>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=26+6;
int a[4][N]; 
char c[N];
int g[N]; // g[i] = { a num | char('A'+i-1) stand for }
bool vis[N];
int n;
bool check();
//set<ULL> S;
//ULL Hash()
//{
//	ULL res=0;
//	for(int i=1;i<=n;i++) 
//		res=res*131ll+(ULL)(g[i]+131ll);
//	return res;
//}
void dfs(int step,int up)
{
//    printf("%d : ",step);
//    for(int i=1;i<=n;i++) 
//        printf("%d ",g[i]);
//    printf("\n\n");

    if(step==0) {
    	if(up==0&&check()) {
    		for(int i=1;i<=n;i++) 
       	    	printf("%d ",g[i]);
  	        printf("\n");
  	    	exit(0);
		}
		return;
    }
//   	ULL h=Hash();
//	if(S.count(h)) return;
//	else S.insert(h);
    int i,j,k;
    int S[3]={n-1,n-1,n-1},T[3]={0,0,0};
    for(i=0;i<=2;i++) {
        if(g[a[i+1][step]]!=-1)
            S[i]=T[i]=g[a[i+1][step]];
    }
    for(i=S[0];i>=T[0];i--) {
        if(g[a[1][step]]!=-1&&g[a[1][step]]!=i) continue;
        if(vis[i]&&g[a[1][step]]==-1) continue;
        
        g[a[1][step]]=i;
        vis[i]=true;
        for(j=S[1];j>=T[1];j--) {
            if(g[a[2][step]]!=-1&&g[a[2][step]]!=j) continue;
            if(vis[j]&&g[a[2][step]]==-1) continue;
            
            g[a[2][step]]=j;
            vis[j]=true;
            for(k=S[2];k>=T[2];k--) {
                if(g[a[3][step]]!=-1&&g[a[3][step]]!=k) continue;
                if(vis[k]&&g[a[3][step]]==-1) continue;
                if((i+j+up)%n!=k) continue;
                
                vis[k]=true;
                g[a[3][step]]=k;
                dfs(step-1,(i+j+up)/n);
                vis[k]=false;
                g[a[3][step]]=-1;
            }
            g[a[2][step]]=-1;
            vis[j]=false;
        }
        g[a[1][step]]=-1;
        vis[i]=false;
    }
    return;
}
bool check()
{
	int i,up=0;
	for(i=n;i>=1;i--) {
		if((g[a[1][i]]+g[a[2][i]]+up)%n!=g[a[3][i]]) 
			return false;
		up=(g[a[1][i]]+g[a[2][i]]+up)/n;
	}
	if(up!=0) return false;
	else return true;
}
int main()
{
	freopen("1.in","r",stdin);
	int i,j;
	cin>>n;
	for(i=1;i<=3;i++) {
	    scanf("%s",c+1);
	    for(j=1;j<=n;j++) 
	        a[i][j]=c[j]-('A'-1);
	}
//	for(i=1;i<=3;i++) {
//	    for(j=1;j<=n;j++) 
//	        printf("%d ",a[i][j]);
//	    printf("\n");
//	}
//	printf("----------------------\n");
	memset(g,-1,sizeof g);
	dfs(n,0);
	return 0;
}
//    if(g[a[1][step]]!=-1&&g[a[2][step]]!=-1&&g[a[3][step]]!=-1) {
//        if((g[a[1][step]]+g[a[2][step]]+up)%n!=g[a[3][step]]) 
//            return;
//        dfs(step-1,(g[a[1][step]]+g[a[2][step]]+up)/n);
//        return;
//    }

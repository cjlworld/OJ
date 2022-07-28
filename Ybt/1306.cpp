#include<cstdio>
#include<cstring>
#include<iostream>

using namespace std;

const int N=3000+5;

int n,m;
int a[N],b[N],f[N][N]; // f[i][j] a[1~i] 和 b[j] 结尾的最长公共上升子序列
int g[N]; // g[k] = max{ states f[i-1][k] | b[k] < a[i] }
int gp[N];
int p[N][N];
void printway(int x,int y)
{
	if(x==0||y==0) return;
	if(p[x][y]!=-1) printway(x-1,p[x][y]),printf("%d ",a[x]);
	else printway(x-1,y);
}

int main()
{
    int i,j;
    cin>>n;
    for(i=1;i<=n;i++) cin>>a[i];
    cin>>m;
    for(i=1;i<=m;i++) cin>>b[i];
    memset(p,-1,sizeof p);
    for(i=1;i<=n;i++) {
        memset(g,0,sizeof g);
        memset(gp,0,sizeof gp);
        int cmax=0,mp=0;
        for(j=1;j<=m;j++) {
        	if(b[j]<a[i]&&f[i-1][j]>=cmax) 
        		cmax=f[i-1][j],mp=j;
        	g[j]=cmax,gp[j]=mp;
		}
        for(j=1;j<=m;j++) {
            f[i][j]=f[i-1][j]; // hasn't used a[i]
            if(a[i]==b[j]&&g[j]+1>=f[i][j]) {//used a[i]
        		p[i][j]=gp[j];
        		f[i][j]=g[j]+1;
			}
        }
    }
    int ans=0;
    for(i=1;i<=m;i++)
        if(f[n][i]>f[n][ans]) ans=i;
    cout<<f[n][ans]<<endl;
    printway(n,ans);
    return 0;
}

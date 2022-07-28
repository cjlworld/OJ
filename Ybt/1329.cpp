#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<bits/stdc++.h>
using namespace std;
int n,m;
int sum=0;
int a[256][256];
int f[1000000][2];
const int dx[]={0,0,0,1,-1};
const int dy[]={0,1,-1,0,0};
inline int Readin()
{
	char c;
	while(c=getchar()) 
		if(c>='0'&&c<='9') return c-'0';
}
int bfs(int x,int y)
{
	memset(f,0,sizeof(f));
	f[1][0]=x; f[1][1]=y;
	int head=0,tail=1;
	int u,v;
	int i,j;
	do  {
		head++;
		for(i=1;i<=4;i++) {
			u=f[head][0]+dx[i]; v=f[head][1]+dy[i];
			if(a[u][v]!=0&&u>=1&&u<=n&&v>=1&&v<=m) {
				tail++;
				f[tail][0]=u; f[tail][1]=v;
				a[u][v]=0;
			}
		}
	} while(head<tail);
}
int main()
{
 //	freopen("1.in","r",stdin);
//	freopen(".out","w",stdout);
	cin>>n>>m;
	int i,j;
	for(i=1;i<=n;i++) {
		for(j=1;j<=m;j++) {
			a[i][j]=Readin();
//			cout<<a[i][j];
		}
//		cout<<endl;
	}
	for(i=1;i<=n;i++) {
		for(j=1;j<=m;j++) {
			if(a[i][j]!=0) {
				sum++;
				bfs(i,j);
			}
		}
	}
	cout<<sum;
	fclose(stdin);fclose(stdout);
	return 0;
}


#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
using namespace std;
int q[2560][2560],c[2560][2560];
int dx[5]={0,1,1};
int dy[5]={0,0,1};
int r;
int cmax=-100;
struct data
{
	int x;
	int y;
}ch[10000000];
data tail;
/*void dfs(int x,int y)
{
	for(int i=1;i<=2;i++) {
		if(x+dx[i]>=y+dy[i]&&x+dx[i]<=r) {
			c[x+dx[i]][y+dy[i]]=max(c[x+dx[i]][y+dy[i]],c[x][y]+q[x+dx[i]][y+dy[i]]);
			dfs(x+dx[i],y+dy[i]);
		}
	}
}*/
int main()
{
//	freopen("1.in","r",stdin);
	cin>>r;
	int i,j,u=0;
	int head=0;
	for(i=1;i<=r;i++) {
		for(j=1;j<=i;j++) {
			cin>>q[i][j];
			u++;
			ch[u].x=i;
			ch[u].y=j;
		}
	}
	c[1][1]=q[1][1];
	while(head<u) {
		head++;
		for(int i=1;i<=2;i++) {
			if(ch[head].x+dx[i]>=ch[head].y+dy[i]&&ch[head].x+dx[i]<=r) {
				tail.x=ch[head].x+dx[i];
				tail.y=ch[head].y+dy[i];
				c[tail.x][tail.y]=max(c[tail.x][tail.y],c[ch[head].x][ch[head].y]+q[tail.x][tail.y]);
			}
		}
	}
	for(i=1;i<=r;i++) {
		if(c[r][i]>cmax) cmax=c[r][i];
	}
	cout<<cmax;
	return 0;
}

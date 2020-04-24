#include<bits/stdc++.h>
using namespace std;
/*第一行为整数n。
第2行到第n+1行（共n行） ，每行两个整数x和y，描述了一个点的坐标。
第n+2行为一个整数m，表示图中连线的个数。
此后的m 行，每行描述一条连线，由两个整数i和j组成，表示第i个点和第j个点之间有连线。
最后一行：两个整数s和t，分别表示源点和目标点。*/
int n,m;
double w[256][256];
struct node
{
	double x;
	double y;
};
node a[256];
int s,t;
inline void add(int xx,int yy)
{
	w[xx][yy]=w[yy][xx]=sqrt(pow(a[xx].x-a[yy].x,2)+pow(a[xx].y-a[yy].y,2));
	return;
}
void Init()
{
	scanf("%d",&n);
	memset(w,127,sizeof(w));
	int i,j;
	int xx,yy;
	for(i=1;i<=n;i++) {
		cin>>a[i].x>>a[i].y;
	}
	scanf("%d",&m);
	for(i=1;i<=m;i++) {
		scanf("%d%d",&xx,&yy);
		add(xx,yy);
	}
	scanf("%d%d",&s,&t);
	return;
}
void Floyed()
{
	int i,j,k;
	for(k=1;k<=n;k++) {
		for(i=1;i<=n;i++) {
			for(j=1;j<=n;j++) {
				if(w[i][j]>w[i][k]+w[k][j])
					w[i][j]=w[i][k]+w[k][j];
			}
		}
	}
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	Init();
	Floyed();
	cout<<fixed<<setprecision(2)<<w[s][t];
	return 0;
}


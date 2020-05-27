#include<cstdio>
#include<iostream>
#define LL long long
#define rint register int
using namespace std;
const int N=1500+5;
int n,m;
bool a[N][N];
pair<int,int> par[N][N];
pair<int,int> Find(const int &x,const int &y)
{
	if(x!=par[x][y].first||y!=par[x][y].second) 
		return par[x][y]=Find(par[x][y].first,par[x][y].second);
	return par[x][y];
}
pair<int,int> x_,y_;
inline void Join(const pair<int,int> &x,const pair<int,int> &y)
{
	x_=Find(x.first,x.second);
	y_=Find(y.first,y.second);
	if(x_==y_) 
		return;
	par[x_.first][x_.second]=y_;
	return;
}
const int STARS=100000+5;
int sign[STARS];
int cnt[N][N];
int main()
{
//	freopen("1.in","r",stdin);
	rint i,j,k;
	char c;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) {
		for(j=1;j<=m;j++) {
			for(c=getchar();c!='.'&&c!='*';c=getchar());
			if(c=='*')
				a[i][j]=true; 
			par[i][j]=pair<int,int>(i,j);
		}
	}
	for(i=1;i<=n;i++) {
		for(j=1;j<=m;j++) {
			if(a[i][j]==false) 
				continue;
			if(j+1<=m&&a[i][j+1]==true) 
				Join(pair<int,int>(i,j),pair<int,int>(i,j+1));
			if(i==n) continue;
			for(k=max(1,j-1);k<=min(m,j+1);k++) 
				if(a[i+1][k]) 
					Join(pair<int,int>(i,j),pair<int,int>(i+1,k)); 
		}
	}
	for(i=1;i<=n;i++) 
		for(j=1;j<=m;j++) {
			if(a[i][j]==false) 
				continue;
			par[i][j]=Find(par[i][j].first,par[i][j].second);	
			cnt[par[i][j].first][par[i][j].second]++;
		}
	int ans=0;
	int cmax=0;
	for(i=1;i<=n;i++) {
		for(j=1;j<=m;j++) {
			if(cnt[i][j]==0) 
				continue;
			sign[cnt[i][j]]++;	
		}
	}
	for(i=1;i<=STARS-1;i++) 
		if(sign[i]) {
			ans++;
			cmax=max(cmax,sign[i]*i);
		}
	printf("%d %d\n",ans,cmax);
	return 0;
}


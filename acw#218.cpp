#include<set>
#include<map>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<bitset>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=14;
const double INF=1e20;
int A,B,C,D;

double f[N][N][N][N][5][5]; 
// f[a][b][c][d][x][y] 表示已经抽取了a张A，b张B，c张C，d张D，
// 小王1~4 表示抽到给了 [a,b,c,d], 0 表示 还没抽，大王同
// 的状态到终点的最小数学期望。 

double dp(int a,int b,int c,int d,int x,int y)
{
	int as=a+(x==1)+(y==1);
	int bs=b+(x==2)+(y==2);
	int cs=c+(x==3)+(y==3);
	int ds=d+(x==4)+(y==4);
	double &u=f[a][b][c][d][x][y];
	if(as>=A&&bs>=B&&cs>=C&&ds>=D) return u=0.0; // ? ? ? ? ? 
	if(u>=0) return u;
	u=0.0;
	double sum=54-(a+b+c+d+(x>0)+(y>0)); 
		// sum 为剩下的卡牌的数量 
	if(a<13) u+=(13.0-a)/sum*(dp(a+1,b,c,d,x,y)+1);
	if(b<13) u+=(13.0-b)/sum*(dp(a,b+1,c,d,x,y)+1);
	if(c<13) u+=(13.0-c)/sum*(dp(a,b,c+1,d,x,y)+1);
	if(d<13) u+=(13.0-d)/sum*(dp(a,b,c,d+1,x,y)+1);
	
	int i; double v;
	if(x==0) {
		v=INF;
		for(i=1;i<=4;i++) 
				v=min(v,dp(a,b,c,d,i,y));
		u+=1.0/sum*(v+1);
	}
	if(y==0) {
		v=INF;
		for(i=1;i<=4;i++) 
				v=min(v,dp(a,b,c,d,x,i));
		u+=1.0/sum*(v+1);	
	}
//	printf("%d %d %d %d %d %d : %.3lf\n",a,b,c,d,x,y,u);
	return u;
}


int main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	memset(f,-1,sizeof f);
	int tmp=0;
	cin>>A>>B>>C>>D;
	if(A>13) tmp+=A-13;
	if(B>13) tmp+=B-13;
	if(C>13) tmp+=C-13;
	if(D>13) tmp+=D-13;
	if(tmp>2) printf("-1.000");
	else printf("%.3lf",dp(0,0,0,0,0,0));
	return 0;
}


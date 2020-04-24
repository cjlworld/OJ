#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N=256;
long double w[N][N]; 
long double a[N][N],b[N][N]; //a(i,j),b(i,j)
int n;
void Init()
{
	int i,j;
	scanf("%d",&n);
	for(i=1;i<=n;i++) 
		for(j=1;j<=n;j++) 
			cin>>a[i][j];
	for(i=1;i<=n;i++) 
		for(j=1;j<=n;j++) 
			cin>>b[i][j];
	return;
}
int cx[N],cy[N]; //link
long double wx[N],wy[N]; //top flag
bool visx[N],visy[N];
long double delta,delt;
bool path(int now)
{
	visx[now]=true;
	for(int i=1;i<=n;i++) {
		if(!visy[i]) {		
			delt=wx[now]+wy[i]-w[now][i];
			if(fabs(delt)<0.00001) 
			{
				visy[i]=true;
				if(cy[i]==0||path(cy[i])) {
					cx[now]=i;
					cy[i]=now;
					return true;
				}
			}
			else if(delt>0) 
				delta=min(delta,delt);
		}
	}
	return false;
}
bool check(long double C)
{
	int i,j;
	for(i=1;i<=n;i++) 
		for(j=1;j<=n;j++) 
			w[i][j]=a[i][j]-b[i][j]*C;
	memset(cx,0,sizeof cx);
	memset(cy,0,sizeof cy);
	memset(wy,0,sizeof wy);
	for(i=1;i<=n;i++) {
		wx[i]=-1e9/1.0;
		for(j=1;j<=n;j++) 
			wx[i]=max(wx[i],w[i][j]);
	}	
	for(i=1;i<=n;i++) {
		while(true) {
			delta=1e9*1.0;
			memset(visx,0,sizeof visx);
			memset(visy,0,sizeof visy);
			if(path(i)) break;
			for(j=1;j<=n;j++) 
				if(visx[j]) 
					wx[j]-=delta;
			for(j=1;j<=n;j++) 
				if(visy[j]) 
					wy[j]+=delta;
		}
	}
	long double res=0.0;
	for(i=1;i<=n;i++) 
		res+=w[i][cx[i]];
	if(res<0) 
		return true;
	else return false;
}
int main()
{
//	freopen("1.in","r",stdin);
	Init();
	long double L=0,R=1e5+5.0,mid;
	while(L+0.0000001<R) {
		mid=(L+R)/2;
		if(check(mid)) R=mid;
		else L=mid;
	}
	R=round(R*1000000.0)/1000000.0;
	cout<<fixed<<setprecision(6)<<R; 
	return 0;
}


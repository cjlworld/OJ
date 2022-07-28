#include<bits/stdc++.h>
using namespace std;
const int N=100+64;
int D,G;//深度为 D (2 <= D <= 100)英尺,G (1 <= G <= 100)，G 为被投入井的垃圾的数量
struct thing
{
	int time;
	int food;
	int high;
}a[1024];
int f[N][N];//f[now][high]=max:life;
int sum=10;
bool rule(const thing &a,const thing &b)
{
	return a.time<b.time;
}
void print(int x)
{
	int i,j;
	for(i=1;i<=D;i++) {
		if(f[x][i]) cout<<"high: "<<i<<" "<<"life: "<<f[x][i]<<endl; 
	}
	cout<<endl;
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i,j,u;
	cin>>D>>G;
	for(i=1;i<=G;i++) 
    	scanf("%d%d%d",&a[i].time,&a[i].food,&a[i].high); 
	sort(a+1,a+G+1,rule);
	for(i=1;i<=G;i++) 
		if(sum>=a[i].time)
			sum+=a[i].food;
	f[0][0]=10;
	for(u=1;u<=G;u++) {//每放入一个垃圾,
		for(i=D+25;i>=0;i--) { //------???
			if(i>=a[u].high&&f[u-1][i-a[u].high]>=a[u].time) 
				f[u][i]=max(f[u][i],f[u-1][i-a[u].high]); //put
			if(f[u-1][i]>=a[u].time) 
				f[u][i]=max(f[u][i],f[u-1][i]+a[u].food); //eat			
		}
	}
	for(i=1;i<=G;i++) 
		for(j=D;j<=D+25;j++) 
			if(f[i][j]) {
				cout<<a[i].time;
				return 0;
			}
	cout<<sum;
	return 0;
}

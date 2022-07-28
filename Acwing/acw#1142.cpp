#include<bits/stdc++.h>
using namespace std;
/*第一行有两个整数n,m表示城市有n个交叉路口，m条道路。
接下来m行是对每条道路的描述，u, v, c表示交叉路口u和v之间有道路相连，分值为c。(1≤n≤300，1≤c≤10000，1≤m≤100000)
*/
int n,m;
struct edge
{
	int x;
	int y;
	int w;
}a[100005];
int par[1024];
int Find(int x)
{
	if(x!=par[x]) return par[x]=Find(par[x]);
	return x;
}
bool OK(long long t)
{
	int i,j;
	for(i=1;i<=n;i++) par[i]=i;
	int x_,y_;
	int sum=0;
	for(i=1;i<=m;i++) {
		if(a[i].w>t) continue;
		x_=Find(a[i].x); y_=Find(a[i].y);
		if(x_!=y_) {
			par[y_]=x_;
			sum++;
			if(sum>=n-1) return true;
		}
	}
	if(sum>=n-1) return true;	
	return false;
}
int main()
{
//	freopen("1.in","r",stdin);
//	freopen(".out","w",stdout);
	int i,j;
	cin>>n>>m;
	for(i=1;i<=m;i++) {
		scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].w);
	}
	long long right=0x7ffffffffff,left=0,mid;
	while(left+1<right) {
//		cout<<left<<" "<<mid<<" "<<right<<endl;
		mid=(left+right)>>1;
		if(OK(mid)) right=mid;
		else left=mid;
	}
	cout<<n-1<<" ";
	cout<<right;
	return 0;
}

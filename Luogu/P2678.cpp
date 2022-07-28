#include<bits/stdc++.h>
#define LL long long
using namespace std;
int L,R,mid;
const int N=5e4+5;
int end,n,m;
int s[N],a[N],c[N];
bool check(const int &t)
{
	int cnt=0;
	memset(c,0,sizeof(c));
	for(int i=1;i<=n+1;i++) c[i]=a[i];
	for(int i=1;i<=n+1;i++) {
		if(c[i]<t) {
			cnt++;
			c[i+1]+=c[i];
			if(cnt>m) return false;
		}  
	}
	return true;
}
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d%d%d",&end,&n,&m);
	for(int i=1;i<=n;i++) 
		scanf("%d",&s[i]);
	s[n+1]=end;
	for(int i=1;i<=n+1;i++) {
		a[i]=s[i]-s[i-1];
	}
	L=0; R=end+1;
	while(L+1<R) {
		mid=L+R>>1;
		if(check(mid)) L=mid;
		else R=mid;
	}
	cout<<L;
	return 0;
}

#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
const int N=1e5+5;
int n;
int ans;
int h[N];
int a[N];
int tot;
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d",&n);
	int i,j;
	for(i=1;i<=n;i++) 
		scanf("%d",&a[i]);
	int	ago=-1;
	for(i=1;i<=n;i++) {
		if(a[i]==ago) continue;
		h[++tot]=a[i];
		ago=a[i];
	}
	for(i=2;i<=tot-1;i++) {
		if(h[i]>h[i-1]&&h[i]>h[i+1]) 
			ans++;//,printf("%d ",h[i]);
		else if(h[i]<h[i-1]&&h[i]<h[i+1]) 
			ans++;//,printf("%d ",h[i]);
	}
	ans++;
	ans++;
	printf("%d",ans);
	return 0;
}


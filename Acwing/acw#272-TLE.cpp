#include<vector> 
#include<cstdio>
#include<iostream>
#include<algorithm>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=3000+5;
int a[N],b[N],f[N][N],n;
vector<int> v;
// f[i][j] 表示 a[1]~a[i] and b[1]~b[j] 产生的最大公共上升子序列。
// f[i][j] = max(f[q][p]+1) ,a[i]=b[j]>a[q]=b[p], q<i,p<j;
int main()
{
//	freopen("1.in","r",stdin);
	int i,j,q,p;
	scanf("%d",&n);
	for(i=1;i<=n;i++) scanf("%d",&a[i]),v.push_back(a[i]);
	for(i=1;i<=n;i++) scanf("%d",&b[i]),v.push_back(b[i]);
	sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
	for(i=1;i<=n;i++) {
		a[i]=(int)(lower_bound(v.begin(),v.end(),a[i])-v.begin())+1;
		b[i]=(int)(lower_bound(v.begin(),v.end(),b[i])-v.begin())+1;
	}
	for(i=1;i<=n;i++) {
		if(a[i]==a[i-1]) continue;
		for(j=1;j<=n;j++) {
			if(a[i]!=b[j]||b[j]==b[j-1]) continue;
			for(q=0;q<=i-1;q++) {
				if(a[q]>=a[i]) continue;
				for(p=0;p<=j-1;p++) {
					if(a[q]!=b[p]) continue;
					f[i][j]=max(f[i][j],f[q][p]+1);
				}
			}
		}
	}
	int ans=0;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++) 
			ans=max(ans,f[i][j]);
	cout<<ans;
	return 0;
}


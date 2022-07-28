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

const int N=2e5+5;

int n,m;
int a[N],b[N],c[N];

vector<int> nums;
int getid(int x)
{
	return (int)(upper_bound(nums.begin(),nums.end(),x)-nums.begin());
}
int cnt[N];
int main()
{
//	freopen("1.in","r",stdin);
	
	int i;
	scanf("%d",&n);
	for(i=1;i<=n;i++) 
		scanf("%d",&a[i]),nums.push_back(a[i]);
	scanf("%d",&m);
	for(i=1;i<=m;i++) {
		scanf("%d",&b[i]);
		nums.push_back(b[i]);
	}
	for(i=1;i<=m;i++) {
		scanf("%d",&c[i]);
		nums.push_back(c[i]);
	}
	
	sort(nums.begin(),nums.end());
	nums.erase(unique(nums.begin(),nums.end()),nums.end());
	
	for(i=1;i<=n;i++) 
		a[i]=getid(a[i]),cnt[a[i]]++;
		
	int ans=0;
	for(i=1;i<=m;i++) {
		b[i]=getid(b[i]),c[i]=getid(c[i]);
		if(cnt[b[i]]>cnt[b[ans]]||(cnt[b[i]]==cnt[b[ans]]&&cnt[c[i]]>cnt[c[ans]]))
			ans=i;
	}
	cout<<ans<<endl;
	return 0;
}


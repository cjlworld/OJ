#include<set>
#include<cstdio>
#include<iostream>
#include<algorithm>
#define LL long long
using namespace std;
const int N=1e5+5;
int n,ans;
int a[N],f[N];// f[i] ��ʾ��i��β��������������еĳ���.(a[i]һ����������) ��
int main()
{
	int i,j;
	cin>>n;
	for(i=1;i<=n;i++) 
		scanf("%d",&a[i]);
	a[0]=1e9;
	for(i=1;i<=n;i++) {
		for(j=0;j<i;j++) 
			if(a[i]<=a[j]) 
				f[i]=max(f[i],f[j]+1);
		ans=max(ans,f[i]);
	}
	cout<<ans;
	return 0;
}

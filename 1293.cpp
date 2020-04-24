#include<bits/stdc++.h>
using namespace std;
int n;
long long f[1005];
long long a[]={0,10,20,50,100};
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	cin>>n;
	if(n==0) { cout<<"0"; return 0; }
	f[0]=1;
	for(i=1;i<=4;i++) {
		for(j=0;j<=n;j++) {
			if(j-a[i]>=0) {
				f[j]=f[j]+f[j-a[i]];
			}
		}
	}
	cout<<f[n];
	return 0;
}

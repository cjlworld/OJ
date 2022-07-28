#include<cstdio>
#include<iostream>

using namespace std;
typedef long long LL;

const int N=1e5+5;

int n;
LL a[N];

int main()
{
	int i,j;
	
	scanf("%d",&n);
	for(i=0;i<n;i++) 
		scanf("%lld",&a[i]); 
	
	int k=0;
	for(i=63;i>=0;i--) {
		for(j=k;j<n;j++) 
			if((a[j]>>i)&1) {
				swap(a[k],a[j]);
				break;
			}
		if(!((a[k]>>i)&1)) continue;
		
		for(j=0;j<n;j++) 
			if(j^k && (a[j]>>i)&1)
				a[j]^=a[k];
		k++;
		if(k==n) break;
	}
	
	LL res=0;
	for(i=0;i<k;i++) res^=a[i];
	printf("%lld\n",res);
	return 0;
}


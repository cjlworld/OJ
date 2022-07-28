#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;
const int N=1000024;
int ans[N];
unsigned long long pow2[N];
unsigned long long n,k;
void cod(int len)
{
	if(len==0) return;
	if(k<pow2[len-1]) {
		ans[len]=0;
	}
	else {
		ans[len]=1;
		k=pow2[len]-1-k;
	}
	cod(len-1);
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	pow2[0]=1;
	for(i=1;i<=65;i++) 
		pow2[i]=pow2[i-1]<<1;
	cin>>n>>k;
	cod(n);
	for(i=n;i>=1;i--) 
	    printf("%d",ans[i]);
	return 0;
}

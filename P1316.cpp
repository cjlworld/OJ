#include<bits/stdc++.h>
using namespace std;
int A,B;
int k[1000005];
int a[1000005];
bool OK(long long t)
{
	int sum=0,s=0;
	int i,j;
	for(i=1;i<=A;i++) {
		s+=a[i];
		if(s>=t) { sum++; s=0; } 
	} 
	if(sum<B-1) return false;
	return true;
}
int main()
{
//	freopen("1.in","r",stdin);
	cin>>A>>B;
	int i,j;
	for(i=1;i<=A;i++) {
		scanf("%d",&k[i]);
	}
	sort(k+1,k+A+1);
	for(i=1;i<=A-1;i++) {
		a[i]=k[i+1]-k[i];
	}
	long long right=0x7ffffffffff,left=0,mid;
	while(left+1<right) {
//	cout<<left<<" "<<mid<<" "<<right<<endl;
		mid=(left+right)>>1;
		if(OK(mid)) left=mid;
		else right=mid;
	}
	cout<<left;
	return 0;
}

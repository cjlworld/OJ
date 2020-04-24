#include<cstdio>
#include<iostream>
#include<algorithm>
#define LL long long
using namespace std;
const int N=30000+5;
int m,n;
int a[N];
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	scanf("%d%d",&m,&n);
	for(i=1;i<=n;i++) 
		scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	int head=1,tail=n;
	int cnt=0;
	while(head<tail) {
		if(a[tail]+a[head]<=m) {
			head++;
			tail--;
			cnt++;
		}
		else {
			tail--;
			cnt++;
		}
	} 
	if(tail==head) cnt++;
	cout<<cnt;
	return 0;
}


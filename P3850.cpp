#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#define LL long long
using namespace std;
const int N=2e5+5;
int num[N],siz,cnt;
char s[N][20];
int q[N];
int n,m;
int a[N];
void insert(int pos,int key)
{
	int i,j,sum=0;
	++pos;
	for(i=1;i<=cnt;i++) {
		if(num[i]==((i==1) ? siz+1 : siz)||(i==cnt&&num[i]==n-(cnt-1)*siz))
			continue;
		if(sum+((i==1) ? siz+1 : siz)-num[i]>=pos) {
			for(j=(i==1) ? 0 : ((i-1)*siz+1);j<=min(n+m,i*siz);j++) {
				if(a[j]>0) 
					continue;
				sum++;
				if(sum==pos) {
					a[j]=key;
					num[i]++;
					return;
				}
			}
		}
		else sum+=((i==1) ? siz+1 : siz)-num[i];
	}
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	scanf("%d",&n);
	for(i=1;i<=n;i++) 
		scanf("%s",s[i]);
	scanf("%d",&m);
	siz=sqrt(m+n);
	cnt=(m+n)/siz+((m+n)%siz>0);
	for(i=1;i<=m;i++) 
		scanf("%s%d",s[i+n],&q[i+n]);
		
	for(i=m+n;i>=n+1;i--) {
		insert(q[i],i);
	}
	for(i=1;i<=n;i++) 
		insert(0,i);
	int k;
	scanf("%d",&k);
	while(k--) {
		scanf("%d",&x);
		printf("%s\n",s[a[x]]);
	}
	return 0;
}

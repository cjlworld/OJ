#include<cstdio>
#include<cstring>
#include<iostream>
#define LL long long
using namespace std;
const int INF=(-1u)>>1;
const int N=256;
int ans;
char name[29];
char tmp[29];
int n;
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	scanf("%d",&n);
	ans=-INF;
	for(i=1;i<=n;i++) {
		scanf("%d%s",&x,tmp);
		if(x>ans) {
			ans=x;
			memset(name,'\0',sizeof name);
			for(j=0;j<=28;j++) 
				name[j]=tmp[j];
		}
	}
	cout<<name;
	return 0;
}


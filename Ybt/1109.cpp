#include<bits/stdc++.h>
#define rint register int 
using namespace std;
const int N=5000+5;
int n,m;
bool b[N]; //open--true;
int main()
{
	scanf("%d%d",&n,&m);
	for(rint i=1;i<=m;i++) {
		int k=1;
		while(k*i<=n) b[k*i]=!b[k*i],++k;
	}
	for(rint i=1;i<=n;i++) {
		if(i==1&&b[i]) printf("%d",i);
		else if(b[i]) printf(",%d",i);
	}
	printf("\n");
	return 0;
}


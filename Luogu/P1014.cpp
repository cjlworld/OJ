#include<bits/stdc++.h>
#define rint register int
using namespace std;
int n;
int main()
{
	scanf("%d",&n);
	for(rint i=1;;i++) {
		if(n-i>0) n=n-i;
		else {
			if(i%2==1) {
				printf("%d/%d",i-n+1,n);
			}
			else printf("%d/%d",n,i-n+1);
			return 0;
		}
	}
	return 0;
}


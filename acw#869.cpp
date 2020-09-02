#include<bits/stdc++.h>
using namespace std;
const int N=1e6+6;
int p[N],tot=0;
int main()
{
    int i,j;
    int n,x;
    cin>>n;
    for(i=1;i<=n;i++) {
        cin>>x;
        tot=0;
        for(j=1;j*j<=x;j++) {
            if(x%j==0) {
            	p[++tot]=j;
				if(j!=x/j) p[++tot]=x/j;
			}		
        }
        sort(p+1,p+tot+1);
        for(j=1;j<=tot;j++) 
        	printf("%d ",p[j]);
        printf("\n");
    }
    return 0;
}

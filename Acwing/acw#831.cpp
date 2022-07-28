#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
char a[N],b[N];
int nxt[N];
int n,m;
void dealkmp()
{
    int i,j=0;
//    printf("nxt = {0,0");
    for(i=2;i<=n;i++) {
        while(a[i]!=a[j+1]&&j>0) 
            j=nxt[j];
        if(a[j+1]==a[i]) 
            j++;
        nxt[i]=j;
//        printf(",%d",nxt[i]);
    }
//    printf("}\n");
    return;
}
void kmp()
{
    int i,j=0;
    for(i=1;i<=m;i++) {
//        printf("%d",j);
        while(b[i]!=a[j+1]&&j>0) 
            j=nxt[j];
        if(a[j+1]==b[i]) j++;
        if(j==n) printf("%d ",i-j+1-1);
    }
    return;
}
int main()
{
    int i,j;
    scanf("%d%s%d%s",&n,a+1,&m,b+1);
//    printf("%s",b+1);
//    printf("m = %d\n",m);
    dealkmp();
    kmp();
    return 0;
}

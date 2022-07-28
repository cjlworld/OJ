#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int p[N],tot=0;
bool tag[N];
void prime(int n)
{
    long long i,j;
    for(i=2;i<=n;i++) {
        if(tag[i]) continue;
        p[++tot]=i;
        for(j=i*i;j<=n;j+=i) 
            tag[j]=true;
    }
    return;
}
int main()
{
    int i;
    int n;
    cin>>n;
    prime(n+1);
    if(tot==n) {
        printf("1\n");
        for(i=2;i<=n+1;i++) 
            printf("1 ");
    }
    else {
        printf("2\n");
        for(i=2;i<=n+1;i++) 
            if(tag[i]) printf("1 ");
            else printf("2 ");
    }
    return 0;
}

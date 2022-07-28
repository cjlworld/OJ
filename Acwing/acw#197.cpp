#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
long long p[N],tot=0;
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
    long long i,j;
    int n;
    cin>>n;
    prime(n);
    for(i=1;i<=tot;i++) {
        int res=0;
        for(j=p[i];j<=n;j*=p[i])
            res+=n/j;
        printf("%lld %d\n",p[i],res);
    }
    return 0;
}

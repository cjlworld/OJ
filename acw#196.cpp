#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N=1e6+5;
int n=1e5;
LL p[N],tot=0;
bool tag[N];
void prime(int n)
{
    LL i,j;
    for(i=2;i<=n;i++) {
        if(tag[i]) continue;
        p[++tot]=i;
        for(j=i*i;j<=n;j+=i)
            tag[j]=true;
    }
    return;
}
vector<LL> pm;
int main()
{
    LL L,U;
    LL i,j;
    prime(n);
    while(scanf("%lld%lld",&L,&U)==2) {
    	if(L==1) L++;
        memset(tag,0,sizeof tag);
        for(i=1;i<=tot&&p[i]*p[i]<=U;i++) {
            for(j=max(L/p[i]*p[i],p[i]*p[i]);j<L;j+=p[i]);
            for(;j<=U;j+=p[i]) 
                tag[j-L]=true;
        }
        pm.clear();
        for(i=0;i<=U-L;i++) 
            if(!tag[i]) 
                pm.push_back(i+L);
        LL ans1=N,ans2=-N;
        for(i=1;i<pm.size();i++) {
            ans1=min(ans1,pm[i]-pm[i-1]);
            ans2=max(ans2,pm[i]-pm[i-1]);
//            cout<<pm[i]<<endl;
        }
        int a=-1,b=-1;
        for(i=1;i<pm.size();i++) {
            if(pm[i]-pm[i-1]==ans1&&a==-1) 
                a=i;
            if(pm[i]-pm[i-1]==ans2&&b==-1)
                b=i;
        }
        if(pm.size()<2) printf("There are no adjacent primes.\n");
        else printf("%d,%d are closest, %d,%d are most distant.\n",pm[a-1],pm[a],pm[b-1],pm[b]);
    }
    return 0;
}


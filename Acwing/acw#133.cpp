#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL n,m,q,u,v,t;
// p= u/v;
priority_queue<int> Q;
int main()
{
//	freopen("1.in","r",stdin);
    int i;
    LL x,cha=0; // nums from Q + cha = real
    scanf("%lld%lld%lld%lld%lld%lld",&n,&m,&q,&u,&v,&t);
    for(i=1;i<=n;i++) {
        scanf("%lld",&x);
        Q.push(x);
    }
    for(i=1;i<=m;i++) {
        x=Q.top()+cha; Q.pop();
        if(i%t==0) printf("%lld ",x);
        Q.push(u*x/v-cha-q); Q.push(x-u*x/v-cha-q);
        cha+=q;
    }
    printf("\n");
    for(i=1;i<=n+m&&Q.size();i++) {
        if(i%t==0) printf("%lld ",Q.top()+cha);
        Q.pop();
    }
    return 0;
}

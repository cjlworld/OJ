#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N=1e5+5;
LL n,m,q,u,v,t;
// p= u/v;
LL a[N];
queue<LL> Q1,Q2,Q3;
// Q1 original
// Q2 x*u/v
// Q3 x-x*u/v
LL cha;// nums from Q + cha = real
LL get()
{
	int x;
	if(!Q1.empty()&&(Q2.empty()||Q1.front()>=Q2.front())&&(Q3.empty()||Q1.front()>=Q3.front())) 
    	x=Q1.front()+cha,Q1.pop();
    else if(!Q2.empty()&&(Q1.empty()||Q2.front()>=Q1.front())&&(Q3.empty()||Q2.front()>=Q3.front())) 
    	x=Q2.front()+cha,Q2.pop();
   	else if(!Q3.empty()&&(Q2.empty()||Q3.front()>=Q2.front())&&(Q1.empty()||Q3.front()>=Q1.front())) 
    	x=Q3.front()+cha,Q3.pop();
    return x;
}
int main()
{
//	freopen("1.in","r",stdin);
    int i;
    LL x; 
    scanf("%lld%lld%lld%lld%lld%lld",&n,&m,&q,&u,&v,&t);
    for(i=1;i<=n;i++) 
        scanf("%lld",&a[i]);
    sort(a+1,a+n+1,greater<int>());
    for(i=1;i<=n;i++) Q1.push(a[i]);
    for(i=1;i<=m;i++) {
		x=get();
    	if(i%t==0) printf("%lld ",x);
    	Q2.push(x*u/v-cha-q); Q3.push((x-x*u/v)-cha-q);
		cha+=q;
    }
    printf("\n");
    for(i=1;i<=n+m;i++) {
    	x=get();
    	if(i%t==0) printf("%lld ",x);
	}
    return 0;
}

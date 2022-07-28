#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;

const int N=1e5+5;

int p[N],tot=0;
bool tag[N];

void prime(int n)
{
    int i,j;
    for(i=2;i<=n;i++) {
        if(!tag[i]) p[++tot]=i;
        for(j=1;j<=tot&&p[j]*i<=n;j++) {
            tag[p[j]*i]=n;
            if(i%p[j]) break;
        }
    }
    return;
}

LL gcd(LL a,LL b)
{
	return b ? gcd(b,a%b) : a;
}
LL lcm(LL a,LL b)
{
	return a/gcd(a,b)*b;
}

int T;
LL a,b,c,d;
vector< pair<LL,int> > v;
vector<LL> factor;

void dfs(int step,LL gma)
{
    LL i,j;
    if(step==(int)v.size()) {
        factor.push_back(gma);
        return;
    }
    for(i=0,j=1;i<=v[step].second;i++,j*=v[step].first) 
        dfs(step+1,gma*j);
    return;
}

void calc(int d)
{
	v.clear();
    for(int i=1;i<=tot&&p[i]*p[i]<=d;i++) {
    	if(d%p[i]==0) {
    		v.push_back(make_pair(p[i],0));
    		while(d%p[i]==0) {
          	  	d/=p[i];
          	  	v[v.size()-1].second++;
			}
		}
	}
	if(d>1) v.push_back(make_pair(d,1));
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
    int i;
    LL x;
    prime(N-1);
    cin>>T;
    while(T--) {
        cin>>a>>b>>c>>d;
        calc(d);
        factor.clear();
//		for(i=0;i<(int)v.size();i++) 
//			printf("%lld ",v[i].first);
//		printf("\n");
        dfs(0,1);
        int ans=0;
        for(i=0;i<(int)factor.size();i++) {
        	x=factor[i];
        //	printf("%lld ",x);
        	if(gcd(x,a)==b&&lcm(x,c)==d) 
        		ans++;
		}
//		printf("\n");
		printf("%d\n",ans);
    }
    return 0; 
}

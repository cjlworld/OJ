#include<vector>
#include<cstdio>
#include<iostream>
#include<algorithm>

using namespace std;

const int N=1e6+5;

vector<int> nums;

int Getnum(int x)
{
    return (int)(lower_bound(nums.begin(),nums.end(),x)-nums.begin())+1;
}

struct Require
{
    int x,y,k;
}r[N];

int T,n;

int par[2*N];
int Find(int x)
{
    if(par[x]!=x) return par[x]=Find(par[x]);
    else return x;
}

int main()
{
//	freopen("1.in","r",stdin);
    int i;
    cin>>T;
    while(T--) {
        scanf("%d",&n);
        for(i=1;i<=n;i++) {
            scanf("%d%d%d",&r[i].x,&r[i].y,&r[i].k);
            nums.push_back(r[i].x);
            nums.push_back(r[i].y);
        }
        
        sort(nums.begin(),nums.end());
        nums.erase(unique(nums.begin(),nums.end()),nums.end());
        
        for(i=1;i<=n;i++) 
            r[i].x=Getnum(r[i].x),r[i].y=Getnum(r[i].y);
            
        for(i=1;i<=(int)nums.size();i++) par[i]=i;
        
        for(i=1;i<=n;i++) 
            if(r[i].k) 
                par[Find(r[i].x)]=Find(r[i].y);
        for(i=1;i<=n;i++) 
            if(!r[i].k&&Find(r[i].x)==Find(r[i].y)) {
                printf("NO\n");
                break;
            }
        if(i==n+1) printf("YES\n");
    }
    return 0;
}

#include<bits/stdc++.h>
using namespace std;
const int N=6000+5;
vector<int> v[N];
//=============================
int n;
int a[N],b[N];
int f[N],dep[N];
void topsort()
{
    queue<int> q;
    int i,x,y;
    for(i=1;i<=n;i++) 
        if(dep[i]==0) 
            q.push(i),f[i]=1;
    while(q.size()) {
        x=q.front(); q.pop();
        for(i=0;i<(int)v[x].size();i++) {
            y=v[x][i];
            f[y]=max(f[y],f[x]+1);
            dep[y]--;
            if(dep[y]==0) 
                q.push(y);
        }
    }
    return;
}
int main()
{
    int i,j;
    cin>>n;
    for(i=1;i<=n;i++) 
        cin>>a[i]>>b[i];
    for(i=1;i<=n;i++) {
        for(j=1;j<=n;j++) 
            if(a[j]>a[i]&&b[j]>b[i]) 
                v[i].push_back(j),dep[j]++;
    }
    topsort();
    int ans=0;
    for(i=1;i<=n;i++) 
        ans=max(ans,f[i]);
    cout<<ans<<endl;
    return 0;
}

#include<map>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef pair<int,int> PII;
typedef map<int,int>::iterator mit;

const int N=2e5+5;

int one[N],idx;
int ver[N],Next[N],edge[N];
inline void AddEdge(int a,int b,int c)
{
    Next[idx]=one[a]; ver[idx]=b; edge[idx]=c; one[a]=idx++;
    Next[idx]=one[b]; ver[idx]=a; edge[idx]=c; one[b]=idx++;
}

int siz[N],dep[N],son[N],fat[N];
int dfn[N],top[N],times;
LL w[N];

void dfs(int x,int fa,int cost)
{
    fat[x]=fa;
    dep[x]=dep[fa]+1;
    w[x]=w[fa]+cost;
    siz[x]=1;
    
    for(int i=one[x],y;~i;i=Next[i]) {
        y=ver[i];
        if(y==fa) continue;
        dfs(y,x,edge[i]);
        siz[x]+=siz[y];
        if(siz[y]>siz[son[x]]) 
            son[x]=y;
    }
}

void dfs(int x)
{
    if(x==son[fat[x]]) top[x]=top[fat[x]];
    else top[x]=x;
    
    dfn[x]=++times;
    if(son[x]) dfs(son[x]);
    for(int i=one[x],y;~i;i=Next[i]) {
        y=ver[i];
        if(y==fat[x] || y==son[x]) continue;
        dfs(y);
    }
}

int lca(int x,int y)
{
    while(top[x]!=top[y]) {
        if(dep[top[x]]<dep[top[y]]) 
            swap(x,y);
        x=top[x]; x=fat[x];
    }
    if(dep[x]<dep[y]) return x;
    else return y;
}

LL dist(int x,int y)
{
    int z=lca(x,y);
    return w[x]+w[y]-2*w[z];
}

int n,m;

map<int,int> mp;

int main()
{
//	freopen("1.in","r",stdin);
    int i;
    int x,y,z;
    char opt[2];
    
    scanf("%d",&n);
    memset(one,-1,sizeof one);
    for(i=1;i<=n-1;i++) {
        scanf("%d%d%d",&x,&y,&z);
        AddEdge(x,y,z);
    }
    
    dfs(1,0,0); dfs(1);
    scanf("%d",&m);
    LL cur=0;
    while(m--) {
        scanf("%s",opt);
        if(*opt=='+') {
            scanf("%d",&x);
            if(mp.empty()) mp[dfn[x]]=x;
            else if(dfn[x]<mp.begin()->first || dfn[x]>(--mp.end())->first) {
            	y=mp.begin()->second;
            	z=(--mp.end())->second;
            	cur=cur-dist(y,z)+dist(x,y)+dist(x,z);
            	mp[dfn[x]]=x;
			}
			else {
				mit it=mp.lower_bound(dfn[x]);
				y=it->second; z=(--it)->second;
				cur=cur-dist(y,z)+dist(x,y)+dist(x,z);
				mp[dfn[x]]=x;
			}
        }
        else if(*opt=='-') {
        	scanf("%d",&x);
        	if(mp.size()==1) mp.erase(mp.begin());
        	else if(x==mp.begin()->second) {
        		y=(--mp.end())->second;
        		z=(++mp.begin())->second;
        		cur=cur-dist(x,y)-dist(x,z)+dist(y,z);
        		mp.erase(mp.begin());
			}
			else if(x==(--mp.end())->second) {
				y=mp.begin()->second;
				z=(--(--mp.end()))->second;
				cur=cur-dist(x,y)-dist(x,z)+dist(y,z);
        		mp.erase(--mp.end());
			}
			else {
				mit it=mp.lower_bound(dfn[x]);
				y=it->second; z=(--it)->second;
				cur=cur-dist(x,y)-dist(x,z)+dist(y,z);
				mp.erase(++it);
			}
		}
		else printf("%lld\n",cur/2);
    }
}

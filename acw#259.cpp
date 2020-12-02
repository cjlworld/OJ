#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;

const int N=1024;

int n,p1,p2,m;

int par[N],d[N];
int Find(int x)
{
    if(par[x]!=x) {
    	int root=Find(par[x]);
    	d[x]=(d[par[x]]+d[x])%2;
    	par[x]=root;
	}
	return par[x];
}

// 路径 d(x,y)=0 (mod 2),表示 x,y 同类
// 路径 d(x,y)=1 (mod 2), 表示 x,y 异类。

int b[N][2];
vector<int> v[N][2];

int cnt;
bool vis[N];

int f[N][N],pre[N][N];
// f[i][j] 表示在前i个对中取到j的方案数。

vector<int> ans;
void printway(int x,int y)
{
	if(pre[x][y]==-1) return;
	int k=pre[x][y];
	for(int i=0;i<(int)v[x][k].size();i++) 
		ans.push_back(v[x][k][i]);
	printway(x-1,y-b[x][k]);
}

int main()
{
//	freopen("1.in","r",stdin);
    int i,j;
	int x,y,root;
    char opt[5];
    
    while(scanf("%d%d%d",&n,&p1,&p2),(n||p1||p2)) {
        m=p1+p2;
        for(i=1;i<=m;i++) par[i]=i;
        memset(d,0,sizeof d);
        
        for(i=1;i<=n;i++) {
            scanf("%d%d%s",&x,&y,opt);
            if(!strcmp(opt,"yes")) { 
				if(Find(x)!=Find(y)) {
					// d[x]+d[root]=0 (mod 2);
					root=par[x];
					d[root]=d[x];
					par[root]=y; 
				}
            }
            else {
				if(Find(x)!=Find(y)) {
					// d[x]+d[root]=1 (mod 2)
					root=par[x];
					d[root]=(d[x]^1);
					par[root]=y;
				}
            }
        }
		
		// 对于 x ，(x,y) 有三种关系
		// 1. 同类
		// 2. 异类
		// 3. 未知
		
		// 把与其同类的缩成一个联通块 
		
		for(i=1;i<=m;i++) 
			v[i][0].clear(),v[i][1].clear();
		memset(vis,0,sizeof vis);
		memset(b,0,sizeof b);
		
		cnt=0;
		for(i=1;i<=m;i++) {
			if(vis[i]) continue; // 所在同类块已经被选过了。
			
			vis[i]=true;
			cnt++;
			b[cnt][0]++;
			v[cnt][0].push_back(i);
			
			for(j=i+1;j<=m;j++) {
				if(Find(i)!=Find(j)) continue;
				// 否则关系已知。
				if((d[i]+d[j])%2==1) b[cnt][1]++,v[cnt][1].push_back(j); // 异类 
				else b[cnt][0]++,v[cnt][0].push_back(j); // 同类。 
				
				vis[j]=true;
			}
		}
		
		memset(f,0,sizeof f);
		memset(pre,-1,sizeof pre);
		f[0][0]=1;
		
		for(i=1;i<=cnt;i++) {
			// 取 b[i][0]
			for(j=0;j<=m;j++) {
				if(j>=b[i][0] && f[i-1][j-b[i][0]]) 
					f[i][j]+=f[i-1][j-b[i][0]],pre[i][j]=0;
				if(j>=b[i][1] && f[i-1][j-b[i][1]]) 
					f[i][j]+=f[i-1][j-b[i][1]],pre[i][j]=1;
			}
		}
		
		if(f[cnt][p1]!=1) {
			printf("no\n");
			continue;
		} 
		
		ans.clear();
		printway(cnt,p1);
		sort(ans.begin(),ans.end());
		for(i=0;i<(int)ans.size();i++) 
			printf("%d\n",ans[i]);
		printf("end\n");
    }
    return 0;
}


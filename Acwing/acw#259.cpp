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

// ·�� d(x,y)=0 (mod 2),��ʾ x,y ͬ��
// ·�� d(x,y)=1 (mod 2), ��ʾ x,y ���ࡣ

int b[N][2];
vector<int> v[N][2];

int cnt;
bool vis[N];

int f[N][N],pre[N][N];
// f[i][j] ��ʾ��ǰi������ȡ��j�ķ�������

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
		
		// ���� x ��(x,y) �����ֹ�ϵ
		// 1. ͬ��
		// 2. ����
		// 3. δ֪
		
		// ������ͬ�������һ����ͨ�� 
		
		for(i=1;i<=m;i++) 
			v[i][0].clear(),v[i][1].clear();
		memset(vis,0,sizeof vis);
		memset(b,0,sizeof b);
		
		cnt=0;
		for(i=1;i<=m;i++) {
			if(vis[i]) continue; // ����ͬ����Ѿ���ѡ���ˡ�
			
			vis[i]=true;
			cnt++;
			b[cnt][0]++;
			v[cnt][0].push_back(i);
			
			for(j=i+1;j<=m;j++) {
				if(Find(i)!=Find(j)) continue;
				// �����ϵ��֪��
				if((d[i]+d[j])%2==1) b[cnt][1]++,v[cnt][1].push_back(j); // ���� 
				else b[cnt][0]++,v[cnt][0].push_back(j); // ͬ�ࡣ 
				
				vis[j]=true;
			}
		}
		
		memset(f,0,sizeof f);
		memset(pre,-1,sizeof pre);
		f[0][0]=1;
		
		for(i=1;i<=cnt;i++) {
			// ȡ b[i][0]
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


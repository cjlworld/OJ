#include<set>
#include<vector>
#include<cstdio>
#include<cstring>
#include<string.h>
#include<iostream>
#include<algorithm>

using namespace std;
typedef pair<int,int> PII;

const int N=256;

void write(const string &s)
{
    for(int i=0;i<(int)s.length();i++) 
        putchar(s[i]);
    putchar('\n');
    return;
}

int f[N][N];
char a[N],b[N];
int n,m;
vector<string> v;
string ans;
vector<PII> pre[N][N];
// pre[i][j] 存 f[i][j] 前(包括f[i][j]) 的第一个公共点对

void dfs(int x,int y)
{
//	write(ans);
//	cout<<ans.length()<<endl;
//	cout<<v.size()<<endl;
    if(ans.length()==(unsigned)f[n][m]) {
        reverse(ans.begin(),ans.end());
        if((int)ans.length()==f[n][m]) 
            v.push_back(ans);
        reverse(ans.begin(),ans.end());
        return;
    }
    int px,py;
    for(int i=0;i<(int)pre[x][y].size();i++) {
        px=pre[x][y][i].first,py=pre[x][y][i].second;
        if(px==x&&py==y) {
            ans.push_back(a[x]);
            dfs(x-1,y-1);
            ans.erase(ans.end()-1);
        }
        else dfs(px,py);
    }
    return;
}
void add(vector<PII> &k,const vector<PII> &g)
{
    for(int i=0;i<(int)g.size();i++) 
        k.push_back(g[i]);
    return;
}

int main()
{
//	freopen("1.in","r",stdin);
    int i,j;
    scanf("%s%s",a+1,b+1);
    n=strlen(a+1); m=strlen(b+1);
    for(i=1;i<=n;i++) {
        for(j=1;j<=m;j++) {
            f[i][j]=max(f[i-1][j],f[i][j-1]);
            if(a[i]==b[j])
                f[i][j]=max(f[i][j],f[i-1][j-1]+1);
                
            if(f[i][j]==f[i-1][j]) 
                add(pre[i][j],pre[i-1][j]);
            if(f[i][j]==f[i][j-1]) 
                add(pre[i][j],pre[i][j-1]);
        
            if(a[i]==b[j]&&f[i-1][j-1]+1==f[i][j]) 
                pre[i][j].push_back(PII(i,j));
        	
        	sort(pre[i][j].begin(),pre[i][j].end());
        	pre[i][j].erase(unique(pre[i][j].begin(),pre[i][j].end()),pre[i][j].end());
        }
    }
    dfs(n,m);
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
    for(i=0;i<(int)v.size();i++) 
        write(v[i]);
    return 0;
}

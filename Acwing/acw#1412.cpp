#include<map>
#include<queue>
#include<stack>
#include<ctime>
#include<cmath>
#include<bitset>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=1000+5,M=2e5+5;

vector<int> add(vector<int> a,vector<int> b)
{
	vector<int> c;
	int t=0;
	if(a.size()<b.size()) swap(a,b);
	for(int i=0;i<(int)a.size();i++) {
		t+=a[i];
		if(i<(int)b.size()) t+=b[i];
		c.push_back(t%10);
		t/=10;
	}
	if(t) c.push_back(t);
	return c;
}

void output(vector<int> a)
{
	for(int i=a.size()-1;i>=0;i--) 
		putchar(a[i]+'0');
}

int h[2][M]; // 滚动的哈希表 
vector<int> v[2][M];

int q[2][M],cnt[2]; // 滚动的队列，保存哈希表内插入的数的集合。 

int Hash(int cur,int k)
{
    int t=k%M;
    while(h[cur][t]!=-1 && h[cur][t]!=k) 
        if(++t==M) t=0;
    return t;
}

void insert(int cur,int state,vector<int> w)
{
    int t=Hash(cur,state);
    if(h[cur][t]==-1) {
        h[cur][t]=state;
        v[cur][t]=w;
        q[cur][++cnt[cur]]=t;
    }   
    else v[cur][t]=add(v[cur][t],w);
}

int get(int state,int k) // 返回 state 在四进制表示下第 k 位的数 (k 从 0 开始)。 
{
    return state>>(k*2)&3;
}
int set(int k,int v) // 构造一个第 k 位 是 v，其余位是 0 的数。 
{
    return v * (1<<k*2);
}

int n,m; 
int a[N][20]; // 保存棋盘的信息。
// tips : 能走的设成 1 , 不能走的为 0 , 这样刚好边界也是不可走的。

int main()
{
//	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
    int i,j,k;
    int x,y;
    m=4;
    
    for(n=1;n<=1000;n++) {
    	memset(a,0,sizeof a);
	    for(i=1;i<=n;i++) 
			for(j=1;j<=m;j++) 
				a[i][j]=1;

	    int cur=0,lt,state;
	    vector<int> w; w.push_back(1);
	    vector<int> ans; ans.push_back(0);
	    memset(h,-1,sizeof h);
	    insert(cur,0,w);
	    for(i=1;i<=n;i++) {
	        // 把所有状态左移 1 位 (4 进制)
	        // 因为上一行的最后一个变成当前行的第一个，并且 上一行的最后一个 肯定为 0。  
	        for(j=1;j<=cnt[cur];j++)
	            h[cur][q[cur][j]]<<=2;
	
	        // 枚举每一个格子 (阶段) 
	        for(j=1;j<=m;j++) {
	            lt=cur,cur^=1; // 滚动 
	
	            cnt[cur]=0; // 清空队列和哈希表！！ 
	            memset(h[cur],-1,sizeof h[cur]);
	
	            // 枚举上一个阶段的每一个状态，并转移。
	            for(k=1;k<=cnt[lt];k++) {
	
	                state=h[lt][q[lt][k]],w=v[lt][q[lt][k]];
	                x=get(state,j-1),y=get(state,j);
	
	                if(!a[i][j]) { // 如果当前的格子不能走.
	                    // 那么只有没有走的状态有用。 
	                    if(x==0&&y==0) insert(cur,state,w);
	                }
	                // 否则当前格子就是可以走。
	
	                else if(x==0&&y==0) {
	                    if(a[i+1][j]&&a[i][j+1])
	                        insert(cur,state+set(j-1,1)+set(j,2),w);
	                    // 新增两个往 下面 和 右边 走的回路。 
	                }
	                else if(x!=0&&y==0) {
	                    if(a[i+1][j]) insert(cur,state,w); // 往下面走。 
	                    if(a[i][j+1]) insert(cur,state-set(j-1,x)+set(j,x),w); // 往右边走。 
	                }
	                else if(x==0&&y!=0) {
	                    if(a[i+1][j]) insert(cur,state-set(j,y)+set(j-1,y),w); // 往下面走。 
	                    if(a[i][j+1]) insert(cur,state,w); // 往右边走。 
	                }
	                else if(x==1&&y==1) {
	                    for(int u=j+1,s=1;u<=m;u++) { // 找到 j 匹配的右括号。 
	                        if(get(state,u)==1) s++;
	                        else if(get(state,u)==2) {
	                            s--;
	                            if(s==0) {
	                                insert(cur,state-set(j-1,1)-set(j,1)-set(u,2)+set(u,1),w); // 找到了。 
	                                break;
	                            }
	                        }
	                    }
	                }
	                else if(x==2&&y==1) insert(cur,state-set(j-1,x)-set(j,y),w);
	                else if(x==2&&y==2) {
	                    for(int u=j-2,s=1;u>=1;u--) {
	                        if(get(state,u)==2) s++;
	                        else if(get(state,u)==1) {
	                            s--;
	                            if(s==0) {
	                                insert(cur,state-set(j-1,2)-set(j,2)-set(u,1)+set(u,2),w);
	                                break;
	                            }
	                        } 
	                    }
	                }
	                else if(x==1&&y==2) { // 终结 
	                    if(i==n&&j==m)
	                        ans=add(ans,w);
	                }
	            }   
	        }
	    }
	    ans=add(ans,ans);
		output(ans);
		printf("LL,");
		cerr<<n<<endl;
	}

    return 0;
}


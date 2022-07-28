#include<set>
#include<map>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<bitset>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=400000+5,INF=0x3f3f3f3f;

int n,m;
int a[181][81];

int h[2][N],v[2][N],q[2][N],cnt[2];
char tt;
int Hash(int cur,int t)
{
	int u=t%N;
	while(~h[cur][u] && h[cur][u]!=t)
		if(++u==N) u=0;
	return u;
}
bool check(int state);
inline void insert(int cur,int state,int val)
{
	if(!check(state)) {
//		printf("here %c\n",tt);
		return;
	}
	int u=Hash(cur,state);
	if(~h[cur][u])
		v[cur][u]=max(v[cur][u],val);
	else h[cur][u]=state,v[cur][u]=val,q[cur][++cnt[cur]]=u;
}

int ask(int x,int y) { return (x>>2*y)&3; }
int make(int j,int t) { return t<<(2*j); }

int find(int state,int j,int dec,int val)
{
	for(int s=0,u;;j+=dec) {
		u=ask(state,j);
		if(u==0) continue;
		else if(u==val) {
			s--;
			if(s==0) return j;
		}
		else s++;
	}
	return -1;
}
bool check(int state)
{
	int j,k,s=0;
	for(j=0;j<=m;j++) {
		k=ask(state,j);
		if(k==1) s++;
		else if(k==2) {
			if(s>0) s--;
			else return false;
		}
	}
	if(s>0) return false;
	else return true;
}


int ans=-INF;

int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k;
	int x,y,z;
	
	cin>>n>>m;
	for(i=0;i<n;i++) 
		for(j=0;j<m;j++) 
			cin>>a[i][j];
	
	int cur=0,lt,state,w;
	memset(h[cur],-1,sizeof h[cur]);
	insert(cur,0,0);
	for(i=0;i<n;i++) {
		// 1.roll
		// 把所有状态左移 1 位 (4 进制)
        // 因为上一行的最后一个变成当前行的第一个，并且 上一行的最后一个 肯定为 0。  
		for(j=1;j<=cnt[cur];j++) 
			h[cur][q[cur][j]]<<=2;
		
		// 枚举每一个格子 (阶段) 
		for(j=0;j<m;j++) {
			lt=cur,cur^=1; // 滚动。
			cnt[cur]=0; // 清空队列和哈希表。 
			memset(h[cur],-1,sizeof h[cur]);
			
			for(k=1;k<=cnt[lt];k++) {
				state=h[lt][q[lt][k]],w=v[lt][q[lt][k]]; // 取出状态。 
				x=ask(state,j),y=ask(state,j+1); // 左边和上面。 
				
				// 分类讨论: tips 
					// 1. 优先讨论有 0 的状态。 
					// 2. 对于所有没有 0 的状态，优先讨论 x!=y 。
					// 3. 最后讨论 x==y
					// ads : 1. 这样刚好把第一行的字母讨论完
					//       2. 先易后难。 
				
				// A.若 x==0 && y==0 , 则 	
					// (1) 若经过该格子，则必有向右和向上的边。
					// (2) 若不经过，原封不动。
					
			 	if(x==0 && y==0) {
			 		tt='A';
			 		if(i+1<n && j+1<m) insert(cur,state+make(j,1)+make(j+1,2),w+a[i][j]);
			 		insert(cur,state,w);
				} 
				
				// B.若 x!=0 && y==0,则必经过该格子。
				// 1. 该路径向下延展。
				// 2. 该路径向右延展。
				
				else if(x!=0 && y==0) {tt='B';
					// down
					if(i+1<n) insert(cur,state,w+a[i][j]);
					// right
					if(j+1<m) insert(cur,state-make(j,x)+make(j+1,x),w+a[i][j]);
				}   
				
				// C.若 x==0 && y!=0  ,与 B 类相同。
				
				else if(x==0 && y!=0) {tt='C';
					// down 
					if(i+1<n) insert(cur,state-make(j+1,y)+make(j,y),w+a[i][j]);
					// right
					if(j+1<m) insert(cur,state,w+a[i][j]);
				} 
				
				// D. 若 x==2 且 y==1
				// 则前手后尾相接，除去插头即可。 
				else if(x==2 && y==1) 
					tt='D',insert(cur,state-make(j,x)-make(j+1,y),w+a[i][j]);
				
				// E. 若 x==1 且 y==2;
				// 则 x,y 联通
				// (1) 若有其他插头则无论联不联通 该状态均不合法。
				// (2) 若无，则连上此插头，一个回路形成。
				
				else if(x==1 && y==2) {tt='E';
					if(state-make(j,x)-make(j+1,y)==0)
						ans=max(ans,w+a[i][j]);	
				}
				
				// F. 若 x==1 && y==1
				
				else if(x==1 && y==1) {tt='F';
					z=find(state,j+1,1,2);
					insert(cur,state-make(j,1)-make(j+1,1)-make(z,2)+make(z,1),w+a[i][j]);
				}
				
				// G. 若 x==2 && y==1
				
				else if(x==2 && y==2) {tt='G';
					z=find(state,j,-1,1);
					insert(cur,state-make(j,2)-make(j+1,2)-make(z,1)+make(z,2),w+a[i][j]);
				} 
			}
			
//			cerr<<cnt[cur]<<endl;
		}
	}
	
	cout<<ans<<endl;
	return 0;
}

// DeBug
// 1. i,j 混用。  解决 ： make(j,t); 
// 2. 最开始也要初始化 哈希表，每到一个新的格子也要初始化。 
// 3. j+1 写成 j 了。
// 4. find 有 0,1,2 三种元素，要先把 0 判掉，再判断， 别用 !=
// 5. cnt[cur]=0; // 清空队列和哈希表。 
// 6. 				// 分类讨论: tips 
					// 1. 优先讨论有 0 的状态。 
					// 2. 对于所有没有 0 的状态，优先讨论 x!=y 。
					// 3. 最后讨论 x==y
					// ads : 1. 这样刚好把第一行的字母讨论完
					//       2. 先易后难。 
// 7. find 里不用设置 j 的范围，这样要是状态不合法，也能发现， 

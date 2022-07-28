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

const unsigned P=199999;
const int INF=1e9+5;
const int dx[]={1,-1,0,0},dy[]={0,0,1,-1};
// 123804765
const int aim[]={4,0,1,2,5,8,7,6,3};

struct HashExcel
{
	int one[P],idx;
	unsigned ver[P];
	int Next[P],step[P];
	void insert(unsigned x,int st)
	{
		unsigned u=x%P;
		for(int i=one[u];i;i=Next[i]) 
			if(ver[i]==x) {
				step[i]=st;
				return;
			}
		Next[++idx]=one[u],one[u]=idx;
		ver[idx]=x,step[idx]=st;
	}
	int query(unsigned x)
	{
		unsigned u=x%P;
		for(int i=one[u];i;i=Next[i]) 
			if(ver[i]==x) return step[i];
		return INF;
	}
}H;

int op[20][4];

int A(int *arr)
{
	int i,res=0;
	for(i=0;i<9;i++) 
		res+=abs(aim[arr[i]]/3-i/3)+abs(aim[arr[i]]%3-i%3);
	return res;
}

struct Node
{
	int a[10];
	int step,Astep;
	unsigned Hash()
	{	
		unsigned res=0;
		for(int i=0;i<9;i++)
			res=res*10u+a[i];
		return res;
	}
	bool operator<(const Node &t) const
	{
		return Astep>t.Astep;
	}
	Node() { memset(a,0,sizeof a),Astep=0; }
};

priority_queue<Node> q;
int bfs(Node state)
{
	while(q.size()) q.pop();
	unsigned h;
	int i;
	int x,y,z;
	q.push(state); 
	H.insert(state.Hash(),0);
	while(q.size()) {
		state=q.top(); q.pop();
		for(i=0;i<9;i++) 
			if(state.a[i]==0) {
				x=i;
				break;
			}
		for(i=0;i<4;i++) {
			if(op[x][i]!=-1) {
				y=op[x][i];
				swap(state.a[x],state.a[y]);
				z=A(state.a);
				if(z==0) return state.step+1;
				state.Astep=z+state.step;
				h=state.Hash();
				if(H.query(h)==INF) {
					H.insert(h,state.step+1);
					state.step++;
					q.push(state);
					state.step--;
				}
				swap(state.a[x],state.a[y]);
			} 
		}
	}	
	return -1;
}

int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k,x,y;
	Node st;
	for(i=0;i<3;i++) 
		for(j=0;j<3;j++) 
			st.a[i*3+j]=getchar()-'0';
	st.Astep=A(st.a);
	st.step=0;
	if(st.Astep==0) {
		printf("0\n");
		return 0;
	}
	memset(op,-1,sizeof op);
	// 预处理出所有的操作 
	for(i=0;i<3;i++) 
		for(j=0;j<3;j++) 
			for(k=0;k<4;k++) {
				x=i+dx[k],y=j+dy[k];
				if(x<3&&x>=0&&y<3&&y>=0) 
					op[i*3+j][k]=x*3+y;
			}
	printf("%d\n",bfs(st));
	return 0;
}

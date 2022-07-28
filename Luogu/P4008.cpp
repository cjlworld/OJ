#include<set>
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
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
#define Debug(x) cout<<#x<<" : "<<x<<endl
void ldr(int now);
void print();

const int N=4e6+5;

struct Node
{
	int ch[2],p;
	char c;
	int size;
	void clear() 
	{
		c='\0'; p=size=0;
		memset(ch,0,sizeof ch);	
	}
}t[N];

int root,idx;
int del[N],dtop=0;

int GetNode() { return (dtop) ? del[dtop--] : ++idx; }
void pushup(int x) { t[x].size=t[t[x].ch[0]].size+t[t[x].ch[1]].size+1; }

void rotate(int x)
{
	int y=t[x].p,z=t[y].p;
	int k=(t[y].ch[1]==x);
	
	t[z].ch[t[z].ch[1]==y]=x; t[x].p=z;
	t[y].ch[k]=t[x].ch[k^1]; t[t[x].ch[k^1]].p=y;
	t[x].ch[k^1]=y; t[y].p=x;
	pushup(y); pushup(x);
	return;
}

void splay(int x,int top)
{
	int y,z;
	while(t[x].p!=top) {
		y=t[x].p; z=t[y].p;
		if(z!=top) {
			if((t[y].ch[1]==x)^(t[z].ch[1]==y)) rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
	if(!top) root=x;
	return;
}

int get_k(int rank)
{
	int x=root,tmp;
	while(rank&&x) {
		tmp=t[t[x].ch[0]].size+1; // 根节点在当前子树中的排名 
		if(tmp==rank) return x;
		else if(rank<tmp) x=t[x].ch[0];
		else rank-=tmp,x=t[x].ch[1];  
	}
	printf("get_k() has an error ! \n");
	return -1;
}
char a[N];
stack<int> S;
int Build(int len)
{
	int v,i;
	while(S.size()) S.pop();
	for(i=1;i<=len;i++) {
		v=GetNode();
		t[v].c=a[i];
		S.push(v);
	}
	while(S.size()) {
		v=S.top(); S.pop();
		pushup(v);
		if(S.size()) t[v].p=S.top(),t[S.top()].ch[1]=v;
		else return v;
	}
	return 0;
}

void ldr(int now)
{
	if(!now) return;
	ldr(t[now].ch[0]);
	putchar(t[now].c);
	ldr(t[now].ch[1]);
	return;
}

void recycle(int now)
{
	if(!now) return;
	recycle(t[now].ch[0]);
	recycle(t[now].ch[1]);
	t[now].clear();
	del[++dtop]=now;
	return;
}

int n;
int it=1; 
// it 表示的是光标之前的那个字符在序列(哨兵也计算在内)中的下标 
#define deal t[t[root].ch[1]].ch[0]
int main()
{
	int i,len;
	char opt[20],c;
	
	scanf("%d",&n);
	a[1]=' '; a[2]=' '; 
	root=Build(2); // 加入两个哨兵，便于处理边界条件
	while(n--) {
		scanf("%s",opt);
		if(!strcmp(opt,"Insert")) {
			scanf("%d",&len);
			for(i=1;i<=len;) {
				c=getchar();
				if(32<=c&&c<=126) a[i]=c,i++;
			}
			splay(get_k(it),0);
			splay(get_k(it+1),root);
			deal=Build(len);
			t[deal].p=t[root].ch[1];
			pushup(t[root].ch[1]); pushup(root);
		}
		else if(!strcmp(opt,"Delete")) {
			scanf("%d",&len);
			splay(get_k(it),0); 
			splay(get_k(it+len+1),root);
			recycle(deal);
			deal=0;
			pushup(t[root].ch[1]); pushup(root);
		}
		else if(!strcmp(opt,"Get")) {
			scanf("%d",&len);
			
			splay(get_k(it),0);
			splay(get_k(it+len+1),root);
			
			ldr(deal);
			printf("\n");
		}
		else if(!strcmp(opt,"Move")) 
			scanf("%d",&it),it++; // 加上哨兵的贡献 
		else if(!strcmp(opt,"Prev")) it--;
		else it++;
	}
	return 0;
}
// Debug
// 1. 加入/删除区间后忘记pushup , 注意要pushup两次 
// 2. rotate 的 t[t[z].ch[1]==y]=x; 写错了，<--- 是对的
// 3. 加入的缓冲区开小了 


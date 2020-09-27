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
//	if(x==-1) printf("there");
	int y,z;
	while(t[x].p!=top) {
		y=t[x].p; z=t[y].p;
//		print();
		if(z!=top) {
			if((t[y].ch[1]==x)^(t[z].ch[1]==y)) rotate(x);
			else rotate(y);
		}
		rotate(x);
//		ldr(root),printf("\n");
	}
	if(!top) root=x;
//	if(x==-1) printf("here");
	return;
}

int get_k(int rank)
{
	int x=root,tmp;
	while(rank&&x) {
//		print();
		tmp=t[t[x].ch[0]].size+1; // 根节点在当前子树中的排名 
		if(tmp==rank) return x;
		else if(rank<tmp) x=t[x].ch[0];
		else rank-=tmp,x=t[x].ch[1];  
	}
	printf("get_k() has an error ! \n");
	return -1;
}

char a[N];

void Build(int &now,int l,int r,int fa)
{
	if(l>r) { now=0; return; }
	
	now=GetNode();
	int mid=(l+r)>>1;	
	t[now].c=a[mid];
	t[now].p=fa;
	
	Build(t[now].ch[0],l,mid-1,now);
	Build(t[now].ch[1],mid+1,r,now);
	
	pushup(now);
}

//void Build(int &now,int l,int r,int fa)
//{
//	int v,i;
//	for(i=l;i<=r;i++) {
//		v=GetNode();
//		if(i==l) now=v;
//		t[v].c=a[i];
//		t[v].size=r-i+1;
//		t[v].p=fa; t[fa].ch[1]=v;
//		fa=v;
//	}
//	return;
//}

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
void print()
{
	printf("\nnew Case : \n");
	for(int i=1;i<=idx;i++) 
		if(t[i].c!='\0') {
//			printf("%d %d\n%d %d\n",i,t[i].ch[0],i,t[i].ch[1]);
			printf("%d : size = %d , lc = %d , rc = %d,father = %d , char = %c\n"
				,i,t[i].size,t[i].ch[0],t[i].ch[1],t[i].p,t[i].c);
		}
			
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	int i,len;
	char opt[20],c;
	
	scanf("%d",&n);
	a[1]=' '; a[2]=' '; 
	Build(root,1,2,0); // 加入两个哨兵，便于处理边界条件 
//	Debug(root);
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
			Build(deal,1,len,t[root].ch[1]);
//			ldr(root); printf("\n");
			pushup(t[root].ch[1]); pushup(root);
//			print();
//			cout<<it<<endl;
//			ldr(root),printf("\n");
//			Debug(root);
		}
		else if(!strcmp(opt,"Delete")) {
//			ldr(root),printf("\n");
			
			scanf("%d",&len);
			
			splay(get_k(it),0); 
//			print();
//			ldr(root),printf("\n");
			splay(get_k(it+len+1),root);
//			print();
			recycle(deal);
			deal=0;
			pushup(t[root].ch[1]); pushup(root);
			
//			ldr(root),printf("\n");
//			Debug(root);
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
//		ldr(root),printf("\n");
	}
	return 0;
}
// Debug
// 1. 加入/删除区间后忘记pushup , 注意要pushup两次 
// 2. rotate 的 t[t[z].ch[1]==y]=x; 写错了，<--- 是对的
// 3. 加入的缓冲区开小了 

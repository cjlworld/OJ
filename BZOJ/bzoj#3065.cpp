#include<cmath>
#include<vector>
#include<cstdio>
#include<iostream>
#include<algorithm>

using namespace std;

const int N=2e5+5;

struct Node
{
	int ch[2],fa;
	int siz;
}t[N];
int root=1,idx=2;
inline void pushup(int x)
{
	t[x].siz=t[t[x].ch[0]].siz+t[t[x].ch[1]].siz+1;
}

void rotate(int x)
{
	int y=t[x].fa,z=t[y].fa;
	int k=(t[y].ch[1]==x);
	if(z) t[z].ch[t[z].ch[1]==y]=x;
	t[x].fa=z;
	t[y].ch[k]=t[x].ch[k^1]; t[t[x].ch[k^1]].fa=y;
	t[x].ch[k^1]=y; t[y].fa=x;
	pushup(y); pushup(x);
}

void splay(int x,int top=0)
{
	int y,z;
	while(t[x].fa!=top) {
		y=t[x].fa; z=t[y].fa;
		if(z^top) {
			if((t[z].ch[1]==y)^(t[y].ch[1]==x))
				rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
	if(!top) root=x;
//	if(root==-1) printf("here");
}

int get_k(int k)
{
	int now=root,y;
	while(now) {
		y=t[t[now].ch[0]].siz;
		if(y+1==k) return now;
		else if(y+1>k) now=t[now].ch[0];
		else k=k-y-1,now=t[now].ch[1];
	}
//	printf("here");
	return -1;
}

bool cmp(const int& a,const int& b) // x<y
{
	splay(a);
	int x=t[t[a].ch[0]].siz;
	splay(b);
	int y=t[t[b].ch[0]].siz;
	return x<y;
}

namespace Vtree
{
	void print(vector<int>& v)
	{
		for(int i=0;i<(int)v.size();i++) 	
			printf("%d ",v[i]);
		printf("\n");
	}
	void ins(vector<int>& v,int x) 
	{	
//		int i;
//		for(i=0;i<(int)v.size();i++) 
//			if(cmp(x,v[i])) break;
//		v.insert(v.begin()+i,x);
		v.insert(lower_bound(v.begin(),v.end(),x,cmp),x); 
	}
	void del(vector<int>& v,int x) { v.erase(lower_bound(v.begin(),v.end(),x,cmp)); }
	int count(vector<int>& v,int l,int r)
	{
//		printf("count(%d ,%d) : ",l,r);
//		print(v);
		return upper_bound(v.begin(),v.end(),r,cmp)-lower_bound(v.begin(),v.end(),l,cmp);
	}	
}

int num=70005;
vector<int> v[N];

inline int lowbit(int x) { return x&(-x); }
void insert(int pos,int key)
{
	key++;
	for(;key<=num;key+=lowbit(key)) {
//		printf("insert in v[%d], pos = %d\n",key,pos);
//		Vtree::print(v[key]);
		Vtree::ins(v[key],pos);
	}		
}
void erase(int pos,int key)
{
	key++;
	for(;key<=num;key+=lowbit(key)) //Vtree::print(v[key]),
		Vtree::del(v[key],pos);
}
int Rank(int x,int l,int r)
{
//	printf("Rank val %d in (%d , %d) = ",x,l,r);
	int res=0; x++;
	for(;x>=1;x-=lowbit(x)) 
		res+=Vtree::count(v[x],l,r);
//	printf("%d\n",res);
	return res;
}
int findkth(int k,int l,int r)
{
	static const int lgn=log2(num);
	int key=0,sum=0;
	for(int i=lgn,y;i>=0;i--) {
	//	printf("count in v[%d], (%d ,%d)\n",key+(1<<i),l,r);
		y=Vtree::count(v[key+(1<<i)],l,r);
		if(sum+y<k && key+(1<<i)<=num) {
			sum+=y,key+=(1<<i);
	//		printf("Accept %d , now key is %d and sum is %d\n",y,key,sum);
		}
	}
	return key+1-1;
}

int NewNode(int pos)
{
//	printf("NewNode (pos = %d) while the size of tree is %d\n",pos,t[root].siz);
	idx++;
	t[idx].siz=1;
	t[idx].ch[0]=t[idx].ch[1]=0;
	splay(get_k(pos));
	splay(get_k(pos+1),root);
	t[t[root].ch[1]].ch[0]=idx;
	t[idx].fa=t[root].ch[1];
	pushup(t[root].ch[1]); pushup(root);
	splay(idx);
	return idx;
}

int FindNode(int pos)
{
	splay(get_k(pos+1));
	return root;
}

int n,m,lastans;
vector<int> a;

int main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	int i;
	int x,y,z;
	char opt[2];
	
	scanf("%d",&n);
	t[1].siz=2; t[1].ch[0]=0; t[1].ch[1]=2; t[1].fa=0;
	t[2].siz=1; t[2].ch[0]=0; t[2].ch[1]=0; t[2].fa=1;
	
	a.push_back(0);
	for(i=1;i<=n;i++) {
		scanf("%d",&x);
		a.push_back(x);
		insert(NewNode(i),a[i]);
//		cerr<<i<<endl;
	}
	
	scanf("%d",&m);

	while(m--) {
//		if(m%1000==0) cerr<<m<<endl;
		scanf("%s",opt);
		if(*opt=='Q') {
			scanf("%d%d%d",&x,&y,&z);
			x^=lastans,y^=lastans,z^=lastans;
			printf("%d\n",lastans=findkth(z,get_k(x+1),get_k(y+1)));
		}
		else if(*opt=='M') {
			scanf("%d%d",&x,&y);
			x^=lastans,y^=lastans;
			erase(FindNode(x),a[x]);
			insert(FindNode(x),a[x]=y);
		}
		else if(*opt=='I') {
			scanf("%d%d",&x,&y);
			x^=lastans,y^=lastans;
			insert(NewNode(x),y);
			a.insert(a.begin()+x,y);
		}
	}
	return 0;
}

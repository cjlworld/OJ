#include<vector>
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define LL long long
#define rint register int
using namespace std;
const int N=5e4+5;
namespace FastIO
{
char c;
bool sign;
template<class T>
inline void read(T &x)
{
	x=0;
	sign=false;
	for(c=getchar();c<'0'||c>'9';c=getchar()) 
		if(c=='-') 
			sign=true;
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+(c&15);
	if(sign) x=~x+1;
 	return;
}
template<class T>
void print(T x)
{
	if(x<0) putchar('-'),x=~x+1;
	if(x>9) print(x/10);
	putchar(x%10+'0');
	return;
}
}
using FastIO::read;
using FastIO::print;
//================================================
//template<class T>
//struct fhqtreap 
//{
//	fhqtreap() 
//	{ 
//		root=NULL; 
//		return;  
//	}
//	#define siz(x) ((x==NULL) ? 0 : x->size)
//	struct Node 
//	{
//		T val;
//		unsigned int size;
//		unsigned int pri;
//		Node *lc,*rc;
//		Node(T val) : val(val) { pri=rand(); lc=rc=NULL; size=1; return; }
//		inline void update() 
//		{
//			size=siz(lc)+siz(rc)+1;
//			return;
//		}
//		inline T begin()
//		{
//			Node *now=this;
//			while(now->lc != NULL) 
//				now = now->lc;
//			return now->val;
//		}
//		inline T end()
//		{
//			Node *now=this;
//			while(now->rc != NULL)
//				now = now->rc;
//			return now->val; 
//		}
//	};
//	Node *root;
//	inline Node* newnode(const T &key) 
//	{
//		return (new Node(key));
//	}
//	void split(Node *now,const T &key,Node *&x,Node *&y) //<= >
//	{
//		if(now==NULL) 
//		{
//			x = y = NULL;
//			return;
//		}
//		if(now->val <= key) 
//		{
//			x = now;
//			split(now->rc,key,x->rc,y);
//			x->update();
//		} 
//		else 
//		{
//			y = now;
//			split(now->lc,key,x,y->lc);
//			y->update();
//		}
//		return;
//	}
//	Node* merge(Node *x,Node *y) 
//	{
//		if(x==NULL) return y;
//		if(y==NULL) return x;
//		if(x->pri > y->pri) 
//		{
//			x->rc = merge(x->rc,y);
//			x->update();
//			return x;
//		} 
//		else {
//			y->lc = merge(x,y->lc);
//			y->update();
//			return y;
//		}
//	}
//	void insert(const T &key) 
//	{
//		Node *x,*y;
//		split(root,key,x,y);
//		root = merge(merge(x,newnode(key)),y);
//		return;
//	}
//	void erase(const T &key) 
//	{
//		Node *x,*y,*z;
//		split(root,key,x,z);
//		split(x,key-1,x,y);
//		if(y!=NULL)
//			y = merge(y->lc,y->rc);
//		x = merge(x,y);
//		root = merge(x,z);
//		return;
//	}
//	T Getnum(int rank) 
//	{
//		Node *now = root;
//		while(rank>0&&now!=NULL) 
//		{
//			if(siz(now->lc)+1==rank)
//				break;
//			if(siz(now->lc)+1 > rank)
//				now = now->lc;
//			else
//				rank-=siz(now->lc)+1,now = now->rc;
//		}
//		return (now==NULL) ? 0 : now->val;
//	}
//	int Getrank(const T &key) 
//	{
//		Node *x,*y,*z;
//		split(root,key-1,x,y);
//		int tmp = siz(x)+1;
//		root = merge(x,y);
//		return tmp;
//	}
//	T Getpre(const T &key) 
//	{
//		Node *x,*y,*z;
//		split(root,key-1,x,y);
//		Node *now = x;
//		if(now==NULL)
//			return 1e7;
//		while(now->rc!=NULL)
//			now = now->rc;
//		root = merge(x,y);
//		return now->val;
//	}
//	T Getsuf(const T &key) 
//	{
//		Node *x,*y,*z;
//		split(root,key,x,y);
//		Node *now = y;
//		if(now==NULL)
//			return -1e7;
//		while(now->lc!=NULL)
//			now = now->lc;
//		root = merge(x,y);
//		return now->val;
//	}
//	int count(const T &key)
//	{
//		Node *x,*y,*z;
//		split(root,key-1,x,z);
//		split(z,key,y,z);
//		int tmp = siz(y);
//		z=merge(y,z);
//		root=merge(x,z);
//		return tmp;
//	}
//	void clear()
//	{
//		root = NULL;
//		return;
//	}
//	int size()
//	{
//		return siz(root);
//	}
//	int between(const T &key1,const T &key2)
//	{
//		Node *x,*y,*z;
//		split(root,key1-1,x,z);
//		split(z,key2,y,z);
//		int tmp = siz(y);
//		z = merge(y,z);
//		root = merge(x,z);
//		return tmp;
//	}
//	T begin()
//	{
//		Node *now = root;
//		if(now==NULL)
//			return -1;
//		while(now->lc != NULL) 
//			now = now->lc;
//		return now->val;
//	}
//	T end() 
//	{
//		Node *now = root;
//		if(now==NULL) 
//			return -1;
//		while(now->rc != NULL) 
//			now = now->rc;
//		return now->val;
//	}
//	bool empty() 
//	{
//		return (root == NULL);
//	}
//	bool find(const T &key) 
//	{
//		if(count(key)==0) 
//			return false;
//		return true;
//	}
//};
//fhqtreap<int> t[4*N];
struct Lazytree
{
	vector<int> v;
	Lazytree() { v.clear(); }
	inline void insert(int key) { v.insert(lower_bound(v.begin(),v.end(),key),key); }
	inline void erase(int key) { v.erase(lower_bound(v.begin(),v.end(),key)); }
	inline int between(int x,int y) { return (int)(upper_bound(v.begin(),v.end(),y)-lower_bound(v.begin(),v.end(),x));}
}t[N<<3];
const int INF=2147483647;
void Insert(int now,const int &pos,const int &key,int l,int r)
{
	t[now].insert(pos);
	if(l==r) return;
	int mid=(l+r)>>1;
	if(key<=mid) Insert(now<<1,pos,key,l,mid);
	else Insert(now<<1|1,pos,key,mid+1,r);
	return;
}
void Erase(int now,const int &pos,const int &key,int l,int r)
{
	t[now].erase(pos);
	if(l==r) return;
	int mid=(l+r)>>1;
	if(key<=mid) Erase(now<<1,pos,key,l,mid);
	else Erase(now<<1|1,pos,key,mid+1,r);
}
int Getrank(int now,const int &key,const int &x,const int &y,int l,int r)
{
	if(l==r) return 1;
	int mid=(l+r)>>1;
	if(key<=mid) return Getrank(now<<1,key,x,y,l,mid);
	else return Getrank(now<<1|1,key,x,y,mid+1,r)+t[now<<1].between(x,y);
}
int Getnum(int now,int rank,const int &x,const int &y,int l,int r)
{
	if(l==r) return l; 
	int tmp=t[now<<1].between(x,y);
	int mid=(l+r)>>1;
	if(tmp>=rank) 
		return Getnum(now<<1,rank,x,y,l,mid);
	else return Getnum(now<<1|1,rank-tmp,x,y,mid+1,r);
}
int Find(int now,const int &x,const int &y,const int &key,int l,int r)
{
	if(l==r) return t[now].between(x,y);
	int mid=(l+r)>>1;
	if(key<=mid) return Find(now<<1,x,y,key,l,mid);
	else return Find(now<<1|1,x,y,key,mid+1,r);
}
struct quiz
{
	int opt;
	int x,y,z;
}q[N];
vector<int> v;
int a[N];
int n,m;
int main()
{
//	freopen("1.in","r",stdin);
	rint i;
	rint tmp;
	read(n); read(m);
	for(i=1;i<=n;i++) {
		read(a[i]);
		v.push_back(a[i]);
	}
	for(i=1;i<=m;i++) {
		read(q[i].opt);
		read(q[i].x); read(q[i].y);
		if(q[i].opt!=3) 
			read(q[i].z);
		if(q[i].opt==1||q[i].opt==4||q[i].opt==5) 
			v.push_back(q[i].z);
		if(q[i].opt==3) 
			v.push_back(q[i].y);
	}
	sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
	for(i=1;i<=n;i++) 
		a[i]=(int)(lower_bound(v.begin(),v.end(),a[i])-v.begin())+1;
	for(i=1;i<=m;i++) {
		if(q[i].opt==3) 
			q[i].y=(int)(lower_bound(v.begin(),v.end(),q[i].y)-v.begin())+1;
		if(q[i].opt==1||q[i].opt==4||q[i].opt==5) 
			q[i].z=(int)(lower_bound(v.begin(),v.end(),q[i].z)-v.begin())+1;
	}
	for(i=1;i<=n;i++) 
		Insert(1,i,a[i],1,v.size());
	for(i=1;i<=m;i++) {
		if(q[i].opt==1) 
			print(Getrank(1,q[i].z,q[i].x,q[i].y,1,v.size()));
		else if(q[i].opt==2) 
			print(v[Getnum(1,q[i].z,q[i].x,q[i].y,1,v.size())-1]);
		else if(q[i].opt==3) 
			Erase(1,q[i].x,a[q[i].x],1,v.size()),Insert(1,q[i].x,q[i].y,1,v.size()),a[q[i].x]=q[i].y;
		else if(q[i].opt==4) {
			tmp=Getrank(1,q[i].z,q[i].x,q[i].y,1,v.size());
			if(tmp==1) 
				print(-INF);
			else print(v[Getnum(1,tmp-1,q[i].x,q[i].y,1,v.size())-1]);
		}
		else if(q[i].opt==5) {
			tmp=Getrank(1,q[i].z,q[i].x,q[i].y,1,v.size());
			if(tmp==q[i].y-q[i].x+2) 
				print(INF);
			else print(v[Getnum(1,tmp+Find(1,q[i].x,q[i].y,q[i].z,1,v.size()),q[i].x,q[i].y,1,v.size())-1]);
		}
		if(q[i].opt!=3) 
			putchar('\n');
	}
	return 0;
}


#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
const int INF=0x3f3f3f3f;
struct node
{
	int lc,rc;
	int pri;//rand();
	int key;
	int size;
	int cnt;//note the repeat
	#define lc(x) t[x].lc //left child
	#define rc(x) t[x].rc //right child
	#define v(x) t[x].key 
	#define p(x) t[x].pri
	#define c(x) t[x].cnt
	#define s(x) t[x].size
};
node t[N];
int pool=0;
int root=0;
int n;
inline void update(const int &k) 
{
	t[k].size=t[t[k].lc].size+t[t[k].rc].size+t[k].cnt;
	return;
}
inline void Zig(int &k) //right turn;
{
	int y=lc(k);
	lc(k)=rc(y);
	rc(y)=k;
	s(y)=s(k);
	update(k);
	k=y;
	return;
}
inline void Zag(int &k) //left turn;
{
	int y=rc(k);
	rc(k)=lc(y);
	lc(y)=k;
	s(y)=s(k);
	update(k);
	k=y;
	return;
}
inline void insert(int &k,const int &key)
{
	if(!k) {
		k=++pool;
		v(k)=key;
		p(k)=rand();
		c(k)=s(k)=1;
		lc(k)=rc(k)=0;
		return;
	}
	else ++s(k);
	if(v(k)==key) ++c(k);
	else if(key<v(k)) {
		insert(lc(k),key);
		if(p(lc(k))<p(k)) Zig(k); 
	}
	else {
		insert(rc(k),key);
		if(p(rc(k))<p(k)) Zag(k);
	}
	return;
}
inline void remove(int &k,const int &key)
{
	if(v(k)==key) {
		if(t[k].cnt>1) --t[k].cnt,--t[k].size;//repeat numbers;
		else if(!t[k].lc||!t[k].rc) k=t[k].lc+t[k].rc; //list node
		else if(t[t[k].lc].pri<t[t[k].rc].pri) Zig(k),remove(k,key);
		else Zag(k),remove(k,key);
		return;
	}
	--s(k); //maintenance size;
	if(key<t[k].key) remove(t[k].lc,key);
	else remove(t[k].rc,key);
	return; 
}
inline int Query_pre(const int &key)
{
	int x=root,res=-INF;
	while(x) {
		if(t[x].key<key) res=t[x].key,x=t[x].rc;
		else x=t[x].lc; 
	}
	return res;
}
inline int Query_suf(const int &key) 
{
	int x=root,res=INF;
	while(x) {
		if(v(x)>key) res=v(x),x=lc(x);
		else x=rc(x);
	}
	return res;
}
inline int Query_kth(int k) //search for the key of the node in the no.k place;
{
	int x=root;
	while(x) {
		if(s(lc(x))<k&&s(lc(x))+c(x)>=k) return v(x);
		if(s(lc(x))>=k) x=lc(x);
		else k-=s(lc(x))+c(x),x=rc(x);
	}
	return 0;
}
inline int Query_rank(const int &key) //search for the rank of the node whose data is key
{
	int x=root,res=0;
	while(x) {
		if(key==v(x)) return res+s(lc(x))+1;
		if(key<v(x)) x=lc(x);
		else res+=s(lc(x))+c(x),x=rc(x);
	}
	return res;
}
/*
1、插入 x 数；
2、删除 x 数（若有多个相同的数，因只删除一个）；
3、查询 x 数的排名（若有多个相同的数，因输出最小的排名）；
4、查询排名为 x 的数；
5、求 x 的前趋（前趋定义为小于 x，且最大的数）；
6、求 x 的后继（后继定义为大于 x，且最小的数）。
*/
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d",&n);
	int opt,x;
	for(int i=1;i<=n;i++) {
		scanf("%d%d",&opt,&x);
		switch(opt) {
			case 1 : insert(root,x); break;
			case 2 : remove(root,x); break;
			case 3 : printf("%d\n",Query_rank(x)); break;
			case 4 : printf("%d\n",Query_kth(x)); break;
			case 5 : printf("%d\n",Query_pre(x)); break;
			case 6 : printf("%d\n",Query_suf(x)); break; 
		}
	}
//	getchar();
	return 0;
}

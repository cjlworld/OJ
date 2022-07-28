#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
template<class T>
inline void read(T &x)
{
	x=0;
	char c;
	bool sign=false;
	for(c=getchar();c<'0'||c>'9';c=getchar()) 
		if(c=='-') 
			sign=true;
	for(;c>='0'&&c<='9';c=getchar()) 
		x=x*10+(c&15);
	if(sign) x=~x+1;
	return;
}
struct Node
{
	Node *ch[2];
	int size;
	int cnt;
	inline void update()
	{
		size = ch[0]->size + ch[1]->size + cnt;
		return;
	}
	Node(int siz,int cn,Node *lc,Node *rc) : size(siz) , cnt(cn) {
		ch[0]=lc;
		ch[1]=rc;
		return;
	}
};
Node *nul=new Node(0,0,NULL,NULL);
Node *root=new Node(0,0,nul,nul);
inline void insert(int *arr,int len)
{
	int i;
	Node *now=root;
	for(i=1;i<=len;i++) {
		now->size++;
		if(now->ch[arr[i]]==nul) 
			now->ch[arr[i]] = new Node(0,0,nul,nul);
		now = now->ch[arr[i]];
	}
	now->cnt++;
	now->size++;
	return;
}
inline int query(int *arr,int len)
{
	int i;
	Node *now=root;
	int res=0;
	for(i=1;i<=len;i++) {
		res+=now->cnt;
		if(now->ch[arr[i]]==nul) 
			return res;
		now = now->ch[arr[i]];
	}
	res+=now->size;
	return res;
}
int n,m;
const int N=5e5+5;
int a[N];
int len;
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	read(n); read(m);
	for(i=1;i<=n;i++) {
		read(len);
		for(j=1;j<=len;j++) 
			read(a[j]);
		insert(a,len);
	}
	for(i=1;i<=m;i++) {
		read(len);
		for(j=1;j<=len;j++) 
			read(a[j]);
		printf("%d\n",query(a,len));
	}
	return 0;
}


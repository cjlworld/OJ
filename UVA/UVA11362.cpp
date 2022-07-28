#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
inline int read(int *arr)
{
	char c;
	int i;
	for(c=getchar();c<'0'||c>'9';c=getchar());
	for(i=1;c>='0'&&c<='9';i++,c=getchar()) 	
		arr[i]=c-'0';
	return i-1;
}
int T;
int n;
int a[10005][13],len[10005];
struct Node
{
	Node *ch[10];
	int cnt;
	Node(int cn,Node *p) : cnt(cn) {
		ch[0]=ch[1]=ch[2]=ch[3]=ch[4]=ch[5]=ch[6]=ch[7]=ch[8]=ch[9]=p;
		return;
	}
};
Node *nul=new Node(0,NULL);
Node *root=new Node(0,nul);
inline void insert(const int *arr,const int &len)
{
	int i;
	Node *now=root;
	for(i=1;i<=len;i++) {
		if(now->ch[arr[i]]==nul) 
			now->ch[arr[i]]=new Node(0,nul);
		now=now->ch[arr[i]]; 
	}
	now->cnt++;
	return;
}
inline bool query(const int *arr,const int &len)
{
	int i;
	Node *now=root;
	for(i=1;i<=len;i++) {
		if(now->ch[arr[i]]==nul) 
			return false;
		if(now->cnt==1) 
			return true;
		now=now->ch[arr[i]];
	}
	return false;
}
inline void clear(Node *now)
{
	if(now==nul) return;
	if(now->cnt) now->cnt=0;
	for(int i=0;i<=9;i++) 
		clear(now->ch[i]);
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	register int i;
	scanf("%d",&T);
	while(T--) {
//		clear(root);
		root=new Node(0,nul);
		scanf("%d",&n);
		for(i=1;i<=n;i++) {
			len[i]=read(a[i]);
			insert(a[i],len[i]);
		}
		for(i=1;i<=n;i++) {
			if(query(a[i],len[i])) {
				puts("NO");
				break;
			}
		}
		if(i==n+1) 
			puts("YES");
	}
	return 0;
}


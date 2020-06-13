#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#define LL long long
#define rint register int
using namespace std;
struct ACmachine
{
	struct Node
	{
		Node *ch[26];
		Node *fail;
		int cnt;
		Node(Node *nul) : fail(nul),cnt(0) {
			for(rint i=0;i<=25;i++) 
				ch[i]=nul;
			return;
		}
	};
	Node *root,*p,*now,*v;
	ACmachine() 
	{ 
		root=new Node(NULL); 
		for(rint i=0;i<=25;i++) 
			root->ch[i]=root;
		root->cnt=0;
		root->fail=root;
		return;
	}
	inline void insert(const char *a,const int &len)
	{
		now=root;
		for(rint i=1;i<=len;i++) {
			if(now->ch[a[i]-'a']==root) 
				now->ch[a[i]-'a']=new Node(root);
			now=now->ch[a[i]-'a'];	 
		}
		now->cnt++;
		return;
	}
	inline void ACbuild()
	{
		rint i;
		queue<Node*> q;
		while(q.size()) 
			q.pop();
		for(i=0;i<=25;i++) 
			if(root->ch[i]!=root) 
				q.push(root->ch[i]);
		while(q.size()) {
			now=q.front(); q.pop();
			for(i=0;i<=25;i++) {
				if(now->ch[i]!=root) 
					now->ch[i]->fail = now->fail->ch[i] , q.push(now->ch[i]); 
				else now->ch[i] = now->fail->ch[i];
			}
		}
		return;
	}
	inline int query(const char *a,int len)
	{
		rint res=0;
		for(rint i=1;i<=len;i++) {
			now = now->ch[a[i]-'a'];
			for(v = now;v!=root&&~v->cnt;v = v->fail) {
				res+=v->cnt;
				v->cnt=-1;
			} //一定要有 ~v->cnt , 否则计算过的cnt会被重复扫描 
		}
		return res;
	}
};
ACmachine A;
const int N=1e6+5;
char a[N];
int n;
int main()
{
// 	freopen("P3808_1.in","r",stdin);
 	rint i;
 	scanf("%d",&n);
 	for(i=1;i<=n;i++) {
 		scanf("%s",a+1);
 		A.insert(a,strlen(a+1)); 
	}
	A.ACbuild();
	scanf("%s",a+1);
	printf("%d\n",A.query(a,strlen(a+1)));
	return 0;
}


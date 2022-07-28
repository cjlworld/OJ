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

// orz cqf 
namespace SBT
{
	const int N=2e5+5;
	
	int root;
	int s[N],ls[N],rs[N],v[N];
	int idx;
	
	inline void pushup(int now) { s[now]=s[ls[now]]+s[rs[now]]+1; }
	inline int NewNode(int key) 
	{
		idx++;
		v[idx]=key;
		s[idx]=1;
		ls[idx]=rs[idx]=0;
		return idx;
	}
	
	inline void Lspin(int& x)
	{
		int y=rs[x];
		rs[x]=ls[y];
		ls[y]=x;
		x=y;
		pushup(ls[x]),pushup(x);
	}
	
	inline void Rspin(int& x)
	{
		int y=ls[x];
		ls[x]=rs[y];
		rs[y]=x;
		x=y;
		pushup(rs[x]),pushup(x);
	}
	
	void Maintain(int& x,bool flag)
	{
		if(!flag) { // 左边一家小孩子捣乱。 
			if(s[ls[ls[x]]]>s[rs[x]]) Rspin(x); // 负负得正。 
			else if(s[rs[ls[x]]]>s[rs[x]]) 
				Lspin(ls[x]),Rspin(x); // 数组下标变参，LR 相反。 
			else return;
		}
		else { // 右边一家小孩子捣乱。 
			if(s[rs[rs[x]]]>s[ls[x]]) Lspin(x);
			else if(s[ls[rs[x]]]>s[ls[x]]) 
				Rspin(rs[x]),Lspin(x);
			else return;
		}
		Maintain(ls[x],0);
		Maintain(rs[x],1);
		Maintain(x,0);
		Maintain(x,1);
	}
	
	void insert(int& now,int key)
	{
		if(!now) 
			return now=NewNode(key),void();
		s[now]++;
		if(key<v[now]) insert(ls[now],key);
		else insert(rs[now],key);
		Maintain(now,key>=v[now]); // 注意是 >= 
	}
	
	int erase(int& x,int key)
    {
        s[x]--;
        if(key==v[x]||(key<v[x] && !ls[x])||(key>v[x] && !rs[x])) { // 走不下去了。 
            int res=v[x];
            if(!ls[x]||!rs[x]) x=ls[x]|rs[x]; // 存在一个子树空的，直接把另外一个子树提上来。 
            else v[x]=erase(ls[x],v[x]+1);  // 否则两个子树都有数。 
			// ls[] 里的数都 <= v[x],所以这实际上是找 x 的非严格前驱。 
            return res;
        }
        else if (key<v[x]) return erase(ls[x],key);
		else return erase(rs[x],key);
    }
    
	int findkth(int now,int k)
	{
		if(!now) return 0;
		if(k<=s[ls[now]]) return findkth(ls[now],k);
		else if(k<=s[ls[now]]+1) return v[now];
		else return findkth(rs[now],k-s[ls[now]]-1);
	}
	
	int rank(int now,int key)
	{
		if(!now) return 0;
		else if(key<=v[now]) return rank(ls[now],key); 
		// 由于旋转，左边仍可能有 = v[now] 的数,而右边的数不可能 < v[now],所以向左。 
		else return rank(rs[now],key)+1+s[ls[now]];
	}
	
	int Prev(int now,int key) { return findkth(now,rank(now,key)); }
	int Succ(int now,int key) { return findkth(now,rank(now,key+1)+1); }
}
using namespace SBT;

int n;

int main()
{
	int opt,x;
	
	scanf("%d",&n);
	while(n--) {
		scanf("%d%d",&opt,&x);
		if(opt==1) insert(root,x);  // insert
		else if(opt==2) erase(root,x); // erase		
		else if(opt==3) printf("%d\n",rank(root,x)+1); // rank
		else if(opt==4) printf("%d\n",findkth(root,x)); // findkth
		else if(opt==5) printf("%d\n",Prev(root,x)); // Prev
		else printf("%d\n",Succ(root,x)); // Succ 
	}
	
	return 0;
}


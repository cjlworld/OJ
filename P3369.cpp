#include<bits/stdc++.h>
using namespace std;
#define siz(x) ((x==NULL) ? 0 : x->size)
struct node
{
	int val;
	int size;
	int pri;
	node *lc,*rc;
	void update()
	{
		size=siz(lc)+siz(rc)+1;
		return;
	}
};
node *root = NULL;
node* newnode(const int &key)
{
	node *now;
	now = new node;
	now->val = key;
	now->pri = rand();
	now->lc = NULL;
	now->rc = NULL;
	now->size = 1;
	return now;
}
void split(node *now,const int &key,node *&x,node *&y)
{
	if(now==NULL) {
		x = y = NULL;
		return;
	}
	if(now->val <= key) {
		x = now;
		split(now->rc,key,x->rc,y);
		x->update();
	}
	else {
		y = now;
		split(now->lc,key,x,y->lc);
		y->update();
	}
	return;
}
node* merge(node *x,node *y)
{
	if(x==NULL) return y;
	if(y==NULL) return x;
	if(x->pri > y->pri) {
		x->rc = merge(x->rc,y);
		x->update();
		return x;
	}
	else {
		y->lc = merge(x,y->lc);
		y->update();
		return y;
	}
}
void insert(const int &key)
{
	node *x,*y,*z;
	split(root,key,x,y);
	root = merge(merge(x,newnode(key)),y);
	return;
}
void erase(const int &key)
{
	node *x,*y,*z;
	split(root,key,x,z);
	split(x,key-1,x,y);
	if(y!=NULL)
		y = merge(y->lc,y->rc);  
	x = merge(x,y);
	root = merge(x,z);
	return;
}
int getnum(int rank)
{
	node *now = root;
	while(rank>0&&now!=NULL) {
		if(siz(now->lc)+1==rank) 
			break;
		if(siz(now->lc)+1 > rank) 
			now = now->lc;
		else 
			rank-=siz(now->lc)+1,now = now->rc;
	}
	return (now==NULL) ? 0 : now->val;
}
int getrank(const int &key)
{
	node *x,*y,*z;
	split(root,key-1,x,y);
	int tmp = siz(x)+1;
	root = merge(x,y);
	return tmp;
}
int getpre(const int &key)
{
	node *x,*y,*z;
	split(root,key-1,x,y);
	node *now = x;
	if(now==NULL) 
		return 1e7;
	while(now->rc!=NULL) 
		now = now->rc;
	root = merge(x,y);
	return now->val;
}
int getsuf(const int &key)
{
	node *x,*y,*z;
	split(root,key,x,y);
	node *now = y;
	if(now==NULL) 
		return -1e7;
	while(now->lc!=NULL)
		now = now->lc;
	root = merge(x,y);
	return now->val; 
}
int main()
{
	//	freopen("1.in","r",stdin);
 	int n;
 	scanf("%d",&n);
 	int opt,x;
 	while(n--) {
 		scanf("%d%d",&opt,&x);
		switch(opt) {
			case 1 : insert(x); break;
			case 2 : erase(x); break;
			case 3 : printf("%d\n",getrank(x)); break;
			case 4 : printf("%d\n",getnum(x)); break;
			case 5 : printf("%d\n",getpre(x)); break; 
			case 6 : printf("%d\n",getsuf(x)); break;
		}	
	}
 	//============================================
	return 0;
}


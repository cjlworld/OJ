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
#include<complex>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

namespace Vtree
{
	void print(vector<int>& v)
	{
		for(int i=0;i<(int)v.size();i++) 	
			printf("%d ",v[i]);
		printf("\n");
	}
	void ins(vector<int>& v,int x) { v.insert(lower_bound(v.begin(),v.end(),x),x); }
	void del(vector<int>& v,int x) { v.erase(lower_bound(v.begin(),v.end(),x)); }
	int count(vector<int>& v,int l,int r)
	{
//		printf("count(%d ,%d) : ",l,r);
//		print(v);
		return upper_bound(v.begin(),v.end(),r)-lower_bound(v.begin(),v.end(),l);
	}	

}

const int N=1e5+5;

int num;
vector<int> v[N];

inline int lowbit(int x) { return x&(-x); }
void insert(int pos,int key)
{
	for(;key<=num;key+=lowbit(key)) {
//		printf("insert in v[%d], pos = %d\n",key,pos);
		Vtree::ins(v[key],pos);
	}
		
}
void erase(int pos,int key)
{
	for(;key<=num;key+=lowbit(key))
		Vtree::del(v[key],pos);
}
int Rank(int x,int l,int r)
{
//	printf("Rank val %d in (%d , %d) = ",x,l,r);
	int res=0;
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
	return key+1;
}

vector<int> nums;
inline int getnw(int x)
{
	return upper_bound(nums.begin(),nums.end(),x)-nums.begin();	
} 

struct Query
{
	int opt,x,y,z;
}q[N];

int n,m;
int a[N];

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int opt,x,y,z;
	
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		nums.push_back(a[i]);
	}
	for(i=1;i<=m;i++) {
		scanf("%d%d%d",&q[i].opt,&q[i].x,&q[i].y);
		if(q[i].opt^3) scanf("%d",&q[i].z);
		if(q[i].opt^2) {
			if(q[i].opt^3) nums.push_back(q[i].z);
			else nums.push_back(q[i].y);
		}
	}
	sort(nums.begin(),nums.end());
	nums.erase(unique(nums.begin(),nums.end()),nums.end());
	num=nums.size()+1;
	for(i=1;i<=n;i++) 
		insert(i,a[i]=getnw(a[i]));
	for(i=1;i<=m;i++) {
		if(q[i].opt^2) {
			if(q[i].opt^3) q[i].z=getnw(q[i].z);
			else q[i].y=getnw(q[i].y);
		}
	}
		
	for(i=1;i<=m;i++) {
		opt=q[i].opt; x=q[i].x; y=q[i].y; z=q[i].z;
		
		if(opt==1) printf("%d\n",Rank(z-1,x,y)+1);
		else if(opt==2) printf("%d\n",nums[findkth(z,x,y)-1]);
		else if(opt==3) erase(x,a[x]),insert(x,a[x]=y);
		else if(opt==4) printf("%d\n",nums[findkth(Rank(z-1,x,y),x,y)-1]);
		else printf("%d\n",nums[findkth(Rank(z,x,y)+1,x,y)-1]);
	}
	return 0;
}


#include<cmath>
#include<vector>
#include<cstdio>
#include<iostream>
#include<algorithm>
#define rg register 

using namespace std;

namespace FastIO
{
	const int _SIZE = (1 << 21) + 1;
	
	inline char NextChar()
	{
		static char ibuf[_SIZE];
		static char *iS,*iT;
		
		if(iS==iT) 
			iS=ibuf,iT=iS+fread(ibuf,1,_SIZE,stdin);
		return (iS == iT ? EOF : *iS++);
	}
	
	template <class T>
	inline void read(T &x) 
	{
		static char c;
		static bool sign;
		
		x=0;
		sign=false;
	    for (c=NextChar();c<'0'||c>'9';c=NextChar())
	        if (c=='-') sign=true;
	    for (;c>='0'&&c<='9';c=NextChar()) 
			x=(x<<1)+(x<<3)+(c&15);
		if(sign) x=-x;
	}
	
	char obuf[_SIZE];
	char *oS=obuf,*oT=obuf+_SIZE-1;
	inline void flush() 
	{
	    fwrite(obuf,1,oS-obuf,stdout);
	    oS=obuf;
	}
	inline void putc(const char &x) 
	{
	    *oS++=x;
	    if(oS==oT) flush();
	}
	
	template <class T>
	inline void print(T x) {
		static char qu[50];
		static int qr;
		
	    if (!x) {
	    	putc('0');
	    	return;
		}
	    if (x<0) putc('-'),x=-x;
	    for(qr=1;x;qr++,x/=10) qu[qr]=x%10+'0';
	    for(qr--;qr>=1;qr--) putc(qu[qr]);
	}

	struct Flusher_ 
	{
 	   ~Flusher_() { flush(); }
	}io_flusher_;
}
using FastIO::read;
using FastIO::print;
#define enter FastIO::putc('\n')

namespace Vtree
{
	void print(vector<int>& v)
	{
		for(int i=0;i<(int)v.size();i++) 	
			printf("%d ",v[i]);
		printf("\n");
	}
	void ins(vector<int>& v,const int& x) { v.insert(lower_bound(v.begin(),v.end(),x),x); }
	void del(vector<int>& v,const int& x) { v.erase(lower_bound(v.begin(),v.end(),x)); }
	int count(vector<int>& v,const int& l,const int& r)
	{
//		printf("count(%d ,%d) : ",l,r);
//		print(v);
		return upper_bound(v.begin(),v.end(),r)-lower_bound(v.begin(),v.end(),l);
	}	

}

const int N=1e5+5;

int num;
vector<int> v[N];

inline int lowbit(const int& x) { return x&(-x); }
inline void insert(const int& pos,rg int key)
{
	for(;key<=num;key+=lowbit(key)) {
//		printf("insert in v[%d], pos = %d\n",key,pos);
		Vtree::ins(v[key],pos);
	}
		
}
inline void erase(const int& pos,rg int key)
{
	for(;key<=num;key+=lowbit(key))
		Vtree::del(v[key],pos);
}
inline int Rank(rg int x,const int& l,const int& r)
{
//	printf("Rank val %d in (%d , %d) = ",x,l,r);
	int res=0;
	for(;x>=1;x-=lowbit(x)) 
		res+=Vtree::count(v[x],l,r);
//	printf("%d\n",res);
	return res;
}
inline int findkth(const int& k,const int& l,const int& r)
{
	static const int lgn=log2(num);
	rg int key=0,sum=0;
	for(rg int i=lgn,y;i>=0;i--) {
		if(key+(1<<i)>num) continue;
	//	printf("count in v[%d], (%d ,%d)\n",key+(1<<i),l,r);
		y=Vtree::count(v[key+(1<<i)],l,r);
		if(sum+y<k) {
			sum+=y,key+=(1<<i);
	//		printf("Accept %d , now key is %d and sum is %d\n",y,key,sum);
		}
	}
	return key+1;
}

vector<int> nums;
inline int getnw(const int& x)
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
	rg int i;
	rg int opt,x,y,z;
	
	read(n); read(m);
	for(i=1;i<=n;i++) {
		read(a[i]);
		nums.push_back(a[i]);
	}
	for(i=1;i<=m;i++) {
		read(q[i].opt); read(q[i].x); read(q[i].y);
		if(q[i].opt^3) read(q[i].z);
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
		
		if(opt==1) print(Rank(z-1,x,y)+1),enter;
		else if(opt==2) print(nums[findkth(z,x,y)-1]),enter;
		else if(opt==3) erase(x,a[x]),insert(x,a[x]=y);
		else if(opt==4) {
			int t=Rank(z-1,x,y);
			if(t==0) print(-2147483647);
			else print(nums[findkth(t,x,y)-1]);
			enter;
		}
		else {
			int t=Rank(z,x,y);
			if(t==y-x+1) print(2147483647);
			else print(nums[findkth(t+1,x,y)-1]);
			enter;
		}
	}
	return 0;
}

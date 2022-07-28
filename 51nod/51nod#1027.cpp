#include<vector>
#include<cstdio>
#include<iostream>
#include<algorithm>

using namespace std;

namespace Bignum
{
	// # Bignum using vector as base 
	// Done in 2021.2.9 by cjlworld
	typedef long long LL;
	typedef vector<LL> vint;
	
	// ## calc +,-,*,/,^,%,
	// ### +
	// #### vint + LL
	vint operator+(vint a,LL b)
	{
		for(int i=0;i<(int)a.size() && b;i++) {
			b+=a[i];
			a[i]=b%10;
			b/=10;
		}
		while(b) a.push_back(b%10),b/=10;
		return a;
	}
	
	// #### vint+vint
	vint operator+(vint a,vint b)
	{
		vint c;
		int t=0;
		if(a.size()<b.size()) swap(a,b);
		for(int i=0;i<(int)a.size();i++) {
			t+=a[i];
			if(i<(int)b.size()) t+=b[i];
			c.push_back(t%10);
			t/=10;
		}
		if(t) c.push_back(t);
		return c;
	}
	
	// ### -
	vint operator-(vint a,vint b)
	{
		for(int i=0;i<(int)b.size();i++) {
			if(a[i]<b[i]) {
				a[i+1]--;
				a[i]+=10;
			}
			a[i]-=b[i];
		}
		for(int i=0;i<(int)a.size();i++) {
			if(a[i]<0) {
				a[i]+=10;
				a[i+1]--;
			}
		}
		while(a.size()>1 && !a.back()) a.pop_back();
		return a;
	}
	
	// ### * 
	// #### using ntt
	const int _N=4e5+5;
	const LL _P=998244353,_G=3;
	
	LL power(LL x,LL k,LL MOD)
	{
	    LL res=1; x%=MOD;
	    while(k) {
	        if(k&1) res=res*x%MOD;
	        x=x*x%MOD; k>>=1;
	    }
	    return res%MOD;
	}
	
	int rev[_N];
	
	void ntt(LL a[],int n,int inv)
	{
	    for(int i=0;i<n;i++)
	        if(rev[i]<i) swap(a[rev[i]],a[i]);
	    for(int k=2,m=1;k<=n;m=k,k<<=1) {
	        LL gn=power(_G,(_P-1)/k,_P);
	        if(inv==-1) gn=power(gn,_P-2,_P);
	        for(int i=0;i<n;i+=k) {
	            LL g=1;
	            for(int j=0;j<m;j++,g=g*gn%_P) {
	                LL u=a[i+j],v=a[i+j+m];
	                a[i+j]=u+g*v; a[i+j+m]=u-g*v;
	            }
	        }
	        for(int i=0;i<n;i++) a[i]=(a[i]%_P+_P)%_P;
	    }
	    if(inv==-1) {
	        for(int i=0;i<n;i++)
	            a[i]=a[i]*power(n,_P-2,_P)%_P;
	    }
	}
	
	// #### vint*vint 
	vint operator*(vint a,vint b)
	{
	    static LL A[_N],B[_N];
	    static vint c; c.clear();
	    
	    for(int i=0;i<(int)a.size();i++) A[i]=a[i];
	    for(int i=0;i<(int)b.size();i++) B[i]=b[i];
	    int tot=a.size()+b.size(),bit=1;
	    while((1<<bit)<tot) bit++;
	    tot=(1<<bit);
	    for(int i=0;i<tot;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
	    ntt(A,tot,1); ntt(B,tot,1);
	    for(int i=0;i<tot;i++) A[i]=A[i]*B[i]%_P;
	    ntt(A,tot,-1);
	    LL t=0;
	    for(int i=0;i<tot;i++) {
	        t+=A[i];
	        A[i]=t%10;
	        t/=10;
	    }
	    for(int i=0;i<(int)(a.size()+b.size());i++) 
	        c.push_back(A[i]);
	    while(!c.back() && c.size()>1) c.pop_back();
	    for(int i=0;i<tot;i++) A[i]=B[i]=rev[i]=0; // ±ðÍüÁËÇå¿Õ¡£ 
	    return c;
	}
	
	// #### vint * LL 
	vint operator*(vint a,LL b)
	{
		vint c;
		LL t=0;
		for(int i=0;i<(int)a.size();i++) {
			t+=a[i]*b;
			c.push_back(t%10);
			t/=10;
		}
		while(t) c.push_back(t%10),t/=10;
		while(c.size()>1 && !c.back()) c.pop_back();
		return c;
	}
	
	// ### /
	// #### vint / LL
	vint operator/(vint a,LL b)
	{
		vint c;
		int t=0;
		for(int i=a.size()-1;i>=0;i--) {
			t=(t<<1)+(t<<3)+a[i];
			c.push_back(t/b);
			t%=b;
		}
		reverse(c.begin(),c.end());
		while(c.size()>1 && !c.back()) c.pop_back();
		return c;
	}
	
	// ### %
	LL operator%(vint a,LL b)
	{
		LL t=0;
		for(int i=a.size()-1;i>=0;i--) 
			t=(t*10+a[i])%b;
		return t;
	}
	
	// ### ^
	vint power(vint x,LL k)
	{
		vint res; res.push_back(1);
		while(k) {
			if(k&1) res=res*x;
			x=x*x; k>>=1;
		}
		return res;
	}
	
	// ## Compare
	// ### < is basic
	bool operator<(const vint& a,const vint& b) 
	{
		if(a.size()!=b.size()) return (a.size()<b.size());
		for(int i=a.size()-1;i>=0;i--) 
			if(a[i]!=b[i]) return (a[i]<b[i]);
		return false;
	}
	
	// ### == is basic too, but it has been done
	// ### <= 
	bool operator<=(const vint& a,const vint& b) 
	{
		return a<b || a==b;
	}

	// ## in and out¡£ 
	// ### in
	istream &operator>>(istream& cin,vint& v)
	{
		static string s;
		v.clear();
		cin>>s;
		reverse(s.begin(),s.end());
		for(int i=0;i<(int)s.length();i++) 
			v.push_back(s[i]-'0');
		return cin;
	}	
	
	// out
	ostream &operator<<(ostream& cout,vint v)
	{
		for(int i=v.size()-1;i>=0;i--) cout<<v[i];
		return cout;
	}
}
using namespace Bignum;

int main()
{
	vint a,b;
	cin>>a>>b;
	cout<<a*b<<endl;
    return 0;
}


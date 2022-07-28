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

LL base=1e15,width=15;

bool cmp(vector<LL> a,vector<LL> b) 
{
	if(a.size()<b.size()) return true;
	else if(a.size()>b.size()) return false;
	for(LL i=a.size()-1;i>=0;i--) {
		if(a[i]<b[i]) return true;
		else if(a[i]>b[i]) return false;
	}
	return false;
}

vector<LL> sub(vector<LL> a,vector<LL> b)
{
	vector<LL> c;
	for(LL i=0;i<(LL)a.size();i++) {
		if(i>=(LL)b.size()) {
			if(a[i]<0) a[i]+=base,a[i+1]--;
			c.push_back(a[i]);
		}
		else {
			if(a[i]<b[i]) a[i]+=base,a[i+1]--;
			c.push_back(a[i]-b[i]);
		}
	}
	while(c.back()==0&&c.size()>1) c.pop_back();
	return c;
}

vector<LL> div(vector<LL> a,LL b)
{
	LL t=0;
	vector<LL> c;
	for(LL i=a.size()-1;i>=0;i--) {
		t=t*base+a[i];
		c.push_back(t/b);
		t=t%b;
	}
	reverse(c.begin(),c.end());
	while(c.back()==0&&c.size()>1) c.pop_back();
	return c;
}

void input(vector<LL> &a)
{
	a.clear();
	string s;
	cin>>s;
	LL t;
	reverse(s.begin(),s.end());
	for(LL i=0;i<(LL)s.length();i+=width) {
		t=0;
		for(LL j=min(i+width,(LL)s.length())-1;j>=i;j--) 
			t=t*10+(s[j]-'0');
		a.push_back(t);
	}
}

void output(vector<LL> a)
{
	for(LL i=a.size()-1;i>=0;i--) {
		if(i==(LL)a.size()-1) printf("%lld",a[i]);
		else printf("%015lld",a[i]);
	}
}

vector<LL> mul(vector<LL> a,LL b)
{
	LL t=0;
	vector<LL> c;
	for(LL i=0;i<(LL)a.size();i++) {
		t+=a[i]*b;
		c.push_back(t%base);
		t/=base;
	}
	while(t) c.push_back(t%base),t/=base;
	while(c.back()==0&&c.size()>1) c.pop_back();
	return c;
}

vector<LL> gcd(vector<LL> a,vector<LL> b)
{
	LL t=0;
	vector<LL> c;
	c.push_back(1);
	while(!cmp(b,c)) {
		if(cmp(a,b)) swap(a,b);
		if(cmp(b,c)) break;
		
		if(b[0]%2==0&&a[0]%2==0) a=div(a,2),b=div(b,2),t++;
		else if(a[0]%2==0) a=div(a,2);
		else if(b[0]%2==0) b=div(b,2);
		else a=sub(a,b);
	}
	while(t--) a=mul(a,2);
	return a;
}

int main()
{
//	freopen("1.in","r",stdin);
	vector<LL> a,b;
	input(a),input(b);
	output(gcd(a,b));
	return 0;
}


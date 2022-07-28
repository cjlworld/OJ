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
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

vector<int> mul(vector<int> a,int b)
{
	vector<int> c;
	int i,t=0;
	for(i=0;i<(int)a.size();i++) {
		t=t+a[i]*b;
		c.push_back(t%10);
		t/=10;
	}
	while(t) c.push_back(t%10),t/=10;
	while(c.size()>1&&c.back()==0) c.pop_back();
	return c;
}

vector<int> add(vector<int> a,vector<int> b)
{
	vector<int> c;
	if(a.size()<b.size()) swap(a,b);
	int i,t=0;
	for(i=0;i<(int)a.size();i++) {
		t+=a[i];
		if(i<(int)b.size()) t+=b[i];
		c.push_back(t%10);
		t/=10;
	}
	if(t) c.push_back(t);
	while(c.size()>1&&c.back()==0) c.pop_back();
	return c;
}

vector<int> div(vector<int> a,int b)
{
	vector<int> c;
	int i,t=0;
	for(i=a.size()-1;i>=0;i--) {
		t=t*10+a[i];
		c.push_back(t/b);
		t%=b;
	}
	reverse(c.begin(),c.end());
	while(c.size()>1&&c.back()==0) c.pop_back();
	return c;
}

int mod(vector<int> a,int b)
{
	int i,c=0;
	for(i=a.size()-1;i>=0;i--) 
		c=(c*10+a[i])%b;
	return c;
}

int num(char c)
{
	if(c>='0'&&c<='9') return c-'0';
	else if(c>='A'&&c<='Z') return c-'A'+10;
	else return c-'a'+36;
}
char word(int x)
{
	if(x>=0&&x<=9) return '0'+x;
	else if(x>=10&&x<=35) return x-10+'A';
	else return x-36+'a';
}

void input(const string &s,vector<int> &v) 
{
	v.clear();
	for(int i=0;i<(int)s.length();i++) 
		v.push_back(num(s[i]));
	reverse(v.begin(),v.end());
}

void output(string &s,vector<int> v)
{
	s="";
	for(int i=0;i<(int)v.size();i++) 
		s=s+word(v[i]);
	reverse(s.begin(),s.end());
}

void print(vector<int> v)
{
	reverse(v.begin(),v.end());
	for(int i=0;i<(int)v.size();i++) 
		printf("%d ",v[i]);
	printf("\n");
}

vector<int> big(int a)
{
	vector<int> c;
	while(a) c.push_back(a%10),a/=10;
	return c;
}

vector<int> base2ten(vector<int> a,int base)
{
	vector<int> c;
	c.push_back(0);
	int i;
	for(i=a.size()-1;i>=0;i--) {
		c=mul(c,base);
		c[0]+=a[i];
	}
	c=mul(c,1); 
	return c;
}

vector<int> ten2base(vector<int> a,int base)
{
	vector<int> c;
	while(a.size()>1||(a.size()==1&&a[0]>0)) {
		c.push_back(mod(a,base));
		a=div(a,base);
	}
	return c;
}

int T;

int main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	int n,m;
	string s;
	vector<int> a,b,c;
	
	scanf("%d",&T);
	while(T--) {
		scanf("%d%d",&n,&m);
		cin>>s;
		
		printf("%d %s\n",n,s.c_str());
		input(s,a);
//		print(a);
		
		b=base2ten(a,n);
//		print(b);
		
		c=ten2base(b,m);
		if(c.size()==0) c.push_back(0);
		output(s,c);
		printf("%d %s\n\n",m,s.c_str());
	}
	return 0;
}


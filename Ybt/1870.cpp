#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=1000+5;
struct chen
{
    LL a,b;
    bool operator<(const chen &t) const
    {
    	return a*b<t.a*t.b;
	}
}t[N];
int n;

void input(vector<LL> &a)
{
	a.clear();
	string s;
	cin>>s;
	reverse(s.begin(),s.end());
	for(int i=0;i<(int)s.length();i++) 
		a.push_back(s[i]-'0');
}

void output(vector<LL> a)
{
	for(int i=a.size()-1;i>=0;i--) 
		putchar(a[i]+'0');
}


vector<LL> mul(vector<LL> a,LL b)
{
	LL t=0;
	vector<LL> c;
	for(int i=0;i<(int)a.size();i++) {
		t+=a[i]*b;
		c.push_back(t%10);
		t/=10;
	}
	while(t) c.push_back(t%10),t/=10;
	while(c.back()==0&&c.size()>1) c.pop_back();
	return c;
}

vector<LL> div(vector<LL> a,LL b)
{
	LL t=0;
	vector<LL> c;
	for(int i=a.size()-1;i>=0;i--) {
		t=t*10+a[i];
		c.push_back(t/b);
		t=t%b;
	}
	reverse(c.begin(),c.end());
	while(c.back()==0&&c.size()>1) c.pop_back();
	return c;
}

bool cmp(vector<LL> a,vector<LL> b) // <
{
	if(a.size()<b.size()) return true;
	else if(a.size()>b.size()) return false;
	for(int i=a.size()-1;i>=0;i--) {
		if(a[i]<b[i]) return true;
		else if(a[i]>b[i]) return false;
	}
	return false;
}

vector<LL> a,b;
int main()
{
//	freopen("1.in","r",stdin);
    int i;
    scanf("%d",&n);
    input(a),input(b);
    for(i=1;i<=n;i++) 
        cin>>t[i].a>>t[i].b;
    sort(t+1,t+n+1);
    vector<LL> ans,a1=a;
    int p=1;
    for(i=1;i<=n;i++) {
        if(cmp(mul(a1,t[i].b),mul(a,t[p].b))) a1=a,p=i;
        a=mul(a,t[i].a);
    }
    ans=div(a1,t[p].b);
    output(ans);
    return 0;
}


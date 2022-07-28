#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<vector<LL>,LL> PVL;

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

PVL div(vector<LL> a,LL b)
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
	return PVL(c,t);
}


int main()
{
    vector<LL> a;
    PVL c;
    LL b;
    input(a); cin>>b;
    c=div(a,b);
    output(c.first),cout<<"\n"<<c.second;
    return 0;
}

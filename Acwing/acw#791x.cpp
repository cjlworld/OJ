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

vector<int> add(vector<int> a,vector<int> b)
{
	vector<int> c;
	if(a.size()<b.size()) swap(a,b);
	int t=0;
	unsigned i;
	for(i=0;i<a.size();i++) {
		t+=a[i];
		if(i<b.size()) t+=b[i];
		c.push_back(t%10);
		t/=10;
	}
	if(t) c.push_back(t);
	return c;
}

void input(vector<int> &a)
{
	a.clear();
	string s;
	cin>>s;
	reverse(s.begin(),s.end());
	for(unsigned i=0;i<s.length();i++) 
		a.push_back(s[i]-'0');
}

void output(vector<int> a)
{
	for(int i=a.size()-1;i>=0;i--) 
		putchar(a[i]+'0');
}
int main()
{
	vector<int> a,b;
	input(a),input(b);
	output(add(a,b));
	return 0;
}


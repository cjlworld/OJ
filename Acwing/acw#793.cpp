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
	int t=0;
	vector<int> c;
	for(int i=0;i<(int)a.size();i++) {
		t+=a[i]*b;
		c.push_back(t%10);
		t/=10;
	}
	while(t) c.push_back(t%10),t/=10;
	while(c.back()==0&&c.size()>1) c.pop_back();
	return c;
}

void input(vector<int> &a)
{
	a.clear();
	string s;
	cin>>s;
	reverse(s.begin(),s.end());
	for(int i=0;i<(int)s.length();i++) 
		a.push_back(s[i]-'0');
}

void output(vector<int> a)
{
	for(int i=a.size()-1;i>=0;i--) 
		putchar(a[i]+'0');
}
int main()
{
	vector<int> a;
	int b;
	input(a); cin>>b;
	output(mul(a,b));
	return 0;
}


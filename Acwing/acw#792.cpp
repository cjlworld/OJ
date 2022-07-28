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

vector<int> sub(vector<int> a,vector<int> b)
{
	vector<int> c;
	for(int i=0;i<(int)a.size();i++) {
		if(i>=(int)b.size()) {
			if(a[i]<0) a[i]+=10,a[i+1]--;
			c.push_back(a[i]);
		}
		else {
			if(a[i]<b[i]) a[i]+=10,a[i+1]--;
			c.push_back(a[i]-b[i]);
		}
	}
	while(c.back()==0&&c.size()>1) c.pop_back();
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

bool cmp(vector<int> a,vector<int> b) // <
{
	if(a.size()<b.size()) return true;
	else if(a.size()>b.size()) return false;
	for(int i=a.size()-1;i>=0;i--) {
		if(a[i]<b[i]) return true;
		else if(a[i]>b[i]) return false;
	}
	return false;
}

int main()
{
	vector<int> a,b,c;
	input(a),input(b);
	if(cmp(a,b)) putchar('-'),swap(a,b);
	output(sub(a,b));
	return 0;
}


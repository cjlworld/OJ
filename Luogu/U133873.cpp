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

string str;
vector<char> a;
stack<char> S;
deque<LL> num;

LL fpow(LL x,LL k)
{
	LL res=1;
	while(k) {
		if(k&1) res=res*x;
		x=x*x; k>>=1;
	}
	return res;
} 

int main()
{
	int i;
	cin>>str;
	for(i=0;i<(int)str.length();i++) {
		if(str[i]>='0'&&str[i]<='9') {
			while(i<(int)str.length()&&str[i]>='0'&&str[i]<='9') a.push_back(str[i]),i++;
			a.push_back('.');
			i--;
		}
		else {
			if(str[i]=='*'||str[i]=='/') {
				while(S.size()&&(S.top()=='*'||S.top()=='/'||S.top()=='^'))
					a.push_back(S.top()),S.pop();
				S.push(str[i]);
			}
			else if(str[i]=='+'||str[i]=='-') {
				while(S.size()&&(S.top()!='('))
					a.push_back(S.top()),S.pop();
				S.push(str[i]);
			}
			else if(str[i]=='^') {
				while(S.size()&&S.top()=='^')
					a.push_back(S.top()),S.pop();
				S.push(str[i]);	
			}
			else if(str[i]=='(') S.push(str[i]);
			else if(str[i]==')') {
				while(S.size()&&S.top()!='(') 
					a.push_back(S.top()),S.pop();
				S.pop();
			}
		}
	}
	while(S.size()) a.push_back(S.top()),S.pop();
	LL x=0,y=0,cur=0;
	for(i=0;i<(int)a.size();i++) {
		if(a[i]>='0'&&a[i]<='9') 
			cur=cur*10ll+(a[i]-'0');
		else if(a[i]=='.') num.push_back(cur),cur=0;
		else {
			x=num.back(),num.pop_back();
			y=num.back(),num.pop_back();
			if(a[i]=='+') num.push_back(y+x);
			else if(a[i]=='-') num.push_back(y-x);
			else if(a[i]=='*') num.push_back(y*x);
			else if(a[i]=='/') num.push_back(y/x);
			else if(a[i]=='^') num.push_back(fpow(y,x));
		}
	}
	cout<<num[0];
	return 0;
}


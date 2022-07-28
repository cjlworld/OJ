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
typedef unsigned long long LL;

LL fpow(LL x,LL k)
{
	LL res=1;
	while(k) {
		if(k&1) res=res*x;
		x=x*x; k>>=1;
	}
	return res;
} 

LL calc(string str)
{
	int i;
	vector<char> a;
	stack<char> S;
	deque<LL> num;
	for(i=0;i<(int)str.length();i++) {
		if(str[i]==' ') continue;
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
	return num[0];
}

vector<LL> deal(string s)
{
	string t;
	int i,j;
	vector<LL> v;
	for(j=0;j<=9;j++) {
		t=s;
		for(i=0;i<(int)t.length();i++) 
			if(t[i]=='a') t[i]=char('0'+j);
//		cout<<t<<endl;
		v.push_back(calc(t));
	}
	return v;
}
int n;

bool check(string s) // ¼ì²éÀ¨ºÅ 
{
	stack<char> Stk;
	int i;
	for(i=0;i<(int)s.length();i++) {
		if(s[i]=='(') Stk.push('(');
		else if(s[i]==')') {
			if(Stk.empty()) return false;
			else Stk.pop();
		}
	}
	if(Stk.size()) return false;
	else return true;
}

int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	vector<LL> a,b;
	string s;
	getline(cin,s);
	a=deal(s);
	
	cin>>n; for(char c=getchar();c!='\n';c=getchar());
	for(i=0;i<n;i++) {
		getline(cin,s);
		if(!check(s)) continue;
		b=deal(s);
		for(j=0;j<10;j++) 
			if(a[j]!=b[j]) break;
		if(j==10) putchar('A'+i);
	}
	
	return 0;
}

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

const int N=256;

string str;
vector<char> a;
stack<char> S;
deque<int> num;

int main()
{
	int i,j,x,y;
	cin>>str;
	for(i=0;i<(int)str.length();i++) {
		if(str[i]>='0'&&str[i]<='9') a.push_back(str[i]);
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
			else if(str[i]=='^') S.push(str[i]);
			else if(str[i]=='(') S.push(str[i]);
			else if(str[i]==')') {
				while(S.size()&&S.top()!='(') 
					a.push_back(S.top()),S.pop();
				S.pop();
			}
		}
	}
	while(S.size()) a.push_back(S.top()),S.pop();
	for(i=0;i<(int)a.size();i++) printf("%c ",a[i]);
	printf("\n");
	for(i=0;i<(int)a.size();i++) {
		if(a[i]>='0'&&a[i]<='9') num.push_back(a[i]&15);
		else {
			x=num.back(),num.pop_back();
			y=num.back(),num.pop_back();
			if(a[i]=='+') num.push_back(y+x);
			else if(a[i]=='-') num.push_back(y-x);
			else if(a[i]=='*') num.push_back(y*x);
			else if(a[i]=='/') num.push_back(y/x);
			else if(a[i]=='^') num.push_back(pow(y,x));
			for(j=0;j<(int)num.size();j++) printf("%d ",num[j]);
			for(j=i+1;j<(int)a.size();j++) printf("%c ",a[j]);
			printf("\n");
		}
	}
	return 0;
}


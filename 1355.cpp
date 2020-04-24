#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<stack>
using namespace std;
const int N=10000+5;
stack<int> q;
char c[N];
int a[N];
inline int getnum(char inc)
{
	if(inc=='<') return 1;
	if(inc=='>') return 2;
	if(inc=='(') return 3;
	if(inc==')') return 4;
	if(inc=='[') return 5;
	if(inc==']') return 6;
	if(inc=='{') return 7;
	if(inc=='}') return 8;
	return 0;
}
int main()
{
//	freopen("1.txt","r",stdin);
	int t,u,len;
	int i,j;
	scanf("%d",&t);
	for(u=1;u<=t;u++) {
		memset(c,'\0',sizeof(c));
		while(!q.empty()) q.pop();
		q.push(958034);
		scanf("%s",c+1);
		len=strlen(c+1);
		for(i=1;i<=len;i++) 
			a[i]=getnum(c[i]);
		for(i=1;i<=len;i++) {
			if(q.size()==1) q.push(a[i]);
			else if(q.top()==1&&a[i]==2) q.pop();
			else if(q.top()==3&&a[i]==4) q.pop();
			else if(q.top()==5&&a[i]==6) q.pop();
			else if(q.top()==7&&a[i]==8) q.pop();
			else if(!(a[i]&1)) {
				q.push(a[i]);
				break;
			}
			else if(a[i]<=q.top()) q.push(a[i]);
			else {
				q.push(a[i]);
				break;
			}
		}
//		cout<<q.size()<<endl;
		if(q.size()==1) cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
	return 0;
}


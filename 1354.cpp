#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;
char f[100000];
char c[100000];
int top=0;
int main()
{
	cin>>c;
	int len=strlen(c);
	if(len%2==1) { cout<<"Wrong"; return 0; }
	for(int i=0;i<len;i++) 
	{
		if(top==0||c[i]=='('||c[i]=='[') { top++; f[top]=c[i]; }
		else if((f[top]=='('&&c[i]==')')||(f[top]=='['&&c[i]==']')) top--;
		else { cout<<"Wrong"; return 0;}
	}
	if(top==0) cout<<"OK";
	else cout<<"Wrong";
	return 0;
}


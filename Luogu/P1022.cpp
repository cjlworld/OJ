#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
using namespace std;
double a=0,x=0,s=0;
char c[256];
char ch;
int i,j=0;
bool p=false;
struct data
{
	int sum;
	int o;
	int bit;
}b[256];
int op(int t)
{
	return b[j].sum*10+(c[t]-'0');
}
int main()
{
//	freopen("1.in","r",stdin);
	gets(c);
	int len=strlen(c);
	for(i=0;i<=255;i++) {
		b[i].o=1;
	}
	for(i=0;i<len;i++)
	{
		if(i==0||p==true) {
			if(c[i]>='0'&&c[i]<='9'||c[i]>='a'&&c[i]<='z'||c[i]>='A'&&c[i]<='Z') {
				b[j].bit=1;
			}
			else if(c[i]=='-') b[j].bit=-1;
			p=false;
		}
		if(c[i]>='0'&&c[i]<='9') {
			b[j].sum=op(i);
		}
		else if(c[i]=='-') b[j].bit=-1;
		else if(c[i]=='+') b[j].bit=1;
		else if(c[i]>='a'&&c[i]<='z'||c[i]>='A'&&c[i]<='Z') {
			ch=c[i];
			if(b[j].sum==0) b[j].sum=1;
			a+=b[j].sum*b[j].bit*b[j].o;
//			cout<<a<<endl;
			b[j].sum=0;
			b[j].bit=1;
			j--;
		}
		else if(c[i]=='=') {
			for(int u=j;u<=255;u++) {
				b[u].o=-1;
			}
			p=true;
		}
		if(c[i+1]=='-'||c[i+1]=='+'||c[i+1]=='='||i==len-1) {
//			b[j].sum=b[j].sum*b[j].bit*b[j].o;
			j++;
			if(c[i]==c[255]) j--;
		}
	}
	for(i=0;i<=j;i++) {
		s+=b[i].sum*b[i].bit*b[i].o;
	}
	a=-a;
	x=(s*1.0)/(a/1.0);
//	for(i=0;i<=j;i++) {
//		cout<<b[i].sum<<" "<<b[i].o<<" "<<b[i].bit<<endl;
//	}/**/
//	cout<<s<<endl<<a<<endl;
	cout<<ch<<"=";
	cout<<fixed<<setprecision(3)<<x<<endl;
	return 0;
}


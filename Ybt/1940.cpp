#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
int m,s,t;
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	cin>>m>>s>>t;
	int mm=m;
	int way=0;
	for(i=1;i<=t;i++) {
		if(m>=10) m-=10,way+=60;
		else {
			if(t==i) way+=17;
			else if(t-i+1==2) {
				if(m>=6) 
					m+=4;
				else way+=17;
			}
			else if(t-i+1>=3&&t-i+1<=6) {
				if(m>=2) m+=4;
				else way+=17;
			}
			else m+=4;
		}
	}
	if(way<s) {
		puts("No");
		cout<<way;
		return 0;	
	}
	way=0;
	m=mm;
	for(i=1;i<=t;i++) {
		if(m>=10) m-=10,way+=60;
		else {
			if(s-way<=17) way+=17;
			else if(s-way<=2*17) {
				if(m>=6) 
					m+=4;
				else way+=17;
			}
			else if(s-way<=6*17) {
				if(m>=2) m+=4;
				else way+=17;
			}
			else m+=4;
		}
		if(way>=s) {
			puts("Yes");
			cout<<i;
			return 0;
		}
	}
	return 0;
}


#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
const int N=10000+5;
int h11,h21;
#define data Data_Data
struct data
{
	int a,b;
	bool end(int lit) 
	{
		if(a>=lit&&a>=b+2) 
			return true;
		if(b>=lit&&b>=a+2) 
			return true;
		return false;  
	}
};
data a[N],b[N];
inline void read(char &c)
{
	c=getchar();
	while(c!='W'&&c!='L'&&c!='E')	
		c=getchar();
	return;
}
int main()
{
	int i,j;
	int x,y,z;
	char c='\0';
	while(c!='E') {
		read(c);
		if(c=='E') break;
		if(c=='W') {
			a[h11].a++;
			b[h21].a++;
			if(a[h11].end(11)) h11++;
			if(b[h21].end(21)) h21++;
		}
		else {
			a[h11].b++;
			b[h21].b++;
			if(a[h11].end(11)) h11++;
			if(b[h21].end(21)) h21++;
		}
	}
	for(i=0;i<=h11;i++) {
		printf("%d:%d\n",a[i].a,a[i].b);
	}
	puts("");
	for(i=0;i<=h21;i++) 
		printf("%d:%d\n",b[i].a,b[i].b);
	return 0;
}

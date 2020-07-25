#include<vector>
#include<cstdio>
#include<iostream>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=512;
int a[N][N];
char b[N][N];
int n,m;
void putans()
{
	int i,j;
	for(i=500;i>=1;i--) {
		for(j=1;j<=500;j++) 
			if(b[i][j]!='.') break;
		if(j!=501) 
			break;
	}
	for(;i>=1;i--,putchar('\n')) 
		for(j=1;j<=4*m+2*n+1;j++) 
			cout<<b[i][j];
}
void paint(int x,int y,char ch)
{
	if(b[x][y]=='.') 		
		b[x][y]=ch;
//	putans();
	return;
}
void draw(int x,int y,int floor)
{
	paint(x,y,'+');
	paint(x+1,y,'|');
	paint(x+2,y,'|');
	paint(x+3,y,'+');
	paint(x,y-1,'-');
	paint(x,y-2,'-');
	paint(x,y-3,'-');
	paint(x,y-4,'+');
	paint(x+1,y-4,'|');
	paint(x+2,y-4,'|');
	paint(x+3,y-4,'+');

	paint(x+3,y-3,'-');
	paint(x+3,y-2,'-');	
	paint(x+3,y-1,'-');
	paint(x+1,y+1,'/');
	paint(x+2,y+2,'+');
	paint(x+3,y+2,'|');
	paint(x+4,y+2,'|');
	paint(x+5,y+2,'+');
	paint(x+4,y+1,'/');
	for(int i=1;i<=3;i++) 
		paint(x+1,y-i,' '),paint(x+2,y-i,' ');
	paint(x+2,y+1,' '); paint(x+3,y+1,' ');
	if(floor>1) 
		return draw(x+3,y,floor-1); 
	for(int i=0;i<=2;i++)
		paint(x+4,y-i,' ');
	paint(x+4,y-3,'/');
	paint(x+5,y-2,'+');
	for(int i=1;i>=-1;i--)
		paint(x+5,y-i,'-');
	return;
}

int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	cin>>n>>m;
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++) 
			cin>>a[i][j];	
	for(i=1;i<=500;i++)
		for(j=1;j<=500;j++) 
			b[i][j]='.';
	for(i=n;i>=1;i--)
		for(j=m;j>=1;j--) 
			draw(2*(n-i+1)-1,4*j+2*((n-i+1)-1)+1,a[i][j]);
	putans();
	return 0;
}



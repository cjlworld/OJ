#include<cstdio>
#include<iostream>
#include<cstring>
#define LL long long
using namespace std;
int f[256][256];
void predeal()
{
	int i,j,k;
	for(i=0;i<=9;i++) 
		f[1][i]=1;
	for(i=2;i<=11;i++) 
		for(j=0;j<=9;j++) 
			for(k=j;k<=9;k++) 
				f[i][j]+=f[i-1][k];
	return;
}
int dim[256];
int prefix(int x)
{
	int i,j,k;
	int cnt=0;
	cnt=0;
	memset(dim,0,sizeof dim);
	while(x) {
		dim[++cnt]=x%10;
		x=x/10;
	}
	int last=0,res=0;
	for(i=cnt;i>=1;i--) {
		if(last>dim[i]) 
			return res; 
		for(j=last;j<=dim[i]-1;j++) {
			res+=f[i][j];
		}
		last=dim[i];
	}
	return ++res;
}
int main()
{
//	freopen("1.in","r",stdin);
	int n,m;
	memset(f,0,sizeof(f));
	predeal();
//	for(int i=1;i<=3;i++,putchar('\n')) 
//		for(int j=1;j<=9;j++) 
//			cout<<f[i][j]<<" ";
	while(cin>>n>>m) {
		cout<<prefix(m)-prefix(n-1)<<endl;
	}
//	cout<<prefix(0)<<endl;
//	cout<<prefix(19)<<endl;
 	return 0;
}


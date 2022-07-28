#include<cstdio>
#include<iostream>

using namespace std;

const int N=256;
int m,n,T;
int w[N][N],v[N][N],tot[N];
int f[N];

int main()
{
	int i,j,k;
	int x,y,z;
	cin>>m>>n>>T;
	for(i=1;i<=n;i++) {
		scanf("%d%d%d",&x,&y,&z);
		v[z][++tot[z]]=x;
		w[z][tot[z]]=y;
	}
	for(k=1;k<=T;k++) 
		for(j=m;j>=0;j--) 
			for(i=1;i<=n;i++) 
				if(j>=v[k][i])
					f[j]=max(f[j],f[j-v[k][i]]+w[k][i]);
	cout<<f[m]<<endl;
	return 0;
}

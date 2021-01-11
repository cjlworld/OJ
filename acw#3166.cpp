#include<iostream>

using namespace std;
typedef long long LL;

const int N=1024;
const LL MOD=1e9+7;

int n,k;
LL s[N][N];

int main()
{
	int i,j;
	
	cin>>n>>k;
	s[0][0]=1;
	for(i=1;i<=n;i++) {
		for(j=1;j<=i;j++) 
			s[i][j]=(s[i-1][j-1]+j*s[i-1][j])%MOD;
	}
	cout<<s[n][k];
	return 0;
}


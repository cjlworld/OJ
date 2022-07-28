#include<bits/stdc++.h>
using namespace std;
/*货币系统中货币的种类数目是 V (1<=V<=25)。要构造的数量钱是 N (1<= N<=10,000)。
第一行: 二个整数，V 和 N 。
第二行： 可用的货币的面值 。*/
int v,n;
int a[256];
unsigned long long f[10005];
int main()
{
//	freopen("1.in","r",stdin);
 	cin>>v>>n;
 	int i,j;
 	for(i=1;i<=v;i++) scanf("%d",&a[i]);
 	f[0]=1;
 	for(i=1;i<=v;i++) {
 		for(j=0;j<=n;j++) {
 			if(j-a[i]>=0) 
				f[j]=f[j]+f[j-a[i]];	
		}
	}
	cout<<f[n]<<endl;
	fclose(stdin);fclose(stdout);
	return 0;
}


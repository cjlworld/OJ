#include<bits/stdc++.h>
using namespace std;
/*����ϵͳ�л��ҵ�������Ŀ�� V (1<=V<=25)��Ҫ���������Ǯ�� N (1<= N<=10,000)��
��һ��: ����������V �� N ��
�ڶ��У� ���õĻ��ҵ���ֵ ��*/
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


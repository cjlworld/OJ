#include<bits/stdc++.h>
using namespace std;
int n,t;//��n�����������ҳ����к�Ϊt(tҲ��������)�Ŀ��ܵ���Ϸ�ʽ��
long long f[1005];
int a[1005];
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	cin>>n>>t;
	for(i=1;i<=n;i++) cin>>a[i];
	if(t==0) { cout<<"0"; return 0; }
	f[0]=1;
	for(i=1;i<=n;i++) {
		for(j=t;j>=0;j--) {
			if(j-a[i]>=0) 
				f[j]=f[j]+f[j-a[i]];
		}
	}
//	for(i=1;i<=t;i++) cout<<f[i]<<" ";
//	cout<<endl;
	cout<<f[t];
	return 0;
}

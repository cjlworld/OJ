#include<bits/stdc++.h>
using namespace std;
int n,m,k;//n---����������;m---Ƥ�����ʼ������ֵ;k---Ұ��С�����������
int w[1005],v[1005];//w[i]---��Ҫ�ľ����������;v[i]---��Ƥ������ɵ��˺���
long long f[1005][1005];
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	cin>>n>>m>>k;
	for(i=1;i<=k;i++) cin>>w[i]>>v[i];
	int t;
	for(t=1;t<=k;t++) {
		for(i=n;i>=0;i--) {
			for(j=m;j>=0;j--) {
				if(i-w[t]>=0&&j-v[t]>=0) 
					f[i][j]=max(f[i][j],f[i-w[t]][j-v[t]]+1);
			}
		}
	}
	cout<<f[n][m]<<" ";
	int Max=f[n][m];
	int Min=0x3f3f3f;
	for(i=1;i<=n;i++) {
		for(j=1;j<=m;j++) {
			if(f[i][j]==Max) Min=min(Min,j);
		}
	}
	cout<<m-Min<<endl;
	return 0;
}


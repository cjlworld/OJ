#include<bits/stdc++.h>
using namespace std;
int n,m;//n(��Ʒ������n��3500)��m(��������,m��12880)��
int w[3505],c[3505];//ÿ�ж�������w[i]��c[i]����ʾÿ����Ʒ�������ͼ�ֵ��
long long f[13000];
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	cin>>n>>m;
	for(i=1;i<=n;i++) cin>>w[i]>>c[i];
	for(i=1;i<=n;i++) {
		for(j=m;j>=0;j--) {
			if(j-w[i]<0) break;
			f[j]=max(f[j],f[j-w[i]]+c[i]);
		}
	}
	cout<<f[m];
	return 0;
}


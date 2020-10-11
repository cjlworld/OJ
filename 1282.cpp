#include<cstdio>
#include<iostream>

using namespace std;

const int N=100+5,INF=1e9;
int a[N][N],s[N][N]; // s[i][j] ��ʾ��i�е�ǰj�����ĺ͡� 
int n;

int main()
{
	int i,j,l,r,x;
	cin>>n;
	for(i=1;i<=n;i++) 
		for(j=1;j<=n;j++) 
			cin>>a[i][j],s[i][j]=s[i][j-1]+a[i][j];
	int ans=-INF,cmax;
	for(l=1;l<=n;l++) {
		for(r=l;r<=n;r++) { // ö���Ӿ������߽���ұ߽� �� 
			// Ȼ��������Ӷκ͵��Ǹ�DP��DP���ϱ߽���±߽硣 
			cmax=s[1][r]-s[1][l-1]; //�ǿ� 
			ans=max(ans,cmax);
			for(i=2;i<=n;i++) {
				x=s[i][r]-s[i][l-1];
				ans=max(ans,x); // Case 1
				ans=max(ans,cmax+x); // Case 2
				cmax=max(cmax+x,x); // �����׺�ͱ�����x���ǿգ� 
			}
		}
	}
	cout<<ans;
	return 0;
}

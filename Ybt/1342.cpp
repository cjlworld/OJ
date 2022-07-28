#include<bits/stdc++.h>
using namespace std;
/*��һ��Ϊ����n��
��2�е���n+1�У���n�У� ��ÿ����������x��y��������һ��������ꡣ
��n+2��Ϊһ������m����ʾͼ�����ߵĸ�����
�˺��m �У�ÿ������һ�����ߣ�����������i��j��ɣ���ʾ��i����͵�j����֮�������ߡ�
���һ�У���������s��t���ֱ��ʾԴ���Ŀ��㡣*/
int n,m;
double w[256][256];
struct node
{
	double x;
	double y;
};
node a[256];
int s,t;
inline void add(int xx,int yy)
{
	w[xx][yy]=w[yy][xx]=sqrt(pow(a[xx].x-a[yy].x,2)+pow(a[xx].y-a[yy].y,2));
	return;
}
void Init()
{
	scanf("%d",&n);
	memset(w,127,sizeof(w));
	int i,j;
	int xx,yy;
	for(i=1;i<=n;i++) {
		cin>>a[i].x>>a[i].y;
	}
	scanf("%d",&m);
	for(i=1;i<=m;i++) {
		scanf("%d%d",&xx,&yy);
		add(xx,yy);
	}
	scanf("%d%d",&s,&t);
	return;
}
void Floyed()
{
	int i,j,k;
	for(k=1;k<=n;k++) {
		for(i=1;i<=n;i++) {
			for(j=1;j<=n;j++) {
				if(w[i][j]>w[i][k]+w[k][j])
					w[i][j]=w[i][k]+w[k][j];
			}
		}
	}
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	Init();
	Floyed();
	cout<<fixed<<setprecision(2)<<w[s][t];
	return 0;
}


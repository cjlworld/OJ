#include<bits/stdc++.h>
using namespace std;
/*��1�У�һ��������N(N��15,000)����ʾС�������������ܹ���������
��2�е���N+1 �У�ÿһ������һ�����յ����ʵ���
����һ���Ǹ�����M��100����ʾ�����յ����˵�����
���M������������С��1,000,000,000������ʾÿ���ʵ�����
�������ݱ�֤ÿ�춼����֧�������ʵ���*/
multiset<int> q;
int n,m;
int sum=0;
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d",&n);
	int i,j;
	int x,y;
	for(i=1;i<=n;i++) {
		scanf("%d",&m);
		for(j=1;j<=m;j++) {
			scanf("%d",&x);
			q.insert(x);
		}
		printf("%d ",*q.begin());	//�����Сֵ
		q.erase(q.begin());	//ɾ����Сֵ
		printf("%d\n",*(--q.end()));	//������ֵ
		q.erase(--q.end());		//ɾ�����ֵ
	}
	return 0;
}


#include<cstdio>
#include<set>
#include<iostream>
#define LL long long
using namespace std;
//����������������һЩ����ֻ��2,3,5������
//����1,2,3,4,5,6,8,9,10,12,15����д���˴�С�����ǰ11��������
//1���ڳ��������������д�����ҳ���1500��������ʲô��
//û������
//�����The 1500'th ugly number is <...>.��<...>Ϊ���ҵ��ĵ�1500�������� 
//ע�⣺<...>�����ҵ������������û�м����ţ� 2�������Ӧ���С� 
const int N=1500;
set<LL> S;
int main()
{
//	freopen("1.in","r",stdin);
	int cnt=0;
	int i,j;
	LL x,y,z;
	S.insert(1); 
	for(i=1;i<=1500;i++) {
		x=*S.begin();
		S.erase(S.begin());
		S.insert(2*x);
		S.insert(3*x);
		S.insert(5*x);
	}
	cout<<"The 1500'th ugly number is "<<x<<"."<<endl; 
	return 0;
}


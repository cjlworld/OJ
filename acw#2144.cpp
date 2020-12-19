#include<set>
#include<map>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<bitset>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=400000+5,INF=0x3f3f3f3f;

int n,m;
int a[181][81];

int h[2][N],v[2][N],q[2][N],cnt[2];
char tt;
int Hash(int cur,int t)
{
	int u=t%N;
	while(~h[cur][u] && h[cur][u]!=t)
		if(++u==N) u=0;
	return u;
}
bool check(int state);
inline void insert(int cur,int state,int val)
{
	if(!check(state)) {
//		printf("here %c\n",tt);
		return;
	}
	int u=Hash(cur,state);
	if(~h[cur][u])
		v[cur][u]=max(v[cur][u],val);
	else h[cur][u]=state,v[cur][u]=val,q[cur][++cnt[cur]]=u;
}

int ask(int x,int y) { return (x>>2*y)&3; }
int make(int j,int t) { return t<<(2*j); }

int find(int state,int j,int dec,int val)
{
	for(int s=0,u;;j+=dec) {
		u=ask(state,j);
		if(u==0) continue;
		else if(u==val) {
			s--;
			if(s==0) return j;
		}
		else s++;
	}
	return -1;
}
bool check(int state)
{
	int j,k,s=0;
	for(j=0;j<=m;j++) {
		k=ask(state,j);
		if(k==1) s++;
		else if(k==2) {
			if(s>0) s--;
			else return false;
		}
	}
	if(s>0) return false;
	else return true;
}


int ans=-INF;

int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k;
	int x,y,z;
	
	cin>>n>>m;
	for(i=0;i<n;i++) 
		for(j=0;j<m;j++) 
			cin>>a[i][j];
	
	int cur=0,lt,state,w;
	memset(h[cur],-1,sizeof h[cur]);
	insert(cur,0,0);
	for(i=0;i<n;i++) {
		// 1.roll
		// ������״̬���� 1 λ (4 ����)
        // ��Ϊ��һ�е����һ����ɵ�ǰ�еĵ�һ�������� ��һ�е����һ�� �϶�Ϊ 0��  
		for(j=1;j<=cnt[cur];j++) 
			h[cur][q[cur][j]]<<=2;
		
		// ö��ÿһ������ (�׶�) 
		for(j=0;j<m;j++) {
			lt=cur,cur^=1; // ������
			cnt[cur]=0; // ��ն��к͹�ϣ�� 
			memset(h[cur],-1,sizeof h[cur]);
			
			for(k=1;k<=cnt[lt];k++) {
				state=h[lt][q[lt][k]],w=v[lt][q[lt][k]]; // ȡ��״̬�� 
				x=ask(state,j),y=ask(state,j+1); // ��ߺ����档 
				
				// ��������: tips 
					// 1. ���������� 0 ��״̬�� 
					// 2. ��������û�� 0 ��״̬���������� x!=y ��
					// 3. ������� x==y
					// ads : 1. �����պðѵ�һ�е���ĸ������
					//       2. ���׺��ѡ� 
				
				// A.�� x==0 && y==0 , �� 	
					// (1) �������ø��ӣ���������Һ����ϵıߡ�
					// (2) ����������ԭ�ⲻ����
					
			 	if(x==0 && y==0) {
			 		tt='A';
			 		if(i+1<n && j+1<m) insert(cur,state+make(j,1)+make(j+1,2),w+a[i][j]);
			 		insert(cur,state,w);
				} 
				
				// B.�� x!=0 && y==0,��ؾ����ø��ӡ�
				// 1. ��·��������չ��
				// 2. ��·��������չ��
				
				else if(x!=0 && y==0) {tt='B';
					// down
					if(i+1<n) insert(cur,state,w+a[i][j]);
					// right
					if(j+1<m) insert(cur,state-make(j,x)+make(j+1,x),w+a[i][j]);
				}   
				
				// C.�� x==0 && y!=0  ,�� B ����ͬ��
				
				else if(x==0 && y!=0) {tt='C';
					// down 
					if(i+1<n) insert(cur,state-make(j+1,y)+make(j,y),w+a[i][j]);
					// right
					if(j+1<m) insert(cur,state,w+a[i][j]);
				} 
				
				// D. �� x==2 �� y==1
				// ��ǰ�ֺ�β��ӣ���ȥ��ͷ���ɡ� 
				else if(x==2 && y==1) 
					tt='D',insert(cur,state-make(j,x)-make(j+1,y),w+a[i][j]);
				
				// E. �� x==1 �� y==2;
				// �� x,y ��ͨ
				// (1) ����������ͷ������������ͨ ��״̬�����Ϸ���
				// (2) ���ޣ������ϴ˲�ͷ��һ����·�γɡ�
				
				else if(x==1 && y==2) {tt='E';
					if(state-make(j,x)-make(j+1,y)==0)
						ans=max(ans,w+a[i][j]);	
				}
				
				// F. �� x==1 && y==1
				
				else if(x==1 && y==1) {tt='F';
					z=find(state,j+1,1,2);
					insert(cur,state-make(j,1)-make(j+1,1)-make(z,2)+make(z,1),w+a[i][j]);
				}
				
				// G. �� x==2 && y==1
				
				else if(x==2 && y==2) {tt='G';
					z=find(state,j,-1,1);
					insert(cur,state-make(j,2)-make(j+1,2)-make(z,1)+make(z,2),w+a[i][j]);
				} 
			}
			
//			cerr<<cnt[cur]<<endl;
		}
	}
	
	cout<<ans<<endl;
	return 0;
}

// DeBug
// 1. i,j ���á�  ��� �� make(j,t); 
// 2. �ʼҲҪ��ʼ�� ��ϣ��ÿ��һ���µĸ���ҲҪ��ʼ���� 
// 3. j+1 д�� j �ˡ�
// 4. find �� 0,1,2 ����Ԫ�أ�Ҫ�Ȱ� 0 �е������жϣ� ���� !=
// 5. cnt[cur]=0; // ��ն��к͹�ϣ�� 
// 6. 				// ��������: tips 
					// 1. ���������� 0 ��״̬�� 
					// 2. ��������û�� 0 ��״̬���������� x!=y ��
					// 3. ������� x==y
					// ads : 1. �����պðѵ�һ�е���ĸ������
					//       2. ���׺��ѡ� 
// 7. find �ﲻ������ j �ķ�Χ������Ҫ��״̬���Ϸ���Ҳ�ܷ��֣� 

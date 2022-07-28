#include<map>
#include<queue>
#include<stack>
#include<ctime>
#include<cmath>
#include<bitset>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=1000+5,M=2e5+5;

vector<int> add(vector<int> a,vector<int> b)
{
	vector<int> c;
	int t=0;
	if(a.size()<b.size()) swap(a,b);
	for(int i=0;i<(int)a.size();i++) {
		t+=a[i];
		if(i<(int)b.size()) t+=b[i];
		c.push_back(t%10);
		t/=10;
	}
	if(t) c.push_back(t);
	return c;
}

void output(vector<int> a)
{
	for(int i=a.size()-1;i>=0;i--) 
		putchar(a[i]+'0');
}

int h[2][M]; // �����Ĺ�ϣ�� 
vector<int> v[2][M];

int q[2][M],cnt[2]; // �����Ķ��У������ϣ���ڲ�������ļ��ϡ� 

int Hash(int cur,int k)
{
    int t=k%M;
    while(h[cur][t]!=-1 && h[cur][t]!=k) 
        if(++t==M) t=0;
    return t;
}

void insert(int cur,int state,vector<int> w)
{
    int t=Hash(cur,state);
    if(h[cur][t]==-1) {
        h[cur][t]=state;
        v[cur][t]=w;
        q[cur][++cnt[cur]]=t;
    }   
    else v[cur][t]=add(v[cur][t],w);
}

int get(int state,int k) // ���� state ���Ľ��Ʊ�ʾ�µ� k λ���� (k �� 0 ��ʼ)�� 
{
    return state>>(k*2)&3;
}
int set(int k,int v) // ����һ���� k λ �� v������λ�� 0 ������ 
{
    return v * (1<<k*2);
}

int n,m; 
int a[N][20]; // �������̵���Ϣ��
// tips : ���ߵ���� 1 , �����ߵ�Ϊ 0 , �����պñ߽�Ҳ�ǲ����ߵġ�

int main()
{
//	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
    int i,j,k;
    int x,y;
    m=4;
    
    for(n=1;n<=1000;n++) {
    	memset(a,0,sizeof a);
	    for(i=1;i<=n;i++) 
			for(j=1;j<=m;j++) 
				a[i][j]=1;

	    int cur=0,lt,state;
	    vector<int> w; w.push_back(1);
	    vector<int> ans; ans.push_back(0);
	    memset(h,-1,sizeof h);
	    insert(cur,0,w);
	    for(i=1;i<=n;i++) {
	        // ������״̬���� 1 λ (4 ����)
	        // ��Ϊ��һ�е����һ����ɵ�ǰ�еĵ�һ�������� ��һ�е����һ�� �϶�Ϊ 0��  
	        for(j=1;j<=cnt[cur];j++)
	            h[cur][q[cur][j]]<<=2;
	
	        // ö��ÿһ������ (�׶�) 
	        for(j=1;j<=m;j++) {
	            lt=cur,cur^=1; // ���� 
	
	            cnt[cur]=0; // ��ն��к͹�ϣ���� 
	            memset(h[cur],-1,sizeof h[cur]);
	
	            // ö����һ���׶ε�ÿһ��״̬����ת�ơ�
	            for(k=1;k<=cnt[lt];k++) {
	
	                state=h[lt][q[lt][k]],w=v[lt][q[lt][k]];
	                x=get(state,j-1),y=get(state,j);
	
	                if(!a[i][j]) { // �����ǰ�ĸ��Ӳ�����.
	                    // ��ôֻ��û���ߵ�״̬���á� 
	                    if(x==0&&y==0) insert(cur,state,w);
	                }
	                // ����ǰ���Ӿ��ǿ����ߡ�
	
	                else if(x==0&&y==0) {
	                    if(a[i+1][j]&&a[i][j+1])
	                        insert(cur,state+set(j-1,1)+set(j,2),w);
	                    // ���������� ���� �� �ұ� �ߵĻ�·�� 
	                }
	                else if(x!=0&&y==0) {
	                    if(a[i+1][j]) insert(cur,state,w); // �������ߡ� 
	                    if(a[i][j+1]) insert(cur,state-set(j-1,x)+set(j,x),w); // ���ұ��ߡ� 
	                }
	                else if(x==0&&y!=0) {
	                    if(a[i+1][j]) insert(cur,state-set(j,y)+set(j-1,y),w); // �������ߡ� 
	                    if(a[i][j+1]) insert(cur,state,w); // ���ұ��ߡ� 
	                }
	                else if(x==1&&y==1) {
	                    for(int u=j+1,s=1;u<=m;u++) { // �ҵ� j ƥ��������š� 
	                        if(get(state,u)==1) s++;
	                        else if(get(state,u)==2) {
	                            s--;
	                            if(s==0) {
	                                insert(cur,state-set(j-1,1)-set(j,1)-set(u,2)+set(u,1),w); // �ҵ��ˡ� 
	                                break;
	                            }
	                        }
	                    }
	                }
	                else if(x==2&&y==1) insert(cur,state-set(j-1,x)-set(j,y),w);
	                else if(x==2&&y==2) {
	                    for(int u=j-2,s=1;u>=1;u--) {
	                        if(get(state,u)==2) s++;
	                        else if(get(state,u)==1) {
	                            s--;
	                            if(s==0) {
	                                insert(cur,state-set(j-1,2)-set(j,2)-set(u,1)+set(u,2),w);
	                                break;
	                            }
	                        } 
	                    }
	                }
	                else if(x==1&&y==2) { // �ս� 
	                    if(i==n&&j==m)
	                        ans=add(ans,w);
	                }
	            }   
	        }
	    }
	    ans=add(ans,ans);
		output(ans);
		printf("LL,");
		cerr<<n<<endl;
	}

    return 0;
}


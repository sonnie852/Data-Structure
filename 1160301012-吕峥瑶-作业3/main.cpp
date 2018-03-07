/*
��ҵ3
�ں�dijkstra���Ż�
*/
#include <iostream>
#include <cstdio>
#include <malloc.h>
#include <strings.h>
#include <fstream>
#include <stack>
#include <queue>
#include <vector>
#define INT_MAX1 100000
using namespace std;
const int maxn=100000+5;
typedef pair<int,int> pii;
struct Edge{
    int to,weight;
    Edge(int to,int weight):to(to),weight(weight){}
};
vector<vector<Edge> > G(maxn);
struct Dijkstra{
    int n,m;
    bool done[maxn];
    int dist[maxn];
    int p[maxn];
    Dijkstra(int n):n(n){
        for(int i=0;i<n;i++) G[i].clear();
    }
    void AddEdge(int from,int to,int weight){
        G[from].push_back(Edge(to,weight));
    }
    void dijkstra(int s)
    {
        priority_queue<pii,vector<pii>,greater<pii> > Q;
        memset(dist,0x7f,sizeof(dist));
        memset(done,false,sizeof(done));

        dist[s]=0;
        Q.push(pii(0,s));
        while(!Q.empty())
        {
            int u=Q.top().second; Q.pop();
            if(done[u]) continue;
            done[u]=true;
            for(int i=0;i<G[u].size();i++)
            {
                Edge& e=G[u][i];
                int v=e.to ,w=e.weight;
                if(dist[v]>dist[u]+w)
                {
                    dist[v]=dist[u]+w;
                    p[v]=u;
                    Q.push(pii(dist[v],v));
                }
            }
        }
    }
};

typedef int ** Graph;
int vertexnum,edgenum;
Graph goal;
/*
ͼ�Ľ���
*/
Graph CreateGraph()
{
    freopen("test.txt","r",stdin);
    scanf("%d %d",&vertexnum,&edgenum);
    goal=(Graph)malloc(sizeof(int *)*(vertexnum+1));
    for(int i=1;i<=vertexnum;i++)
    {
        goal[i]=(int *)malloc(sizeof(int)*(vertexnum+1));
    }
    for(int i=1;i<=vertexnum;i++)
        for(int j=1;j<=vertexnum;j++)
            goal[i][j]=INT_MAX1;
    int x,y,z;
    for(int i=1;i<=edgenum;i++)
    {
        scanf("%d %d %d",&x,&y,&z);
        goal[x][y]=z;
    }
    cout<<"�����ͼΪ��"<<endl;
    for(int i=1;i<=vertexnum;i++)
    {for(int j=1;j<=vertexnum;j++)
            if(goal[i][j]==INT_MAX1)cout<<"��"<<"  ";
            else cout<<goal[i][j]<<"  ";
    cout<<endl;
    }
    return goal;
}
int MinCost(int D[],bool S[])
{
    int temp=INT_MAX1;
    int w;
    for(int i=2;i<=vertexnum;i++)
        if(!S[i]&&D[i]<temp)
    {
        temp=D[i];
        w=i;
    }
    return w;
}
/*
dijkstra�㷨
*/
void Dijkstra(Graph C,int D[],int P[],bool S[])
{
    for(int i=2;i<=vertexnum;i++)
    {
        D[i]=C[1][i];
        S[i]=false;
        P[i]=1;
    }
    for(int i=2;i<=vertexnum;i++)
    {
        int w=MinCost(D,S);

        int sum=0;
        S[w]=true;
        for(int v=2;v<=vertexnum;v++)
            if(S[v]!=true)
        {
            sum=D[w]+C[w][v];
            if(sum<D[v]){D[v]=sum;P[v]=w;}
        }

    }
    cout<<"��ʱԴ��Ϊ1"<<endl;
    for(int i=2;i<=vertexnum;i++)
    {
        if(D[i]>=100000){cout<<"���ɴ�"<<endl;continue;}
        cout<<"��Դ�㵽"<<i<<"����̾���Ϊ"<<D[i]<<endl;
        cout<<"���·��Ϊ:"<<endl;
        stack <int>path;
        int i1=i;
        path.push(i);
        while(i1!=1)
        {
            path.push(P[i1]);
            i1=P[i1];
        }
        cout<<"1";
        path.pop();
        while(!path.empty())
        {
            cout<<"->";
            cout<<path.top();
            path.pop();
        }
        cout<<endl;
    }
}
void getPath(int i ,int j,int **P1){
    if(P1[i][j]==-1) printf("->%d ",j);
    else{
        getPath(i,P1[i][j],P1);
        getPath(P1[i][j],j,P1);
    }
}
/*
��floyedΪ�����Ĳ���
*/
void Floyed(Graph goal,int **D1,int **P1,int option)
{
    int A[vertexnum+1][vertexnum+1];
    for(int i=1;i<=vertexnum;i++)
    {
        for(int j=1;j<=vertexnum;j++)
        {
            D1[i][j]=goal[i][j];

            P1[i][j]=-1;
            if(goal[i][j]==INT_MAX1)A[i][j]=0;
            else A[i][j]=1;
        }
    }
    for(int k=1;k<=vertexnum;k++)
    {
        for(int i=1;i<=vertexnum;i++)
        {
            for(int j=1;j<=vertexnum;j++)
            {
                if(D1[i][k]+D1[k][j]<D1[i][j])
                {
                    D1[i][j]=D1[i][k]+D1[k][j];
                    P1[i][j]=k;
                }
            }
        }
    }
//��̾����������·������
    if(option==2){
    cout<<"��̾������"<<endl;
    for(int i=1;i<=vertexnum;i++)
    {
        for(int j=1;j<=vertexnum;j++)
        {
            if(D1[i][j]==INT_MAX1)cout<<"��"<<"  ";
            else cout<<D1[i][j]<<"  ";
        }
        cout<<endl;
    }
    cout<<"���·������"<<endl;
    for(int i=1;i<=vertexnum;i++)
    {
        for(int j=1;j<=vertexnum;j++)
        {
            cout<<P1[i][j]<<"  ";
        }
        cout<<endl;
    }}
    if(option==3){
    for(int i=1;i<=vertexnum;i++)
    {
        for(int j=1;j<=vertexnum;j++)
        {
            if(D1[i][j]==INT_MAX1)cout<<i<<"��"<<j<<"֮�䲻�ɴ�"<<endl;
            else
            {
                cout<<i<<"��"<<j<<"֮�����·������Ϊ��"<<D1[i][j]<<endl;
                cout<<i<<"��"<<j<<"֮�����·��Ϊ��"<<endl;
                cout<<i;
                getPath(i,j,P1);
                cout<<endl;
            }
        }
        cout<<endl;
    }}
//��Ŀ��ڵ����̳���
    if(option==4){
    cout<<"������Ҫ���ҵ�Ŀ��ڵ�"<<endl;
    int score;
    scanf("%d",&score);
    if(score>vertexnum)cout<<"������Ч";
    else
    {
        cout<<"������ǣ�"<<score<<endl;
        for(int i=1;i<=vertexnum;i++)
        {
            if(i==score)continue;
            if(D1[i][score]==INT_MAX1)continue;
            cout<<"����"<<i<<"������"<<score<<"�����·�������� "<<D1[i][score]<<" ,·���ǣ�"<<endl;
            cout<<i;
            getPath(i,score,P1);
            cout<<endl;
        }
    }}
//һ�Զ���֮�����̾���
    if(option==5){
    cout<<"����һ�Զ���"<<endl;
    int temp;
    scanf("%d",&temp);
    int m,n;
    scanf("%d %d",&m,&n);
    cout<<"��"<<m<<"��"<<n<<endl;
    if(m>vertexnum||n>vertexnum)cout<<"������Ч";
    else
    {
        if(D1[m][n]==INT_MAX1){cout<<"���ɴ�";}
        else{
        cout<<"��̾���Ϊ"<<D1[m][n]<<endl;
        cout<<"���·��Ϊ : ";
        cout<<m;
        getPath(m,n,P1);}
    }
    cout<<endl<<"��"<<n<<"��"<<m<<endl;
    if(m>vertexnum||n>vertexnum)cout<<"������Ч";
    else
    {
        if(D1[n][m]==INT_MAX1){cout<<"���ɴ�";}
        else{
        cout<<"��̾���Ϊ"<<D1[n][m]<<endl;
        cout<<"���·��Ϊ : ";
        cout<<n;
        getPath(n,m,P1);}
    }
    }

//�ɴ����

    if(option==6){
            cout<<endl<<"�ɴ����Ϊ"<<endl;
    for (int i = 1;i <=vertexnum;i++)
    {
        for (int j = 1;j <=vertexnum;j++)
        {
            if (A[j][i])
            {
                for (int k = 1;k <=vertexnum;k++)
                {
                    A[j][k] = A[j][k]|A[i][k];//�߼���
                }
            }
        }
    }
    for(int i=1;i<=vertexnum;i++)
    {
        for(int j=1;j<=vertexnum;j++)
        {
            cout<<A[i][j]<<"  ";
        }
        cout<<endl;
    }
    }
}

int main()
{
    int option;
    cout<<"1.Dijkstra"<<endl;
    cout<<"2.Fliyed��̾������·������"<<endl;
    cout<<"3.��������֮�����·���;���"<<endl;
    cout<<"4.��Ŀ����̾����·��"<<endl;
    cout<<"5.һ�Զ��㵽�˴˵����·���;���"<<endl;
    cout<<"6.�ɴ����"<<endl;
    cout<<"7.Dijkstra�Ż�"<<endl;
    scanf("%d",&option);

    goal=CreateGraph();
    int D[vertexnum+1],P[vertexnum+1];
    bool S[vertexnum+1];
    if(option==1){
    cout<<endl<<"Dijkstra"<<endl<<endl;
    Dijkstra(goal,D,P,S);}
    if(option==2||option==3||option==4||option==5||option==6){
    Graph P1,D1;
    P1=(Graph)malloc(sizeof(int *)*(vertexnum+1));
    for(int i=1;i<=vertexnum;i++)
    {
        P1[i]=(int *)malloc(sizeof(int)*(vertexnum+1));
    }
    D1=(Graph)malloc(sizeof(int *)*(vertexnum+1));
    for(int i=1;i<=vertexnum;i++)
    {
        D1[i]=(int *)malloc(sizeof(int)*(vertexnum+1));
    }
    cout<<endl<<"Floyed"<<endl<<endl;
    Floyed(goal,D1,P1,option);
    fclose(stdin);}
/*
�Ż���dijkstra
*/
    if(option==7){
    cout<<"dijkstra���Ż�"<<endl;
    freopen("test1.txt","r",stdin);
    int n,m,u,v,w;
    cin>>n>>m;
     struct Dijkstra d(n);
    for(int i=0;i<m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        d.AddEdge(u,v,w);
    }
    d.dijkstra(1);
    for(int i=2;i<=n;i++)
    cout<<"Դ��1��"<<i<<"���·������Ϊ"<<d.dist[i]<<endl;
    cout<<"��Դ�㵽���һ����������·��Ϊ"<<endl;
    vector<int> ans;
    for(int i=n;i!=1;i=d.p[i]) ans.push_back(i);
    ans.push_back(1);
    for(int i=ans.size()-1;i>=0;i--) {cout<<ans[i];if(i!=0)cout<<"->";}
    fclose(stdin);}
    return 0;
}

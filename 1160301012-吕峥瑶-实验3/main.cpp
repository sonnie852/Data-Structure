#include<iostream>
#include<cstdio>
#include<fstream>
#include<queue>
#include<stack>
#define VertexNum 30
using namespace std;

/*
�ڽӾ���Ľṹ
*/
typedef struct{
    int vertex[VertexNum];//��������
    int edge[VertexNum][VertexNum];//�ӵ�һ�����㵽�ڶ�������ߵ�Ȩ��
    int n,e;//�ߺͶ������Ŀ
}MTGraph;
/*
�ڽӱ�ṹ
*/
typedef struct node{
    int adjvex;//������
    int cost;//��ͷ��㵽�ý��ıߵ�Ȩ��
    struct node *next;//��һ����ͷ�������Ľ��
}EdgeNode;
typedef struct{
    int vertex;//ͷ�����
    EdgeNode *firstedge;//��ͷ���������ĵ�һ�����
}VertexNode;//ͷ���ṹ
typedef struct{
    VertexNode verlist[VertexNum];//ͷ�������
    int n,e;//�ߺͽ�����Ŀ
}AdjGraph;//�ڽӱ�
/*
ʮ������ṹ
*/
typedef struct ArcBox{
    int tailvex,headvex;
//tailvex ��β��, ָʾ��β������ͼ�е�λ��
//headvex: ͷ��, ָʾ��ͷ������ͼ�е�λ��
    struct ArcBox *hlink,*tlink;
//hlink ������, ָ��ͷ��ͬ����һ����
//tlink ������ָ��β��ͬ����һ����
    int info;//��Ϣ
}ArcBox;//���ṹ
typedef struct VexNode{
    int data;//������
    ArcBox *firstin,*firstout;
// firstin ������ָ���Ըö���Ϊ��ͷ�ĵ�һ������㡣firstout ������ָ���Ըö���Ϊ��β�ĵ�һ�������
}VexNode;//ͷ���ṹ
typedef struct{
    VexNode xlist[VertexNum];//ͷ�������
    int vexnum,arcnum;//�ߺͽ����Ŀ
}OLGraph;//�����ڽӱ�

/*
�����ڽӾ���
*/
void Create0(MTGraph *G)
{
    int i,j,k,w;
    scanf("%d",&G->n);
    scanf("%d",&G->e);
    for(i=1;i<=G->n;i++)
    {
        scanf("%d",&G->vertex[i]);
    }
    for(i=1;i<=G->n;i++)
    {
        for(j=1;j<=G->n;j++)
        {
            G->edge[i][j]=0;
        }
    }
    for(k=1;k<=G->e;k++)
    {
        scanf("%d %d %d",&i,&j,&w);
        G->edge[i][j]=w;
        //G->edge[j][i]=w;
    }
}
/*
��ӡ�ڽӾ���
*/
void Print0(MTGraph *G)
{
    cout<<"    ";
    for(int i=1;i<=G->n;i++)
    {
        printf("%3d",G->vertex[i]);
    }
    cout<<endl<<endl;
    for(int i=1;i<=G->n;i++)
    {
        cout<<i<<"   ";
        for(int j=1;j<=G->n;j++)
        {
            printf("%3d",G->edge[i][j]);
        }
        cout<<endl;
    }
}
/*
�����ڽӱ�
*/
void Create1(AdjGraph &G)
{
    cin>>G.n>>G.e;
    int m,n;
    int w;
    for(int i=1;i<=G.n;i++)
    {
        cin>>G.verlist[i].vertex;
        G.verlist[i].firstedge=NULL;
    }
    for(int i=1;i<=G.e;i++)
    {
        cin>>m>>n>>w;
        //m
        EdgeNode *p=new EdgeNode;
        p->cost=w;
        p->adjvex=n;
        EdgeNode *tmp;
        tmp=G.verlist[m].firstedge;
        G.verlist[m].firstedge=p;
        p->next=tmp;
    }
}
/*
��ӡ�ڽӱ�
*/
void Print1(AdjGraph &G)
{
    for(int i=1;i<=G.n;i++)
    {
        cout<<G.verlist[i].vertex;
        EdgeNode *tmp=G.verlist[i].firstedge;
        while(tmp!=NULL)
        {
            cout<<"-> ";
            cout<<tmp->adjvex<<"|"<<tmp->cost;//"|"�����Ǳ�Ȩ��

            tmp=tmp->next;
        }
        cout<<endl;
    }
}
/*
����ʮ������
*/
void Create2(OLGraph &G)
{
    scanf("%d %d",&G.vexnum,&G.arcnum);
    for(int i=1;i<=G.vexnum;i++)
    {
        scanf("%d",&G.xlist[i].data);
        G.xlist[i].firstin=NULL;
        G.xlist[i].firstout=NULL;
    }
    for(int k=1;k<=G.arcnum;k++)
    {
        int m,n,w;
        scanf("%d %d %d",&m,&n,&w);
        ArcBox *p=new ArcBox;

        p->tailvex=m;
        p->headvex=n;
        p->info=w;
        p->tlink=G.xlist[m].firstout;
        p->hlink=G.xlist[n].firstin;
        G.xlist[m].firstout=p;
        G.xlist[n].firstin=p;
    }
}
/*
��ӡʮ������
*/
void Print2(OLGraph &G)
{
    for(int i=1;i<=G.vexnum;i++)
    {

        cout<<G.xlist[i].data<<"���"<<endl;
        ArcBox *tmp=G.xlist[i].firstin;
        while(tmp!=NULL)
        {
            cout<<"w:"<<"("<<tmp->info<<")";
            cout<<tmp->tailvex<<"->"<<tmp->headvex<<"  ";//<<"w:"<<tmp->info<<"  ";
            tmp=tmp->hlink;
        }
        cout<<endl;
        cout<<G.xlist[i].data<<"����"<<endl;
        ArcBox *tmp1=G.xlist[i].firstout;
       while(tmp1!=NULL)
        {
            cout<<"w:"<<"("<<tmp1->info<<")";
            cout<<tmp1->tailvex<<"->"<<tmp1->headvex<<"  ";//<<"w:"<<tmp->info<<"  ";
            tmp1=tmp1->tlink;
        }
        cout<<endl;
    }
    return;
}
/*
�ڽӾ���ת�ڽӱ�
*/
void turn0to1(MTGraph &G0,AdjGraph &G1)
{
    G1.e=G0.e;
    G1.n=G0.n;
    for(int i=1;i<=G0.n;i++)
    {
        G1.verlist[i].vertex=G0.vertex[i];
        G1.verlist[i].firstedge=NULL;
    }
    for(int i=1;i<=G0.n;i++)
    {
        for(int j=1;j<=G0.n;j++)
        {
            if(G0.edge[i][j]!=0)
            {
                EdgeNode *p=new EdgeNode;
                p->cost=G0.edge[i][j];
                p->adjvex=j;
                EdgeNode *tmp;
                tmp=G1.verlist[i].firstedge;
                G1.verlist[i].firstedge=p;
                p->next=tmp;
            }
        }
    }
}
/*
�ڽӱ�ת�ڽӾ���
*/
void turn1to0(MTGraph &G0,AdjGraph &G1)
{

    G0.e=G1.e;
    G0.n=G1.n;
    for(int i=1;i<=G1.n;i++)
    {
        G0.vertex[i]=G1.verlist[i].vertex;
    }
    for(int i=1;i<=G0.n;i++)
    {
        for(int j=1;j<=G0.n;j++)
        {
            G0.edge[i][j]=0;
        }
    }
    for(int i=1;i<=G1.n;i++)
    {
        EdgeNode *tmp=G1.verlist[i].firstedge;
        while(tmp!=NULL)
        {
            G0.edge[i][tmp->adjvex]=tmp->cost;
            tmp=tmp->next;
        }
    }
}
/*
�ڽӱ�תʮ������
*/
void turn1to2(AdjGraph &G1,OLGraph &G2)
{

    G2.arcnum=G1.e;
    G2.vexnum=G1.n;
    for(int i=1;i<=G2.vexnum;i++)
    {
        G2.xlist[i].data=G1.verlist[i].vertex;
        G2.xlist[i].firstin=NULL;
        G2.xlist[i].firstout=NULL;
    }
    for(int k=1;k<=G2.vexnum;k++)
    {
        EdgeNode *tmp=G1.verlist[k].firstedge;
        while(tmp!=NULL)
        {
            int m,n,w;
            m=G1.verlist[k].vertex;
            n=tmp->adjvex;
            w=tmp->cost;
            ArcBox *p=new ArcBox;
            p->tailvex=m;
            p->headvex=n;
            p->info=w;
            p->tlink=G2.xlist[m].firstout;
            p->hlink=G2.xlist[n].firstin;
            G2.xlist[m].firstout=p;
            G2.xlist[n].firstin=p;
            tmp=tmp->next;
        }
    }
}
/*
ʮ������ת�ڽӱ�
*/
void turn2to1(AdjGraph &G1,OLGraph &G2)
{

    G1.e=G2.arcnum;
    G1.n=G2.vexnum;
    for(int i=1;i<=G1.n;i++)
    {
        G1.verlist[i].vertex=G2.xlist[i].data;
        G1.verlist[i].firstedge=NULL;
    }

        int m,n,w;
        for(int j=1;j<=G1.n;j++)
        {
            ArcBox *tmp=G2.xlist[j].firstin;
            while(tmp!=NULL)
            {
                w=tmp->info;
                m=tmp->tailvex;
                n=tmp->headvex;
                EdgeNode *p=new EdgeNode;
                p->cost=w;
                p->adjvex=n;
                EdgeNode *tmp1;
                tmp1=G1.verlist[m].firstedge;
                G1.verlist[m].firstedge=p;
                p->next=tmp1;
                tmp=tmp->hlink;
            }
        }
}
/*
�ڽӾ���תʮ������
*/
void turn0to2(MTGraph &G0,OLGraph &G2)
{

    G2.arcnum=G0.e;
    G2.vexnum=G0.n;
    for(int i=1;i<=G2.vexnum;i++)
    {
        G2.xlist[i].data=G0.vertex[i];
        G2.xlist[i].firstin=NULL;
        G2.xlist[i].firstout=NULL;
    }

     for(int i=1;i<=G0.n;i++)
    {
        for(int j=1;j<=G0.n;j++)
        {
            if(G0.edge[i][j]!=0)
            {
                int m,n,w;
                m=i;
                n=j;
                w=G0.edge[i][j];
                ArcBox *p=new ArcBox;

                p->tailvex=m;
                p->headvex=n;
                p->info=w;
                p->tlink=G2.xlist[m].firstout;
                p->hlink=G2.xlist[n].firstin;
                G2.xlist[m].firstout=p;
                G2.xlist[n].firstin=p;
            }
        }
    }

}
/*
ʮ������ת�ڽӾ���
*/
void turn2to0(MTGraph &G0,OLGraph &G2)
{

    G0.e=G2.arcnum;
    G0.n=G2.vexnum;
    for(int i=1;i<=G0.n;i++)
    {
        G0.vertex[i]=G2.xlist[i].data;
    }
    for(int i=1;i<=G0.n;i++)
    {
        for(int j=1;j<=G0.n;j++)
        {
            G0.edge[i][j]=0;
        }
    }
        for(int j=1;j<=G0.n;j++)
        {
            int m,n,w;
            ArcBox *tmp=G2.xlist[j].firstin;
            while(tmp!=NULL)
            {
                w=tmp->info;
                m=tmp->tailvex;
                n=tmp->headvex;
                G0.edge[m][n]=w;
                tmp=tmp->hlink;
            }
        }
}
int visited[VertexNum];//���ʱ��������ȫ�ֱ���
int dfn[VertexNum];//����������
/*
��ʼ��
*/
void initial()
{
    for(int i=0;i<VertexNum;i++)
    {
        visited[i]=0;
        dfn[i]=0;
    }
}
/*
���ڽӾ�������������������ݹ�
*/
void DFS0(MTGraph *G,int i)
{
    cout<<G->vertex[i]<<"  ";
    visited[i]=1;
    for(int j=1;j<=G->n;j++)
    {
        if((G->edge[i][j]!=0)&&visited[j]==0)
        {
            DFS0(G,j);
        }
    }
}
/*
���ڽӱ�����������������ݹ�
*/
void DFS1(AdjGraph *G,int i)
{
    EdgeNode *p;
    cout<<G->verlist[i].vertex<<"  ";
    visited[i]=1;
    p=G->verlist[i].firstedge;
    while(p)
    {
        if(!visited[p->adjvex])
            DFS1(G,p->adjvex);
        p=p->next;
    }
}
/*
��ʮ����������������������ݹ�
*/
void DFS2(OLGraph *G,int i)
{
    ArcBox *p;
    cout<<G->xlist[i].data<<"  ";
    visited[i]=1;
    p=G->xlist[i].firstout;
    while(p)
    {
        if(!visited[p->headvex])
            DFS2(G,p->headvex);
        p=p->tlink;
    }
}
/*
���ڽӾ������������������
*/
void BFS0(MTGraph *G,int k)
{
    int i,j;
    queue<int>q;
    cout<<G->vertex[k]<<"  ";
    visited[k]=1;
    q.push(G->vertex[k]);
    while(!q.empty())
    {
        i=q.front();
        q.pop();
        for(j=1;j<=G->n;j++)
        {
            if(G->edge[i][j]!=0&&visited[j]==0)
            {
                cout<<G->vertex[j]<<"  ";
                visited[j]=1;
                q.push(G->vertex[j]);
            }
        }
    }
}
/*
���ڽӱ����������������
*/
void BFS1(AdjGraph *G,int k)
{
    int i;
    EdgeNode *p;
    queue<int>q;
    cout<<G->verlist[k].vertex<<"  ";
    visited[k]=1;
    q.push(G->verlist[k].vertex);
    while(!q.empty())
    {
        i=q.front();
        q.pop();
        p=G->verlist[i].firstedge;
        while(p)
        {
            if(!visited[p->adjvex])
            {
                cout<<G->verlist[p->adjvex].vertex<<"  ";
                visited[p->adjvex]=1;
                q.push(p->adjvex);
            }
            p=p->next;
        }
    }
}
/*
��ʮ���������������������
*/
void BFS2(OLGraph *G,int k)
{
    int i;
    ArcBox *p;
    queue<int>q;
    cout<<G->xlist[k].data<<"  ";
    visited[k]=1;
    q.push(G->xlist[k].data);
    while(!q.empty())
    {
        i=q.front();
        q.pop();
        p=G->xlist[i].firstout;
        while(p)
        {
            if(!visited[p->headvex])
            {
                cout<<G->xlist[p->headvex].data<<"  ";
                visited[p->headvex]=1;
                q.push(p->headvex);

            }
            p=p->tlink;
        }
    }
}
/*
���ڽӾ�������������������ǵݹ�
*/
void DFS_0(MTGraph *G,int i)
{
    stack<int>s;
    s.push(G->vertex[i]);
    cout<<s.top()<<"  ";
    visited[s.top()]=1;
    while(!s.empty())
    {
        i=s.top();
        for(int j=1;j<=G->n;j++)
        {
            if((G->edge[i][j]!=0)&&visited[j]==0)
            {
                s.push(G->vertex[j]);
                cout<<s.top()<<"  ";
                visited[j]=1;
                i=j;j=0;
            }
        }
        if(!s.empty())
        {
            s.pop();
        }
    }

}
/*
���ڽӱ�����������������ǵݹ�
*/
void DFS_1(AdjGraph *G,int i)
{
   // cout<<G->verlist[10].firstedge->adjvex<<endl;
    stack<int>s;
    s.push(G->verlist[i].vertex);
    cout<<s.top()<<"  ";
    visited[s.top()]=1;
    int flag=0;
    while(!s.empty())
    {

        i=s.top();
        for(EdgeNode *tmp=G->verlist[i].firstedge;tmp!=NULL;)
        {
           // cout<<"&"<<tmp->adjvex<<" ";
            if(visited[tmp->adjvex]==0)
            {
                s.push(tmp->adjvex);
                cout<<s.top()<<"  ";
                visited[tmp->adjvex]=1;
                i=s.top();
                flag=1;

             }
             tmp=tmp->next;
             if(flag==1){flag=0;tmp=G->verlist[i].firstedge;}

        }
        if(!s.empty())
        {
            s.pop();
        }
    }

}
/*
��ʮ����������������������ǵݹ�
*/
void DFS_2(OLGraph *G,int i)
{
    stack<int>s;
    s.push(G->xlist[i].data);
    cout<<s.top()<<"  ";
    visited[s.top()]=1;
    int flag=0;
    while(!s.empty())
    {
        i=s.top();

        for(ArcBox *tmp=G->xlist[i].firstout;tmp!=NULL;)
        {
            if(visited[tmp->headvex]==0)
            {
                s.push(tmp->headvex);
                cout<<s.top()<<"  ";
                visited[tmp->headvex]=1;
                i=s.top();
                flag=1;

             }
             tmp=tmp->tlink;
             if(flag==1){flag=0;tmp=G->xlist[i].firstout;}

        }
        if(!s.empty())
        {
            s.pop();
        }
    }
}
int main()
{
    int option;
    cout<<"1.�ڽӾ�����"<<endl;
    cout<<"2.�ڽӱ���"<<endl;
    cout<<"3.�ڽӶ��ر���"<<endl;
    cout<<"4.�����ڽӾ���������ת�����ڽӱ�"<<endl;
    cout<<"5.�����ڽӱ�������ת�����ڽӾ���"<<endl;
    cout<<"6.�����ڽӱ�������ת����ʮ������"<<endl;
    cout<<"7.����ʮ������������ת�����ڽӱ�"<<endl;
    cout<<"8.�����ڽӾ���������ת����ʮ������"<<endl;
    cout<<"9.����ʮ������������ת�����ڽӾ���"<<endl;
    scanf("%d",&option);

    if(option==1)
    {
        freopen("test.txt","r",stdin);
        MTGraph Graph;
        Create0(&Graph);
        Print0(&Graph);
        initial();
        cout<<"�ڽӾ����������ȱ������ݹ飩"<<endl;
        DFS0(&Graph,2);
        cout<<endl;
        initial();
        cout<<"�ڽӾ����������ȱ������ǵݹ飩"<<endl;
        DFS_0(&Graph,2);
        cout<<endl;
        initial();
        cout<<"�ڽӾ���Ĺ�����ȱ���"<<endl;
        BFS0(&Graph,2);
        fclose(stdin);
    }

    if(option==2)
    {
        freopen("test.txt","r",stdin);
        AdjGraph Graph;
        Create1(Graph);
        Print1(Graph);
        initial();
        cout<<"�ڽӱ��������ȱ������ݹ飩"<<endl;
        DFS1(&Graph,2);
        cout<<endl;
        initial();
        cout<<"�ڽӱ��������ȱ������ǵݹ飩"<<endl;
        DFS_1(&Graph,2);
        cout<<endl;
        initial();
        cout<<"�ڽӱ�Ĺ�����ȱ���"<<endl;
        BFS1(&Graph,2);
        fclose(stdin);
    }

    if(option==3)
    {
        freopen("test.txt","r",stdin);
        OLGraph Graph;
        Create2(Graph);
        Print2(Graph);
        initial();
        cout<<"�����ڽӱ��������ȱ������ݹ飩"<<endl;
        DFS2(&Graph,2);
        cout<<endl;
        initial();
        cout<<"�����ڽӱ��������ȱ������ǵݹ飩"<<endl;
        DFS_2(&Graph,2);
        cout<<endl;
        initial();
        cout<<"�����ڽӱ�Ĺ�����ȱ���"<<endl;
        BFS2(&Graph,2);
        fclose(stdin);
    }

    if(option==4)
    {
        freopen("test.txt","r",stdin);
        MTGraph Graph0;
        AdjGraph Graph1;
        Create0(&Graph0);
        cout<<"ת��ǰ"<<endl;
        Print0(&Graph0);
        turn0to1(Graph0,Graph1);
        cout<<"ת����"<<endl;
        Print1(Graph1);
        fclose(stdin);
    }

    if(option==5)
    {
        freopen("test.txt","r",stdin);
        MTGraph Graph0;
        AdjGraph Graph1;
        Create1(Graph1);
        cout<<"ת��ǰ"<<endl;
        Print1(Graph1);
        turn1to0(Graph0,Graph1);
        cout<<"ת����"<<endl;
        Print0(&Graph0);
        fclose(stdin);

    }

    if(option==6)
    {
        freopen("test.txt","r",stdin);
        AdjGraph Graph1;
        OLGraph Graph2;
        Create1(Graph1);
        cout<<"ת��ǰ"<<endl;
        Print1(Graph1);
        turn1to2(Graph1,Graph2);
        cout<<"ת����"<<endl;
        Print2(Graph2);
        fclose(stdin);
    }

     if(option==7)
    {
        freopen("test.txt","r",stdin);
        AdjGraph Graph1;
        OLGraph Graph2;
        Create2(Graph2);
        cout<<"ת��ǰ"<<endl;
        Print2(Graph2);
        turn2to1(Graph1,Graph2);
        cout<<"ת����"<<endl;
        Print1(Graph1);
        fclose(stdin);
    }

     if(option==8)
    {
        freopen("test.txt","r",stdin);
        MTGraph Graph0;
        OLGraph Graph2;
        Create0(&Graph0);
        cout<<"ת��ǰ"<<endl;
        Print0(&Graph0);
        turn0to2(Graph0,Graph2);
        cout<<"ת����"<<endl;
        Print2(Graph2);
        fclose(stdin);
    }

     if(option==9)
    {
        freopen("test.txt","r",stdin);
        MTGraph Graph0;
        OLGraph Graph2;
        Create2(Graph2);
        cout<<"ת��ǰ"<<endl;
        Print2(Graph2);
        turn2to0(Graph0,Graph2);
        cout<<"ת����"<<endl;
        Print0(&Graph0);
        fclose(stdin);
    }
    return 0;
}

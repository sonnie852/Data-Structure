#include<stdio.h>
#include<stdlib.h>
#include<cstdio>
#include<iostream>
#include<stack>
#include<queue>
#include <string.h>
#include<math.h>
#include<time.h>
#define max 100
using namespace std;

clock_t startTime1,endTime1,startTime2,endTime2,startTime3,endTime3;
int cnt2=0,cnt3=0;
typedef struct BiTree
{
    char data;
    struct BiTree *Lchild;
    struct BiTree *Rchild;
    bool ltag, rtag;
}BiTree,*Binary_Tree;
Binary_Tree Head=NULL;
int x;
Binary_Tree s[max]; /*  ����ָ�����飬��Ŷ��������ָ�� */
Binary_Tree *ptmp;
int cnt=0;
Binary_Tree CreateBT()
{   int i,j;
    char ch;
    Binary_Tree bt,p; /* bt Ϊ����p���ڽ������ */
    cin>>i>>ch ;
    while ( i != 0&&ch != '0') {
    p =new struct BiTree;
    p->data=ch;
    p->Lchild=NULL; p->Rchild=NULL;

    s[i]=p;
    if (i==1) bt=p ;
    else {
    j=i/2; /*�����ı��*/
    if (i%2==0) s[j]->Lchild=p; /*i��j������� */
    else s[j]->Rchild=p; /*i��j���Ҷ��� */
    }
    cin>>i>>ch ;
    }
    return s[1];
}

//����һ��������

char ch;
int CreateBiTree(Binary_Tree *T)
{
   *T=(Binary_Tree)malloc(sizeof(BiTree));
    if(!(*T))
        exit(OVERFLOW);
    scanf("%c",&ch);

    if(ch=='0')
       {*T=NULL;}
    else
    {
        (*T)->data=ch;
        (*T)->ltag=true;
        (*T)->rtag=true;
        CreateBiTree(&((*T)->Lchild));
        CreateBiTree(&((*T)->Rchild));
    }
    return 1;
}

//�ȱ���������
int PreShowBiTree(Binary_Tree T)
{
    if(T!=NULL)
    {
        printf("%c  ",T->data);
        PreShowBiTree(T->Lchild);
        PreShowBiTree(T->Rchild);
    }
    return 1;
}


//�б���������
int MidShowBiTree(Binary_Tree T)
{
    if(T!=NULL)
    {
        MidShowBiTree(T->Lchild);
        printf("%c  ",T->data);
        MidShowBiTree(T->Rchild);
    }
    return 1;
}


//�����������
int BehShowBiTree(Binary_Tree T)
{
    if(T!=NULL)
    {
        BehShowBiTree(T->Lchild);
        BehShowBiTree(T->Rchild);
        printf("%c  ",T->data);
    }
    return 1;
}
//�������������
int LevelOrderTraversal(Binary_Tree T)
{
    queue<struct BiTree>Que;
    if(T==NULL)return -1;
    Que.push(*T);
    while(!Que.empty())
    {
        BiTree temp;
        temp=Que.front();
        Que.pop();
        cout<<temp.data<<"  ";
        cnt++;
        T=&temp;
        if(T->Lchild!=NULL){Que.push(*(T->Lchild));}
        if(T->Rchild!=NULL){Que.push(*(T->Rchild));}
    }
    return 0;
}
int PreShowBiTree1(Binary_Tree T)
{
    stack<Binary_Tree>S1;
    ptmp=(Binary_Tree *)malloc(sizeof(Binary_Tree)*cnt);
    int i=-1;
    while(T||!S1.empty())
    {
        while(T)
        {
            printf("%c  ",T->data);
            ptmp[++i]=T;
            S1.push(T);
            T=T->Lchild;
        }
        if(!S1.empty())
        {
            T=S1.top();
            S1.pop();
            T=T->Rchild;
        }
    }
    return 1;
}

//�б���������
int MidShowBiTree1(Binary_Tree T)
{
   stack<Binary_Tree>Stk;
   Binary_Tree T1=T;
   while(T1||!Stk.empty())
   {
       while(T1)
       {
           Stk.push(T1);
           T1=T1->Lchild;
           cnt2++;
       }
       if(!Stk.empty())
       {
           T1=Stk.top();
           Stk.pop();
           printf("%c  ",T1->data);
           T1=T1->Rchild;
           cnt2++;
       }
   }
   return 1;
}
int BehShowBiTree1(Binary_Tree T)
{
    stack<Binary_Tree> S2;
    Binary_Tree curr = T ;           // ָ��ǰҪ���Ľڵ�
    Binary_Tree previsited = NULL;    // ָ��ǰһ�������ʵĽڵ�
    while(curr != NULL || !S2.empty())  // ջ��ʱ����
    {
        while(curr != NULL)            // һֱ������ֱ��Ϊ��
        {
            S2.push(curr);
            curr = curr->Lchild;
        }
        curr = S2.top();
        // ��ǰ�ڵ���Һ������Ϊ�ջ����Ѿ������ʣ�����ʵ�ǰ�ڵ�
        if(curr->Rchild == NULL || curr->Rchild == previsited)
        {
            printf("%c  ",curr->data);
            previsited = curr;
            S2.pop();
            curr = NULL;
        }
        else
            curr = curr->Rchild;      // ��������Һ���
    }
   return 1;
}

BiTree *pre=NULL;
void InThread(Binary_Tree T)
{
    Binary_Tree p;
    p=T;
    if(p)
    {
        InThread(p->Lchild);
        p->ltag=(p->Lchild)?true:false;
        p->rtag=(p->Rchild)?true:false;
        if(pre){
            if(pre->rtag==false)
                pre->Rchild=p;
            if(p->ltag==false)
                p->Lchild=pre;
        }
        pre=p;
        InThread(p->Rchild);
    }
}
Binary_Tree InOrderTh(Binary_Tree T)//������
{
    Binary_Tree temp1=T;
    Binary_Tree temp2=T;
    Binary_Tree Head;
    Head=new BiTree;
    Head->Lchild=T;
    Head->Rchild=Head;
    Head->data='#';
    Head->ltag=true;
    Head->rtag=true;
    InThread(T);
    while(temp1->ltag!=false)
    {
        temp1=temp1->Lchild;
    }
    temp1->Lchild=Head;
    while(temp2->rtag!=false)
    {
        temp2=temp2->Rchild;
    }
    temp2->Rchild=Head;
    return Head;

}
Binary_Tree PreNext(Binary_Tree p)//������
{
  //  if(p==Head)return NULL;
    Binary_Tree q;
    if(p->ltag==true)
        q=p->Lchild;
    else{
        q=p;
        while(q->rtag==false)
            q=q->Rchild;
        q=q->Rchild;
    }
    return q;
}
//���������ӣ���������ӣ����û������ӣ�������������������
Binary_Tree InNext(Binary_Tree p)//������
{
    Binary_Tree q;
    q=p->Rchild;
    cnt3++;
    if(p->rtag==true)
    {
        if(q->ltag==true)
        while(q->ltag==true)
        {q=q->Lchild;cnt3++;}
        else cnt3++;
    }
    return q;
}
Binary_Tree BeNext(Binary_Tree p)//������
{
    Binary_Tree q;
    Binary_Tree tmp;
    Binary_Tree T;
    for(int i=0;i<cnt;i++)
    {
        if(ptmp[i]->Lchild==p&&ptmp[i]->ltag==true)
        {
            tmp=ptmp[i];
            break;
        }
        if(ptmp[i]->Rchild==p&&ptmp[i]->rtag==true)
        {
            tmp=ptmp[i];
            break;
        }
    }

    q=tmp;
    if(q->Lchild==p&&q->rtag==true)
    {
        q=q->Rchild;
        while(q->ltag==true)q=q->Lchild;
        return q;
    }
    if(q->Rchild==p||q->rtag==false)
    {
        return q;
    }
}
void PreShowBiTree2(Binary_Tree Head)//��������ǵݹ�
{
    Binary_Tree p;
    p=Head->Lchild;
    while(p!=Head)
    {
        cout<<p->data<<"  ";
        p=PreNext(p);
    }
}
void InOrderTh2(Binary_Tree Head)//��������ǵݹ�
{
    Binary_Tree p=Head->Lchild;

     while(p->ltag==true)
            p=p->Lchild;
    while(p!=Head)
    {

      printf("%c  ",p->data);
      p=InNext(p);
    }

}

//�ҵ��丸���������������Ǹýڵ㣬��ô�Ǹ����������������ڵ㡣������Ҷ��ӣ����Ǹ��׽ڵ㡣
void BeOrderTh2(Binary_Tree Head)//��������ǵݹ�
{
    Binary_Tree p=Head->Lchild;
     while(p->ltag==true)
            p=p->Lchild;
     while(p!=Head->Lchild)
     {
        cout<<p->data<<"  ";
        p=BeNext(p);
     }
     cout<<p->data<<endl;

     cout<<endl;
}
char *a=(char *)malloc(sizeof(char)*(pow(2,x)-1));
void Print2x(Binary_Tree T,int x)
{
    queue<struct BiTree>Q;
    int m=1;
    if(T==NULL){return;}
    Q.push(*T);
    
    int x1=x;
   
    while(!Q.empty())
    {
        BiTree temp;
        temp=Q.front();
        Q.pop();
        a[m++]=temp.data;
        T=&temp;
        if(T->Lchild==NULL&&m<=pow(2,x)-1)a[m++]='#';
        if(T->Rchild==NULL&&m<=pow(2,x)-1)a[m++]='#';
        if(T->Lchild!=NULL){
                Q.push(*(T->Lchild));
        }
        if(T->Rchild!=NULL){
                Q.push(*(T->Rchild));
        }
        if(m>pow(2,x)-1)return ;
    }

}
void Print2(Binary_Tree T,int x)
{
    Print2x(T,x);
    for(int k=0;k<x;k++)cout<<" ";
    for(int i=1;i<=pow(2,x)-1;i++)
    {
        cout<<a[i]<<" ";
        if(fabs((log(i+1)/log(2))-(int)((log(i+1)/log(2)))==0||i==7||i==15))
           {
               cout<<endl;
            for(int k=0;k<x-i;k++)cout<<" ";
           }
    }
    cout<<endl;
    return;
}
void Print1(Binary_Tree T,int x)
{
    queue<struct BiTree>Q1;
    if(T==NULL){return;}
    Q1.push(*T);
    double t=0;
    int x1=x;
    for(int i=0;i<x;i++)cout<<" ";
    while(!Q1.empty())
    {

        BiTree temp;
        temp=Q1.front();
        Q1.pop();
        cout<<temp.data<<"  ";
        t++;
       
        if(fabs((log(t+1)/log(2))-(int)((log(t+1)/log(2))))==0||t==7||t==15)
        {
            cout<<endl;
            x1--;
            for(int i=0;i<x1;i++)cout<<" ";
        }
        T=&temp;
        if(T->Lchild!=NULL){Q1.push(*(T->Lchild));}
        if(T->Rchild!=NULL){Q1.push(*(T->Rchild));}
        if((log(t+1)/log(2))==x)break;
    }
    cout<<endl;
    return ;
}

int main()
{
    BiTree * T=NULL;
    printf("�봴��һ����������ѡ�񴴽���ʽ:\n");
    cout<<"1.��������ݹ齨��:"<<endl;
    cout<<"�������������˳���������Ԫ�أ��м䲻���ո�#��ʾ�ս��"<<endl;
    cout<<"2.�ǵݹ齨��"<<endl;
    cout<<"���ղ��������˳���������Ԫ�أ�ÿ����"<<endl<<"��ͷ����λ���Լ���Ӧλ�õ�Ԫ�أ��ԡ�0 0����������"<<endl;
    int option;
    cin>>option;
    if(option==1){ freopen("exp.txt","r",stdin);CreateBiTree(&T);}
    if(option==2){  freopen("exp1.txt","r",stdin);T=CreateBT();}
    scanf("%d",&x);

    cout<<"�������ṹ����"<<endl;
    Print1(T,x);
    printf("�ݹ��������: \n");
    PreShowBiTree(T);
    printf("\n");
    printf("�ݹ��������:  \n");
    startTime1 = clock();
    MidShowBiTree(T);
    endTime1 = clock();
    printf("\n");
    printf("�ݹ�������: \n");
    BehShowBiTree(T);
    printf("\n");
    printf("�ǵݹ����������\n");
    PreShowBiTree1(T);
    printf("\n");
    printf("�ǵݹ��������:  \n");
    startTime2 = clock();
    MidShowBiTree1(T);
    endTime2 = clock();
    printf("\n");
    printf("�ǵݹ�������: \n");
    BehShowBiTree1(T);
    printf("\n");
    printf("���������\n");
    LevelOrderTraversal(T);
    printf("\n");
    printf("����������֮��\n");
    Binary_Tree t;
    t=InOrderTh(T);
    cout<<"����������������£�"<<endl;
    Print2(T,x+1);
    cout<<endl;
    printf("�ǵݹ����������\n");
    PreShowBiTree2(t);
    printf("\n");
    printf("�ǵݹ��������:  \n");
    startTime3 = clock();
    InOrderTh2(t);
    endTime3=clock();
    printf("\n");
    printf("�ǵݹ�������: \n");
    BeOrderTh2(t);
    printf("\n");

    fclose(stdin);
   // cout << "Totle Time : " <<(double)(endTime1 - startTime1) / CLOCKS_PER_SEC << "s" << endl;
   // cout << "Totle Time : " <<(double)(endTime2 - startTime2) / CLOCKS_PER_SEC << "s" << endl;
   //  cout << "Totle Time : " <<(double)(endTime3 - startTime3) / CLOCKS_PER_SEC << "s" << endl;

    cout<<"�ǵݹ���ջ����������� ��"<<cnt2<<"��"<<endl;
    cout<<"��������������������� ��"<<cnt3<<"��"<<endl;
    return 0;
}


#include<iostream>
#include<cstdio>
#include <malloc.h>
#include<math.h>
#define MAX(a, b)    ( (a) > (b) ? (a) : (b) )

using namespace std;


typedef int Type;

typedef struct AVLTreeAVLTreeNode{
    Type value;                    // �ؼ���(��ֵ)
    int height_count;
    struct AVLTreeAVLTreeNode *left;    // ����
    struct AVLTreeAVLTreeNode *right;    // �Һ���
}AVLTreeNode, *AVLTree;

int Pheightc;
char Phbuf[6][200];
int Phx;

void pprint_tree(AVLTree tree, int level){
    if (tree == NULL){
        Phx += (pow(2, Pheightc - level) - 1);
        return;
    }
    char(*a)[200] = Phbuf;
    pprint_tree(tree->left, level + 1);
    a[level][Phx++] = tree->value;
    pprint_tree(tree->right, level + 1);

}

int height_count(AVLTreeNode *p)
{
	if(p==NULL)return 0;
	else{return ((AVLTreeNode *)(p))->height_count; }
}
/*
	��ӡ���ĺ���
*/
void printTree(AVLTree tree){
    Pheightc=0;
    Phx=0;
    if (tree == NULL) return;
    char(*a)[200] = Phbuf;
    for (int i = 0; i<6; i++){
        for (int j = 0; j<200; j++){
            a[i][j] = '#';
        }
    }
    //�Ȼ�ȡ���߶�
    Pheightc = height_count(tree);
    if (Pheightc > 6){
        cout << "error" << endl;
        return;
    }
    pprint_tree(tree, 0);
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 200; j++){
            if (a[i][j] =='#') cout << " ";
            else cout << (int)a[i][j];
        }
        cout << endl;
    }
}

/*
  ��ȡAVL���ĸ߶�
 */
int avltree_height_count(AVLTree tree)
{
    return height_count(tree);
}

/*
  LL�������Ӧ�����(����ת)��

  ����ֵ����ת��ĸ��ڵ�
 */
AVLTreeNode* LLRotation(AVLTree temp2)
{
    AVLTree temp1;

    temp1 = temp2->left;
    temp2->left = temp1->right;
    temp1->right = temp2;

    temp2->height_count = MAX( height_count(temp2->left), height_count(temp2->right)) + 1;
    temp1->height_count = MAX( height_count(temp1->left), temp2->height_count) + 1;

    return temp1;
}

/*
  RR�����Ҷ�Ӧ�����(�ҵ���ת)��

  ����ֵ����ת��ĸ��ڵ�
 */
 AVLTreeNode* RRRotation(AVLTree temp1)
{
    AVLTree temp2;

    temp2 = temp1->right;
    temp1->right = temp2->left;
    temp2->left = temp1;

    temp1->height_count = MAX( height_count(temp1->left), height_count(temp1->right)) + 1;
    temp2->height_count = MAX( height_count(temp2->right), temp1->height_count) + 1;

    return temp2;
}


/*
  LR�����Ҷ�Ӧ�����(��˫��ת)��

  ����ֵ����ת��ĸ��ڵ�
 */
 AVLTreeNode* LRRotation(AVLTree temp3)
{
    temp3->left = RRRotation(temp3->left);

    return LLRotation(temp3);
}

/*
  RL�������Ӧ�����(��˫��ת)��

  ����ֵ����ת��ĸ��ڵ�
 */
 AVLTreeNode* RLRotation(AVLTree temp1)
{
    temp1->right = LLRotation(temp1->right);

    return RRRotation(temp1);
}

/*
  �������뵽AVL���У������ظ��ڵ�
  ����ֵ��
      ���ڵ�
 */
AVLTreeNode* avltree_insert(AVLTree tree, Type value)
{
    if (tree == NULL)
    {
        // �½��ڵ�
		AVLTreeNode* p;
		p = (AVLTreeNode *)malloc(sizeof(AVLTreeNode));
		p->value = value;
		p->height_count = 0;
		p->left = NULL;
		p->right = NULL;
		tree=p;
        if (tree==NULL)
        {
            printf("ERROR!\n");
            return NULL;
        }
    }
    else if (value < tree->value) // Ӧ�ý�value���뵽"tree��������"�����
    {
        tree->left = avltree_insert(tree->left, value);
        // ����ڵ����AVL��ʧȥƽ�⣬�������Ӧ�ĵ��ڡ�
        if (height_count(tree->left) - height_count(tree->right) == 2)
        {
            if (value < tree->left->value)
            {
                cout<<"LL֮ǰ"<<endl;
                printTree(tree);
                tree = LLRotation(tree);
                cout<<"LL֮��"<<endl;
                printTree(tree);
            }
            else
            {
                cout<<"LR֮ǰ"<<endl;
                printTree(tree);
                tree = LRRotation(tree);
                cout<<"LR֮��"<<endl;
                printTree(tree);
            }
        }
    }
    else if (value > tree->value) // Ӧ�ý�value���뵽"tree��������"�����
    {
        tree->right = avltree_insert(tree->right, value);
        // ����ڵ����AVL��ʧȥƽ�⣬�������Ӧ�ĵ��ڡ�
        if (height_count(tree->right) - height_count(tree->left) == 2)
        {
            if (value > tree->right->value)
            {
                cout<<"RR֮ǰ"<<endl;
                printTree(tree);
                tree = RRRotation(tree);
                cout<<"RR֮��"<<endl;
                printTree(tree);
            }
            else
            {
                cout<<"RL֮ǰ"<<endl;
                printTree(tree);
                tree = RLRotation(tree);
                cout<<"RL֮��"<<endl;
                printTree(tree);
            }
        }
    }
    else //value == tree->value)
    {
        printf("error!\n");
    }
    tree->height_count = MAX( height_count(tree->left), height_count(tree->right)) + 1;
    return tree;
}
/*
    ����
*/
AVLTreeNode *avltree_search(AVLTree tree,Type value)
{
        if(tree->value==value)return tree;
        if(tree->value<value) return avltree_search(tree->right,value);
        if(tree->value>value) return avltree_search(tree->left,value);
}

/*
    �����,��С�ڵ�
*/

AVLTreeNode *avltree_maximum(AVLTreeNode * T)
{
    AVLTreeNode *temp=T;
    while(temp->right!=NULL)
    {
        temp=temp->right;
    }
    return temp;
}
AVLTreeNode *avltree_minimum(AVLTreeNode * T)
{
    AVLTreeNode *temp=T;
    while(temp->left!=NULL)
    {
        temp=temp->left;
    }
    return temp;
}
/*
  ɾ�����(z)�����ظ��ڵ�
  ����ֵ��
      ���ڵ�
 */
AVLTreeNode* delete_AVLTreeNode(AVLTree tree, AVLTreeNode *z)
{
    // ��Ϊ�� ���� û��Ҫɾ���Ľڵ㣬ֱ�ӷ���NULL��
    if (tree==NULL || z==NULL)
        return NULL;

    if (z->value < tree->value)        // ��ɾ���Ľڵ���tree����������
    {
        tree->left = delete_AVLTreeNode(tree->left, z);
        // ɾ���ڵ����AVL��ʧȥƽ�⣬�������Ӧ�ĵ��ڡ�
        if (height_count(tree->right) - height_count(tree->left) == 2)
        {
            AVLTreeNode *r =  tree->right;
            if (height_count(r->left) > height_count(r->right))
                tree = RLRotation(tree);
            else
                tree = RRRotation(tree);
        }
    }
    else if (z->value > tree->value)// ��ɾ���Ľڵ���"tree��������"��
    {
        tree->right = delete_AVLTreeNode(tree->right, z);
        // ɾ���ڵ����AVL��ʧȥƽ�⣬�������Ӧ�ĵ��ڡ�
        if (height_count(tree->left) - height_count(tree->right) == 2)
        {
            AVLTreeNode *l =  tree->left;
            if (height_count(l->right) > height_count(l->left))
                tree = LRRotation(tree);
            else
                tree = LLRotation(tree);
        }
    }
    else    // tree�Ƕ�ӦҪɾ���Ľڵ㡣
    {
        // tree�����Һ��Ӷ��ǿ�
        if ((tree->left) && (tree->right))
        {
            if (height_count(tree->left) > height_count(tree->right))
            {
                AVLTreeNode *max = avltree_maximum(tree->left);
                tree->value = max->value;
                tree->left = delete_AVLTreeNode(tree->left, max);
            }
            else
            {
                AVLTreeNode *min = avltree_minimum(tree->right);
                tree->value = min->value;
                tree->right = delete_AVLTreeNode(tree->right, min);
            }
        }
        else
        {
            AVLTreeNode *tmp = tree;
            tree = tree->left ? tree->left : tree->right;
            delete(tmp);
        }
    }

    return tree;
}

/*
  ɾ�����(value�ǽڵ�ֵ)�����ظ��ڵ�
  ����ֵ��
      ���ڵ�
 */

AVLTreeNode* avltree_delete(AVLTree tree, Type value)
{
    AVLTreeNode *z;
    if ((z = avltree_search(tree, value)) != NULL)
        tree = delete_AVLTreeNode(tree, z);
    return tree;
}

void inorder(AVLTreeNode* T)
{
    if (T == NULL)
        return;
    else
    {
        inorder(T->left);
        printf("%d ", T->value);
        inorder(T->right);
    }
}

int* search(int value,AVLTreeNode * T)
{
    if(value==T->value){cout<<value<<"��"<<&(T->value)<<endl;return &(T->value);}
    if(value>T->value)return search(value,T->right);
    if(value<T->value)return search(value,T->left);
}

int main()
{
    freopen("test.txt","r",stdin);
    freopen("ans.txt","w",stdout);
    AVLTreeNode* T=NULL;

    int arr[16];
    for(int i=0;i<=15;i++)
        scanf("%d",&arr[i]);


    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
       {
         T = avltree_insert(T,arr[i]);
       }
    cout<<"����:"<<endl;
    inorder(T);
    cout<<endl;
    printTree(T);
    cout<<"ɾ��Ԫ��11��"<<endl;
    T=avltree_delete(T, 11);
    inorder(T);
    cout<<endl;
    printTree(T);
    cout<<endl;
    int *temp;
    temp=search(10,T);
    cout<<temp<<"��:"<<*temp<<endl;
    fclose(stdin);
    fclose(stdout);
    return 0;
}

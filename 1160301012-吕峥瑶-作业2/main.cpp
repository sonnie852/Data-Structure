/*
    ��С���Ż��Ĺ���������
*/
#include <stdio.h>
#include <stdlib.h>
#include<iostream>

#define MAX_TREE_HT 100
using namespace std;
int total=0;
int total1=0;
struct MinHeapNode {
    char data;         // ������ַ������е�һ���ַ�
    unsigned freq;     // �ַ����ֵĴ���
    struct MinHeapNode *left, *right;
};//��С�ѵĽ��
struct MinHeap {
    unsigned size;     // ��С��Ԫ�صĸ���
    unsigned capacity;  //�������
    struct MinHeapNode **array;
};// ��С��: ��Ϊ���ȶ���ʹ��
struct node{
    char arr[95];
    int freq[95];
};
struct code{
    int *hufcode;
    int num;
};
typedef struct node Node;
typedef code Code;
typedef struct MinHeapNode * MHN;
Code str[95];//��95���ַ�����Ӧ�Ĺ���������
Node hufman;
//��ʼ��һ����С�ѽڵ�
MHN newNode(char data, unsigned freq) {
    MHN temp = (MHN) malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
};

// ����һ������Ϊcapacity ����С��
struct MinHeap* newMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    MHN *array = (MHN *)malloc(minHeap->capacity * sizeof(MHN));
    minHeap->array = array;
    return minHeap;
};

//  swap �����ѽڵ�
void swapMinHeapNode(MHN *a, MHN *b) {
    MHN temp = *a;
    *a = *b;
    *b = temp;
}

//�õ����ӽڵ��±꣬Ĭ�ϵ�һ���ڵ��±�Ϊ0
int getLeftIndex(int index) {
    return ((index << 1) + 1);
}

//�õ��Һ��ӽڵ��±꣬Ĭ�ϵ�һ���ڵ��±�Ϊ0
int getRightIndex(int index) {
    return ((index << 1) + 2);
}

// ������С��
void adjustMinHeap(struct MinHeap* minHeap, int index) {
    int less = index;
    int left = getLeftIndex(index);
    int right = getRightIndex(index);
    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[less]->freq) {
        less = left;
    }
    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[less]->freq) {
        less = right;
    }

    if (less != index) {
        swapMinHeapNode(&minHeap->array[less], &minHeap->array[index]);
        adjustMinHeap(minHeap, less);
    }
}

//���ѵĴ�С�Ƿ�Ϊ1
int isSizeOne(struct MinHeap* minHeap) {
    return (minHeap->size == 1);
}

// ����Ƿ���Ҷ�ӽڵ�
int isLeaf(MHN node) {
    return !(node->left) && !(node->right);
}



//ȡ�ö�����С�Ľڵ�
MHN extractMin(struct MinHeap* minHeap) {
    MHN temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size-1];
    --minHeap->size;
    adjustMinHeap(minHeap, 0);
    return temp;
}

// ����С���в���һ���ڵ�
void insertMinHeap(struct MinHeap* minHeap,MHN minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && minHeapNode->freq < minHeap->array[(i-1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i-1) / 2];
        i = (i-1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

//����һ����С��
void buildMinHeap(struct MinHeap* minHeap) {
    int index = minHeap->size - 1;
    int i;
    for (i = (index - 1) / 2; i >= 0; --i) {
        adjustMinHeap(minHeap, i);
    }
}

// ����һ������Ϊ size����С�ѣ������� data[] �е�Ԫ�ص���С��
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) {
    struct MinHeap* minHeap = newMinHeap(size);
    for (int i = 0; i < size; i++) {
        minHeap->array[i] = newNode(data[i],  freq[i]);
    }
    minHeap ->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}

// ������������
MHN buildHuffmanTree(char data[], int freq[], int size) {
    MHN left, right, top;
    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);
    while (!isSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = newNode('.', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}
// ��ӡ
void printArr(int arr[], int n,int tp)
{
    int i;
    for (i = 0; i < n; ++i)
    {
        printf("%d", arr[i]);
        str[tp].hufcode[i]=arr[i];
    }
    printf("\n");
}
// ��ӡ����������
void printCodes(MHN root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr ,top + 1);
    }
    // �����Ҷ�ӽڵ�ʹ�ӡ
    if (isLeaf(root)) {
        printf("%c :", root->data);
        int tp=(int)(root->data)-32;
        str[tp].hufcode=(int *)malloc(sizeof(int)*(top));
        str[tp].num=top;
        printArr(arr, top,tp);
    }
}


// ����������������������ӡ�ù�������
 MHN HuffmanCodes(char data[], int freq[], int size)
{
   //  ������������
    MHN root = buildHuffmanTree(data, freq, size);
   // ��ӡ�����õĹ�������
    int arr[MAX_TREE_HT], top = 0;
    printCodes(root, arr, top);
    return root;
}

//��ʼ������
void initial(Node &hufman)
{
    for(int i=0;i<=94;i++)
    {
        hufman.arr[i]=i+32;
       // printf("%c",hufman.arr[i]);
        hufman.freq[i]=0;
    }
}
//���ļ���ȡ
void ReadFromFile(Node &hufman)
{
    char ch;
    while((scanf("%c",&ch)!=EOF))
    {
        int temp=(int)ch;
        hufman.freq[temp-32]=hufman.freq[temp-32]+1;
    }
}
//��ӡƵ��
void Print(Node &hufman)
{
        hufman.arr[8]='(';
    for(int i=0;i<=94;i++)
    {
        printf("%c : %d\n",hufman.arr[i],hufman.freq[i]);
    }
}
//�ѱ���д��code.txt
void TFileTHuf()
{
    FILE *fp;
    FILE *fp1;
    fp=fopen("test.txt","r");
    fp1=fopen("code.txt","w");
    char ch;
    while((ch= fgetc(fp)) != EOF)
    {
        total1++;
        int tp=(int)ch-32;
        for(int i=0;i<str[tp].num;i++)
        {
             fprintf(fp1,"%d",str[tp].hufcode[i]);
             total++;
        }
    }
    fclose(fp);
    fclose(fp1);
}
//����ת���ĵ�
void Decode(MHN root)
{
    FILE *fp3;
    FILE *fp4;
    fp4=fopen("decode.txt","w");
    fp3=fopen("code.txt","r");
    int temp;
    MHN tempnode=root;
    char ch;
    while((ch= fgetc(fp3))!= EOF)
    {
        temp=ch-'0';
        if(temp==0)tempnode=tempnode->left;
        else tempnode=tempnode->right;
        if(isLeaf(tempnode))
        {
            fprintf(fp4,"%c",tempnode->data);
            tempnode=root;
        }
    }
    fclose(fp3);
    fclose(fp4);
}
//�������̺�Ч��
void analyse(int total,int total1)
{
    cout<<"�ı�һ��"<<total1<<"�ַ�"<<endl;
    cout<<"��������������"<<total<<"bit"<<endl;
    cout<<"ԭ�ı������Ʊ�������"<<total1*8<<"bit"<<endl;
    double rate;
    rate=total/(total1*8.0)*100;
    cout<<"ѹ����Ϊ"<<rate<<"%"<<endl;
}
int main() {
    freopen("test.txt","r",stdin);
    initial(hufman);
    ReadFromFile(hufman);
    Print(hufman);
    MHN root;
    root=HuffmanCodes(hufman.arr, hufman.freq,95);
    Decode(root);
    TFileTHuf();
    analyse(total,total1);
    fclose(stdin);
    return 0;
}

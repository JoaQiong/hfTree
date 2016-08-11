#include <iostream>
#include <string>
using namespace std;
template <class Type>
class hfTree{
private:
    struct Node{    //数组中的元素类型
        Type data;    //结点值
        int weight;   //结点权值
        int parent,left,right;  //结点父结点，左右孩子的下标
    };

    Node *elem;
    int length;

public:
    struct hfCode{   //保存哈夫曼编码的类型
        Type data;  //待编码的字符
        string code;   //对应的哈夫曼编码
    };

    hfTree(const Type *v,const int *w,int size);    //构造一棵哈夫曼树，构造函数无返回值
    void getCode(hfCode result[]); //从哈夫曼树生成的哈夫曼编码
    ~hfTree() {delete [] elem;}

};

template <class Type>
hfTree<Type>::hfTree(const Type *v,const int *w,int size){
    const int MAX_INT=32767;
    int min1,min2; //最小和次最小权值
    int pos1,pos2;  //最小和次最小权值所对应的下标

    //置初值
    length=2*size;
    elem=new Node[length];

    for(int i=size;i<length;i++){
        elem[i].data=v[i-size];
        elem[i].weight=w[i-size];
        elem[i].parent=elem[i].left=elem[i].right=0;
    }

    //归并森林中的树
    for(int i=size-1;i>0;--i){
        int tmp;
        min1=min2=MAX_INT;
        pos1=pos2=0;
        //这里j不应该从size开始，而是从i+1开始
        for(int j=i+1;j<length;++j){
            if(elem[j].parent==0){
                if(elem[j].weight<min1){
                    min2=min1;
                    pos2=pos1;
                    min1=elem[j].weight;
                    pos1=j;
                }
                else if(elem[j].weight<min2){
                    min2=elem[j].weight;
                    pos2=j;
                }
//                if(min1<=min2){
//                    tmp=min1;
//                    min1=min2;
//                    min2=tmp;
//                }
            }
        }
        elem[i].weight=min1+min2;
        elem[i].left=pos2;
        elem[i].right=pos1;

        //忘了给elem[i]赋值了
        elem[i].parent=0;

        elem[pos1].parent=i;
        elem[pos2].parent=i;
    }

    for(int i=1;i<length;i++){
        cout<<elem[i].weight<<'\t'<<elem[i].parent<<'\t'<<elem[i].left<<'\t'<<elem[i].right<<endl;
    }
}

template <class Type>
void hfTree<Type>::getCode(hfCode result[]){
    int size=length/2;
    int p,s;  //s是当前正要处理的结点的下标,p是s的父结点的下标

    for(int i=size;i<length;i++){
        result[i-size].data=elem[i].data;
        result[i-size].code="";
        p=elem[i].parent;
        s=i;
        while(p){
            if(elem[p].left==s){
                result[i-size].code='0'+result[i-size].code;
            }
            else{
                result[i-size].code='1'+result[i-size].code;
            }
            s=p;
            p=elem[p].parent;
        }
    }
}

int main(){
    char ch[]={"aeistdn"};
    int w[]={10,15,12,3,4,13,1};

    hfTree<char> tree(ch,w,7);
    hfTree<char>::hfCode result[7];

    tree.getCode(result);

    for(int i=0;i<7;i++){
        cout<<result[i].data<<'\t'<<result[i].code<<endl;
    }
    return 0;
}


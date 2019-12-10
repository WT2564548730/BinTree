#include <iostream>
using namespace std;

#define MaxSize 100
typedef int ElementType;
//二叉树/（哈夫曼树）
typedef struct TNode{
    ElementType Weight;
    struct TNode *Left;
    struct TNode *Right;
}*BinTree,*HuffmanTree;

//堆
typedef struct HNode{
    HuffmanTree Data[MaxSize];
    int Size;
}*Heap,*MinHeap,*MaxHeap;

//打印树形
void PrintTree(BinTree T,int nLayer);
//求树高（用于打印树形，平衡二叉树的调整）
int GetHeight(BinTree T);
//树的创建
BinTree BuildTree(int tag);                                        //二叉树(层次遍历）和二叉搜索树的创建
BinTree CreateBinTree();                                        //二叉搜索树树的初始化
BinTree InsertBinTree(BinTree T,ElementType X);                    //向树中插入元素
BinTree InsertBinTree(BinTree T,ElementType L,ElementType R);
//树的遍历（非递归）
void LeverTraversal(BinTree T);                                    //层序遍历
void PreOrderTraversal(BinTree T);                                //先序遍历非递归算法
int InOrderTraversal(BinTree T);                                //中序遍历非递归算法
void PostOrderTraversal(BinTree T);                                //后序遍历非递归算法
//二叉搜索树的删除
BinTree Delete(BinTree T,ElementType X);
BinTree Find(BinTree T,ElementType X);
BinTree FindP(BinTree T,BinTree Tx,int &flag);
BinTree DDelete(BinTree T,BinTree Tx);
BinTree LRDelete(BinTree T,BinTree Tx);
BinTree LDelete(BinTree T,BinTree Tx);
BinTree RDelete(BinTree T,BinTree Tx);
BinTree NDelete(BinTree T,BinTree Tx);
//二叉搜索树的判定
bool IsBST(BinTree T);                                             //中序遍历判断
//平衡二叉树的调整
BinTree SingleRotation(BinTree T,int Tag);                        //左（右）单旋
BinTree LeftRightRotation(BinTree T,int Tag);                     //左右（右左）双旋
//堆的创建（最小堆为例）
MinHeap BuildMinHeap();                                            //最小堆的创建
MinHeap CreateMinHeap();                                        //初始化堆
//堆的插入删除及调整（最小堆为例）
HuffmanTree DeleteMin(MinHeap &H);                                //最小堆的删除
MinHeap InsertMin(MinHeap H,HuffmanTree HT);                    //最小堆的插入
//哈夫曼树的构造
HuffmanTree Huffman();

int main(){
    //树的创建
    cout<<"*****************************************"<<endl;
    cout<<"构造二插搜索树"<<endl;
    BinTree BST=BuildTree(1);                            //内含平衡二叉树的调整
    PrintTree(BST,GetHeight(BST));
    //树的遍历（非递归）
    LeverTraversal(BST);
    PreOrderTraversal(BST);
    InOrderTraversal(BST);
    PostOrderTraversal(BST);
    cout<<"*****************************************"<<endl;
    //二叉搜索树的删除
    while(1){
        int n;
        cout<<"请输入要删除结点的权重 : ";
        cin>>n;
        if(n==0)    break;
        
        BST=Delete(BST,n);
        PrintTree(BST,GetHeight(BST));
    }
    cout<<"*****************************************"<<endl;
    //二叉搜索树的判定
    cout<<"判断二叉搜索树"<<endl;
    cout<<"层次遍历思想构造普通二叉树"<<endl;
    BinTree BT=BuildTree(0);
    PrintTree(BT,GetHeight(BT));
    
    if(IsBST(BT))    cout<<"This is a BST!!!"<<endl;
    cout<<"*****************************************"<<endl;
    //哈夫曼树的构造
    cout<<"构造哈夫曼树"<<endl;
    HuffmanTree HT=Huffman();                                //内含最小堆的创建，插入删除等操作
    PrintTree(HT,GetHeight(HT));
    
    return 0;
}

//打印树形
void PrintTree(BinTree T, int nLayer)   //按竖向树状打印的二叉树
{
    if(!T)
        return;
    PrintTree(T->Right,nLayer+1);
    for(int i=0;i<nLayer;i++)
        cout<<"   ";
    cout<<T->Weight<<endl;
    PrintTree(T->Left ,nLayer+1);
}

//求树高
int GetHeight(BinTree T){
    int LH,RH,MH;
    if(T){
        LH=GetHeight(T->Left);
        RH=GetHeight(T->Right);
        MH=LH>RH?LH:RH;
        return (MH+1);
    }
    else    return 0;
}

//树的创建
BinTree BuildTree(int tag){
    BinTree T=NULL;
    if(tag==0){
        T=CreateBinTree();
        int n;
        //输入待插入结点
        cout<<"请输入树根 : ";
        cin>>n;
        T->Weight=n;
        
        BinTree Q[MaxSize];
        int rear=0;
        int front=0;
        
        Q[rear++]=T;
        while(rear!=front){
            BinTree Tmp=Q[front++];
            
            int l,r;
            cout<<"请输入 "<<Tmp->Weight<<" 的左右子树值 : ";
            cin>>l>>r;
            
            Tmp=InsertBinTree(Tmp,l,r);
            if(Tmp->Left)    Q[rear++]=Tmp->Left;
            if(Tmp->Right)    Q[rear++]=Tmp->Right;
        }
    }else{
        while(1){
            int n;
            cout<<"请输入待插入结点 : ";
            cin>>n;
            if(n==0)    break;
            
            T=InsertBinTree(T,n);
            PrintTree(T,GetHeight(T));
        }
    }
    return T;
}

//树的初始化
BinTree CreateBinTree(){
    BinTree T=new TNode;
    T->Left=T->Right=NULL;
    
    return T;
}

//普通树的插入
BinTree InsertBinTree(BinTree T,ElementType L,ElementType R){
    if(L){
        T->Left=CreateBinTree();
        T->Left->Weight=L;
    }
    if(R){
        T->Right=CreateBinTree();
        T->Right->Weight=R;
    }
    
    return T;
}

//二叉搜索树的插入及调平
BinTree InsertBinTree(BinTree T,ElementType X){
    if(!T){
        T=new TNode;
        T->Weight=X;
        T->Right=T->Left=NULL;
    }else{
        if(X<T->Weight){
            T->Left=InsertBinTree(T->Left,X);
            if(GetHeight(T->Left)-GetHeight(T->Right)==2){
                if(X<T->Left->Weight)
                    T=SingleRotation(T,0);
                else
                    T=LeftRightRotation(T,0);
            }
        }
        else{
            T->Right=InsertBinTree(T->Right,X);
            if(GetHeight(T->Right)-GetHeight(T->Left)==2){
                if(X>T->Right->Weight)
                    T=SingleRotation(T,1);
                else
                    T=LeftRightRotation(T,1);
            }
        }
    }
    return T;
}

//层序遍历
void LeverTraversal(BinTree T){
    cout<<"层序遍历结果为 : ";
    
    BinTree Q[MaxSize];
    int front=0;
    int rear=0;
    
    if(T)
        Q[rear++]=T;
    while(rear!=front){
        BinTree Tmp=Q[front++];
        if(front==1)    cout<<Tmp->Weight;
        else    cout<<" "<<Tmp->Weight;
        
        if(Tmp->Left)
            Q[rear++]=Tmp->Left;
        if(Tmp->Right)
            Q[rear++]=Tmp->Right;
    }
    cout<<endl;
}

//先序遍历
void PreOrderTraversal(BinTree T){
    cout<<"先序遍历结果为 : ";
    BinTree S[MaxSize];
    int top=-1;
    int flag=0;
    
    while(1){
        while(T){
            if(flag==0){
                cout<<T->Weight;
                flag++;
            }else
                cout<<" "<<T->Weight;
            S[++top]=T;
            T=T->Left;
        }
        
        if(top==-1)    break;
        
        T=S[top--]->Right;
    }
    cout<<endl;
}

//中序遍历
int InOrderTraversal(BinTree T){
    cout<<"中序遍历结果为 : ";
    BinTree S[MaxSize];
    int top=-1;
    int flag=0,mark=1;
    int Last;
    
    while(1){
        while(T){
            S[++top]=T;
            T=T->Left;
        }
        
        if(top==-1)    break;
        
        BinTree Tmp=S[top--];
        if(flag==0){
            Last=Tmp->Weight;
            cout<<Tmp->Weight;
            flag++;
        }else{
            cout<<" "<<Tmp->Weight;
            if(mark==1&&Tmp->Weight>Last)
                Last=Tmp->Weight;
            else
                mark=0;
        }
        
        T=Tmp->Right;
    }
    cout<<endl;
    return mark;
}

//后序遍历
void PostOrderTraversal(BinTree T){
    cout<<"后序遍历结果为 : ";
    BinTree S[MaxSize];
    int top=-1;
    
    BinTree t=NULL;
    int flag=1;
    while(1){
        while(T){
            if(flag==1){
                S[++top]=T;
                T=T->Left;
            }else
                break;
        }
        
        if(top==-1)    break;
        
        BinTree Tmp=S[top];
        if(Tmp->Right&&Tmp->Right!=t){
            flag=1;
            T=Tmp->Right;
            continue;
        }else{
            cout<<Tmp->Weight<<" ";
            T=S[--top];
            flag=0;
            t=Tmp;
        }
    }
    cout<<endl;
}

//二叉搜索树的删除
BinTree Delete(BinTree T,ElementType X){
    if(!T){
        cout<<"该树为空！！！无法删除"<<endl;
        return NULL;
    }
    BinTree Tx=Find(T,X);
    if(!Tx)    return NULL;
    if(GetHeight(T)==1)
        return NULL;
    
    if(Tx==T)
        T=DDelete(T,Tx);
    else{
        if(Tx->Left&&Tx->Right)        T=LRDelete(T,Tx);
        if(Tx->Left&&!Tx->Right)    T=LDelete(T,Tx);
        if(!Tx->Left&&Tx->Right)    T=RDelete(T,Tx);
        if(!Tx->Left&&!Tx->Right)    T=NDelete(T,Tx);
    }
    
    return T;
}

//定位自身
BinTree Find(BinTree T,ElementType X){
    BinTree Tx=T;
    
    if(!Tx->Left&&!Tx->Right&&Tx->Weight!=X){
        cout<<"树中无该元素！！！"<<endl;
        return NULL;
    }
    
    if(X<Tx->Weight){
        Tx=Find(Tx->Left,X);
        if(Tx->Weight==X)    return Tx;
        if(!Tx)    return NULL;
    }
    if(X>T->Weight){
        Tx=Find(Tx->Right,X);
        if(Tx->Weight==X)    return Tx;
        if(!Tx)    return NULL;
    }
    
    if(X==Tx->Weight)
        return Tx;
}

//定位双亲
BinTree FindP(BinTree T,BinTree Tx,int &flag){
    BinTree P=T;
    while(1){
        if(P->Left==Tx){
            flag=0;
            break;
        }
        if(P->Right==Tx){
            flag=1;
            break;
        }
        if(Tx->Weight<P->Weight){
            P=P->Left;
            continue;
        }
        if(Tx->Weight>P->Weight)    P=P->Right;
    }
    
    return P;
}

//根节点的删除
BinTree DDelete(BinTree T,BinTree Tx){
    BinTree t=Tx->Right;
    T=t;
    while(t->Left)
        t=t->Left;
    t->Left=Tx->Left;
    delete Tx;
    
    return T;
}

//左右孩子都非空的删除
BinTree LRDelete(BinTree T,BinTree Tx){
    BinTree t=Tx->Right;
    while(t->Left)
        t=t->Left;
    t->Left=Tx->Left;
    
    int flag=0;
    BinTree P=FindP(T,Tx,flag);
    
    if(flag==0)    P->Left=Tx->Right;
    else    P->Right=Tx->Right;
    delete Tx;
    
    return T;
}

//左孩子不空有孩子空的删除
BinTree LDelete(BinTree T,BinTree Tx){
    int flag=0;
    BinTree P=FindP(T,Tx,flag);
    
    if(flag==0)    P->Left=Tx->Left;
    else    P->Right=Tx->Left;
    delete Tx;
    
    return T;
}

//右孩子不空左孩子空的删除
BinTree RDelete(BinTree T,BinTree Tx){
    int flag=0;
    BinTree P=FindP(T,Tx,flag);
    
    if(flag==0)    P->Left=Tx->Right;
    else    P->Right=Tx->Right;
    delete Tx;
    
    return T;
}

//左右孩子都为空的删除
BinTree NDelete(BinTree T,BinTree Tx){
    int flag=0;
    BinTree P=FindP(T,Tx,flag);
    if(flag==0)    P->Left=NULL;
    else    P->Right=NULL;
    
    delete Tx;
    return T;
}

//中序遍历判断一棵树是否为二叉搜索树
bool IsBST(BinTree T){
    int mark=InOrderTraversal(T);
    if(mark==1)    return true;
    else    return false;
}

//单旋
BinTree SingleRotation(BinTree T,int Tag){
    if(Tag==0){
        BinTree Tmp=T->Left;
        T->Left=Tmp->Right;
        Tmp->Right=T;
        
        return Tmp;
    }else{
        BinTree Tmp=T->Right;
        T->Right=Tmp->Left;
        Tmp->Left=T;
        
        return Tmp;
    }
}

//双旋
BinTree LeftRightRotation(BinTree T,int Tag){
    if(Tag==0){
        T->Left=SingleRotation(T->Left,1);
        T=SingleRotation(T,0);
    }else{
        T->Right=SingleRotation(T->Right,0);
        T=SingleRotation(T,1);
    }
    return T;
}

//哈夫曼树的构造
HuffmanTree Huffman(){
    MinHeap H=BuildMinHeap();
    while(H->Size){
        HuffmanTree HT=new TNode;
        HT->Left=DeleteMin(H);
        HT->Right=DeleteMin(H);
        
        HT->Weight=HT->Left->Weight+HT->Right->Weight;
        H=InsertMin(H,HT);
        
        if(H->Size==1)    return HT;
    }
}

//最小堆的创建
MinHeap BuildMinHeap(){
    MinHeap H=CreateMinHeap();
    
    while(1){
        HuffmanTree T=new TNode;
        T->Left=T->Right=NULL;
        cout<<"请输入树权重 : ";
        cin>>T->Weight;
        if(T->Weight==0)    break;
        
        H=InsertMin(H,T);
    }
    return H;
}

//最小堆的初始化
MinHeap CreateMinHeap(){
    MinHeap H=new HNode;
    H->Size=0;
    
    return H;
}

//最小堆的插入
MinHeap InsertMin(MinHeap H,HuffmanTree HT){
    int i=++H->Size;
    for(;i>=2&&HT->Weight<H->Data[i/2]->Weight;i/=2)
        H->Data[i]=H->Data[i/2];
    H->Data[i]=HT;
    
    return H;
}

//最小堆的删除
HuffmanTree DeleteMin(MinHeap &H){
    HuffmanTree HT=H->Data[1];
    HuffmanTree Tmp=H->Data[H->Size--];
    
    int C,P=1;
    for(P=1;2*P<=H->Size;P=C){
        C=2*P;
        if(C+1<=H->Size&&H->Data[C]->Weight>H->Data[C+1]->Weight)
            C++;
        if(Tmp->Weight>H->Data[C]->Weight){
            H->Data[P]=H->Data[C];
            continue;
        }
        else    break;
    }
    H->Data[P]=Tmp;
    
    return HT;
}


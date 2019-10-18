#include<iostream>
#include<queue>
using namespace std;


template<class T>
class BinaryTree
{
    private:
    struct Node
    {
        T data;
        Node *left, *right;
        
        Node():left(NULL),right(NULL){}
        Node(T x,Node *L = NULL, Node *R = NULL):data(x),left(L),right(R){}
        ~Node(){}
    };

    Node *root;

    public:
    BinaryTree():root(NULL){}
    BinaryTree(T x){root = new Node(x);}
    ~BinaryTree();
    void clear();
    bool isEmpty() const;
    T Root(T flag) const;
    T lchild(T x, T flag) const;
    T rchild(T x, T flag) const;
    void delLeft(T x);
    void delRight(T x);
    void preOrder() const;
    void midOrder() const;
    void postOrder() const;
    void levelOrder() const;
    void createTree(T flag);
    T parent(T x, T flag) const
    {
        return flag;
    }
    int size() const;
    int height() const;

    private:
    Node *find(T x,Node *t) const;
    void clear(Node *&t);
    void preOrder(Node *t) const;
    void midOrder(Node *t) const;
    void postOrder(Node *t) const;
    int size(Node *t) const;
    int height(Node *t) const;
};

template<class T>
bool BinaryTree<T>:: isEmpty() const
{
    return root==NULL;
}

template<class T>
T BinaryTree<T>:: Root(T flag) const
{
    if(root==NULL) return flag;
    else return root->data;
}

template<class T>
void BinaryTree<T>::clear(BinaryTree<T>::Node *&t)
{
    if(t==NULL) return;
    clear(t->left);
    clear(t->right);
    delete t;
    t = NULL;
}

template<class T>
void BinaryTree<T>::clear()
{
    clear(root);
}

template<class T>
BinaryTree<T>::~BinaryTree()
{
    clear(root);
}

template<class T>
void BinaryTree<T>::preOrder(BinaryTree<T>::Node *t) const
{
    if(t==NULL) return;
    cout<<t->data<<' ';
    preOrder(t->left);
    preOrder(t->right);
}

template<class T>
void BinaryTree<T>::preOrder() const
{
    cout<<"\n preOrder traverse:";
    preOrder(root);
}

template<class T>
void BinaryTree<T>::midOrder(BinaryTree<T>::Node *t) const
{
    if(t==NULL) return;
    midOrder(t->left);
    cout<<t->data<<' ';
    midOrder(t->right);
}

template<class T>
void BinaryTree<T>::midOrder() const
{
    cout<<"\n midOrder traverse:";
    midOrder(root);
}

template<class T>
void BinaryTree<T>::postOrder (BinaryTree<T>::Node *t) const
{
    if(t==NULL) return;
    postOrder(t->left);
    postOrder(t->right);
    cout<<t->data<<' ';
}

template<class T>
void BinaryTree<T>::postOrder () const
{
    cout<<"\n postOrder traverse:";
    postOrder(root);
}

template<class T>
void BinaryTree<T>::levelOrder() const
{
    queue<Node *> q;
    Node *temp;

    cout<<"\n levelOrder traverse:";
    q.push(root);

    while(!q.empty())
    {
        temp = q.front();
        q.pop();
        cout<<temp->data<<' ';
        if(temp->left)
        {
            q.push(temp->left);
        }
        if(temp->right)
        {
            q.push(temp->right);
        }
    }
}

template<class T>
typename BinaryTree<T>::Node *BinaryTree<T>::find(T x,BinaryTree<T>::Node *t) const
{
    Node *temp;
    if(t==NULL) return NULL;
    if(t->data==x) return t;
    if((temp = find(x,t->left))) return temp;
    else
    {
        return find(x,t->right);
    }
}

template<class T>
void BinaryTree<T>::delLeft(T x)
{
    Node *temp = find(x,root);
    if(temp==NULL) return;
    clear(temp->left);
}

template<class T>
void BinaryTree<T>::delRight(T x)
{
    Node *temp = find(x,root);
    if(temp==NULL) return;
    clear(temp->right);
}

template<class T>
T BinaryTree<T>::lchild(T x,T flag) const
{
    Node *temp = find(x,root);
    if(temp==NULL||temp->left==NULL) return flag;

    return temp->left->data;
}

template<class T>
T BinaryTree<T>::rchild(T x, T flag) const
{
    Node *temp = find(x,root);
    if(temp==NULL||temp->right==NULL) return flag;

    return temp->right->data;
}

template<class T>
void BinaryTree<T>::createTree(T flag)
{
    queue<Node*> q;
    Node *temp;
    T x, ldata, rdata;
    //创建树，输入flag表示空
    cout<<"\n Enter root data:";
    cin>>x;
    root = new Node(x);
    q.push(root);

    while(!q.empty())
    {
        temp = q.front();
        q.pop();
        cout<<"\n enter "<<temp->data<<"'s two sons("<<flag<<"表示空结点):";
        cin>>ldata>>rdata;
        if(ldata!=flag) q.push(temp->left=new Node(ldata));
        if(rdata!=flag) q.push(temp->right=new Node(rdata));
    }

    cout<<"create complected!\n";
}

template<class T>
int BinaryTree<T>::size() const
{
    return size(root);
}

template<class T>
int BinaryTree<T>::size(Node *t) const
{
    if(t==NULL) return 0;
    return 1+size(t->left)+size(t->right);
}

template<class T>
int BinaryTree<T>::height() const
{
    return height(root);
}

template<class T>
int BinaryTree<T>::height(Node *t) const
{
    if(t==NULL) return 0;
    else
    {
        int lt = height(t->left),rt = height(t->right);
        return 1+((lt>rt)?lt:rt);
    }
    
}
int main( )
{
    BinaryTree<char> tree;

    tree.createTree('@');
    cout<<"the size of the tree is: "<<tree.size()<<endl;
    cout<<"the height of the tree is: "<<tree.height()<<endl;
    tree.preOrder();
}

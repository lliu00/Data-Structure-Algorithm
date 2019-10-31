#include<iostream>
using namespace std;

template<class T>
class list
{
public:
    virtual bool isEmpty() const = 0;
    virtual int insert() = 0;
    virtual bool remove() = 0;
    //virtual bool find()const = 0;
    virtual T getElement()const = 0;
    virtual void clear() =0;
    virtual void traverse() const = 0;
    virtual ~list() = 0;
};
template <class T>
struct node
{
    T data;
    node *next;
    node(){next = NULL;}
    node(T x,node *p):data(x),next(p){}
};

template<class T>
 class LinkedList: public list<T>
 {
    private:
         node<T> *head;

    public:
        LinkedList(){head = new node<T>;}
        void preCreateList(T val[],int len);
        void postCreateList(T val[],int len);
        bool isEmpty() const;
        int insert(const T x,int index);
        int length() const;
        bool remove(int index);
        node<T>* find(const T x);
        void clear();
        void traverse() const;
        ~LinkedList();

};

//头插法建立链表
template<class T>
void LinkedList<T>::preCreateList(T *val, int len)
{
    for(int i =0;i<len;i++)
    {
        node<T> p = new node<T>(val[i]);
        p.next = head->next;
        head->next = p;
    }
}
//尾插法建立链表
template<class T>
void LinkedList<T>::postCreateList(T *val, int len) {
    node<T> p = head;
    for (int i = 0; i < len; i++)
    {
        node *newNode = new node<T>(val[i]);
        p.next = newNode;
        p = p.next;
    }
}

template<class T>
bool LinkedList<T>::isEmpty() const
{
    return head->next==NULL;
}

//插入第index结点前插入元素x
template<class T>
int LinkedList<T>::insert(const T x,int index)
{
    if(index<1||index>length())
    {
        cout<<"ERROR";
        return 0;
    }
    node<T> *p = head->next;
    while(p&&i<index-1)
    {
        p=p->next;
    }
    if(!p) return 0;
    else
    {
        node<T> *tmp = new node<T>(x);
        tmp->next = p->next;
        p->next = tmp;
    }
    return 1;
}

//在链表中查找元素值为x的结点，成功返回结点指针，失败报错
template<class T>
node<T>* LinkedList<T>::find(const T x)
{
    node<T> *p = head;
    while(p)
    {
        if(p->data==x)
        {
            return p;
        }
        p = p->next;
    }
    cout<<"Error";
    return nullptr;
}

//返回单链表得长度
template <class T>
int LinkedList<T>::length() const
{
    if(isEmpty()) return 0;
    int count = 0;
    node<T> *p = head->next;
    while(p)
    {
        count++;
        p=p->next;
    }
    return count;
}
//删除链表中第index个元素节点
template<class T>
bool LinkedList<T>::remove(int index)
{
    if(isEmpty()||index<1||index>length())
    {
        cout<<"ERROR";
        return false;
    }
    node<T> *p = head->next;
    int i = 1;
    while(p&&i<index-1)
    {
        p = p->next;
        i++;
    }
    if(p&&p->next)
    {
        node<T> *tmp = p->next;
        p->next = tmp->next;
        delete tmp;
        return true;
    }
    else
    {
        cout<<"ERROR";
        return false;
    }
}

template<class T>
void LinkedList<T>::clear()
{
    if(isEmpty()) return;
    node<T> *tmp = head;
    while(head)
    {
        head = head->next;
        delete tmp;
        tmp = head;
    }
}

template<class T>
void LinkedList<T>::traverse() const
{
    node<T> *p = head->next;
    while(p)
    {
        cout<<p->data<<'\t';
        p = p->next;
    }
}

template<class T>
LinkedList<T>::~LinkedList()
{
    clear();
}

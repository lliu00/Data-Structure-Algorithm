#include<iostream>
using namespace std;

template<class T>
class hashTable
{
    public:
        virtual bool find(const T &x) const = 0;
        virtual bool insert(const T &x) = 0;
        virtual bool remove(const T &x) = 0;
};

template<class T>
class openHashTable:public hashTable<T>
{
    private:
        struct node
        {
            T data;
            node *next;

            node(const T &d):data(d),next(NULL){}
            node(){next = NULL;}
        };

        node *array;
        int size;

    public:
        openHashTable(int len = 101);
        ~openHashTable();
        bool find(const T &x) const;
        bool insert(const T &x);
        bool remove(const T &x);
};


template<class T>
openHashTable<T>::openHashTable(int len)
{
    size = len;
    array = new node *[size];
    for(int i =0;i<size;i++)
    {
        array[i] = new node;
    }
}

template<class T>
openHashTable<T>::~openHashTable()
{
    node *p, *q;

    for(int i =0;i<size;i++)
    {
        p = array[i];
    }

    do
    {
        q = p->next;
        delete p;
        p = q;
    }while(p!=NULL);

    delete [] array;
}

template<class T>
bool openHashTable<T>::insert(const T &x)
{
    int pos;
    node *p;

    pos = x % size;
    p = array[pos]->next;
    while(p!=NULL&&p->data!=x)
    {
        p = p->next;
    }
    if(p==NULL)
    {
        p = new node(x);
        p->next = array[pos]->next;
        array[pos]->next = p;
        return true;
    }

    return false;
}

template<class T>
bool openHashTable<T>::find(const T &x) const
{
    int pos;
    node *p;

    pos = x % size;
    p = array[pos]->next;

    while(p!=NULL&&p->data!=x)
    {
        p = p->next;
    }
    if(p!=NULL) return true;
    else return false;
}

template<class T>
bool openHashTable<T>::remove(const T &x)
{
    int pos;
    node *p, *q;

    pos = x%size;
    p = array[pos]->next;
    while(p!=NULL && p->data!=x)
    {
        p = p->next;
    }
    if(p == NULL) return false;
    else
    {
        q = p->next;
        p->next = q->next;
        delete q;
        return true;
    }
    
}

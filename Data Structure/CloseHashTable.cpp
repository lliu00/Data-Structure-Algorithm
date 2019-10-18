#include<iostream>
using namespace std;

template <class T>
class hashtable
{
    public:
        virtual bool find(const T &x) const = 0;
        virtual bool insert(const T &x) const = 0;
        virtual bool remove(const T &x) const = 0;

    /*protected:
        int (*key)(const T &x);
      static int defaultKey (const int &k) {return k;}
    */
};

template <class T>
class closeHashTable:public hashtable<T>
{
    private:
        struct node
        {
            T data;
            int state;

            node()
            {
                state = 0;
            }
        };

    node *array;
    int size;

    public:
        closeHashTable(int len);
        ~closeHashTable(){delete []array;}
        bool find(const T &x) const;
        bool insert(const T &x);
        bool remove(const T &x);

        void rehash();
};

template<class T>
closeHashTable<T>::closeHashTable(int len)
{
    size = len;
    array = new node[size];
}

template<class T>
bool closeHashTable<T>:: insert(const T &x)
{
    int initPos, pos;

    initPos = pos = x%size;

    do
    {
        if(array[pos].state!=1)
        {
            array[pos].data = x;
            array[pos].state = 1;
            return true;
        }
        if(array[pos].state==1&&array[pos].data==x)
        {
            return true;
        }

        pos = (pos+1) % size;
    } while (pos!=initPos);

    return false;
}

template<class T>
bool closeHashTable<T>:: remove(const T &x)
{
    int initPos, pos;

    initPos = pos = x%size;

    do
    {
        if(array[pos].state==0) return false;
        if(array[pos].state==1&&array[pos].data==x)
        {
            array[pos].state = 2;
            return true;
        }
        pos = (pos+1)%size;
    } while (pos!=initPos);
    
    return false;
}

template<class T>
bool closeHashTable<T>::find(const T &x) const
{
    int initPos, pos;

    initPos = pos = x%size;
    do
    {
        if(array[pos].state==0) return false;
        if(array[pos].state==1&&array[pos].data == x) return true;
        pos = (pos+1)%size;
    }while(pos!=initPos);

    return false;
}

template<class T>
void closeHashTable<T>::rehash()
{
    node *temp = array;

    array = new node[size];
    for(int i =0;i<size;i++)
    {
        if(temp[i].state==1) insert(temp[i].data);
    }
    delete []temp;
}

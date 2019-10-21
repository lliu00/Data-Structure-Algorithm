#include <iostream>
#include<queue>
using namespace std;

template<class Type>
class priorityQueue:public queue<Type>
{
    public:
        priorityQueue(int capacity = 100);
        priorityQueue(const Type data[],int size);
        ~priorityQueue();
        bool isEmpty() const;
        void enQueue(const Type &x);
        Type deQueue();
        Type getHead() const;
    
    private:
        int size;
        Type *array;
        int maxSize;

    void doublespace();
    void buildHeap();
    void percolateDown(int hole);
};

template<class Type>
priorityQueue<Type>::priorityQueue(int capacity)
{
    maxSize = capacity;
    size = 0;
    data = new Type[capacity];
}

template<class Type>
priorityQueue<Type>::~priorityQueue()
{
    delete [] array;
}

template<class Type>
bool priorityQueue<Type>::isEmpty()const
{
    return size==0;
}

template<class Type>
Type priorityQueue<Type>::getHead() const
{
    return array[1];
}



template<class Type>
void priorityQueue<Type>::enQueue(const Type &x)
{
    int hole;
    if(size==maxSize-1) doublespace();

    //向上过滤
    for(hole=++size;x>array[hole]&&hole!=1;hole = hole/2)
    {
        array[hole] = array[hole/2];
    }
    array[hole] = x;
}

template<class Type>
Type priorityQueue<Type>::deQueue()
{
    Type minItem;
    minItem = array[1];
    array[1] = array[size--];
    percolateDown(1);
    return minItem;
}

template<class Type>
void priorityQueue<Type>::percolateDown (int hole)
{
    int child;
    Type tmp = array[hole];

    for(;hole*2<size;hole = child)
    {
        child = hole*2;
        if(child!=size&&array[child+1]<array[child])
            child++;
        if(array[child]<tmp) array[hole] = array[child];
        else break;
    }

    array[hole] = tmp;
}

template<class Type>
void priorityQueue<Type>::buildHeap ()
{
    for(int i = size/2;i>0;i--)
    {
        percolateDown(i);
    }
}

template<class Type>
priorityQueue<Type>::priorityQueue(const Type *data,int len):maxSize(len+10),size(len)
{
    array = new Type[maxSize];
    for(int i =0;i<len;i++)
        array[i+1] = data[i];
    buildHeap();        
}

template<class Type>
void priorityQueue<Type>::doublespace ()
{
    Type *tmp = array;
    maxSize*=2;
    array = new Type[maxSize];
    for(int i =0;i<=size;i++)
    {
        array[i] = tmp[i];
    }
    delete []tmp;
}

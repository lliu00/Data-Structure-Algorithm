#include<iostream>
#define MaxSize 20
using namespace std;
typedef int DataType;
class Stack
{
public:
        DataType data[MaxSize];
        int top;

public:
    void InitStack()
    {
        top = -1;
    }

    DataType pop()
    {
        if(top==-1)
        {
            return 0;
        }
        return data[top--];
    }

    void push(DataType x)
    {
        if(top==MaxSize-1)
        {
            cout<<"overflow"<<endl;
            return;
        }
        data[++top] = x;
    }

    DataType GetTop()
    {
        if(top==-1) return 0;
        return data[top];
    }

    int IsEmpty()
    {
        return top==-1;
    }
};
int main()
{
    Stack S;
    DataType e;
    S.InitStack();
    cout<<"push 10 and 15 to the Stack."<<endl;
    S.push(15);
    S.push(10);
    e = S.GetTop();
    cout<<"the val of top: "<<e<<endl;
    S.pop();
    e = S.GetTop();
    cout<<"the val of top: "<<e<<endl;
    if(S.IsEmpty())
    {
        cout<<"empty stack"<<endl;
    }
    else
    {
        cout<<"not empty"<<endl;//栈有一个元素，非空.
    }
}

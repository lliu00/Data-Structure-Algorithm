#include <iostream>
using namespace std;

template <typename T>
class LinkStack
{
private:
    struct node
    {
        T data;
        node *next;
        node(const T &x, node *p = NULL)
        {
            data = x;
            next = p;
        }
        node() : next(NULL) {}
        ~node() {}
    };
    node *top;

public:
    LinkStack();
    ~LinkStack();
    void push(T x);
    T pop();
    T GetTop();
    bool IsEmpty();
};

template <typename T>
LinkStack<T>::LinkStack()
{
    top = NULL;
}

template <typename T>
LinkStack<T>::~LinkStack()
{
    node *temp;
    while (top)
    {
        temp = top;
        top = top->next;
        delete temp;
    }
}

template <typename T>
bool LinkStack<T>::IsEmpty()
{
    return top == NULL;
}

template <typename T>
void LinkStack<T>::push(T x)
{
    node *s = new node;
    s->data = x;
    s->next = NULL;
    if (IsEmpty())
    {
        top = s;
        return;
    }
    s->next = top;
    top = s;
    //delete (s);
}

template <typename T>
T LinkStack<T>::pop()
{
    node *s = top;
    T x = s->data;
    top = top->next;
    delete (s);
    return x;
}

template <typename T>
T LinkStack<T>::GetTop()
{
    return top->data;
}

int main()
{
    LinkStack<int> S;
    int e;
    cout << "push 10 and 15 to the Stack." << endl;
    S.push(15);
    S.push(10);
    e = S.GetTop();
    cout << "the val of top: " << e << endl;
    S.pop();
    e = S.GetTop();
    cout << "the val of top: " << e << endl;
    if (S.IsEmpty())
    {
        cout << "empty stack" << endl;
    }
    else
    {
        cout << "not empty" << endl; //栈有一个元素，非空.
    }
}

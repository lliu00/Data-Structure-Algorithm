#include<iostream>
using namespace std;

template<class T>
class hfTree
{
    private:
        struct node
        {
            T data;
            int weight;
            int parent,left,right;
        };

        node *elem;
        int length;

    public:
        struct hfCode
        {
            T data;
            string code;
        };

        hfTree(const T *v,const int *w,int size);
        void getCode(hfCode result[]);
        ~hfTree(){delete []elem;}
};

template<class T>
hfTree<T>::hfTree(const T *v,const int *w,int size)
{
    const int MAX_INT = 65535;
    int min1, min2;
    int x, y;
    //初始化
    length = 2*size;
    elem = new node[length];

    for(int i = size;i<length;i++)
    {
        elem[i].data = v[i-size];
        elem[i].weight = w[i-size];
        elem[i].parent = elem[i].left = elem[i].right = 0;
    }
    //找到权重最小的结点和次小的结点，并归并森林中的树
    for(int k = size-1;k>0;k--)
    {
        min1 = min2 = MAX_INT;
        x = y = 0;
        //找出当前最小树
        for(int i = k+1;i<length;i++)
        {
            if(elem[i].parent==0)//保证已经处理过上个最小树和此最小树不再处理
            {
                if(elem[i].weight<min1)
                {
                    min1 = elem[i].weight;
                    x = i;
                }
            }
        }
        //找出当前次小树
        for(int i = k+1;i<length;i++)
        {
            if(elem[i].parent==0)
            {
                if(elem[i].weight<min2&&i!=x)
                {
                    min2 = elem[i].weight;
                    y = i;
                }
            }
        }

        elem[k].weight = min1 + min2;
        elem[k].left = x;
        elem[k].right = y;
        elem[k].parent = 0;
        elem[x].parent = k;
        elem[y].parent = k;
    }
}

template<class T>
void hfTree<T>::getCode(hfCode result[])
{
    int size = length/2;
    int p, cur;//cur是追溯过程中正在处理的结点，p是cur 的父节点下标
    //对每个代编码的字符
    for(int i=size;i<length;i++)
    {
        result[i-size].data = elem[i].data;
        result[i-size].code = "";
        p = elem[i].parent;
        cur = i;
        //向根追溯
        while(p)
        {
            if(elem[p].left==cur)
            {
                result[i-size].code = '0'+result[i-size].code;
            }
            else
            {
                result[i-size].code = '1'+result[i-size].code;;
            }
            cur = p;
            p = elem[p].parent;
        }
    }
}

int main()
{
    char ch[] = {"aeistdn"};
    int w[] = {10,15,12,3,4,13,1};

    hfTree<char> tree(ch,w,7);
    hfTree<char>::hfCode result[7];

    tree.getCode(result);

    for(int i =0;i<7;i++)
    {
        cout<<result[i].data<<' '<<result[i].code<<endl;
    }

    return 0;
}

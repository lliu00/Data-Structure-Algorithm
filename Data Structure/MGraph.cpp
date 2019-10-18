#include<iostream>
using namespace std;

template<typename TypeOfVer, typename TypeOfEdge>
class adjMGraph
{
public:
	adjMGraph(int vSize, const TypeOfVer d[], const TypeOfEdge noEdgeFlag = 65535);
	~adjMGraph();
	void insert(TypeOfVer v1, TypeOfVer v2, TypeOfEdge w);
	void remove(TypeOfVer v1, TypeOfVer v2);
	bool exist(TypeOfVer v1, TypeOfVer v2) const;
	void dfs() const;
    void bfs() const;
	void dijkstra();
	void floyd() const;

private:
	int VERTEX_NUM;
	int EDGE_NUM;
	TypeOfEdge** Edge;
	TypeOfVer* data;
	TypeOfEdge noEdge;
	int INFINITY = 65535;
	int find(TypeOfVer v) const;
	void dfs(int start, bool visited[]) const;
    void bfs(int start, bool visited[]) const;
	void dijkstra(bool collected[],TypeOfEdge dist[],int prev[],int start);
	int FindMindist(TypeOfEdge dist[],bool collected[]);
	void printPath(int start,int end,int prev[]) const;
};

template<class TypeOfVer,class TypeOfEdge>
int adjMGraph<TypeOfVer, TypeOfEdge>::find(TypeOfVer v) const
{
		for (int i = 0; i < VERTEX_NUM; i++)
		{
			if (data[i] == v)
			{
				return i;
			}
		}
		return -1;
}

template<class TypeOfVer, class TypeOfEdge>
adjMGraph<TypeOfVer, TypeOfEdge>::adjMGraph(int vSize, const TypeOfVer d[], const TypeOfEdge noEdgeFlag)
{

	VERTEX_NUM = vSize;
	EDGE_NUM = 0;
	noEdge = noEdgeFlag;

	data = new TypeOfVer[vSize];
	for (int i = 0; i < vSize; i++)
	{
		data[i] = d[i];
	}

	Edge = new TypeOfEdge * [vSize];
	for (int i = 0; i < vSize; i++)
	{
		Edge[i] = new TypeOfEdge[vSize];
		for (int j = 0; j < vSize; j++)
		{
			Edge[i][j] = noEdge;
		}
		Edge[i][i] = 0;
	}
}

template<class TypeOfVer, class TypeOfEdge>
adjMGraph<TypeOfVer, TypeOfEdge>::~adjMGraph()
{
	delete[]data;
	for (int i = 0; i < VERTEX_NUM; i++)
	{
		delete[]Edge[i];
	}
	delete[]Edge;
}

template<class TypeOfVer, class TypeOfEdge>
void adjMGraph<TypeOfVer, TypeOfEdge>::insert(TypeOfVer v1, TypeOfVer v2, TypeOfEdge w)
{
	int i = find(v1), j = find(v2);
	Edge[i][j] = w;
	EDGE_NUM++;
}

template<class TypeOfVer, class TypeOfEdge>
void adjMGraph< TypeOfVer, TypeOfEdge>::remove(TypeOfVer v1, TypeOfVer v2)
{
	int i = find(v1), j = find(v2);
	Edge[i][j] = noEdge;
	EDGE_NUM--;
}

template<class TypeOfVer, class TypeOfEdge>
bool adjMGraph<TypeOfVer, TypeOfEdge>::exist(TypeOfVer v1, TypeOfVer v2) const
{
	int i = find(v1), j = find(v2);
	if (Edge[i][j] != noEdge) return true;
	else return false;
}

template<class TypeOfVer, class TypeOfEdge>
void adjMGraph<TypeOfVer, TypeOfEdge>::dfs() const
{
	bool* visited = new bool[VERTEX_NUM];
	TypeOfVer v;

	for (int i = 0; i < VERTEX_NUM; i++)
	{
		visited[i] = false;
	}

	cout << "please enter the vertex you want to traverse:" << ' ';
	cin >> v;
	int start = find(v);
	cout << "the dfs order of the graph is:" << endl;
	dfs(start, visited);
}

template<class TypeOfVer, class TypeOfEdge>
void adjMGraph<TypeOfVer, TypeOfEdge>::dfs(int start, bool visited[]) const
{
	int v1 = start;
	cout << data[v1] << ' ';
	visited[v1] = true;
	for (int v2 = 0; v2 < VERTEX_NUM; v2++)
	{
		if (Edge[v1][v2] != noEdge && visited[v2] != true)
		{
			dfs(v2, visited);
		}
	}
}

template<class TypeOfVer,class TypeOfEdge>
void adjMGraph<TypeOfVer, TypeOfEdge>::bfs() const
{
    bool *visited = new bool[VERTEX_NUM];
    TypeOfVer v;

    for(int i =0;i<VERTEX_NUM;i++)
    {
        visited[i] = false;
    }

    cout<<"please enter the vertex you want to traverse:"<<endl;

    cin>>v;

    int start = find(v);
    
    cout<<"the bfs order of the graph is:"<<endl;
    bfs(start,visited);
}

template<class TypeOfVer,class TypeOfEdge>
void adjMGraph<TypeOfVer, TypeOfEdge>::bfs(int start,bool visited[]) const
{
    int q[100];
    int front, rear, v1;
    front = rear = -1;
    v1 = start;
    q[++rear] = v1;

    cout<<data[v1]<<' ';
    visited[v1] = true;

    while(front!=rear)
    {
        v1 = q[rear--];
        for(int v2 = 0;v2<VERTEX_NUM;v2++)
        {
            if(Edge[v1][v2]!=noEdge&&visited[v2]!=true)
            {
                cout<<data[v2]<<' ';
                visited[v2] = true;
                q[++rear] = v2;
            }
        }
    }
}

template<class TypeOfVer, class TypeOfEdge>
void adjMGraph<TypeOfVer, TypeOfEdge>::dijkstra()
{
	TypeOfVer v;
	bool *collected = new bool[VERTEX_NUM];
	TypeOfEdge *dist = new TypeOfEdge[VERTEX_NUM];
	int *prev = new int[VERTEX_NUM];
	for(int i =0;i<VERTEX_NUM;i++)
	{
		collected[i] = false;
		dist[i] = INFINITY;
		prev[i] = -1;
	}


	cout<<"enter the source vertex:";
	cin>>v;

	int start = find(v);

	dijkstra(collected,dist,prev,start);
}

template<class TypeOfVer,class TypeOfEdge>
int adjMGraph<TypeOfVer,  TypeOfEdge>::FindMindist(TypeOfEdge dist[],bool collected[])
{
	int MinV, V;
	int Mindist = INFINITY;
	for(V=0;V<VERTEX_NUM;V++)
	{
		if(collected[V]==false&&dist[V]<Mindist)
		{
			Mindist = dist[V];
			MinV = V;
		}
	}
	if(Mindist<INFINITY)
	{
		return MinV;
	}
	else return -1;
}

template<class TypeOfVer,class TypeOfEdge>
void adjMGraph<TypeOfVer,TypeOfEdge>:: dijkstra(bool collected[],TypeOfEdge dist[],int prev[],int start)
{
	dist[start] = 0;

	while(1)
	{
		int V = FindMindist(dist,collected);
		if(V==-1) break;
		collected[V] = true;
		for(int W = 0;W<VERTEX_NUM;W++)
		{
		if(collected[W]!=true)
		{
			if(dist[V]+Edge[V][W]<dist[W])
			{
				dist[W] = dist[V] + Edge[V][W];
				prev[W] = V;
			}
		}
		}
	}	

	for(int i =0;i<VERTEX_NUM;i++)
	{
		cout<<"从 "<<data[start]<<" 到 "<<data[i]<<" 的路径是:"<<endl;
		printPath(start, i, prev);
		cout<<"\t distance is:"<<dist[i]<<endl;
	}
}

template<class TypeOfVer,class TypeOfEdge>
void adjMGraph<TypeOfVer,TypeOfEdge>::printPath(int start,int end,int prev[]) const
{
	if(start==end)
	{
		cout<<data[start];
		return;
	}
	printPath(start, prev[end], prev);
	cout<<"-"<<data[end];
}

template<class TypeOfVer,class TypeOfEdge>
void adjMGraph<TypeOfVer,TypeOfEdge>::floyd() const
{
	TypeOfEdge **d = new TypeOfEdge*[VERTEX_NUM];
	int **prev = new int*[VERTEX_NUM];
	int i,j,k;

	for(i=0;i<VERTEX_NUM;i++)
	{
		d[i] = new TypeOfEdge[VERTEX_NUM];
		prev[i] = new int[VERTEX_NUM];
		for(j=0;j<VERTEX_NUM;j++)
		{
			d[i][i] = Edge[i][j];
			prev[i][j] = (Edge[i][j]!=noEdge)?i:1;
		}
	}

	//迭代过程
	for(k=0;k<VERTEX_NUM;k++)
	{
		for(i=0;i<VERTEX_NUM;i++)
		{
			for(j=0;j<VERTEX_NUM;j++)
			{
				if(d[i][k]+d[k][j]<d[i][j])
				{
					d[i][j] = d[i][k]+d[k][j];
					prev[i][j] = prev[k][j];
				}
			}
		}
	}

	//输出过程
	cout<<"最短路径长度:"<<endl;
	for(i=0;i<VERTEX_NUM;i++)
	{
		cout<<endl;
		for(j=0;j<VERTEX_NUM;j++)
		{
			cout<<d[i][j]<<'\t';
		}
	}

	cout<<"最短路径:"<<endl;
	for(i=0;i<VERTEX_NUM;i++)
	{
		cout<<endl;
		for(j=0;j<VERTEX_NUM;j++)
		{
			cout<<prev[i][j]<<'\t';
		}
	}
}

int main()
{
	adjMGraph<char, int> G(4, "abcd", 65535);

	G.insert('a', 'c', 1);
	G.insert('c', 'd', 2);
	G.insert('d', 'b', 3);
	G.insert('b', 'a', 4);

	G.dfs();
	cout<<endl;

    G.bfs();

	G.dijkstra();
	cout<<endl;

	G.floyd();
}

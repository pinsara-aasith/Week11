#include <iostream>
#include <vector>

using namespace std;

class Edge
{
public:
    int origin;
    int destination;
    int weight;
};

class Vertex
{
public:
    int label;
    bool visited = false;

    vector<Edge *> edges;

    Vertex(int label)
    {
        this->label = label;
    }
};

struct Graph
{
    int vertexCount = 6;
    vector<Vertex *> vertices;
    vector<Edge *> edges;

    vector<Edge *> mstEdges;

    void intializeVertices()
    {
        for (int i = 0; i < vertexCount; i++)
        {
            vertices.push_back(new Vertex(i));
        }
    }

    void addEdge(int v1, int v2, int weight)
    {
        Edge *e1 = new Edge;
        e1->origin = v1;
        e1->destination = v2;
        e1->weight = weight;

        vertices[v1]->edges.push_back(e1);

        Edge *e2 = new Edge;
        e2->origin = v2;
        e2->destination = v1;
        e2->weight = weight;

        vertices[v2]->edges.push_back(e2);

        edges.push_back(e2);
    }

    void printEdges()
    {

        for (Edge *e : edges)
        {
            cout << e->weight;
        }
    }

    void printMST()
    {
        for (Edge *e : mstEdges)
        {
            cout << e->origin << "-----" << e->destination << " " << e->weight << " " << endl;
        }
    }

    void initializeMST()
    {
        for (auto vertix : vertices)
        {
            vertix->visited = false;
        }

        vector<Vertex *> currentVertices;
        vertices[0]->visited = true;
        currentVertices.push_back(vertices[0]);

        while (currentVertices.size() < vertices.size())
        {
            int currentLowestCost = INT_MAX;
            Edge *safestLowestCostEdge = nullptr;

            for (auto vertix : currentVertices)
            {
                for (auto edge : vertix->edges)
                {
                    // Check If the vertix is safe
                    auto destination = vertices[edge->destination];
                    if (destination->visited)
                    {
                        continue;
                    }

                    if (currentLowestCost > edge->weight)
                    {
                        currentLowestCost = edge->weight;
                        safestLowestCostEdge = edge;
                    }
                }
            }

            if (safestLowestCostEdge == nullptr)
                continue;

            mstEdges.push_back(safestLowestCostEdge);
            auto selectedVertix = vertices[safestLowestCostEdge->destination];

            currentVertices.push_back(selectedVertix);
            selectedVertix->visited = true;
        }
    }
};

int main()
{

    Graph *g = new Graph;
    g->intializeVertices();

    g->addEdge(0, 5, 1);
    g->addEdge(1, 3, 1);
    g->addEdge(1, 2, 2);
    g->addEdge(0, 1, 3);
    g->addEdge(2, 3, 3);
    g->addEdge(4, 5, 4);
    g->addEdge(4, 3, 5);
    g->addEdge(2, 5, 5);
    g->addEdge(1, 4, 10);

    g->initializeMST();
    g->printMST();
}

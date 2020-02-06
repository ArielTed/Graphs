#include <cstdlib>
#include <iostream>
#include <limits>
#include <cfloat>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <list>
#include <ctime>
#include <stdexcept>
#include <stack>

using namespace std;

class Edge;

class Node
{
    private:
        string payload;
        bool visited;
        vector<Edge*>* adjacents;
        double distance;
    
    public:
        Node(const string &elem) : payload(elem), visited(false), distance(DBL_MAX)
        {
            adjacents = new vector<Edge*>();
        }
    
        ~Node() { }
        
        void setVisited(bool v)
        {
            visited = v;
        }
 
        bool isVisited()
        {
            return visited;
        }
    
        void setDistance(double d)
        {
            distance = d;
        }
    
        double getDistance()
        {
            return distance;
        }
  
        void addEdge(Edge* e)
        {
            adjacents->push_back(e);
        }
    
        int degree() const
        {
            return (int)adjacents->size();
        }
    
        string getPayload() const
        {
            return payload;
        }
    
        vector<string>* neighbors();
    
        vector<Edge*>* adjacentsList()
        {
            return adjacents;
        }
};

class Edge
{
    private:
        Node*  node;
        double weight;
        friend class Node;
    
    public:
        Edge(Node* n, double w) : node(n), weight(w) { }
    
        ~Edge() { }
    
        void setWeight(double w)
        {
            weight = w;
        }
    
        Node* getNode() const
        {
            return node;
        }
    
        double getWeight() const
        {
            return weight;
        }
};

class Graph
{
    private:
        map<string, Node*>* graph;
        bool directed;
    
    public:
        Graph(bool directed) : directed(directed)
        {
            graph = new map<string, Node*>();
        }

        ~Graph()
        {
            delete graph;
        }
  
        //DO NOT CHANGE THE FOLLOWING METHODS
        void addNode(string node);
        void addEdge(string nid1, string nid2, double w);
        void printGraph();

        //Homework
        bool IsThereTripletClique();
        double GetMinDistance(string city1, string city2);
        bool isGraphConnected();
        double LongestSimplePath();
        void GenerateRandomNodes(int numberNodes); //Generate random nodes
        void GenerateRandomEdges(int numberNodes, int numberEdges, double weight); //Generate random edges with existing nodes in the graph
    
    private:
        void setFalse(); //set all nodes to unvisited
        void setDistanceInfinite(); //set all nodes distance to infinity (DBL_MAX)
        void dfs(Node* n); //Helper function for isGraphConnected using Depth First Search
        void dijkstra(Node* startnode); //Dijkstra algorithm for GetMinDistance
        int random_int(int val_min, int val_max); //Generate a random int
        void dfs2(Node* n, double dp[]); //Helper function for LongestSimplePath using Depth First Search
};

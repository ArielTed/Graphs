#include "graph.h"

vector<string>* Node::neighbors()
{
   vector<string>* vec = new vector<string>();
    
   vector<Edge*>::iterator it;
   for (it = adjacents->begin(); it != adjacents->end(); it++)
   {
       vec->push_back((*it)->getNode()->getPayload());
   }
    
   return vec;
}

void Graph::addNode(string name)
{
    Node* node = new Node(name);
    graph->insert(pair<string, Node*> (name, node));
}

void Graph::addEdge(string k1, string k2, double w = 1.0)
{
    map<string, Node*>::iterator it1, it2;
    it1 = graph->find(k1);
    it2 = graph->find(k2);

    if (it1 != graph->end() && it2 != graph->end())
    {
        Node* n1 = (*it1).second;
        Node* n2 = (*it2).second;

        Edge* e = new Edge(n2, w);
        n1->addEdge(e);
        if (!directed)
        {
            Edge* be = new Edge(n1, w);
            n2->addEdge(be);
        }
    }
}

void Graph::printGraph()
{
    map<string, Node*>::iterator it;
    for (it = graph->begin(); it != graph->end(); it++)
    {
        Node* n = (*it).second;
        cout << n->getPayload() << " [";
    
        vector<string>* neigh  = n->neighbors();
        vector<string>::iterator itn;
        for(itn = neigh->begin(); itn != neigh->end(); itn++)
        {
            if (itn == neigh->end() - 1)
                cout << (*itn);
            else cout << (*itn) << " ";
        }
        
        cout << "]" << endl;
    }
}

void Graph::setFalse()
{
    map<string, Node*>::iterator it;
    for (it = graph->begin(); it != graph->end(); it++)
    {
        (*it).second->setVisited(false);
    }
}

void Graph::setDistanceInfinite()
{
    map<string, Node*>::iterator it;
    for (it = graph->begin(); it != graph->end(); it++)
    {
        (*it).second->setDistance(DBL_MAX);
    }
}

bool Graph::IsThereTripletClique()
{
    map<string, Node*>::iterator it;
    for (it = graph->begin(); it != graph->end(); it++) //go through each node
    {
        Node* n = (*it).second;
        vector<string>* neighbors = n->neighbors();

        for (int i = 0; i < n->degree(); i++) //go through each neighbor of the node
        {
            Node* n2 = n->adjacentsList()->at(i)->getNode();
            vector<string>* neighbors2 = n2->neighbors();
            for (int j = 0; j < neighbors->size(); j++)
            {
                for (int k = 0; k < neighbors2->size(); k++) //go through each neighbor of the node's neighbors
                {
                    if (neighbors->at(j) == neighbors2->at(k)) //check if the node and one of his neighbor have a neighbor in common
                        return true;
                }
            }
        }
    }
    return false;
}

bool Graph::isGraphConnected()
{
    setFalse();
    
    Node* n = nullptr;
    
    map<string, Node*>::iterator it;
    for (it = graph->begin(); it != graph->end(); it++)
    {
        if ((*it).second->degree() <= 0) //if a node has no neighbor, then graph is not connected
            return false;
        else n = (*it).second;
    }
    
    dfs(n); //runs dfs from any node, here the last one
    
    for (it = graph->begin(); it != graph->end(); it++)
    {
        if (!(*it).second->isVisited())
        {
            return false; //after running dfs, if a node is not visited, it means graph is not connected
        }
    }
    return true;
}

void Graph::dfs(Node* n) //Depth-first search starting from node n
{
    n->setVisited(true);
    
    for (int i = 0; i < n->degree(); i++)
    {
        if (!n->adjacentsList()->at(i)->getNode()->isVisited())
        {
            dfs(n->adjacentsList()->at(i)->getNode());
        }
    }
}

void Graph::dijkstra(Node* startnode) //Dijkstra algorithm using STL priority queue
{
    setFalse();
    setDistanceInfinite();
    
    priority_queue<Node*, vector<Node*>, greater<Node*> > pq;
        
    pq.push(startnode);
    startnode->setDistance(0);
    
    while (!pq.empty())
    {
        Node* u = pq.top();
        pq.pop();
        
        for (int i = 0; i < u->degree(); i++)
        {
            if (u->getDistance() + u->adjacentsList()->at(i)->getWeight() < u->adjacentsList()->at(i)->getNode()->getDistance())
            {
                u->adjacentsList()->at(i)->getNode()->setDistance(u->getDistance() + u->adjacentsList()->at(i)->getWeight());
                pq.push(u->adjacentsList()->at(i)->getNode());
            }
        }
    }
}

double Graph::GetMinDistance(string city1, string city2)
{
    map<string, Node*>::iterator it1, it2;
    it1 = graph->find(city1);
    it2 = graph->find(city2);
    
    dijkstra((*it1).second); //runs dijkstra algorithm and update all nodes distance to min distance from start node (city1) to the node
    
    return (*it2).second->getDistance(); //return distance of the node wanted in parameter
}

void Graph::GenerateRandomNodes(int numberNodes)
{
    for (int i = 1; i <= numberNodes; i++)
    {
        addNode(to_string(i));
    }
}

int Graph::random_int(int val_min, int val_max)
{
    int rand = 0;
    do
    {
        rand = val_min + std::rand()/(RAND_MAX/(val_max - val_min+1));
    }
    while (rand > val_max);
    return rand;
}

void Graph::GenerateRandomEdges(int numberNodes, int numberEdges, double weight)
{
    for (int i = 0; i < numberEdges; i++)
    {
        int node1 = random_int(1, numberNodes); //choosing two different nodes of the graph randomly
        int node2 = -1;
        do
        {
            node2 = random_int(1, numberNodes);
        } while (node2 == node1);
        
        map<string, Node*>::iterator it1, it2;
        it1 = graph->find(to_string(node1));
        it2 = graph->find(to_string(node2));
        
        bool verif = false;
        if ((*it1).second->degree() > 0)
        {
            vector<Edge*>::iterator it;
            for (it = (*it1).second->adjacentsList()->begin(); it != (*it1).second->adjacentsList()->end(); it++)
            {
                if ((*it)->getNode()->getPayload() == (*it2).first)
                {
                    verif = true; //Check if the edge doesn't already exist
                }
            }
        }
        
        if (verif) //If the edge already exists, we do the loop again
            i--;
        else addEdge((*it1).first, (*it2).first, weight); //else, we can add it
    }
}

void Graph::dfs2(Node* n, double dp[])
{
    n->setVisited(true);
  
    vector<Edge*>::iterator it;
    for (it = n->adjacentsList()->begin(); it != n->adjacentsList()->end(); it++)
    {
  
        if (!(*it)->getNode()->isVisited())
            dfs2((*it)->getNode(), dp);
        
        dp[stoi(n->getPayload())] = max(dp[stoi(n->getPayload())], 1 + dp[stoi((*it)->getNode()->getPayload())]);
    }
}

double Graph::LongestSimplePath()
{
    double dp[graph->size()]; //array to store longest path for each node
    memset(dp, 0, sizeof dp);
    
    setFalse();
  
    map<string, Node*>::iterator it;
    for (it = graph->begin(); it != graph->end(); it++)
    {
        if (!(*it).second->isVisited())
            dfs2((*it).second, dp); //runs dfs for each node not yet visited
    }
  
    double longest = 0;
  
    for (int i = 0; i < graph->size(); i++)
    {
        longest = max(longest, dp[i]); //updates longest simple path to the max value of dp
    }
    
    return longest;
}

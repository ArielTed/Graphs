#include "graph.h"

int random_int(int val_min, int val_max)
{
    int rand = 0;
    do
    {
        rand = val_min + std::rand()/(RAND_MAX/(val_max - val_min+1));
    }
    while (rand > val_max);
    return rand;
}

int main()
{
    srand((unsigned)time(0));
    
    Graph g(true);
    
    int numberNodes = 100, numberEdges = 500;
    g.GenerateRandomNodes(numberNodes);
    g.GenerateRandomEdges(numberNodes, numberEdges, 1);
    g.GenerateRandomEdges(numberNodes, numberEdges, 2);
    g.GenerateRandomEdges(numberNodes, numberEdges, 3);
    
    const int CLOCKS_PER_MS = CLOCKS_PER_SEC / 1000;

    clock_t Start = clock();
    g.IsThereTripletClique();
    clock_t End = clock();
    float elapsedTime_IsThereTripletClique = (float)(End - Start) / CLOCKS_PER_MS;

    Start = clock();
    g.isGraphConnected();
    End = clock();
    float elapsedTime_isGraphConnected = (float)(End - Start) / CLOCKS_PER_MS;

    int node1 = random_int(1, numberNodes);
    int node2 = -1;
    do
    {
        node2 = random_int(1, numberNodes);
    } while (node2 == node1);

    Start = clock();
    g.GetMinDistance(to_string(node1), to_string(node2));
    End = clock();
    float elapsedTime_GetMinDistance = (float)(End - Start) / CLOCKS_PER_MS;
    
    Start = clock();
    g.LongestSimplePath();
    End = clock();
    float elapsedTime_LongestSimplePath = (float)(End - Start) / CLOCKS_PER_MS;

    cout << "\nExecution time for function IsThereTripletClique() : " << elapsedTime_IsThereTripletClique << " milliseconds.\n";
    cout << "\nExecution time for function isGraphConnected() : " << elapsedTime_isGraphConnected << " milliseconds.\n";
    cout << "\nExecution time for function GetMinDistance() : " << elapsedTime_GetMinDistance << " milliseconds.\n";
    cout << "\nExecution time for function LongestSimplePath() : " << elapsedTime_LongestSimplePath << " milliseconds.\n\n";
            
    return 0;
}

/***************************************************************************
 * * The school assignment asked for only algorithm for the shortest path.
 * * But, I wanted to write this code ofr myself.
 ***************************************************************************/

#include <iostream>
#include <climits>
#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include <string>
#include <sstream>
#include <utility>
//#include <list>
//#define V 8

typedef std::pair<int, int> iPair;
void dijkstra(std::vector <std::vector<int> > & adja, int start, int Vt);
int show(){

    std::ifstream in_file;
    in_file.open("graph.txt");

    if (!in_file) {
        std::cerr << "Error while opening input file" << std::endl;
        return 1;
    }
    int V;
    in_file>>V;

    std::string line;
    int u, v, w;

    std::vector< std::vector<int> > gh;

    while (std::getline(in_file, line)) {
        //while(!in_file.eof())  {
        //std::vector<int> array;

        std::istringstream iss(line);

        while(iss>>u>>v>>w) {

            gh.push_back({u, v, w});
        }
    }

    for(int i=0; i<V; i++) {
        std::cout<<"\nStarting point: "<<i<<std::endl;
        dijkstra(gh, i, V);
    }

return 0;
}


void dijkstra(std::vector <std::vector<int> > & adja, int start, int Vt){

    std::priority_queue< iPair, std::vector<iPair>, std::greater<> > priQ;

    std::vector<int> dist((unsigned long)Vt, INT_MAX);
    std::map<int, int> parent;
    std::map<int, std::vector<int> >parentPath;
    std::vector<bool> visited((unsigned long)Vt, false);

    priQ.push(std::make_pair(0, start));
    dist[start] = 0;

    while (!priQ.empty()) {

        int u = priQ.top().second; visited[u] = true;
        priQ.pop();


        for(int i= 0; i < adja.size(); i++) {

            if(adja[i][0] == u) {

                int v = adja[i][1];
                int weight = adja[i][2];

                if ((dist[v] > dist[u] + weight) && dist[u] != INT_MAX && !visited[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    parentPath[v].push_back(u);

                    priQ.push(std::make_pair(dist[v], v));
                }
           }
        }
    }

    std::cout<<"Vertex Distance from Source"<<std::endl;
    for(int j=0; j <Vt; j++) {
        std::cout<<j<<": "<<dist[j]<<std::endl;
    }
    std::cout<<"Vertex: Parents"<<std::endl;
    for(auto d: parent) {
        std::cout << d.first << ":  " << d.second << std::endl;
    }

    std::cout<<"Vertex: Parents Path"<<std::endl;
    for(auto mapIt = begin(parentPath); mapIt !=end(parentPath); mapIt++){
        std::cout<<mapIt->first<<": ";
        for(auto c: mapIt->second) {
            std::cout<<c<<" ";
        }
        std::cout<<std::endl;
    }

}

int main() {
    std::cout << "Dijkstra's Algorithm" << std::endl;
    //std::vector <std::vector<int, int> > adja;
    //int V = 8;
    show();
    return 0;

    /*********************************************
    std::vector<std::vector<int> > graph;
    graph.push_back({0, 2, 4});
    graph.push_back({0, 5, 7});
    graph.push_back({1, 4, 9});
    graph.push_back({1, 7, 3});
    graph.push_back({2, 0, 4});
    graph.push_back({2, 3, 3});
    graph.push_back({2, 5, 2});
    graph.push_back({2, 6, 9});

    graph.push_back({3, 2, 3});
    graph.push_back({3, 4, 3});
    graph.push_back({3, 6, 7});

    graph.push_back({4, 1, 9});
    graph.push_back({4, 3, 3});
    graph.push_back({4, 6, 2});
    graph.push_back({4, 7, 7});

    graph.push_back({5, 0, 7});
    graph.push_back({5, 2, 2});
    graph.push_back({5, 6, 8});

    graph.push_back({6, 2, 9});
    graph.push_back({6, 3, 7});
    graph.push_back({6, 4, 2});
    graph.push_back({6, 5, 8});
    graph.push_back({6, 7, 3});

    graph.push_back({7, 1, 3});
    graph.push_back({7, 4, 7});
    graph.push_back({7, 6, 3});

    //for(auto a: graph) {
    //        std::cout<<a[0]<<" "<<a[1]<<" "<<a[2]<< std::endl;
    //}

    for(int i=0; i<V; i++) {
       std::cout<<"\nStarting point: "<<i<<std::endl;
        dijkstra(graph, i);
    }
    *****************************************************************/

}

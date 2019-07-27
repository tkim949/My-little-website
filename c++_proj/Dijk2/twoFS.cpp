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
#include <iomanip>
//#include <list>
//#define V 8

typedef std::pair<int, int> iPair;
//typedef std::pair<int, std::string> iPair;

std::vector<int> dijkstra(std::map<int, std::map<int, int> > & ad, int start, int Vt);
//std::vector<int> dijkstra(std::map<std::string, std::map<std::string, int> > & ad, int start, int Vt);
void twoSta(std::vector<std::vector<int> > & ot);

int show(){

    std::ifstream in_file;
    in_file.open("graph2.txt");

    if (!in_file) {
        std::cerr << "Error while opening input file" << std::endl;
        return 1;
    }
    int V;
    in_file>>V;

    std::string line;
    int u, v, w;
   // int w;
   // std::string u, v;

    //std::map<std::string, std::map<std::string, int> > ad;
    std::map<int, std::map<int, int> > ad;

    while (std::getline(in_file, line)) {

        std::istringstream iss(line);

        while(iss>>u>>v>>w) {

            //gh.push_back({u, v, w});
            ad[u].insert(std::make_pair(v, w));
            ad[v].insert(std::make_pair(u, w));

        }
    }
    for(auto m: ad) {
        std::cout<<m.first<<": ";
        for(auto p: m.second){
            std::cout<<"["<<p.first<<": "<<p.second<<"], ";
        }
        std::cout<<std::endl;
    }



    std::vector <std::vector<int> > matr((unsigned long)V, std::vector<int>((unsigned long)V));
    std::vector<int> dis;
   for(int i=0; i<V; i++) {
   // for(auto a: ad)  {
        dis = dijkstra(ad, i, V);
        //for(int i=0; i<V; i++) {
            for (int h = 0; h < dis.size(); h++) {

                matr[i][h] = dis[h];
            }
        //}
    }

    for(int s=0; s<V; s++) {
        for(int t=0; t<V; t++) {
            std::cout<<std::setw(3)<<matr[s][t];
        }
        std::cout<<std::endl;
    }

    twoSta(matr);

    return 0;

}

void twoSta(std::vector<std::vector<int> > &ot) {

    std::vector<std::vector<int> > twoFS;
    int sum, min;
    for(int i=0; i <ot.size(); i++) {


        for(int j= i+1; j<ot[0].size(); j++) {
            sum =0;
            std::cout<<"Fire Stations: "<<i<<" & "<<j<<" ";
            min =0;


            for(int k=0; k<ot.size(); k++) {

                if(k != i && k !=j) {

                    if( ot[i][k] <= ot[j][k] ) {

                        twoFS.push_back({i, k, ot[i][k]});
                        min = ot[i][k];

                      //  std::cout<<i<<" "<<k<<" distance ="<<ot[i][k]<<" : ";
                    }
                    else{
                        twoFS.push_back({j, k, ot[j][k]});
                        min = ot[j][k];
                       // std::cout<<j<<" "<<k<<" distance ="<<ot[j][k]<<" : ";
                    }

                    sum +=min;

                }

            }


          std::cout<<"Total minimum  distance: "<<sum<<std::endl;
        }

    }
/*********************************************************************
    for(auto e: twoFS) {
        for (int t = 0; t < e.size(); t++) {
            std::cout << e[t] << " ";
        }
        std::cout << std::endl;
    }
*********************************************************************/

}


//std::vector<int> dijkstra(std::map<std::string, std::map<std::string, int> > & ad, std::string start, int Vt);
std::vector<int> dijkstra(std::map<int, std::map<int, int> > & ad, int start, int Vt){

    std::priority_queue< iPair, std::vector<iPair>, std::greater<iPair> > priQ;

    //std::vector<int> dist((unsigned long)Vt, INT_MAX);
    std::vector<int> dist((unsigned long)Vt, INT_MAX);
    std::map<int, int> parent;
    std::map<int, std::vector<int> >parentPath;
    std::vector<bool> visited((unsigned long)Vt, false);

    priQ.push(std::make_pair(0, start));
    dist[start] = 0;
    int count =0;
    while (!priQ.empty()) {

        int u = priQ.top().second;
        visited[u] = true;
        //std::cout<<"priorityQ: "<<priQ.top().second<<", "<<u<<std::endl;
        priQ.pop();

        //for (auto it = ad.find(u); it != ad.end(); it++) {
        for(auto r: ad){
            if(r.first == u) {
                for (auto el: r.second) {

                   // std::cout << "u: " << u << "it->first: " << r.first << std::endl;
                    count +=1;
                    int v = el.first;
                    int weight = el.second;

                    if ((dist[v] > dist[u] + weight) && dist[u] != INT_MAX) {
                   // if (!visited[v] && (dist[v] > dist[u] + weight) && dist[u] != INT_MAX) {
                        dist[v] = dist[u] + weight;
                        parent[v] = u;
                        parentPath[v].push_back(u);

                        priQ.push(std::make_pair(dist[v], v));
                    }
                }
            }

        }

    }
    
            std::cout<<"Vertex Distance from Source"<<std::endl;
            for(int j=0; j <Vt; j++) {
                std::cout<<j<<": "<<dist[j]<<std::endl;
            }
           /****************************************************
            std::cout<<"Vertex: Parents"<<std::endl;
            for(auto d: parent) {
                std::cout << d.first << ":  " << d.second << std::endl;
            }
           **************************************************/

            std::cout<<"Vertex: Parents Path"<<std::endl;
            for(auto mapIt = begin(parentPath); mapIt !=end(parentPath); mapIt++){
                std::cout<<mapIt->first<<": ";
                for(auto c: mapIt->second) {
                    std::cout<<c<<" ";
                }
                std::cout<<std::endl;
            }


    std::cout<<"Count: "<<count<<std::endl;
    return dist;

}

int main() {
    std::cout << "Dijkstra's Algorithm" << std::endl;
    //std::vector <std::vector<int, int> > adja;
    //int V = 8;
    show();
    return 0;
}

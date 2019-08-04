
/**********************************************************************************
 * * In the class, we only dealt BFS and Dijkstra for the HW.
 * * And this topological sorting was only for the practice Q and theoretical.
 * * but this topological sorting looked fascinating!
 ********************************************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <stack>
#include <set>
#include <sstream>
void topoSort(std::map<std::string, std::vector<std::string> > & mapG);
void distan(std::stack<std::string> str, std::map<std::string, std::vector<std::string> > & mapG);
void print(std::stack<std::string> st);

int show() {

    std::ifstream in_file;
    in_file.open("graph.txt");

    if (!in_file) {
        std::cerr << "Error while opening input file" << std::endl;
        return 1;
    }
    std::string line;

    std::map <std::string, std::vector<std::string> > mapG;
    std::string a, b;

    while (std::getline(in_file, line)) {

        std::istringstream iss(line);

        while (iss >> a >> b) {

            // mapG.insert(std::make_pair(b, a));
            mapG[b].push_back(a); //parent to the key and children to the values.
        }
    }
    topoSort(mapG);

  return 0;
}

void topoSHelp(std::string const & s, std::set<std::string> & visit, std::stack<std::string> & st, std::map<std::string, std::vector<std::string> > & mapG){

    visit.insert(s);

    for(auto c: mapG[s]){
        if(visit.count(c) != 0){
            continue;
        }

        topoSHelp(c, visit, st, mapG);
    }

    st.push(s);
}


void topoSort(std::map<std::string, std::vector<std::string> > & mapG) {

    std::stack<std::string> st;
    std::set<std::string> visited;

    for(auto const &a: mapG){

        if(visited.count(a.first)!=0){
            continue;
        }
        topoSHelp(a.first, visited, st, mapG);

    }
    print(st);
    distan(st, mapG);

}

void print(std::stack<std::string> st){

    while (!st.empty()) {
        if(st.top()=="NONE"){
             st.pop();
             continue;  
         }
        std::cout<< st.top()<<" ";
        st.pop();
    }
    std::cout<<std::endl;

}

void distan(std::stack<std::string> str, std::map<std::string, std::vector<std::string> > & mapG){

    std::map<std::string, int> dist;
    std::map<std::string, std::vector<std::string> > path;

    for(auto d: mapG){
        dist[d.first] = 0;
        path[d.first] = {};
    }
    int maxP=0;

    std::string f = str.top();

    while(!str.empty()) {

        std::string f = str.top();
        str.pop();

        for (auto r: mapG) {
            if (r.first == f) {
                for (auto el: r.second) {

                    if(dist[el] < dist[f] + 1) {
                        dist[el] = std::max(dist[el], dist[f] + 1);

                    }
                    maxP = std::max(maxP, dist[el]);
                }
            }

        }
    }
    std::string t, m;
    for(auto const & g: dist){
        if(g.second == maxP) {

           t = g.first;
           m = g.first;
        }
    }
    for(auto d: dist){
       if(d.first == "NONE") continue;
        std::cout<<"dist "<<d.first<<" "<<d.second<<std::endl;
    }

    int count = maxP-1;

    while(count >= 0){

        for(auto const & r: dist) {

            if (r.second == count) {

                for (auto const &q: mapG[r.first]) {

                    if (t == q) {
                        path[m].push_back(q);
                        t = r.first;
                    }
                }
            }
        }
        count--;
    }

    for(auto const & r: path[m]){

        std::cout<<r<<" ";
    }
    std::cout<<std::endl;



}

int main() {
    std::cout << "Hello, World!" << std::endl;
    show();
    return 0;
}

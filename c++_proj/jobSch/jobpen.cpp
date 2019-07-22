/************************************************************************
 * * Originally school assignment, but it was only asking for describing and
 * * pseudocode, but I wanted to write this code.
 *************************************************************************/


#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stack>
#include <queue>
#include <sstream>
std::queue<int> jobSchedule(std::vector < std::vector<int> > & sT, int totD);
std::stack<int> scheduleLS(std::vector <std::vector<int> > & sT);

std::queue<int> jobScheduleAl(std::vector < std::vector<int> > & sT, int totD); 
void insertSort( std::vector<std::vector<int> > &arr, int len){

    int obj, j;
    for(int i =1; i < len; ++i) {

             obj = arr[i][0];
             std::vector<int> temp;
             temp = arr[i];

            //obj = arr[i];
            j = i - 1;

            while (j >= 0 && arr[j][0] < obj) {

                arr[j + 1] = arr[j];

                j -= 1;
            }
           // arr[j + 1] = obj;
           arr[j +1] = temp;

    }

}


int show() {
    std::ifstream in_file;
    in_file.open("job1.txt");

    if (!in_file) {
        std::cerr << "Error while opening input file" << std::endl;
        return 1;
    }

    std::ofstream out_file;
    out_file.open("result.txt", std::ios::out);

    if(!out_file) {
        std::cerr << "Error while opening output file" << std::endl;
        return 1;
    }

   // std::string line;
    int d= 1;
      
         // while(std::getline(in_file, line)){       
          while(!in_file.eof()){
     
            int penalty =0, deadline =0;
            int cnt, idNum;
            int totalD;
           // std::istringstream iss(line);
             in_file >> cnt;
             in_file >> totalD;
           // iss>> cnt;
           // iss>>totalD;            

            if(in_file.eof()){
                    break;
            }
            std::vector< std::vector<int> > vecOut;
            std::vector<int> vecIn;

            out_file <<"\nSet " << d  << std::endl;
            std::cout<<"\nSet " <<d <<std::endl;


           for (int j = 0; j < cnt; j++) {

               vecIn.clear();
               
                in_file>>idNum;
                in_file>>penalty;
                in_file>>deadline;
               //while(iss>>idNum>>penalty>>deadline){
                vecIn.push_back(penalty);
                vecIn.push_back(deadline);
                vecIn.push_back(idNum);

                vecOut.push_back(vecIn);
               //}
            }

            //std::sort(vecOut.begin(), vecOut.end(), std::greater<>());
           /******************************************************
           for(int i=0; i <vecOut.size(); i++) {

               for(int j= 0; j<3; j++) {

                   std::cout<<vecOut[i][j]<<" ";
               }
               std::cout<<std::endl;
           }
           **********************************************************/

            int sz = static_cast<int> (vecOut.size());

            insertSort(vecOut, sz);
            /*****************************************************
            std::cout<<"After sorting: "<<std::endl;

            for(auto v: vecOut) {
                for(auto i: v){
                    std::cout<<i <<" ";
                }
                std::cout<<std::endl;
            }
           ***************************************************************/

            std::queue <int> sta;

            sta = jobSchedule(vecOut, totalD);

            std::cout<<"Number of activities selected = "<<sta.size()<<std::endl;
            std::cout<<"Activities: ";
            out_file<<"Number of activities selected = "<<sta.size()<<std::endl;
            out_file<<"Activities: ";

            while(!sta.empty()) {
                std::cout<<sta.front()<<" ";
                out_file<<sta.front()<<" ";
                sta.pop();
            }
             
            std::cout<<std::endl;
            out_file<<std::endl;
            std::queue <int> staAl;

            staAl = jobScheduleAl(vecOut, totalD);

            std::cout<<"Al Number of activities selected = "<<staAl.size()<<std::endl;
            std::cout<<"Activities: ";
            out_file<<"Al Number of activities selected = "<<staAl.size()<<std::endl;
            out_file<<"Activities: ";

            while(!staAl.empty()) {
                std::cout<<staAl.front()<<" ";
                out_file<<staAl.front()<<" ";
                staAl.pop();
            }
         d +=1;
         //if(!in_file.eof()) break;
         std::cout<<std::endl;
         out_file<<std::endl;
        }

    in_file.close();
    out_file.close();

    return 0 ;

}


std::queue<int> jobSchedule(std::vector < std::vector<int> > & sT, int totD) {

    std::queue <int> queJ;
    int size = static_cast<int> (sT.size());
    std::vector <bool> isVac ((unsigned int)totD, true);
    std::vector <bool> beforeD ((unsigned int)size, false);
    for(int i=0; i < size; i++) {

        int idx = std::min(totD, sT[i][1]) -1;

        while(idx >=0 && (sT[i][1]-1 <= idx)) {

            if(isVac[idx]) {
                queJ.push(sT[i][2]);
                beforeD[i] = true;
                isVac[idx] = false;
                idx = -1;
            }

            else{
                idx -=1;
            }

        }
     }
       for(int j=0; j<size; j++){
       // for(auto a: beforeD){
           if(beforeD[j] == false) {
             queJ.push(sT[j][2]);
        }
       // std::cout<<std::endl;
    }
   return queJ ;
}

std::queue<int> jobScheduleAl(std::vector < std::vector<int> > & sT, int totD) {

    std::queue <int> queAl;
    int size = static_cast<int> (sT.size());
    std::vector <bool> isVac ((unsigned int)totD, true);

    for(int i=0; i < size; i++) {
        queAl.push(sT[i][2]);
       /***********************************************
        int idx = std::min(totD, sT[i][1]) -1;

        while(idx >=0 && (sT[i][1]-1 <= idx)) {

            if(isVac[idx]) {
                queJ.push(sT[i][2]);
                isVac[idx] = false;
                idx = -1;
            }

            else{
                idx -=1;
            }

        }
     ******************************************************/
    }

    return queAl ;
}



std::stack<int> scheduleLS(std::vector <std::vector<int> > & sT){


     std::stack <int> st;

        int size = static_cast<int> (sT.size());

        st.push(sT[0][2]);

        int j = 0;

        for(int i = 1; i< size; i++) {

            if(sT[j][0] >= sT[i][1]) {

                st.push(sT[i][2]);
                j=i;

            }

        }

    return st;

}


int main() {
    std::cout << "==================================="<<std::endl;
    std::cout << "   Please see the result.txt!" << std::endl;
    std::cout << "==================================="<<std::endl;
    show();

    return 0;
}

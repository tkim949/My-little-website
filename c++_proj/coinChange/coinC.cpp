/**************************************************************
 * * This is my personal project
 * * Dynamic Programming: coinChange
 *************************************************************/



#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stack>
#include <climits>

std::vector<int> usedCoinArr(std::vector<int> usedCoin, std::vector<int> vec, int total);
int coinChange(std::vector<int> vec, int total);
int show(){

    int total;
    int coin;
    std::vector <int> coinList;
    std::ifstream in_file;
    in_file.open("coin.txt");

    if (!in_file) {
        std::cerr << "Error while opening input file" << std::endl;
        return 1;
    }

    in_file >> total;

    while(in_file>>coin){

        coinList.push_back(coin);
    }

    coinChange(coinList, total);
    in_file.close();

}

int coinChange(std::vector<int> vec, int total) {

    int minN [total +1];
    std::vector<int> usedC(total+1, -1);
    //int usedC [total +1];

    minN[0] = 0; // when we use 0 coin, the result is 0

    for(int i = 1; i <=total; i++) {
        minN[i] = INT_MAX; //just placeholder
        //usedC[i] = -1;
    }

    for(int j = 0; j < vec.size(); j++){ //I used <= but it was wrong. < is correct

        for(int i=1; i <=total; i++) {

            if( i >= vec[j]) {
                if(minN[i - vec[j]] +1 < minN [i]) {
                    minN[i] = minN[i - vec[j]] +1;
                    usedC[i] = j; //store the index number of used coin according to the amount.
                }
            }

        }

    }
    std::cout<<"Our total: "<<total<<std::endl;
    std::cout<<"The minimum number of coins: "<< minN[total]<<std::endl;
    std::vector<int> usedArr;
    usedArr = usedCoinArr(usedC, vec, total);
    std::cout<<"used coin from coin change function: ";
    for(auto u: usedArr){
        std::cout<<u<<" ";
    }
    std::cout<<std::endl;
/********************************************************
    if(usedC[total] == -1) {
        std::cout<< "No solution"<<std::endl;
    }

    int bottomS = total;

    std::cout<<"The used coin is: ";

    while (bottomS > 0) {

        int k = usedC[bottomS];
        std::cout<< vec[k]<<" ";
        bottomS = bottomS - vec[k];
    }
    ****************************************************/
   std::cout<<std::endl;
}

std::vector<int> usedCoinArr(std::vector<int> usedC, std::vector<int> vec, int total){
    
    std::vector<int> usedA(vec.size(), 0);
    if(usedC[total] == -1) {
        std::cout<< "No solution"<<std::endl;
        
    }

    int bottomS = total;

    std::cout<<"The used coin is: ";

    while (bottomS > 0) {

        int k = usedC[bottomS];
        usedA[k] +=1;
       // usedA.push_back(vec[k]);
        std::cout<< vec[k]<<" ";
        bottomS = bottomS - vec[k];
    }
  std::cout<<std::endl;
    return usedA;
}



int main() {
    std::cout << "Coin change!" << std::endl;
    show();
    return 0;
}

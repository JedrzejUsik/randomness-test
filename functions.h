#ifndef RANDOMNESS_TEST_FUNCTIONS_H
#define RANDOMNESS_TEST_FUNCTIONS_H

#include <cmath>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>
#include <bitset>
#include "namespace_std.h"
#include <filesystem>
#define N 10 // number of digits in the biggest pattern

void bintotxt(){
    std::ifstream fbin ;
    fbin.open("QNGFile.dat",std::ios::out | std::ios::binary);
    fstream txt;
    txt.open("1010.txt", std::ios::in | std::ios::out );

    string rnum;// string for random number
    char byte;
    while(fbin.get(byte)){
        //cout<<"1";
    }
    txt.close();
    fbin.close();
}

string pattern_maker(int size,int n){//Look at the function name... It's not so hard
    {
        string r;
        while(n!=0) {
            r=(n%2==0 ?"0":"1")+r;
            n/=2;
        }

        while(r.length()<size){// because we want 0011 for 4-digit pattern, without it we will get 11
            r="0"+r;
        }
        return r;
    }
}
void test(){
    std::ifstream fbin ;
    fbin.open("QNGFile.dat",std::ios::out | std::ios::binary);
    fstream fres ;
    fres.open("test_results.txt", std::ios::in | std::ios::out );
    fres<<"pattern"<<'\t'<<"pattern count"<<'\t'<<"percentage"<<'\t'<<"should-be %"<<endl;

    string rnum;// string for random number
    bintotxt();
    /*cout << static_cast<int>(x) << endl;
    string potatoe; // string named after you
    double average,count=0;

    for(int i=1;i<=N;i++){//how big is pattern?, pow(2,i) is pattern size
        for(int j=0;j<pow(2,i);j++){//set pattern, j is pattern in decimal
            potatoe=pattern_maker(i,j);
            count=0;
            for(int k=0;k<rnum.length()-i;k++) {//count pattern in random generated number
                if(rnum.substr(k,i)==potatoe){
                    count++;
                }
            }
            //cout<<potatoe<<'\t'<<count<<'\t'<<count/(rnum.length()-i)*100<<'\t'<< 1/(double)pow(2,i)*100 <<endl;
        }
    }*/

    fbin.close();
    fres.close();
}


#endif //RANDOMNESS_TEST_FUNCTIONS_H

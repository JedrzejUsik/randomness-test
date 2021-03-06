// Created by basement troll
#ifndef RANDOMNESS_TEST_FUNCTIONS_H
#define RANDOMNESS_TEST_FUNCTIONS_H

#include <cmath>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>
#include <thread>
#include <bitset>
#include "namespace_std.h"
#include <filesystem>
#include <random>
#define N 100 // number of digits in the biggest pattern
#define T 8 // number of threads, don't use more than ~75% of your Logical Processors or you will kill your pc
#define MPC 64 // maximum patterns checked, set to 2^N for all patterns
string rnum;// because multithread is copying variables, without global string we will make 4 copies of
            // rnum 800 MB each, i'm stupid so i don't have any better ideas


void pseudorandom1(unsigned __int64 n){// remember to put bintotxt() in test() into comment before using it, bintotxt will overwrite file
    std::ofstream txt;
    txt.open("1010.txt",std::ios::out | std::ios::binary);
    srand(time(nullptr));

    for(unsigned __int64 i=0; i<n; ++i)
    {
        txt << rand()%2;
    }
    txt.close();
}

void pseudorandom2(unsigned __int64 n){// remember to put bintotxt() in test() into comment before using it, bintotxt will overwrite file
    std::ofstream txt;
    txt.open("1010.txt",std::ios::out | std::ios::binary);
    std::mt19937 gen(time(nullptr));
    std::uniform_int_distribution<> distr(0, 1);

    for(unsigned __int64 i=0; i<n; ++i)
    {
        txt << distr(gen);
    }
    txt.close();
}

void bintotxt(){// function will translate binary file to txt file, every 1 and 0 will become char 0 or 1
    std::ifstream binary ;
    binary.open("QNGFile.dat",std::ios::out | std::ios::binary);
    std::ofstream txt;
    txt.open("1010.txt",std::ios::out | std::ios::binary);

    string rnum;// string for random number
    char byte;
    while(binary.get(byte))
    txt<<std::bitset< 8 >( byte );

    txt.close();
    binary.close();
}

string pattern_maker(unsigned __int64 size,unsigned __int64 n){//Look at the function name... It's not so hard
    {
        string r="";
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

void check_pattern(std::ofstream &fres, unsigned __int64 i, unsigned __int64 j){
    string potatoe=pattern_maker(i,j);
    double count=0;
    for(unsigned __int64 k=0;k<rnum.length()-i;k++) {//count pattern in random generated number
        if(rnum.substr(k,i)==potatoe){
            count++;
        }
    }
    cout<<i<<'\t'<<potatoe<<'\t'<<count<<'\t'<<count/(rnum.length()-i)*100<<'\t'<< 1/(double)pow(2,i)*100 <<endl;
    fres<<i<<'\t'<<potatoe<<'\t'<<count<<'\t'<<count/(rnum.length()-i)*100<<'\t'<< 1/(double)pow(2,i)*100 <<endl;
}

void test(){// main testing function.
    std::ifstream fbin ;
    fbin.open("1010.txt",std::ios::out);
    std::ofstream fres ;
    fres.open("test_results.txt", std::ios::in | std::ios::out );
    fres<<"p.length"<<"pattern"<<'\t'<<"pattern count"<<'\t'<<"percentage"<<'\t'<<"should-be %"<<endl;
    string potatoe; // string named after you
    fbin>>rnum;
    double count=0,completed=0,max,progress=0;
    double n=log(MPC)/log(2);
    if(pow(2,N)>MPC) max=4*(n*n)*(n+1)*(n+1)/4+(N-n)*MPC;//should be good
    else max=4*(N*N)*(N+1)*(N+1)/4;
    std::thread th[T];
    srand (time(NULL));
    unsigned __int64 start_time = time(NULL);


    for(unsigned __int64 i=1;i<=N;i++){//how big is pattern?, pow(2,i) is pattern size
        for(unsigned __int64 j=0;j<pow(2,i);j+=T*(1+(unsigned __int64)(pow(2,i)/MPC-1))) {//set pattern, j is pattern in decimal, we will split (for example) 1024 patterns into 0-128-256-384-512-640-768-896-1024 groups
            progress=(completed)/max;
            cout<<endl<<"progress: "<<progress*100<<"%"<<endl;
            cout<<"should end in (I hope) less than: "<<(int)(((time(NULL)-start_time)/(progress)*(1+0.01*N/i)/3600))<<" hours "<<((int)((time(NULL)-start_time)/(progress)*(1+0.01*N/i))%3600)/60<<" minutes "<<(int)((time(NULL)-start_time)/(progress)*(1+0.01*N/i))%60<<" seconds "<<endl;
            //yes, it is ineffective :(, (1+0.01*N/i) because for longer patterns checking will take more time
            cout<<"time passed: "<<(int)(((time(NULL)-start_time)/3600))<<" hours "<<(int)(((time(NULL)-start_time))%3600)/60<<" minutes "<<(time(NULL)-start_time)%60<<" seconds "<<endl<<endl;

            for (unsigned __int64 k = 0; k < T &&k<pow(2,i); k++) {//starting T threads
                th[k] = std::thread(check_pattern, std::ref(fres), i, (j+(k*(T*(1+(unsigned __int64)(pow(2,i)/MPC-1)))/8)+rand()%((T*(1+(unsigned __int64)(pow(2,i)/MPC-1)))/8)));
                //not random: (j+(k*(T*(1+(int)(pow(2,i)/MPC-1)))/8)) random: (j+(k*(T*(1+(int)(pow(2,i)/MPC-1)))/8)+rand()%((T*(1+(int)(pow(2,i)/MPC-1)))/8))
            }cout<<endl;
            for (unsigned __int64 k = 0;  k < T &&k<pow(2,i); k++) {//wait for threads to join
                th[k].join();
            }
            if(pow(2,i)<T) completed+=pow(2,i);
            else completed+=T;
        }
    }

    fbin.close();
    fres.close();
}

#endif //RANDOMNESS_TEST_FUNCTIONS_H
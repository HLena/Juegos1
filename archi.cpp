#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <omp.h>
#include <stdio.h>
#include <time.h>

using namespace std;

void fun_count_words(){
    ifstream infile;
    infile.open ("file5.txt");

    ofstream outfile;
    outfile.open ("file1Out.txt");

    map<string,int> dic;
    pair<map<string,int>::iterator,bool> ret;
    map<string,int>::iterator it = dic.begin();
    string word;

    //double wtime = omp_get_wtime();
    clock_t begin = clock();
    if (infile.is_open()) {
        //bool flag=true;
        #pragma omp parrallel for num_threads(16) default (none)\
        private (infile,word)

        for (;infile>>word; ){
        //while (file >> word){
            ret=dic.insert(pair<string,int>(word,1));
            #pragma omp critical
            if (ret.second==false){
                ret.first->second+=1;
            }
        }
    }else {
        cout << "Error al abrir archivo";
    }
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout<<"time: "<<elapsed_secs<<endl;

    for (it=dic.begin(); it!=dic.end(); ++it)
        cout << it->first << " " << it->second << '\n';
    outfile.close();
    
}

int main () {
    fun_count_words();
    // ifstream infile;
    // infile.open ("input_text.txt");

    // ofstream outfile;
    // outfile.open ("output.txt");

    // map<string,int> dic;
    // pair<map<string,int>::iterator,bool> ret;
    // map<string,int>::iterator it = dic.begin();
    // string word;

    // //double wtime = omp_get_wtime();
    // clock_t begin = clock();
    // if (infile.is_open()) {
    //     //bool flag=true;
    //     #pragma omp parrallel for num_threads(16) default (none)\
    //     private (file,word)

    //     for (;infile>>word; ){
    //     //while (file >> word){
    //         ret=dic.insert(pair<string,int>(word,1));
    //         #pragma omp critical
    //         if (ret.second==false){
    //             ret.first->second+=1;
    //         }
    //     }
    // }else {
    //     cout << "Error al abrir archivo";
    // }
    // clock_t end = clock();
    // double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    // cout<<"time: "<<elapsed_secs<<endl;

    // for (it=dic.begin(); it!=dic.end(); ++it)
    //     cout << it->first << " " << it->second << '\n';
    // outfile.close();
    // return 0;
}

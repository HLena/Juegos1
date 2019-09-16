#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <omp.h>
#include <stdio.h>
#include <time.h>

using namespace std;

void fun_count_words(string filename){
    ifstream infile;
    infile.open (filename);

    // ofstream outfile;
    // outfile.open ("file1Out.txt");

    map<string,int> dic;
    map<string,int>::iterator it = dic.begin();
    string word;

    clock_t begin = clock();
    if (infile.is_open()){
        //bool flag=true;
        // #pragma omp parrallel for default(none) num_threads(8) private(infile,word)
            for (;infile>>word;)
            {
                // int tid = omp_get_thread_num();
                // cout << "hilo_id:"<<tid<<" "<<word<<endl;
                // #pragma omp critical
                if(dic.find(word) == dic.end())
                    dic.insert(pair<string, int>(word,1));
                else
                    dic[word]++;
              
            }
        // }
        infile.close();
    }else {
        cout << "Error al abrir archivo";
    }
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout<<"time: "<<elapsed_secs<<endl;

    for (it=dic.begin(); it!=dic.end(); ++it)
        cout << it->first << " " << it->second << '\n';
    // outfile.close();
    
}



void InvertedIndex(string filename){
    ifstream infile;
    infile.open (filename);

    // map<string,map<string,int> > dic;
    // map<string,int>::iterator it = dic.begin();
    string word;

    // clock_t begin = clock();
    if (infile.is_open()){
        //bool flag=true;
        #pragma omp parrallel for default(none) num_threads(16) private(infile,word)
        {

            for (;infile>>word;)
            {
                // int tid = omp_get_thread_num();
                // cout << "hilo_id:"<<tid<<" "<<word<<endl;
                #pragma omp critical
                if(dic.find(word) == dic.end()){
                    // cout<<"nueva: "<<word<<" añado: "<<filename<<endl;
                    map<string,int> tmp;
                    tmp.insert(make_pair(filename,1));
                    dic.insert(make_pair(word,tmp));
                }else{
                    // cout<<" ya_puesta: "<<word<<endl;
                    if(dic[word].find(filename) == dic[word].end()){
                        // cout<<" añadiendo_txt = "<<filename<<endl;
                        dic[word].insert(make_pair(filename,1));
                    }
                    // else{
                    //     cout<<" ya_esta = "<<filename<<endl;
                    // }
                }
              
            }
        }
        infile.close();
    }else {
        cout << "Error al abrir archivo";
    }
    // clock_t end = clock();
    // double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    // cout<<"time: "<<elapsed_secs<<endl;

    // for (it=dic.begin(); it!=dic.end(); ++it)
    //     cout << it->first << " " << it->second << '\n';
    
    
    
// }

void PrintDic(map<string,map<string,int> > &dic){
    map<string,map<string,int> >::iterator it;
    for (it=dic.begin(); it!=dic.end(); ++it){
        cout << it->first << ": ";
        // map<string,int> tmp = it;
        map<string,int>::iterator it1;
        cout<<"("<<it->second.size()<<") ";
        for(it1 = it->second.begin();it1 != it->second.end(); it1++){
            cout << it1->first << " ";
        }
        cout<<endl;
    }
}


// int HelloFunc(){
//     int i;
//     int numthreads = 8;
// #pragma omp parallel for default(none) num_threads(numthreads) private(i)
//     for (i = 0; i < 100; i++)
//     {
//         int tid = omp_get_thread_num();
//         printf("Hello world from omp thread %d\n", tid);
//     }
//     return -1;
// }

int main () {
    fun_count_words("file1.txt");
    // HelloFunc();
    
}

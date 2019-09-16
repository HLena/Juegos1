#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <sstream>
// #include "Cloud_lab1.cpp"
#include <thread>

#include<mutex>


using namespace std;

// mutex mtx;

#define NTHREADS 10


map<string,map<string,int> > dic;
// void PrintDic();

// void ReadFiles(int num){
//     string infile = "";
//     // int file;
//     map<string,map<string,int> > dic;
//     clock_t begin = clock();
//     for (int file = 1; file <= num; file++){
//         stringstream out;
//         out << file;
//         infile = "file" + out.str()+".txt";
//         cout <<"==========="<<infile<<"==========="<<endl;
//         // fun_count_words(infile);
//         InvertedIndex(infile,dic);

//     }
//     clock_t end = clock();
//     double elapsed_secs = (double(end - begin) / CLOCKS_PER_SEC)/60;
//     cout<<"time: "<<elapsed_secs<<endl;
//     PrintDic();

// }

// void *thread_funtion(void *dum){

// }
void InvertedIndex(string filename){
// void InvertedIndex(string filename,map<string,map<string,int> > &dic){
    ifstream infile;
    infile.open(filename);

    // map<string,map<string,int> > dic;
    // map<string,int>::iterator it = dic.begin();
    string word;

    // clock_t begin = clock();
    // mtx.lock();
    if (infile.is_open()){
        //bool flag=true;
        #pragma omp parrallel for num_threads(16) default (none)\
        private (infile,word)
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
    }else {
        cout << "Error al abrir archivo"<<endl;
    }
    infile.close();
 
}

// void PrintDic(map<string,map<string,int> > &dic){
void PrintDic(){
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

void ReadFiles2(){
    string infile = "";
    // pthread_t thread_id[NTHREADS];
    map<string,map<string,int> > dic;
    thread *thread_id = new thread[NTHREADS];
    clock_t start= clock();
    // int i,j;
    for(int i = 0; i < NTHREADS; i++){
        stringstream out;
        out << i + 1;
        infile = "file" + out.str()+".txt";
        cout<<infile<<endl;
        // pthread_create(&thread_id[i], NULL, thread_funtion,NULL);
        thread_id[i] = thread(InvertedIndex,infile);
    }

    for(int i = 0; i < NTHREADS; i++){
        thread_id[i].join();
    }
    clock_t fin =clock();

    double time=(double(fin-start)/CLOCKS_PER_SEC);
    cout<<"time:"<<time<<endl;
    PrintDic();

}

int main(){
    // ReadFiles(5);
    ReadFiles2();
    // fun_count_words("example1.txt");
}
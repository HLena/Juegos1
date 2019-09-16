#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <sstream>
// #include "Cloud_lab1.cpp"
#include<mutex>
#include <thread>


using namespace std;


#define NTHREADS 10


mutex mtx;
map<string,map<string,int> > dic;

void InvertedIndex(string filename){
// void InvertedIndex(string filename,map<string,map<string,int> > &dic){
    ifstream infile;
    infile.open (filename);

    // map<string,map<string,int> > dic;
    // map<string,int>::iterator it = dic.begin();
    string word;

    // clock_t begin = clock();
    if (infile.is_open()){
        //bool flag=true;
        #pragma omp parrallel for default(none) num_threads(4) private(infile,word)
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
        cout << "Error al abrir archivo"<<endl;
    }
    
    
    
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

void ReadFiles(){
    string infile = "";
    // pthread_t thread_id[NTHREADS];
    map<string,map<string,int> > dic;
    thread *thread_id = new thread[NTHREADS];
    int i,j;
    clock_t start= clock();
    for(i=0; i < NTHREADS; i++){
        stringstream out;
        out << i + 1;
        infile = "file" + out.str()+".txt";
        cout<<infile<<endl;
        // pthread_create(&thread_id[i], NULL, thread_funtion,NULL);
        mtx.lock();
        thread_id[i] = thread(InvertedIndex,infile);
        mtx.unlock();
    }
    clock_t fin =clock();

    double time=(double(fin-start)/CLOCKS_PER_SEC);
    cout<<"time:"<<time<<endl;
    PrintDic();

}

int main(){
    // ReadFiles(5);
    ReadFiles();
    // fun_count_words("example1.txt");
}
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <thread>
#include <vector>
#include <algorithm>

#define MAX_THREADS 8
using namespace std;
//////
map<string,map<string,int>> mymap; /// string int
pair<map<string,map<string,int>>::iterator,bool> ret;

void indice_invertido(string filename){
    ifstream file;
    file.open (filename);
    string word;
    if (file.is_open()) {
        //bool flag=true;
        #pragma omp parrallel for num_threads(16) default (none)\
        private (file,word)
        for (;file>>word; ){
            ///ret=mymap.insert(pair<string,string>(word,filename));
            #pragma omp critical
            if(mymap.find(word)==mymap.end()){
                map<string,int> aux;
                aux.insert(make_pair(filename,1));
                mymap.insert(make_pair(word,aux));
            }else{
                if(mymap[word].find(filename)==mymap[word].end()){
                    mymap[word].insert(make_pair(filename,1));
                }
            }
        }
    }else {
        cout << "Error opening file";
    }
    file.close();
}



int main () {

    ofstream ofs;
    ofs.open ("outputfinalData.txt");
    ///CREACION DE LOS THREADS
    thread *threads = new thread[MAX_THREADS];

    clock_t start= clock();
    for (int i=0;i<MAX_THREADS;i++){
        string arc="file"+(to_string(i))+".txt";
        cout<<"************** "<<arc<<" ***************"<<endl;
        threads[i]=thread(indice_invertido,arc);
    }
    for (int i = 0; i < MAX_THREADS; i++){
        threads[i].join();
    }
    clock_t fin =clock();

    double time=(double(fin-start)/CLOCKS_PER_SEC);
    //cout << "mymap contains:\n";
    map<string,map<string,int>>::iterator it = mymap.begin();
    /*for (it=mymap.begin(); it!=mymap.end(); ++it)
        ofs << it->first << " => " << it->second << '\n';*/
    for (it =mymap.begin();it!=mymap.end();++it){
        ofs<<it->first<<" => ";
        map<string,int>::iterator it2;
        ofs<<"["<<it->second.size()<<"] ";
        for (it2=it->second.begin();it2!=it->second.end();++it2){
            ofs<<it2->first<<" ";
        }
        ofs<<endl;
    }
    ofs<<"TIEMPO: "<<time ;
    //ofs<<time;
    ofs.close();

/*
    map<string,vector<string>> mymap; /// strig int
    pair<map<string,vector<string>>::iterator,bool> ret;

    ret=mymap.insert(pair<string,vector<string>>("ab",vector<string>("hola")));
    ret=mymap.insert(pair<string,vector<string>>("ab",vector<string>("hola")));
    if (ret.second==false){
        ret.first->second=ret.first->second.push_back("chau");
    }
    cout << "mymap contains:\n";
    map<string,<vector<string>>::iterator it = mymap.begin();
    for (it=mymap.begin(); it!=mymap.end(); ++it)
        ofs << it->first << " => " << it->second << '\n';
*/
        /*
    vector<string> myvec={"uno", "dos","tres"};
    vector<string>::iterator it;
    it=find(myvec.begin(),myvec.end(),"uno");
    if (it != myvec.end())
        std::cout << "Element found in myvector: " << *it << '\n';
    else
        std::cout << "Element not found in myvector\n";*/
    return 0;
}

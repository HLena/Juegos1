#include <iostream>
#include <fstream>
#include <map>
#include <ctime>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <omp.h>

using namespace std;

void createDic(map<string,int> &m){
    cout<<"mapsize: "<<m.size()<<endl;

    for (map<string,int>::iterator it=m.begin(); it!=m.end(); ++it)
        cout << it->first << " " << it->second << '\n';
    //write in a file
    // ofstream outfile;
    // // outfile.open("output.txt");
    // for (map<string,int>::iterator it=m.begin(); it!=m.end(); ++it)
    //     outfile << it->first << " " << it->second << '\n';
    // outfile.close();

}

void countwords()
{   
    map<string,int> dic;
	ifstream infile;
    clock_t begin = clock();
	infile.open("input_text.txt");
	char word[30];

	while(!infile.eof())
	{
		infile>>word;
        if(dic.find(word) == dic.end())
            dic.insert (pair<string,int>(word,1) );
        else
            dic[word]++;
        // cout<<word<<endl;
	}

    // cout<<endl;
	infile.close();

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout<<"time: "<<elapsed_secs<<endl;
    createDic(dic);

}

// void mmap_funtion(void){
//     size_t pagesize = getpagesize();
//     printf("System page size: %zu bytes\n", pagesize);
 
//     char * region = mmap(
//     (void*) (pagesize * (1 << 20)),   // Map from the start of the 2^20th page
//     pagesize,                         // for one page length
//     PROT_READ|PROT_WRITE|PROT_EXEC,
//     MAP_ANON|MAP_PRIVATE,             // to a private block of hardware memory
//     ,
//     );

//     if (region == MAP_FAILED) {
//         perror("Could not mmap");
//         return 1;
//     }
 
//     strcpy(region, "Hello, poftut.com");
 
//     printf("Contents of region: %s\n", region);
 
//     int unmap_result = munmap(region, 1 << 10);
//     if (unmap_result != ) {
//         perror("Could not munmap");
//         return 1;
//     }
//     // getpagesize
//     return ;
// }


void fun_openMp(){
    ifstream infile;
    infile.open ("input_text.txt");

    // ofstream outfile;
    // outfile.open ("output.txt");

    map<string,int> dic;
    pair<map<string,int>::iterator,bool> ret;
    map<string,int>::iterator it = dic.begin();
    string word;

    //double wtime = omp_get_wtime();
    clock_t begin = clock();
    if (infile.is_open()) {
        //bool flag=true;
        #pragma omp parrallel for num_threads(16) default (none)\
        private (file,word)

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
    createDic(dic);
    // cout << "palabras:\n";
    // for (it=dic.begin(); it!=dic.end(); ++it)
    //     cout << it->first << " " << it->second << '\n';
    // outfile.close();
}



int main(){
    // countwords();
    fun_openMp();
}
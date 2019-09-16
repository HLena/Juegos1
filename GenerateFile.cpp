#include <iostream>
#include <fstream>
#include <omp.h>
#include <random>
#include <time.h>
#include <map>

using namespace std;

// void generator(fstream words){

// }
// void wordcount (fstream archivo){
//     map<string,int> mymap;

// }
int main(){
    srand(time(NULL));
    // vector<string> words1={"Peru", "computerScience","UNSA","cloudComputing","Arequipa",
    //                     // "2019","Amazonia","Adidas", "Creer","Nike",
    //                     // "ASUS", "Amazon","DataCentral","Microsoft","Linux",
    //                     "OpenSource","OpenMP","Apple","Azure","bytes",
    //                     "laptops","wifi"};

    // vector<string> words1={"Brasil", "Ciencia","Nvidia","NUBE","Cuzco",
    //                     "2019","Africa","Adidas", "Creer","Nike",
    //                     "ASUS", "Amazon","Datos","Microsoft","Linux",
    //                     "OpenSource","MPI","Windows","Azure","bits",
    //                     "WAN","wifi"};

    //  vector<string> words1={"Videojuegos", "BigData","UNSA","Network","Earth",
    //                     "2013","Firework","Puma", "Creer","Nike",
    //                     "ASUS", "Amazon","Datos","Claro","Linux",
    //                     // "OpenSource","MPI","Mause","Azure","bits",
    //                     "WLAN","Red"};
      
    //   vector<string> words1={"Moviles", "Seguridad","Etica","Network","Servidor",
    //                     "Drive","Firework","Android", "Creer","Nike",
    //                     // "hp", "Amazon","Datos","Claro","Linux",
    //                     "App","MPI","Mause","Azure","Megas",
    //                     "Bluetooh","Red"};
    
    fstream words;
    words.open("file10.txt",fstream::in| fstream::out| fstream::app);
    int i=30000000; // 2.5GB
    // #pragma omp parallel for 
    for (int j=0;j<i;j++){
        int var = rand () % words1.size() + 0;
        words<<words1[var]+" ";
    }
    words.close();
    return 0;
}

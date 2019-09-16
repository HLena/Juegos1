// #include <stdio.h>
// #include <mpi.h>

// int main (int argc, char **argv)
// {
//   int myrank = 0;
//   MPI_Comm comm = MPI_COMM_WORLD;

//   // Initialize MPI and get the process rank
//   MPI_Init(&argc, &argv);
//   MPI_Comm_rank(comm,&myrank);

//   // Build the filename for the given process
//   std::string filename = "input_" + myrank + ".txt";

//   // Open the file stream and read or write
//   std::ifstream in(filename.c_str());
//   read_file(in);
//   in.close();

//   // Finalize MPI and exit
//   MPI_Finalize();
//   return 0;
// }

// #include <iostream>
// #include <map>
// #include <omp.h>
// #include <stdio.h>
// #include <time.h>
// #include <sstream>

#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>


using namespace std;
const int NTHREADS = 10;

struct thread_args {
    string arg1;
};

void * Funtion(void * thread_nr){
    thread_args *args = (thread_args*)thread_nr;
    string res = args->arg1;
    printf("thread %d ans %s",rank,res.c_str());
    // return new int(res); // Return an `int` pointer to pass ba
    pthread_exit(NULL);         //exit from current thread
}


int main( int argc, char *argv[] )
{
    // MPI_Fint handleA, handleB;
    // int rc;
    // int errs = 0;
    // int rank,comm_size;
    // MPI_File cFile;
    // MPI_Init( &argc, &argv );
    // MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    // MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

    // string infile="";
    // clock_t start= clock();
    // int i;
    // for(i=0; i < NTHREADS; i++){
    //     stringstream out;
    //     out << i + 1;
    //     infile = "file" + out.str()+".txt";
    //     if(rank == i){
    //       rc = MPI_File_open( MPI_COMM_WORLD, infile.c_str(), MPI_MODE_WRONLY | MPI_MODE_DELETE_ON_CLOSE | MPI_MODE_CREATE, MPI_INFO_NULL, &cFile );

    //     }
    
    //     if(rc) {
    //       printf( "Unable to open file \"temp\"\n" );
    //       fflush(stdout);
    //     }
    //     else{
    //       // printf();
    //       MPI_File_close( &cFile );
    //     }
    // }
    // MPI_Finalize();
    // clock_t fin =clock();

    // double time=(double(fin-start)/CLOCKS_PER_SEC);
    // cout<<"time:"<<time<<endl;

    pthread_t thread[NTHREADS];
    int temp_arg[NTHREADS] ;

    /*creating all threads*/
    for(int current_t = 0; current_t < NTHREADS; current_t++){

      temp_arg[current_t] = current_t;
      stringstream out;
      out << current_t + 1;
      thread_args t1;
      t1.arg1 = "file" + out.str()+".txt";
      int result = pthread_create(&thread[current_t], NULL, Funtion, &t1)  ;
      if (result !=0){
        cout << "Error creating thread " << current_t << ". Return code:" << result <<  endl;
      }

  


  
}
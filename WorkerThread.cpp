#include <chrono>
#include <iostream>
#include "WorkerThread.h"
#include <fstream>

using namespace std;

//to access queue
extern SyncQueue Qobject;

WorkerThread :: WorkerThread(int WThCount):WorkThreadCount(WThCount){
}

WorkerThread :: ~WorkerThread(){
}

//This function creates three worker thread
void WorkerThread :: CreateThreeWorkerThread(){
   
   /* Create three threads */
   for(unsigned int i =0;i<WorkThreadCount;i++){
      t[i] = std::thread (&WorkerThread::FillMTable,this);
      t[i].detach();
     }
}

//This function adds words to MTable
void WorkerThread :: AddWordtoMTable(std:: string str){

    WorkThMutexobj.lock();
    map<string, int>::iterator it = MTable.find(str);
    if (it != MTable.end())
        it->second = it->second+1;
    else{
        MTable.insert(std::make_pair(str, 1));  
    } 
    WorkThMutexobj.unlock();
}

//This function reads the file and calls AddWordtoMTable() function
void  WorkerThread :: FillMTable(){
   while(1){
       string filename= Qobject.GetFilefrmQ();
       if(!filename.empty()){
           ifstream  file (filename.c_str());
           string line;
           
           if (file.is_open()){  
               while ( getline (file,line)){
                   std::size_t prev = 0, pos;
                   while ((pos = line.find_first_of("~`=!@#$%^&*)/\?-_|[,. }](_-+{;':""></", prev)) != std::string::npos){
                       if (pos > prev){
                           AddWordtoMTable(line.substr(prev, pos-prev));
                       }
                   prev = pos+1;
                   }
                   if (prev < line.length()){
                       AddWordtoMTable(line.substr(prev, std::string::npos));
                   }
               }

           file.close();
           }
           else{
               cout << "-Unable to open file-" << endl;
           }
       } 
   }
}

//This function returns the MTable
multimap<int,string,greater<int>> WorkerThread:: getTableEntry(){   
   multimap<int ,string,greater<int>> mmtbl;
   map<string,int>::iterator iter; 
         for(iter=MTable.begin(); iter!=MTable.end(); ++iter){
             mmtbl.insert(make_pair(iter->second,iter->first));
         }
  return mmtbl;
}
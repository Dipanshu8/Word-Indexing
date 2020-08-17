#include<SyncQueue.h>

SyncQueue :: SynQueue(){
    CountFileSize = 0;
}

SyncQueue :: ~SynQueue(){
}

//This function add filepath to synchornized queue
void SyncQueue :: AddFileNameinQ(string filepath){
    MutexObject.lock();
    Queue.push(filepath);
    CountFileSize++;
    MutexObject.unlock();
}

//This function read the filepath from synchronized queue
string SyncQueue :: GetFilefrmQ(){
    string filename="";
    MutexObject.lock();
    if(!Queue.empty()){
        filename = Queue.front();
        Queue.pop();
    }
    MutexObject.unlock();
return filename;
}

//This function returns the size of synchronized queue This check is required before fetching filepath from queue
int SyncQueue :: GetCount(){
    int CountSize = 0;
    CountSize=Queue.size();
return CountSize;
}

//This function returns the total number of file processed by synchornized queue

int SyncQueue :: GetFileCount(){
    return CountFileSize;
}

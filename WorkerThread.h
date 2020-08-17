#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H
#include "SyncQueue.h"
#include <map>
#include <thread>
#include <mutex>


class WorkerThread{
    public :
        WorkerThread(int WThCount);
        ~WorkerThread();
        
        //creates three thread//
        int CreateThreeWorkerThread(); 
        
        //filles MTable with words//
        void FillMTable();
        
        //return MTable//
        multimap<int,string,greater<int>> getTableEntry(); /* To get sorted table */

    private:        
        int AddWordtoMTable(string);
        map<string,int> MTable;
        mutex WorkThMutexobj;
        const int WorkThreadCount;
        thread t[3];
};
#endif

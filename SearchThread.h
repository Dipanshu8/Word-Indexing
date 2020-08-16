//This class is used to search .txt file in the specified directory and saves the results in synchronised queue.

#ifndef SEARCHTHREAD_H
#define SEARCHTHREAD_H

#include "SyncQueue.h"
#include <dirent.h>
#include <ftw.h>
#include <string>

class SearchThread{

	public: SearchThread(); 
		~SearchThread();
                /* This searches .txt file in the directory and saves the result in queue*/ 
		int StartSearchTxtFiles(string);
	        static int callback(const char *fpath, const struct stat *sb, int typeflag);
};
#endif  /*SEARCHTHREAD_H*/

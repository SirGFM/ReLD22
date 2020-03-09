#ifndef __SAVE_H
#define __SAVE_H

#include <cstdio>

#define EMPTY	-1
// Id Not Found
#define INF		-2
// File Not Opened
#define FNO		-3

#define ISWRITING 1
#define ISREADING 2
#define DIDWRITE 4
#define DIDREAD 8

namespace CppOGL {
	class Save {
		private:
			FILE *file;
			const char *filename;
			int state;
			int size;
		public:
			Save();
			~Save();
			
			void bind(const char *name);
			void flush(int force);
			void close();
			
			int write(const char *id, void *data, int size);
			int read(const char *id, void *data);
			int clear();
		private:
			int getIDPosition(const char *id);
			void readID(char **id);
			void getFileSize();
	};
}

#endif

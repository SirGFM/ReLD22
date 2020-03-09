#ifndef __AUDIOLL_H
#define __AUDIOLL_H

/**
 * Linked list for keeping reference of every playing audio.
 */
namespace CppOGL {
	class Audio;
	
	class AudioLL {
		public:
			static int num;
		private:
			static AudioLL *pushAll;
			static int nextID;
		public:
			int id;
			int pos;
			float volume;
			Audio *self;
			struct AudioLL *next;
		public:
			AudioLL(Audio *audio);
			~AudioLL();
			void reuse(Audio *audio);
			void clear();
			void push(AudioLL *all);
		private:
			void pvpush();
	};
}

#endif

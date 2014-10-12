#ifndef _ALBUM
#define _ALBUM
#include <vector>
#include "song.h"
using namespace std;

class Album {
public:
  Album();
  void import(Song*);
  Song* get_song(unsigned int);
  int get_antal();
  int get_year(); 
  int get_disc_number();
  string get_genre();
  string get_artist();
  string get_album();
  vector<Song *> get_songs();
private:
  vector <Song*> songs;
  int year;
  int disc_number;
  string genre;
  string artist;
  string album;
};
#endif

#ifndef _SONG
#define _SONG
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <utility>
using namespace std;
class Song {
public:
  Song();
  void setvalue(char* value);
  void setvalue(string &key, string &val);
  string get_name();
  string get_artist();
  string get_album();
  string get_genre();
  int get_total_time();
  int get_track_number();
  int get_year();
  string get_date_added();
  int get_disc_number();

private:
  string name;
  string artist;
  string album;  
  string genre;
  int total_time;  
  int track_number;
  int year;
  string date_added;
  int disc_number;
};
#endif

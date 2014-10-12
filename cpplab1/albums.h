#ifndef _ALBUMS
#define _ALBUMS
#include <vector>
#include "album.h"
using namespace std;

class Albums {
public:
  Albums();
  void import(Song*);
  vector <Album*> get_list();
  vector <Album*> albums;
private:
  int last_disc_number;
  int index;  
  string last_album;
};
#endif

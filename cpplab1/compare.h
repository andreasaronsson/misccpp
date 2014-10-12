#ifndef _COMPARE
#define _COMPARE
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <utility>
#include "albums.h"

class CmpName {
  public:
	  bool operator() (Song*, Song*) const;
};
class CmpArtist {
  public:
	  bool operator() (Song*, Song*) const;
	  bool operator() (Album*, Album*) const;
};
class CmpAlbum {
  public:
	  bool operator() (Song*, Song*) const;
	  bool operator() (Album*, Album*) const;
};
class CmpGenre {
  public:
	  bool operator() (Song*, Song*) const;
	  bool operator() (Album*, Album*) const;
};
class CmpTrackNumber {
  public:
	  bool operator() (Song*, Song*) const;
};
class CmpYear {
  public:
	  bool operator() (Song*, Song*) const;
	  bool operator() (Album*, Album*) const;
};
class CmpDiscNumber {
  public:
	  bool operator() (Song*, Song*) const;
};

#endif

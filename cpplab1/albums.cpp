#include "albums.h"
#include <vector>
using namespace std;
Albums::Albums()
{
  this->last_album = "";
  this->last_disc_number = 0;
  this->index = -1;

}
void Albums::import(Song* song)
{
  
  if (this->last_album == song->get_album() && (this->last_disc_number == song->get_disc_number() || song->get_disc_number()>1))
    {
      this->albums.at(index)->import(song);
    }
  else
    {
      Album *temp_album;
      temp_album = new Album;
      temp_album->import(song);
      this->albums.push_back(temp_album);
      this->index++;
      this->last_album = song->get_album();
      this->last_disc_number = song->get_disc_number();
      temp_album = new Album;
    }
}
vector <Album*> Albums::get_list()
{
  return this->albums;
}

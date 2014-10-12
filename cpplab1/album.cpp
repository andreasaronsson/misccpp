#include "album.h"
using namespace std;
Album::Album()
{
  this->year=this->disc_number=0;
}
void Album::import(Song* song)
{
  this->songs.push_back(song);
  if(this->songs.size()==1)
    {
      this->year = song->get_year();
      this->genre = song->get_genre();
      this->artist = song->get_artist();
      this->album = song->get_album();
      this->disc_number = song->get_disc_number();
    }
  else
  {
    if (this->year == 0)
      this->year = song->get_year();  
    if (this->genre == "")
      this->genre = song->get_genre();
    if(this->artist != song->get_artist())
      this->artist = "Various Artists";
  }
}
Song* Album::get_song(unsigned int index)
{
  if (index < this->songs.size())
    return this->songs[index];
  return NULL;
}
string Album::get_album()
{
  return this->album;
}
int Album::get_year()
{
  return this->year;
}
string Album::get_genre()
{
  return this->genre;
}
string Album::get_artist()
{
  return this->artist;
}
int Album::get_antal()
{
  return this->songs.size();
}
int Album::get_disc_number()
{
  return this->disc_number;
}
vector<Song *> Album::get_songs()
{
  return this->songs;
}

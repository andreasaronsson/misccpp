#include "song.h"
Song::Song()
{
  this->total_time = this-> track_number = this->year = 0;
  this->disc_number = 1;

}

void Song::setvalue(string &key, string &val) {
  if ( key == "Name" ) name = val;
  else if ( key == "Artist" ) artist = val;
  else if ( key == "Album" ) album = val;
  else if ( key == "Genre" ) genre = val;
  else if ( key == "Total Time" ) total_time = atoi((char *)val.c_str());
  else if ( key == "Track Number" ) track_number = atoi((char *)val.c_str());
  else if ( key == "Year" ) year = atoi(( char *)val.c_str());
  else if ( key == "Date Added" ) date_added = val;
  else if ( key == "Disc Number" ) disc_number = atoi(( char *)val.c_str());
}

string Song::get_name()
{
  return name;
}
string Song::get_artist()
{
  return this->artist;
}
string Song::get_album()
{
  return this->album;
}
string Song::get_genre()
{
  return this->genre;
}
int Song::get_total_time()
{
  return this->total_time;
}
int Song::get_track_number()
{
  return this->track_number;
}
int Song::get_year()
{
  return this->year;
}
string Song::get_date_added()
{
  return this->date_added;
}
int Song::get_disc_number()
{
  return this->disc_number;
}


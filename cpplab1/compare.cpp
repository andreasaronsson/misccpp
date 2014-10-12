# include "compare.h"

using namespace std;

// Compare Trackname
bool CmpName::operator() (Song *s1, Song *s2) const {
  return s1->get_name() < s2->get_name();
}

// Compare name of artist
bool CmpArtist::operator() (Song *s1, Song *s2) const {
  return s1->get_artist() < s2->get_artist();
}
bool CmpArtist::operator() (Album *a1, Album *a2) const {
  return a1->get_artist() < a2->get_artist();
}

// Compare name of Album
bool CmpAlbum::operator() (Song *s1, Song *s2) const {
  return s1->get_album() < s2->get_album();
}
bool CmpAlbum::operator() (Album *a1, Album *a2) const {
  return a1->get_album() < a2->get_album();
}

// Compare the Genre
bool CmpGenre::operator() (Song *s1, Song *s2) const {
  return s1->get_genre() < s2->get_genre();
}
bool CmpGenre::operator() (Album *a1, Album *a2) const {
  return a1->get_genre() < a2->get_genre();
}

// Compare Track number
bool CmpTrackNumber::operator() (Song *s1, Song *s2) const {
  return s1->get_track_number() < s2->get_track_number();
}

// Compare Year of recording
bool CmpYear::operator() (Song *s1, Song *s2) const {
  return s1->get_year() < s2->get_year();
}
bool CmpYear::operator() (Album *a1, Album *a2) const {
  return a1->get_year() < a2->get_year();
}

// Compare Disc number
bool CmpDiscNumber::operator() (Song *s1, Song *s2) const {
  return s1->get_disc_number() < s2->get_disc_number() ;
}

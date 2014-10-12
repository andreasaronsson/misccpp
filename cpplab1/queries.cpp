#include "queries.h"
#include "compare.h"
#include <sstream>
#include <iomanip>

/* Vilka album gavs ut �r X? */
void query1(vector<Song *>& songs, int key_y) {
  CmpYear yearcmp;
  CmpArtist artistcmp;
  CmpAlbum albumcmp;
  pair<vector<Song *>::iterator, vector<Song *>::iterator> p;
  Song *key;
  string key_s = "Year";
  string key_ys;
  stringstream ss;
  ss << key_y;
  ss >> key_ys;
  key->setvalue(key_s,key_ys);
  sort(songs.begin(),songs.end(),yearcmp);
  p = equal_range(songs.begin(),songs.end(),key,yearcmp);
  if (p.first == p.second) {
    cout << "Det finns inget album som sl�pptes " << key_y << "." << endl;
  }
  else {
    stable_sort(p.first,p.second,albumcmp);
    stable_sort(p.first,p.second,artistcmp);
    cout << "Album som sl�pptes " << key_y << endl;
    for (vector<Song *>::iterator i = p.first; i != p.second; i++) {
      cout << (*i)->get_artist() << " - ";
      cout << (*i)->get_album() << endl;
    }
  }
  getchar();
}

/* Vilka album gavs ut �r X? (album*-vector) */
void query1(vector<Album *>& albums, int key_y) {
  CmpYear yearcmp;
  CmpArtist artistcmp;
  CmpAlbum albumcmp;
  pair<vector<Album *>::iterator, vector<Album *>::iterator> p;
  Album *key;
  Song *keys;
  string key_s = "Year";
  string key_ys;
  stringstream ss;
  keys = new Song;
  key = new Album;
  ss << key_y;
  ss >> key_ys;
  keys->setvalue(key_s,key_ys);
  key->import(keys);
  sort(albums.begin(),albums.end(),yearcmp);
  p = equal_range(albums.begin(), albums.end(), key, yearcmp);
  if (p.first == p.second) {
    cout << "Det finns inget album som sl�pptes " << key_y << "." << endl;
  }
  else {
    stable_sort(p.first,p.second,albumcmp);
    stable_sort(p.first,p.second,artistcmp);
    cout << "Album som sl�pptes " << key_y << ":" << endl;
    cout << "========================" << endl;
    for (vector<Album *>::iterator i = p.first; i != p.second; i++) {
      cout << (*i)->get_artist() << " - ";
      cout << (*i)->get_album() << endl;
    }
  }
  cout << "===========================================" << endl;
  cout << "Tryck enter f�r att g� tillbaka till menyn." << endl;
  getchar();
}

/* P� vilka album finns l�t X? */
void query2(vector<Song *>& songs, string& key_n) {
  CmpName namecmp;
  CmpAlbum albumcmp;
  CmpArtist artistcmp;
  CmpYear yearcmp;
  Song *key;
  key = new Song;
  string key_s = "Name";
  key->setvalue(key_s,key_n);
  pair<vector<Song *>::iterator, vector<Song *>::iterator> p;
  sort(songs.begin(),songs.end(),namecmp);
  p = equal_range(songs.begin(),songs.end(),key,namecmp);
  if (p.first == p.second) {
    cout << "Det finns ingen l�t som heter s�." << endl;
  }
  else {
    stable_sort(p.first,p.second,albumcmp);
    stable_sort(p.first,p.second,artistcmp);
    stable_sort(p.first,p.second,yearcmp);
    cout << key_n << " finns med p� f�ljande album:" << endl;
    cout << "==================================================" << endl;
    for (vector<Song *>::iterator i = p.first; i != p.second; i++) {
      cout << (*i)->get_year() << " - ";
      cout << (*i)->get_artist() << " - ";
      cout << (*i)->get_album() << endl;
    }
  }
  cout << "===========================================" << endl;
  cout << "Tryck enter f�r att g� tillbaka till menyn." << endl;
  getchar();

}

/*  Vilka album finns i genre X? */
void query3(vector<Album *>& albums, string& key_g) {
  CmpGenre genrecmp;
  CmpYear yearcmp;
  CmpAlbum albumcmp;
  Album *key;
  Song *keys;
  key = new Album;
  keys = new Song;
  string key_s = "Genre";
  keys->setvalue(key_s,key_g);
  key->import(keys);
  pair<vector<Album *>::iterator, vector<Album *>::iterator> p;
  sort(albums.begin(), albums.end(), genrecmp);
  p = equal_range(albums.begin(), albums.end(), key, genrecmp);
  if (p.first == p.second) {
    cout << key_g << " �r nog inte en genre Lennart lyssnar p� s� ofta."<<endl;
  }
  else {
    stable_sort(p.first, p.second, albumcmp);
    stable_sort(p.first, p.second, yearcmp);
    cout << "F�ljande album finns inom genren " << key_g << endl;
    cout << "==================================================" << endl;
    for (vector<Album *>::iterator i = p.first; i != p.second; i++) {
      cout << (*i)->get_year() << " - ";
      cout << (*i)->get_album();
      cout << " (" << (*i)->get_artist() << ")" << endl;
    }
  }
  cout << "===========================================" << endl;
  cout << "Tryck enter f�r att g� tillbaka till menyn." << endl;
  getchar();

}

/* Vilka album har artist X gjort f�re �r Y? */
void query4(vector<Album *>& albums, string& key_a, int key_y) {
  CmpArtist artistcmp;
  CmpYear yearcmp;
  CmpAlbum albumcmp;
  Album *key;
  key = new Album;
  Song *keys;
  keys = new Song;
  string key_s = "Artist";
  keys->setvalue(key_s, key_a);
  key_s = "Year";
  string key_ys;
  stringstream ss;
  ss << (key_y -1);
  ss >> key_ys;
  keys->setvalue(key_s, key_ys);
  key->import(keys);
  pair<vector<Album *>::iterator, vector<Album *>::iterator> p;
  sort(albums.begin(), albums.end(), artistcmp);
  p = equal_range(albums.begin(), albums.end(), key, artistcmp);
  if (p.first == p.second) {
    cout << "Ingen tr�ff d�r inte." << endl;
  }
  else {
    stable_sort(p.first, p.second, albumcmp);
    stable_sort(p.first, p.second, yearcmp);
    vector<Album *>::iterator end = upper_bound(p.first, p.second, key, yearcmp);
    if (p.first == end) {
      cout << "Ingen tr�ff d�r inte." << endl;
    }
    else {
    cout << "Dessa album har getts ut av " << key_a << " innan " << key_y << endl;
    cout << "==================================================" << endl;
      for (vector<Album *>::iterator i = p.first; i != end; i++) {
	cout << (*i)->get_year() << " - ";
	cout << (*i)->get_album() << endl;
      }
    }
  }
  cout << "===========================================" << endl;
  cout << "Tryck enter f�r att g� tillbaka till menyn." << endl;
  getchar();

}

/* Vilka album har artist XYZ gjort? */
void query5(vector<Album *>& albums, string& key_a) {
  CmpArtist artistcmp;
  CmpAlbum albumcmp;
  CmpTrackNumber tncmp;
  CmpDiscNumber dncmp;
  Album *key;
  Song *keys;
  key = new Album;
  keys = new Song;
  string key_s = "Artist";
  keys->setvalue(key_s, key_a);
  key->import(keys);
  pair<vector<Album *>::iterator, vector<Album *>::iterator> p;
  sort(albums.begin(), albums.end(), artistcmp);
  p = equal_range(albums.begin(), albums.end(), key, artistcmp);
  if (p.first == p.second) {
  cout << "Ingen tr�ff d�r inte." << endl;
  }
  else {
    vector<Song *> songs;
    stable_sort(p.first, p.second, albumcmp);
    cout << "Album som getts ut av " << key_a << endl;
    cout << "==================================================" << endl;
    for (vector<Album *>::iterator i = p.first; i != p.second; i++) {
      cout << (*i)->get_year() << " - ";
      cout << (*i)->get_album() << endl;
      songs = (*i)->get_songs();
      sort(songs.begin(), songs.end(), tncmp);
      stable_sort(songs.begin(), songs.end(), dncmp);
      for (vector<Song *>::iterator si = songs.begin();si != songs.end();si++) {
	cout << "\t" <<setw(2)<<(*si)->get_track_number();
	cout << ". ["<<setw(2)<<(*si)->get_total_time()/60000;
	cout << ":" << setw(2)<<setfill('0')<<((*si)->get_total_time()/1000)%60;
	cout << "] " << (*si)->get_name() <<setfill(' ')<< endl;
      }
      getchar();
    }
  }
  cout << "===========================================" << endl;
  cout << "Tryck enter f�r att g� tillbaka till menyn." << endl;
  getchar();
}

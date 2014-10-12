#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <string>
#include "albums.h"
#include "compare.h"
#include "queries.h"

using namespace std;

int menu(vector<Song*>&, vector<Album*>&); // hanterar menyvalen 
void print_menu(void); // rensar terminal samt  printar ledtexter. 


int main(void) {
  setlocale(LC_ALL,"sv_SE");
  string raw, bit, d="<dict>", k="<key>", dq="</dict>", kq="</key>";
  int ndict=0;
  Albums albums;
  Song *song;
  vector<string> v;
  vector<Song*> s;
  vector<Album*> al;

  ifstream inFile("iTunes.xml", ios::in);

  while( getline(inFile, raw) ) {

    if(string::npos != raw.find(d)) {
      ++ndict;
    }
    song = new Song;
    while ( ndict==3 ) {
      getline(inFile, raw);
      if ( string::npos != raw.find(k) ) {
        size_t current = 0 , next = 0;
        while ( current != string::npos ) {
	  next = raw.find( '>', current );
	  current = raw.find( '<', next );
	  if ( 0 != current-next-1  && current != string::npos ) 
	    v.push_back( string( raw , next+1 , current-next-1 ) );
	  current = (next == string::npos) ? string::npos : next + 1 ;
	}
	song->setvalue(v.front(),v.back());
	v.clear();
      }

      if ( string::npos != raw.find(dq) ) {
	getline(inFile, raw);
	ndict--;
	s.push_back(song);
	albums.import(song);
      }
    }

    if ( string::npos != raw.find(dq) ) {
      ndict--;
    }
  }

  inFile.close();

  // här startar vi menyn
  al = albums.get_list();
  while(  menu(s,al) );
  return 0;  
}


int menu(vector<Song*>& song , vector<Album*>& album){
  
  bool exit = 1;
  int selected, artal;
  
  stringstream ss; 
  // denna används för att interfacet inte skall balla ur om icke numeriska 
  // tecken matas in på årtal.Tillsammans med int_txt och artal.

  string search_key1, int_txt; 

  print_menu();
  cin >> selected;
  system("clear");
  switch(selected) {
  case 1:
    cout << setw(18) << "Ange årtal: ";
    cin >> ws;  
    getline(cin, int_txt);
    ss << int_txt;
    ss >> artal;
    query1(album, artal);
    break;
  case 2 :
    cout << "Ange låtnamn: "<< flush;
    cin >> ws; 
    getline(cin,search_key1);
    query2(song, search_key1);
    break;
  case 3:
    cout << "Ange genre: ";
    cin >> ws; 
    getline(cin,search_key1);
    query3(album, search_key1);
    break;
  case 4:
    cout << "Ange artist: ";
    cin >> ws;
    getline(cin, search_key1);
    cout << "Ange årtal: ";
    cin >> ws;
    getline(cin, int_txt);
    ss << int_txt;
    ss >> artal;
    query4(album, search_key1, artal);
    break;
  case 5:
    cout << "Ange artist: ";
    cin >> ws;
    getline(cin, search_key1);
    query5(album, search_key1);
    break;
  case 6:
    exit = 0;
    break;
  }
  return exit;
}


void print_menu(){
  system("clear");
  cout << setw(20) << "" << "VÄLKOMMEN TILL LAB 1 (jaff)" << endl << endl
       << setw(10) << "1" << "    " << "Vilka album gavs ut år X ?" << endl 
       << setw(10) << "2" << "    " << "På vilka album finns låt X ?" << endl
       << setw(10) << "3" << "    " << "Vilka album finns i genre X ?" << endl
       << setw(10) << "4" << "    " << "Vilka album har artist X gjort före år Y ?" << endl
       << setw(10) << "5" << "    " << "Vilka album har artist  XYZ gjort ?" << endl
       << setw(10) << "6" << "    " << "Avsluta program" << endl << endl
       << setw(18) << "Sökning: ";
  
}

#include "prefs.h"
Prefs::Prefs()
{

  setlocale(LC_ALL,"sv_SE");
  vector<string> v;  
  string filename, raw, nextraw, bit, d="<dict>", k="<key>", dq="</dict>", kq="</key>", sq= "</string";
 
  ifstream inFile(".stalin", ios::in);

  while( getline(inFile, raw) ) {
    
    //cout << raw << endl;
    if ( string::npos != raw.find(k) ) {
      size_t current = 0 , next = 0;

      while ( current != string::npos ) {
	next = raw.find( '>', current );
	current = raw.find( '<', next );
	if ( 0 != current-next-1  && current != string::npos ) 
	  v.push_back( string( raw , next+1 , current-next-1 ) );
	current = (next == string::npos) ? string::npos : next + 1 ;
      }
      if (v.size() == 2)
	if (v.front() == "name") this->name = v.back();      
	else if (v.front() == "address") this->address = v.back();
	else if (v.front() == "pop") this->pop = v.back();
	else if (v.front() == "popUser") this->popUser = v.back();
	else if (v.front() == "popPass") this->popPass = v.back();
	else if (v.front() == "smtp") this->smtp = v.back();
	else if (v.front() == "smtpUser") this->smtpUser = v.back();
	else if (v.front() == "smtpPass") this->smtpPass = v.back();
	else if (v.front() == "signature") this->signature = v.back();
      v.clear();
    }

  }

  inFile.close();

}

string Prefs::get_name()
{
  return this->name;
}
string Prefs::get_address()
{
  return this->address;
}
string Prefs::get_pop()
{
  return this->pop;
}
string Prefs::get_popUser()
{
  return this->popUser;
}
string Prefs::get_popPass()
{
  return this->popPass;
}
string Prefs::get_smtp()
{
  return this->smtp;
}

string Prefs::get_smtpUser()
{
  return this->smtpUser;
}

string Prefs::get_smtpPass()
{
  return this->smtpPass;
}

string Prefs::get_signature()
{
  return this->signature;
}


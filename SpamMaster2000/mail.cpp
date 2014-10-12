#include "mail.h"
Mail::Mail()
{
}

void Mail::setvalue(string &key, string &val)
{

  if ( key == "From" )
     this->from = this->unmime(val);
  else if( key == "Date" ) this->date = this->unmime(val);
  else if (key == "Subject" ) this->subject = this->unmime(val);
  else if (key == "To" ) this->to = this->unmime(val);
  else if (key == "Body" ) this->body = this->unmime(val);
  else if (key == "Headers" ) this->headers = this->unmime(val);
}

string Mail::get_from()
{
  return this->from;
}
string Mail::get_date()
{
  return this->date;
}
string Mail::get_subject()
{
  return this->subject;
}
string Mail::get_to()
{
  return this->to;
}
string Mail::get_body()
{
  return this->body;
}
string Mail::get_headers()
{
  return this->headers;
}

void Mail::mailsave(string filename)
{
 
  setlocale(LC_ALL,"sv_SE");
  string wbuffer;
 

  ofstream outFile(filename.c_str(), ios::trunc);
  wbuffer += "Date: " + this->date;
  wbuffer += "\nSubject: " + this->subject;
  wbuffer += "\nFrom: " + this->from;
  wbuffer += "\nTo: " +this->to;
  wbuffer += "\n\n" + this->body;
  outFile.write(wbuffer.c_str(), wbuffer.size());
  

  outFile.close();

}

string Mail::unmime(string intext)
{  
  size_t found;
  size_t last_found = 0;
  string mimes;
  while ( (found = intext.find("=", last_found)) != string::npos ) {
    mimes = intext.substr(found,3);
    if ( mimes == "=3C" ) intext.replace(found, 3, 1, '\x3c');
    else if ( mimes == "=3E" ) intext.replace(found, 3, 1, '\x3E');
    else if ( mimes == "=0A" ) intext.replace(found, 3, 1, '\x0A');
    last_found = found + 1 ;
  }
  return intext;
}


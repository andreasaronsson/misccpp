#include "mail.h"
Mail::Mail()
{
}

void Mail::setvalue(string &key, string &val)
{
  if ( key == "From" ) this->from = val;
  else if( key == "Date" ) this->date = val;
  else if (key == "Subject" ) this->subject = val;
  else if (key == "To" ) this->to = val;
  else if (key == "Body" ) this->body = val;
  else if (key == "Headers" ) this->headers = val;
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


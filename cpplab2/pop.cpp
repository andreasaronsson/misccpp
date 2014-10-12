#include "pop.h"
#include "mail.h"
#include <vector>

Pop::Pop() {
}

Pop::Pop(string h, string u, string p) {
  this->host = h;
  this->user = u;
  this->pass = p;
}

void Pop::setvalue(string key, string val) {
  if ( key == "Host" ) this->host = val;
  else if ( key == "User" ) this->user = val;
  else if ( key == "Pass" ) this->pass = val;
}

string Pop::get_host() {
  return this->host;
}
string Pop::get_user() {
  return this->user;
}
string Pop::get_pass() {
  return this->pass;
}

int Pop::pop( Mailbox &inbox ) {
  char ans[999];
  string buff;
  Mail *new_mail;
  
  InetHostAddress server( host.c_str() );
  if ( ! server.isInetAddress() ) {
    cout << "No such hostname" << endl;
    return -1;
  }
  TCPStream tcp_pop(server, 110);
  if ( tcp_pop == NULL ) {
    cout << "Could not connect to server.";
    return -2;
  }
  
  // Connection established
  tcp_pop.getline(ans,998);
  buff = ans;
  if ( buff.substr(0,1) == "-" ) {
    cout << buff << endl;
    return -3;
  }

  // Try to log in
  tcp_pop << "USER " << this->user << endl;
  tcp_pop.getline(ans,998);
  buff = ans;
  if ( buff.substr(0,1) == "-" ) {
    cout << "SVAR USER: " << buff << endl;
    return -4;
  }
  tcp_pop << "PASS " << this->pass << endl;
  tcp_pop.getline(ans,998);
  buff = ans;
  if ( buff.substr(0,1) == "-" ) {
    cout << "SVAR PASS: " << buff << endl;
    return -5;
  }
  
  // Now we are logged in.
  tcp_pop << "LIST" << endl;
  tcp_pop.getline(ans,998);
  buff = ans;
  if ( buff.substr(0,1) == "-" ) {
    cout << "SVAR LIST: " << buff << endl;
    return -6;
  }
  
  // Store indexes of mails on server
  tcp_pop.getline(ans,998);
  buff = ans;
  int num_mails = 0;
  int mail_id;
  vector<int> new_mails;
  new_mails.reserve(64);
  while ( buff != ".\r" ) {
    // Fetch messageID if mails in inbox
    stringstream list;
    list << buff;
    list >> mail_id;
    new_mails.push_back(mail_id);
    num_mails++;
    tcp_pop.getline(ans,998);
    buff = ans;
  }
  for (int i = 0; i < num_mails; i++ ) {
    string head, to, from, subject, date, body, temp, attr, data;
    tcp_pop << "RETR " << new_mails.at(i) << "\r" << endl;
    tcp_pop.getline(ans,998);
    buff = ans;
    if ( buff.substr(0,3) == "+OK" ) {
      new_mail = new Mail();
      tcp_pop.getline(ans,998);
      buff = ans;
      while ( buff != "\r" ) {
	// Message header
	buff.erase( buff.end() - 1 );
	temp = buff;
	tcp_pop.getline(ans,998);
	buff = ans;
	while ( buff.substr(0,1) == " " || buff.substr(0,1) == "\t" ) {
	  // Folding header, this line belongs with the one above
	  buff.erase( buff.end() - 1 );
	  temp = temp + "\n" + buff;
	  tcp_pop.getline(ans,998);
	  buff = ans;
	}
	// Now we check to see which header-item should be set.
	attr = temp.substr( 0, temp.find_first_of(":") );
	if ( attr == "To" ||
	     attr == "From" ||
	     attr == "Date" ||
	     attr == "Subject" ) {
	  // The headers we are interested in
	  data = temp.substr( temp.find_first_of(":") + 2);
	  new_mail->setvalue( attr, data );
	}
	else {
	  // The not-so-interesting headers.
	  head = head + "\n" + temp;
	}
      }
      head.erase( head.begin() );
      attr = "Headers";
      new_mail->setvalue(attr, head);
      tcp_pop.getline(ans,998);
      //head.erase(head.end()-1);
      buff = ans;
      while ( buff != ".\r" ) {
	// Message body
	if ( buff.substr(0,1) == "." ) {
	  // Lines beginning with a "." has an extra dot while in transfer...
	  buff.erase( buff.begin() );
	}
	buff.erase(buff.end()-1);
	body = body + buff + "\n";
	tcp_pop.getline(ans,998);
	buff = ans;
      }
      body.erase(body.end()-1);
      
      if ( head.find("QUOTED-PRINTABLE") != string::npos ||
	   head.find("quoted-printable") != string::npos ) unmime( body );
            
      attr = "Body";
      new_mail->setvalue( attr, body );
      inbox.import( new_mail );
      
      /*
      tcp_pop << "DELE " << new_mails.at(i) << "\r" << endl;
      tcp_pop.getline(ans,999);
      buff = ans;
      */
    }
  }
  tcp_pop << "QUIT\r" << endl;
  return num_mails;
}

void Pop::unmime( string &body ) {
  size_t found;
  size_t last_found = 0;
  string mimes;
  while ( (found = body.find("=", last_found)) != string::npos ) {
    mimes = body.substr(found,3);
    if ( mimes.substr(0,2) == "=\n" ) {
      // This is where the client inserted a CRLF we do not want.
      body.erase(found,2);
      found--;
    }
    else if ( mimes == "=00" ) body.replace(found, 3, 1, '\x00');
    else if ( mimes == "=01" ) body.replace(found, 3, 1, '\x01');
    else if ( mimes == "=02" ) body.replace(found, 3, 1, '\x02');
    else if ( mimes == "=03" ) body.replace(found, 3, 1, '\x03');
    else if ( mimes == "=04" ) body.replace(found, 3, 1, '\x04');
    else if ( mimes == "=05" ) body.replace(found, 3, 1, '\x05');
    else if ( mimes == "=06" ) body.replace(found, 3, 1, '\x06');
    else if ( mimes == "=07" ) body.replace(found, 3, 1, '\x07');
    else if ( mimes == "=08" ) body.replace(found, 3, 1, '\x08');
    else if ( mimes == "=09" ) body.replace(found, 3, 1, '\x09');
    else if ( mimes == "=0A" ) body.replace(found, 3, 1, '\x0A');
    else if ( mimes == "=0B" ) body.replace(found, 3, 1, '\x0B');
    else if ( mimes == "=0C" ) body.replace(found, 3, 1, '\x0C');
    else if ( mimes == "=0D" ) body.replace(found, 3, 1, '\x0D');
    else if ( mimes == "=0E" ) body.replace(found, 3, 1, '\x0E');
    else if ( mimes == "=0F" ) body.replace(found, 3, 1, '\x0F');
    else if ( mimes == "=10" ) body.replace(found, 3, 1, '\x10');
    else if ( mimes == "=11" ) body.replace(found, 3, 1, '\x11');
    else if ( mimes == "=12" ) body.replace(found, 3, 1, '\x12');
    else if ( mimes == "=13" ) body.replace(found, 3, 1, '\x13');
    else if ( mimes == "=14" ) body.replace(found, 3, 1, '\x14');
    else if ( mimes == "=15" ) body.replace(found, 3, 1, '\x15');
    else if ( mimes == "=16" ) body.replace(found, 3, 1, '\x16');
    else if ( mimes == "=17" ) body.replace(found, 3, 1, '\x17');
    else if ( mimes == "=18" ) body.replace(found, 3, 1, '\x18');
    else if ( mimes == "=19" ) body.replace(found, 3, 1, '\x19');
    else if ( mimes == "=1A" ) body.replace(found, 3, 1, '\x1A');
    else if ( mimes == "=1B" ) body.replace(found, 3, 1, '\x1B');
    else if ( mimes == "=1C" ) body.replace(found, 3, 1, '\x1C');
    else if ( mimes == "=1D" ) body.replace(found, 3, 1, '\x1D');
    else if ( mimes == "=1E" ) body.replace(found, 3, 1, '\x1E');
    else if ( mimes == "=1F" ) body.replace(found, 3, 1, '\x1F');
    else if ( mimes == "=20" ) body.replace(found, 3, 1, '\x20');
    else if ( mimes == "=3D" ) body.replace(found, 3, 1, '\x3D');
    else if ( mimes == "=AO" ) body.replace(found, 3, 1, '\xA0');
    else if ( mimes == "=A1" ) body.replace(found, 3, 1, '\xA1');
    else if ( mimes == "=A2" ) body.replace(found, 3, 1, '\xA2');
    else if ( mimes == "=A3" ) body.replace(found, 3, 1, '\xA3');
    else if ( mimes == "=A4" ) body.replace(found, 3, 1, '\xA4');
    else if ( mimes == "=A5" ) body.replace(found, 3, 1, '\xA5');
    else if ( mimes == "=A6" ) body.replace(found, 3, 1, '\xA6');
    else if ( mimes == "=A7" ) body.replace(found, 3, 1, '\xA7');
    else if ( mimes == "=A8" ) body.replace(found, 3, 1, '\xA8');
    else if ( mimes == "=A9" ) body.replace(found, 3, 1, '\xA9');
    else if ( mimes == "=AA" ) body.replace(found, 3, 1, '\xAA');
    else if ( mimes == "=AB" ) body.replace(found, 3, 1, '\xAB');
    else if ( mimes == "=AC" ) body.replace(found, 3, 1, '\xAC');
    else if ( mimes == "=AD" ) body.replace(found, 3, 1, '\xAD');
    else if ( mimes == "=AE" ) body.replace(found, 3, 1, '\xAE');
    else if ( mimes == "=AF" ) body.replace(found, 3, 1, '\xAF');
    else if ( mimes == "=B0" ) body.replace(found, 3, 1, '\xB0');
    else if ( mimes == "=B1" ) body.replace(found, 3, 1, '\xB1');
    else if ( mimes == "=B2" ) body.replace(found, 3, 1, '\xB2');
    else if ( mimes == "=B3" ) body.replace(found, 3, 1, '\xB3');
    else if ( mimes == "=B4" ) body.replace(found, 3, 1, '\xB4');
    else if ( mimes == "=B5" ) body.replace(found, 3, 1, '\xB5');
    else if ( mimes == "=B6" ) body.replace(found, 3, 1, '\xB6');
    else if ( mimes == "=B7" ) body.replace(found, 3, 1, '\xB7');
    else if ( mimes == "=B8" ) body.replace(found, 3, 1, '\xB8');
    else if ( mimes == "=B9" ) body.replace(found, 3, 1, '\xB9');
    else if ( mimes == "=BA" ) body.replace(found, 3, 1, '\xBA');
    else if ( mimes == "=BB" ) body.replace(found, 3, 1, '\xBB');
    else if ( mimes == "=BC" ) body.replace(found, 3, 1, '\xBC');
    else if ( mimes == "=BD" ) body.replace(found, 3, 1, '\xBD');
    else if ( mimes == "=BE" ) body.replace(found, 3, 1, '\xBE');
    else if ( mimes == "=BF" ) body.replace(found, 3, 1, '\xBF');
    else if ( mimes == "=C0" ) body.replace(found, 3, 1, '\xC0');
    else if ( mimes == "=C1" ) body.replace(found, 3, 1, '\xC1');
    else if ( mimes == "=C2" ) body.replace(found, 3, 1, '\xC2');
    else if ( mimes == "=C3" ) body.replace(found, 3, 1, '\xC3');
    else if ( mimes == "=C4" ) body.replace(found, 3, 1, '\xC4');
    else if ( mimes == "=C5" ) body.replace(found, 3, 1, '\xC5');
    else if ( mimes == "=C6" ) body.replace(found, 3, 1, '\xC6');
    else if ( mimes == "=C7" ) body.replace(found, 3, 1, '\xC7');
    else if ( mimes == "=C8" ) body.replace(found, 3, 1, '\xC8');
    else if ( mimes == "=C9" ) body.replace(found, 3, 1, '\xC9');
    else if ( mimes == "=CA" ) body.replace(found, 3, 1, '\xCA');
    else if ( mimes == "=CB" ) body.replace(found, 3, 1, '\xCB');
    else if ( mimes == "=CC" ) body.replace(found, 3, 1, '\xCC');
    else if ( mimes == "=CD" ) body.replace(found, 3, 1, '\xCD');
    else if ( mimes == "=CE" ) body.replace(found, 3, 1, '\xCE');
    else if ( mimes == "=CF" ) body.replace(found, 3, 1, '\xCF');
    else if ( mimes == "=D0" ) body.replace(found, 3, 1, '\xD0');
    else if ( mimes == "=D1" ) body.replace(found, 3, 1, '\xD1');
    else if ( mimes == "=D2" ) body.replace(found, 3, 1, '\xD2');
    else if ( mimes == "=D3" ) body.replace(found, 3, 1, '\xD3');
    else if ( mimes == "=D4" ) body.replace(found, 3, 1, '\xD4');
    else if ( mimes == "=D5" ) body.replace(found, 3, 1, '\xD5');
    else if ( mimes == "=D6" ) body.replace(found, 3, 1, '\xD6');
    else if ( mimes == "=D7" ) body.replace(found, 3, 1, '\xD7');
    else if ( mimes == "=D8" ) body.replace(found, 3, 1, '\xD8');
    else if ( mimes == "=D9" ) body.replace(found, 3, 1, '\xD9');
    else if ( mimes == "=DA" ) body.replace(found, 3, 1, '\xDA');
    else if ( mimes == "=DB" ) body.replace(found, 3, 1, '\xDB');
    else if ( mimes == "=DC" ) body.replace(found, 3, 1, '\xDC');
    else if ( mimes == "=DD" ) body.replace(found, 3, 1, '\xDD');
    else if ( mimes == "=DE" ) body.replace(found, 3, 1, '\xDE');
    else if ( mimes == "=DF" ) body.replace(found, 3, 1, '\xDF');
    else if ( mimes == "=E0" ) body.replace(found, 3, 1, '\xE0');
    else if ( mimes == "=E1" ) body.replace(found, 3, 1, '\xE1');
    else if ( mimes == "=E2" ) body.replace(found, 3, 1, '\xE2');
    else if ( mimes == "=E3" ) body.replace(found, 3, 1, '\xE3');
    else if ( mimes == "=E4" ) body.replace(found, 3, 1, '\xE4');
    else if ( mimes == "=E5" ) body.replace(found, 3, 1, '\xE5');
    else if ( mimes == "=E6" ) body.replace(found, 3, 1, '\xE6');
    else if ( mimes == "=E7" ) body.replace(found, 3, 1, '\xE7');
    else if ( mimes == "=E8" ) body.replace(found, 3, 1, '\xE8');
    else if ( mimes == "=E9" ) body.replace(found, 3, 1, '\xE9');
    else if ( mimes == "=EA" ) body.replace(found, 3, 1, '\xEA');
    else if ( mimes == "=EB" ) body.replace(found, 3, 1, '\xEB');
    else if ( mimes == "=EC" ) body.replace(found, 3, 1, '\xEC');
    else if ( mimes == "=ED" ) body.replace(found, 3, 1, '\xED');
    else if ( mimes == "=EE" ) body.replace(found, 3, 1, '\xEE');
    else if ( mimes == "=EF" ) body.replace(found, 3, 1, '\xEF');
    else if ( mimes == "=F0" ) body.replace(found, 3, 1, '\xF0');
    else if ( mimes == "=F1" ) body.replace(found, 3, 1, '\xF1');
    else if ( mimes == "=F2" ) body.replace(found, 3, 1, '\xF2');
    else if ( mimes == "=F3" ) body.replace(found, 3, 1, '\xF3');
    else if ( mimes == "=F4" ) body.replace(found, 3, 1, '\xF4');
    else if ( mimes == "=F5" ) body.replace(found, 3, 1, '\xF5');
    else if ( mimes == "=F6" ) body.replace(found, 3, 1, '\xF6');
    else if ( mimes == "=F7" ) body.replace(found, 3, 1, '\xF7');
    else if ( mimes == "=F8" ) body.replace(found, 3, 1, '\xF8');
    else if ( mimes == "=F9" ) body.replace(found, 3, 1, '\xF9');
    else if ( mimes == "=FA" ) body.replace(found, 3, 1, '\xFA');
    else if ( mimes == "=FB" ) body.replace(found, 3, 1, '\xFB');
    else if ( mimes == "=FC" ) body.replace(found, 3, 1, '\xFC');
    else if ( mimes == "=FD" ) body.replace(found, 3, 1, '\xFD');
    else if ( mimes == "=FE" ) body.replace(found, 3, 1, '\xFE');
    else if ( mimes == "=FF" ) body.replace(found, 3, 1, '\xFF');
    last_found = found + 1 ;
  }
}

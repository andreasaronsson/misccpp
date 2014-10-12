#include "smtp.h"
#include <sstream>

Smtp::Smtp() {
}

Smtp::Smtp(string hostname) {
  this->host = hostname;
}

void Smtp::setvalue(string key, string val) {
  if ( key == "Host" ) this->host = val;
}

string Smtp::get_host() {
  return this->host;
}

string Smtp::send(Mail* message, Mailbox &sentbox) {
  
  InetHostAddress server( host.c_str() );
  if ( ! server.isInetAddress() ) {
    return "No such hostname.";
  }
  
  TCPStream tcp_smtp(server, 25);
  if ( tcp_smtp == NULL ) {
    return "Could not connect to server.";
  }

  char ans[256];
  string buff;
  
  // Read & check greeting
  tcp_smtp.getline(ans,255);
  buff = ans;

  if ( buff.substr(0,3) != "220" ) {
    if ( buff.substr(0,3) == "554" ) {
      tcp_smtp << "QUIT\r" << endl;
    }
    return "Transaction failed.";
  }

  // Send EHLO & check answer
  tcp_smtp << "EHLO " << getenv("HOSTNAME") << "\r" << endl;
  tcp_smtp.getline(ans,255);
  buff = ans;
  if ( buff.substr(0,3) != "250" ) {
    return "EHLO didn't work.";
  }

  // Sender
  tcp_smtp << "MAIL FROM:" << message->get_from() << "\r" << endl;
  tcp_smtp.getline(ans,255);
  buff = ans;
  if ( buff.substr(0,3) != "250" ) {
    return buff;
  }

  // Recipient
  tcp_smtp << "RCPT TO:" << message->get_to() << "\r" << endl;
  tcp_smtp.getline(ans,255);
  buff = ans;
  if ( buff.substr(0,3) != "250" ) {
    return buff;
  }
  
  // Now start sending headers
  tcp_smtp << "DATA" << "\r" << endl;
  tcp_smtp.getline(ans,255);
  buff = ans;
  if ( buff.substr(0,3) != "354" ) {
    return buff;
  }
  tcp_smtp << "Date: " << message->get_date() << "\r" << endl;
  tcp_smtp << "From: " << message->get_from() << "\r" << endl;
  tcp_smtp << "To: " << message->get_to() << "\r" << endl;
  tcp_smtp << "Subject: " << message->get_subject() << "\r" << endl;

  // Send an empty line, then start sending the message body
  tcp_smtp << "\r" << endl;
  stringstream body;
  body << message->get_body();
  while ( body ) {
    body.getline(ans,255);
    buff = ans;
    if ( buff.substr(0,1) == "." ) tcp_smtp << ".";
    tcp_smtp << buff << "\r" << endl;
  }

  // Send a line containing inly . to end the message
  tcp_smtp << ".\r" << endl;
  
  // Read response from smtp server
  tcp_smtp.getline(ans,255);
  buff = ans;
  if ( buff.substr(0,3) != "250" ) {
    return "Error, message not sent";
  }

  // Message successfully sent, quit the connection
  tcp_smtp << "QUIT\r" << endl;
  sentbox.import( message );
  return "Success";
}

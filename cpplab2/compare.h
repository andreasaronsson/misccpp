#ifndef _COMPARE
#define _COMPARE
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <utility>
#include "mail.h"

class CmpSubject
{
 public:
  bool operator() (Mail*, Mail*) const;
};

class CmpDate
{
 public:
  bool operator() (Mail*, Mail*) const;
};

class CmpFrom
{
 public:
  bool operator() (Mail*, Mail*) const;
};

#endif

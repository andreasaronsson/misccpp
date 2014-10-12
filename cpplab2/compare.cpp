#include "compare.h"

using namespace std;

//Compare subject
bool CmpSubject::operator() (Mail *m1, Mail *m2) const
{
  return m1->get_subject() < m2->get_subject();
}

//Compare date
bool CmpDate::operator() (Mail *m1, Mail *m2) const
{
  return m1->get_date() < m2->get_date();
}

//Compare from
bool CmpFrom::operator() (Mail *m1, Mail *m2) const
{
  return m1->get_from() < m2->get_from();
}

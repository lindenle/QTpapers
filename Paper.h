#ifndef __PAPER_H__
#define __PAPER_H__

#include "Entry.h"

class Paper : public Entry
{
  
 public:
  
  Paper();
  
  void set_arxiv_number(const QString& s)
  {_arxiv_number=s;}

  void set_abstract(const QString & s)
  {_abstract=s;}

  void set_journal(const QString & s)
  {_journal=s;}
  
  QString get_arxiv_number()
  {return _arxiv_number;}
  
  QString get_abstract()
  {return _abstract;}

  QString get_journal()
  {return _journal;}

  void fetch_from_arxiv(){;}
  
  int open_new_dialog();
  
 private:
  
  QString _arxiv_number;
  QString _journal;
  QString _abstract;
  
};
#endif ///__PAPER_H__

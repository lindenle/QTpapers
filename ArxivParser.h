#ifndef __ARXIV_PARSER__
#define __ARXIV_PARSER__

#include "Parser.h"

class ArxivParser : public Parser
{

 public:
  ArxivParser(){;}
  
  QString getTitle();
  QString getAuthors();
  QString getAbstract();
  QString getPaperName();
  QUrl getDownloadLocation();
  QDate getDate();
  QString getNumber();
};

#endif //__ARXIV_PARSER__

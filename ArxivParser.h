#ifndef __ARXIV_PARSER__
#define __ARXIV_PARSER__

#include "Parser.h"

class ArxivParser : public Parser
{
 public:
  QString getTitle();
  QString getAuthors();
  QString getAbstract();
  QString getPaperName();
  QString getDownloadLocation();
};

#endif //__ARXIV_PARSER__

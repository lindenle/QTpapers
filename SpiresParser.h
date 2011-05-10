#ifndef __SPIRES_PARSER__
#define __SPIRES_PARSER__

#include "Parser.h"

class SpiresParser : public Parser
{
 public:

  SpiresParser(){;}

  QString getTitle();
  QString getAuthors();
  QString getAbstract();
  QString getPaperName();
  QUrl    getDownloadLocation();
  QDate   getDate();
  QString getNumber();


};

#endif //__SPIRES_PARSER__

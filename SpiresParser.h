#ifndef __SPIRES_PARSER__
#define __SPIRES_PARSER__

#include "Parser.h"

class SpiresParser : public Parser
{
 public:
  QString getTitle();
  QString getAuthors();
  QString getAbstract();
  QString getPaperName();
  QString getDownloadLocation();

};

#endif //__SPIRES_PARSER__

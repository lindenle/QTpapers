#ifndef __PARSER__
#define __PARSER__

//base class for parser

#include <QRegExp>
#include <QWebPage>
#include <QWebFrame>
#include <QUrl>
#include <QDate>
#include <QTextStream>

class Parser 
{
 public:
 Parser():
  _cleanup("<.*>"),
  _stdout(stdout)
    {
      _cleanup.setMinimal(true);
    }

  ~Parser();

  //need to implement these in the base class
  virtual QString getTitle()=0;
  virtual QString getAuthors()=0;
  virtual QString getAbstract()=0;
  virtual QString getPaperName()=0;
  virtual QUrl    getDownloadLocation()=0;
  virtual QDate   getDate()=0;
  virtual QString getNumber()=0;

  void setData(const QString & data){_data = data;}

 protected:
  QString _data;
  QRegExp _cleanup;
  QTextStream _stdout;
};

#endif //__PARSER__

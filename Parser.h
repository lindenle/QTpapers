#ifndef __PARSER__
#define __PARSER__

//base class for parser

#include <QRegExp>
#include <QWebPage>
#include <QWebFrame>

class Parser 
{
 public:
  Parser(QWebPage * page = 0, QWebFrame * frame = 0)
    {
      _frame = frame;
      _page=page;
    }

  ~Parser();

  //need to implement these in the base class
  virtual QString getTitle()=0;
  virtual QString getAuthors()=0;
  virtual QString getAbstract()=0;
  virtual QString getPaperName()=0;
  virtual QString getDownloadLocation()=0;

  void cleanupHtmlTags();
  void setFrame(QWebFrame * f){_frame=f;}
  void setPage(QWebPage * p ){_page=p;}

 private:
  QWebPage * _page;
  QWebFrame * _frame;
  QString * _data;
  QRegExp * _reg_exp;
};

#endif //__PARSER__

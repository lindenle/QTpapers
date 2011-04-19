#ifndef __PARSER__
#define __PARSER__

//base class for parser

#include <QRegExp>
#include <QWebPage>
#include <QWebFrame>
#include <QUrl>

class Parser 
{
 public:
  Parser(const QUrl & url)
    {
      _url = url;
    }

  ~Parser();

  //need to implement these in the base class
  virtual QString getTitle()=0;
  virtual QString getAuthors()=0;
  virtual QString getAbstract()=0;
  virtual QString getPaperName()=0;
  virtual QString getDownloadLocation()=0;

  void cleanupHtmlTags();
  /* void setFrame(const QWebFrame & f){ _frame=f;} */
  /* void setPage(const QWebPage & p ){ _page=p;} */
  void setUrl(const QUrl & url) { _url = url;} 
  /* QWebFrame getFrame(void){ return _frame;} */
  /* QWebPage  getPage(void){ return _page;} */
  /* QUrl      getUrl(void) { return _url;}      */

 private:
  QWebPage  * _page;
  QWebFrame * _frame;
  QString _data;
  QRegExp * _reg_exp;
  QUrl _url;
};

#endif //__PARSER__

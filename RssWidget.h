#ifndef __RSS_WIDGET__
#define __RSS_WIDGET__

#include <QWebView>
#include <QStringList>
#include <QTextStream>

class RssWidget : public QWebView
{
  Q_OBJECT

 public:

  RssWidget();
  
 private slots:

  void add_feed(){;}

  void delete_feed(){;}

 private:


 protected:
  
  //Need a list of all the rss feeds that we have
  QStringList _feeds;
  QString _current_feed;
  QTextStream _stdout;

};

#endif //__RSS_WIDGET__

#ifndef __RSS_WIDGET__
#define __RSS_WIDGET__

#include <QWebView>
#include <QComboBox>
#include <QSplitter>
#include <QStringList>
#include <QTextStream>

class RssWidget : public QSplitter
{
  Q_OBJECT

 public:

  RssWidget();

  QUrl url(){return _rss_view->url();}

  QWebPage * page(){return _rss_view->page();}
  
 private slots:

  void add_feed(){;}

  void delete_feed(){;}

  void update_web_view();

  void set_current_rss();

 private:

  QAction * addFeed;    
  QAction * deleteFeed;    

 protected:
  
  //Need a list of all the rss feeds that we have
  QTextStream _stdout;
  QString _current_rss;
  QStringList _feeds;
  QWebView *  _rss_view;
  QComboBox * _rss_list;
  
};

#endif //__RSS_WIDGET__

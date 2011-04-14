#ifndef __RSS_WIDGET__
#define __RSS_WIDGET__

#include <QWebView>
#include <QComboBox>
#include <QSplitter>
#include <QTextStream>
#include <QMap>

class RssWidget : public QSplitter
{
  Q_OBJECT

 public:
  typedef QMap<QString,QUrl> UrlMap;
  typedef QMapIterator<QString,QUrl> UrlMapIter;


  RssWidget();

  QUrl url(){return _rss_view->url();}

  QWebPage * page(){return _rss_view->page();}
  
 private slots:

  void add_feed(){;}

  void delete_feed(){;}

  void update_web_view();

  void update_list_box();

  void set_current_rss(const QString & feed);

  void back(){_rss_view->back();}

  void forward(){_rss_view->forward();}

 private:

  QAction * addFeed;    
  QAction * deleteFeed;    

 protected:
  
  //Need a list of all the rss feeds that we have
  QTextStream _stdout;
  QUrl _current_rss;
  UrlMap _feeds;
  QWebView *  _rss_view;
  QComboBox * _rss_list;
  
};

#endif //__RSS_WIDGET__

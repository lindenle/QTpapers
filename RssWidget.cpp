
#include "RssWidget.h"

RssWidget::RssWidget() :
  _stdout(stdout),
  _current_rss("http://arxiv.org/")
{
  //first we have to pack the two new widgets up;

  _rss_view = new QWebView();
  _rss_list = new QComboBox();

  // the defaults
  _feeds["ArXiv"]=QUrl("http://arxiv.org/");
  _feeds["Spires"]=QUrl("http://www.slac.stanford.edu/spires/");
  _feeds["New"]=QUrl("");

  update_list_box();

  connect(_rss_list, SIGNAL(currentIndexChanged(const QString & )), this, SLOT(set_current_rss(const QString & )));

  //pack the widgets
  addWidget(_rss_list);  
  addWidget(_rss_view);  
  setOrientation(Qt::Vertical);

  //update the web view
  update_web_view();

}

void RssWidget::set_current_rss(const QString & feed)
{
  if ( feed == "New" )
    {
      //need to add a dialog here to add a feed
      _stdout << "Feature not enabled" << endl;
      //also need to thing about how to map a parser to the feed...
      return;
    }
  _stdout << "set_current_rss " << feed  << endl;
  _current_rss = _feeds[feed];
  _stdout << "set_current_rss " << _current_rss.toString()  << endl;
  update_web_view();
}

void RssWidget::update_web_view()
{
  _rss_view->load(_current_rss);
  _rss_view->show();
}

void RssWidget::update_list_box()
{
  UrlMapIter miter(_feeds);
  while ( miter.hasNext() ) 
    {
      miter.next();
      if ( miter.key() != "New" )
	_rss_list->addItem( miter.key() );
    }
  //always put "New" last
  _rss_list->addItem( "New" );
}


#include "RssWidget.h"

RssWidget::RssWidget() :
  _stdout(stdout),
  _current_rss("http://arxiv.org/")
{
  //first we have to pack the two new widgets up;

  _rss_view = new QWebView();
  _rss_list = new QComboBox();

  _rss_list->addItem(tr("Arxiv"));
  _rss_list->addItem(tr("New RSS"));

  connect(_rss_list, SIGNAL(currentIndexChanged), this, SLOT());

  addWidget(_rss_list);  
  addWidget(_rss_view);  

  setOrientation(Qt::Vertical);

  //here we need to make it so that the url drop down list can be
  //selected and then it will change the rss view
  update_web_view();
}

void RssWidget::set_current_rss()
{
  _stdout << "set_current_rss"  << endl;
  //  _current_rss = _rss_list->...
  update_web_view();
}

void RssWidget::update_web_view()
{
  _rss_view->load(QUrl(_current_rss));

  _rss_view->show();
}


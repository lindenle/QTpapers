
#include "RssWidget.h"

RssWidget::RssWidget() :
  _stdout(stdout)
{
  
  load(QUrl("http://arxiv.org/"));

  show();
}




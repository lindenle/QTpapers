#include "Parser.h"
#include <QNetworkRequest>

QString Parser::requestPageData(const QUrl & url)
{
  QString bob;
  _net_manager->get(QNetworkRequest(url));
  //  connect()
  return bob;
}

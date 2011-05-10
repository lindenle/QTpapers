#include "Parser.h"

QString Parser::requestPageData(const QUrl & url)
{
  _net_manager->get(QNetworkRequest(url));
  //  connect()
}

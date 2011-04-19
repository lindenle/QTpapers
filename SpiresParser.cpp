#include "SpiresParser.h"

QString SpiresParser::getTitle()
{
  QString search = "<!-- START RESULTS -->";
  
  QString title = _data.right(_data.size() - ( _data.indexOf(search) + search.size() ) );
  search = "</b><br>"; 
  title = title.left(title.indexOf(search) );
  title.replace(_cleanup,"");
  title.replace("\n","");
  return title;
}

QString SpiresParser::getAuthors()
{
  QString search = "wwwauthors";
  QString authors = _data.right(_data.size() - ( _data.indexOf(search) + search.size() ) );
  search = "</i></a>";
  authors = authors.left( authors.indexOf(search) );
  authors.replace(QRegExp(".*[0-9]>"),"");
  authors.replace(_cleanup,"");
  authors.replace("\n","");
  //here we really want to grab the url from spires and get all the authors...
  return authors;
}

QString SpiresParser::getAbstract()
{
  QString abstract;

  return abstract;
}

QString SpiresParser::getPaperName()
{
  QString name;

  return name;
}

QUrl SpiresParser::getDownloadLocation()
{
  QUrl location;

  return location;
}

QDate SpiresParser::getDate()
{
  QDate date;

  return date;
}

QString SpiresParser::getNumber()
{
  QString number;

  return number;
}

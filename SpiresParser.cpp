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
  authors.replace(QRegExp(".*[0-9]\">"),"");
  authors.replace(_cleanup,"");
  authors.replace("\n","");
  //here we really want to grab the url from spires and get all the authors...
  return authors;
}

QString SpiresParser::getAbstract()
{
  QString search = "Abstract";
  QString abstract_url_str= _data.left(_data.indexOf(search));
  search = "href=";
  abstract_url_str = abstract_url_str.right( abstract_url_str.size() - ( abstract_url_str.lastIndexOf(search)+search.size() ) );
  abstract_url_str.replace(_cleanup,"");
  abstract_url_str.replace("\n","");
  abstract_url_str.replace(">", "");
  abstract_url_str.replace(" ", "");
  _stdout << "SpiresParser::getAbstract " << abstract_url_str << endl;
  QUrl abstract_url(abstract_url_str);  
  //fetch the url and parse... how to do this...
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
  QString search = "PDF";
  QString location_url_str= _data.left(_data.indexOf(search));
  search = "href=";
  location_url_str = location_url_str.right( location_url_str.size() - ( location_url_str.lastIndexOf(search)+search.size() ) );
  location_url_str.replace(_cleanup,"");
  location_url_str.replace("\n","");
  location_url_str.replace(">", "");
  location_url_str.replace(" ", "");
  _stdout << "SpiresParser::getLocation " << location_url_str << endl;
  QUrl location(location_url_str);  
  return location;
}

QDate SpiresParser::getDate()
{

  QString search = "</i></a>";
  QString date_str = _data.right(_data.size() - ( _data.indexOf(search) + search.size() ) );
  search = "<a href=";
  date_str = date_str.left( date_str.indexOf(search) );
  search = ".";
  date_str = date_str.left( date_str.indexOf(search) );
  date_str.replace(_cleanup,"");
  date_str.replace("\n","");
  date_str.replace(" ", "");
  QDate date = QDate::fromString(date_str,"MMMyyyy");
  return date;
}

QString SpiresParser::getNumber()
{
  QString number;

  return number;
}

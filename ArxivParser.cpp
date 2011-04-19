#include "ArxivParser.h"

QString ArxivParser::getTitle()
{
  QString title;
  QString search = "Title:</span>";
  title =   _data.right(_data.size() - ( _data.indexOf(search) + search.size(\
									       ) ) );
  search = "</h1>";
  title = title.left(title.indexOf(search) );
  title.replace(_cleanup,"");
  title.replace("\n","");
  return title;
}

QString ArxivParser::getAuthors()
{
  QString authors;
  QString search = "Authors:</span>";
  authors =   _data.right(_data.size() - ( _data.indexOf(search) + search.size() ) ); 
  search = "</div>";
  authors = authors.left(authors.indexOf(search) );
  authors.replace(_cleanup,"");
  authors.replace("\n","");
  return authors;
}

QString ArxivParser::getAbstract()
{
  QString abstract;
  QString search = "Abstract:</span>";
  abstract =   _data.right(_data.size() - ( _data.indexOf(search) + search.size() ) ); 
  search = "</blockquote>";
  abstract = abstract.left(abstract.indexOf(search) );
  abstract.replace(_cleanup,"");
  abstract.replace("\n","");
  return abstract;
}

QString ArxivParser::getPaperName()
{
  QString search = "Download:</h2>";
  QString name = _data.right( _data.size() - ( _data.indexOf(search) + search.size() ) );
  search ="\" accesskey=\"f\">PDF";
  name = name.left(name.indexOf(search));
  QRegExp ps("<li>.*PostScript.*</li>");
  name.replace(ps,"");
  name.replace("<li><a href=\"","");
  name.replace("\n","");
  name.replace(_cleanup,"");
  name.replace("/pdf/","");
  name+=".pdf";
  return name;
}

QUrl ArxivParser::getDownloadLocation()
{
  QString loc_str = getPaperName();
  loc_str.replace(".pdf","");
  loc_str = "http://arxiv.org/pdf/" + loc_str;
  QUrl location(loc_str);
  return location;
}

QDate ArxivParser::getDate()
{
  QString search = "(Submitted on ";
  QString date_str = _data.right(_data.size() - ( _data.indexOf(search) + search.size() ) );
  search=")";
  date_str = date_str.left( date_str.indexOf(search) );
  date_str.replace(_cleanup,"");
  date_str.replace(QRegExp("v[0-9]"), "");
  date_str.replace("(", "");
  date_str.replace(" ", "");
  QDate date = QDate::fromString(date_str,"dMMMyyyy");
  return date;
}

QString ArxivParser::getNumber()
{
  QString search = "<td class=\"tablecell arxivid\">";
  QString number = _data.right(_data.size() - ( _data.indexOf(search) + search.size() ) );
  search = "</td>";
  number = number.left(number.indexOf(search) );
  number.replace(_cleanup,"");
  return number;
}

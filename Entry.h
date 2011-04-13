#ifndef __ENTRY_H__
#define __ENTRY_H__

#include <QObject>
#include <QString>
#include <QDate>

// This is the base clase for any entry in a library
// This can be inheritted by other types of entry classes.

class Entry 
{

 public:
  
 Entry(  QString author="", 
	 QString title="")
    { set_author(author);
      set_title(title);}
  
  QString get_author(void) const
  {return _author;}
  
  QString get_author_short(int number=3) const;

  QString get_title(void) const
  {return _title;}
  
  QDate get_date(void) const
  {return _date;}

  QString get_file_name(void) 
  {return _file_name;}
  
  void set_author(const QString& s)
  {_author=s;}
  
  void set_title(const QString& s)
  {_title=s;}
  
  void set_date(const QDate& d)
  {_date=d;}

  void set_date(const QString& s)
  {_date.fromString(s);}

  void set_file_name(const QString& s)
  {_file_name=s;}
  
  virtual int open_new_dialog();
  
 protected:
  
  QString _author;
  QString _title;
  QDate _date;
  QString _file_name;
  
  int _entry_id;
};

#endif //__ENTRY_H__

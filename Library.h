#ifndef __LIBRARY_H__
#define __LIBRARY_H__

#include "Paper.h"

#include <vector>
#include <QList>
#include <QString>
#include <QTextStream>



class Paper;
class LibraryDialog;

class Library 
{

 public:

  Library();

  //! what kind of library is he?
  enum LibraryType {PaperLib, TalkLib};

  //! set the library type 
  void  set_library_type(const LibraryType& t)
  {_type=t;}

  //! get the library type 
  LibraryType get_library_type(void)
  {return _type;}

  //! a shortcut to the _entry_list
  std::vector<Entry *> get_entry_list()
    {return _entry_list;}

  //! get the full file path for the library
  void set_library_file(const QString& s);

  //! set the name of the library
  void set_library_name(const QString & s)
  {_name=s;}

  //! set the directory to save the library
  void set_library_directory(const QString & s)
  {_directory=s;}

  //! get the name of the library
  QString get_library_name(void)
  {return _name;}

  //! get the full file path for the library
  QString get_library_file(void)
  {return (_directory+"/"+_name+".xml");}

  //! get the directory the libray lives in
  QString get_library_directory(void)
  {return _directory;}

  //! add an entry to a library
  void add_entry(Entry *  e)
  {_entry_list.push_back(e);}
  
  //! load the library from a file
  bool open_library();
  
  //!close a library by writing out an xml file
  bool close_library();

  //! might be nice to actually have some search functions here...
  int open_library_dialog();

  void set_current_entry(Entry * e)
  {_current_entry=e;}

  Entry * get_current_entry()
  {return _current_entry;}

  void delete_current_entry();

  void remove_library_file();

 private:
  
  std::vector<Entry *> _entry_list;

  Entry * _current_entry;

  QString _name;

  QString _directory;

  QTextStream _stdout;

  LibraryType _type;
};

#endif //__LIBRARY_H__

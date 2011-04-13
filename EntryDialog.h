#ifndef __ENTRYDIALOG_H__
#define __ENTRYDIALOG_H__

#include <QDateEdit>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

#include "Library.h"
#include "Entry.h"

class Library;
class Entry;

class EntryDialog : public QDialog
{
  Q_OBJECT

 public:

  EntryDialog(QWidget * parent = 0);

  void set_library( Library * l )
  {_library_pointer = l;}

  virtual void set_entry( Entry * e );

 public slots:

  virtual void ok_clicked();
  void open_file_search();
  void open_file();

 protected:

  QLabel * _title;
  QLineEdit * _title_edit;
  QLabel * _author;
  QLineEdit * _author_edit;
  QLabel * _date;
  QDateEdit * _date_edit;
  QLabel * _file;
  QLineEdit * _file_edit;
  QPushButton * _search;
  QPushButton * _open;
  QPushButton * _ok;
  QPushButton * _cancel;
  QVBoxLayout * _topdown;
  Library * _library_pointer;
  Entry * _entry_pointer;

};

#endif // __ENTRYDIALOG_H__

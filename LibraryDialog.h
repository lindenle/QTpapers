#ifndef __LIBRARYDIALOG_H__
#define __LIBRARYDIALOG_H__

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "Library.h"

class Library;

class LibraryDialog : public QDialog
{
  Q_OBJECT

 public:

  LibraryDialog(QWidget * parent = 0);

  void set_library( Library * l )
  {_library_pointer = l;}

 public slots:

  void open_directory_search();
  void ok_clicked();

 private:
  QLabel * _library;
  QLineEdit * _libraryname;
  QLabel * _directory;
  QLineEdit * _directoryname;
  QPushButton * _search;
  QPushButton * _ok;
  QPushButton * _cancel;
  Library * _library_pointer;
};

#endif // __LIBRARYDIALOG_H__

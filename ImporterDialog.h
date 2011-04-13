#ifndef __IMPORTDIALOG_H__
#define __IMPORTDIALOG_H__

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "Import.h"

class Import;

class ImportDialog : public QDialog
{
  Q_OBJECT

 public:

  ImportDialog(QWidget * parent = 0);

  void set_import( Import * l )
  {_import_pointer = l;}

 public slots:

  void open_directory_search();
  void ok_clicked();

 private:
  QLabel * _import;
  QLineEdit * _importname;
  QLabel * _directory;
  QLineEdit * _directoryname;
  QPushButton * _search;
  QPushButton * _ok;
  QPushButton * _cancel;
  Import * _import_pointer;
};

#endif // __IMPORTDIALOG_H__

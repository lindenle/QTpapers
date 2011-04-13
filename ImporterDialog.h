#ifndef __IMPORTERDIALOG_H__
#define __IMPORTERDIALOG_H__

#include <QFileDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "Importer.h"

class Importer;

class ImporterDialog : public QFileDialog
{
  Q_OBJECT

 public:

  ImporterDialog(QWidget * parent = 0);

  void set_import( Importer * l )
  {_importer_pointer = l;}

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
  Importer * _importer_pointer;
};

#endif // __IMPORTERDIALOG_H__

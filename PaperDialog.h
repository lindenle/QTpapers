#ifndef __PAPERDIALOG_H__
#define __PAPERDIALOG_H__

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>

#include "Library.h"
#include "Paper.h"
#include "EntryDialog.h"

class Library;
class Entry;
class EntryDialog;

class PaperDialog : public EntryDialog
{

 public:
  
  PaperDialog(QWidget * parent = 0);

  void set_entry( Entry * e );

 public slots:

   void ok_clicked();

 private:

  QLabel * _abstract;
  QTextEdit * _abstract_edit;
  QLabel * _arxiv;
  QLineEdit * _arxiv_edit;
  QLabel * _journal;
  QLineEdit * _journal_edit;
  
};

#endif // __PAPERDIALOG_H__

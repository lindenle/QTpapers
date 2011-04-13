#ifndef __TALKDIALOG_H__
#define __TALKDIALOG_H__

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>

#include "Library.h"
#include "Talk.h"
#include "EntryDialog.h"

class Library;
class Entry;
class EntryDialog;

class TalkDialog : public EntryDialog
{

 public:

  TalkDialog(QWidget * parent = 0);

 private:

  QLabel * _abstract;
  QTextEdit * _abstract_edit;
  QLabel * _conference;
  QLineEdit * _conference_edit;

};

#endif // __TALKDIALOG_H__

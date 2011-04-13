#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>

#include "TalkDialog.h"

TalkDialog::TalkDialog(QWidget * parent):
  EntryDialog(parent)
{
  //can we get the widget stack and add new ones
  _conference = new QLabel(tr("Conference"));
  _conference_edit = new QLineEdit;
  _conference->setBuddy(_conference_edit);

  QWidget * conference = new QWidget;
  QHBoxLayout * conference_layout = new QHBoxLayout;
  conference_layout->addWidget(_conference);
  conference_layout->addWidget(_conference_edit);
  conference->setLayout(conference_layout);

  _abstract = new QLabel(tr("Abstract"));
  _abstract_edit = new QTextEdit;
  _abstract->setBuddy(_abstract_edit);

  QWidget * abstract = new QWidget;
  QHBoxLayout * abstract_layout = new QHBoxLayout;
  abstract_layout->addWidget(_abstract);
  abstract_layout->addWidget(_abstract_edit);
  abstract->setLayout(abstract_layout);
  _topdown->insertWidget(2,conference);
  _topdown->insertWidget(3,abstract);
  setLayout(_topdown);
}



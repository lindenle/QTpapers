#include "PrefDialog.h"
#include <QHBoxLayout>
#include <QFileDialog>
#include <QProcess>
#include <QSettings>

PrefDialog::PrefDialog(QWidget * parent) :
  QDialog(parent)
{
  setWindowTitle(tr("Preferences"));

  _file = new QLabel(tr("PDF Viewer"));
  _file_edit = new QLineEdit;
  _file->setBuddy(_file_edit);
  _search = new QPushButton(tr("Search"));  
  connect(_search, SIGNAL(clicked()), this, SLOT(open_file_search()));
  QSettings settings("LindenLevy", "QtPapers");
  settings.beginGroup("Collection Preferences");
  _file_edit->setText( settings.value("PDF Viewer").toString());
  settings.endGroup();

  QWidget * file = new QWidget;
  QHBoxLayout * file_layout = new QHBoxLayout;
  file_layout->addWidget( _file);
  file_layout->addWidget( _file_edit);
  file_layout->addWidget( _search);
  file->setLayout(file_layout);

  QWidget * buttons = new QWidget;
  _ok = new QPushButton(tr("OK"));
  connect(_ok, SIGNAL(clicked()), this, SLOT(ok_clicked()));
  _cancel = new QPushButton(tr("CANCEL"));
  connect(_cancel, SIGNAL(clicked()), this, SLOT(reject()));

  QHBoxLayout * bottom_buttons = new QHBoxLayout;
  bottom_buttons->addWidget(_ok);
  bottom_buttons->addWidget(_cancel);
  buttons->setLayout(bottom_buttons);

  _topdown = new QVBoxLayout();
  _topdown->addWidget(file);
  _topdown->addWidget(buttons);
  setLayout(_topdown);
  //here we need to set some signals
}

void PrefDialog::ok_clicked()
{
  //store the new settings into
  QSettings settings("LindenLevy", "QtPapers");
  settings.beginGroup("Collection Preferences");
  QDir directory(_file_edit->text());
  settings.setValue("PDF Viewer", directory.absolutePath());
  settings.endGroup();
  close();
}

void PrefDialog::open_file_search()
{

  QFileDialog dialog(this);
  dialog.setFileMode(QFileDialog::ExistingFile);
  dialog.setViewMode(QFileDialog::Detail);
  dialog.hasFocus();
  dialog.show();
  QStringList fileNames;
  if (dialog.exec())
    {
      fileNames = dialog.selectedFiles();
      _file_edit->setText(fileNames.at(0));
    }  
}


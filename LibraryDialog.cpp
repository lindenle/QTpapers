#include "LibraryDialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QSettings>

#include <stdlib.h>

LibraryDialog::LibraryDialog(QWidget * parent) :
  QDialog(parent)
{
  setWindowTitle(tr("New Library"));

  _library = new QLabel(tr("Library Name"));
  _libraryname = new QLineEdit;
  _library->setBuddy(_libraryname);
  
  _directory = new QLabel(tr("Directory Location"));
  _directoryname = new QLineEdit;
  //set a default directory from the settings
  QSettings settings;
  settings.beginGroup("LastLibrary");
  _directoryname->setText( settings.value("directory",QString(getenv("HOME"))).toString());
  settings.endGroup();

  _directory->setBuddy(_directoryname);
  _search = new QPushButton(tr("Search"));
  
  connect(_search, SIGNAL(clicked()), this, SLOT(open_directory_search()));
  
  QWidget * directory = new QWidget;
  QHBoxLayout * directory_layout = new QHBoxLayout;
  directory_layout->addWidget( _directory);
  directory_layout->addWidget( _directoryname);
  directory_layout->addWidget( _search);
  directory->setLayout(directory_layout);

  QWidget * buttons = new QWidget;
  _ok = new QPushButton(tr("OK"));
  connect(_ok, SIGNAL(clicked()), this, SLOT(ok_clicked()));
  _cancel = new QPushButton(tr("CANCEL"));
  connect(_cancel, SIGNAL(clicked()), this, SLOT(reject()));

  QHBoxLayout * bottom_buttons = new QHBoxLayout;
  bottom_buttons->addWidget(_ok);
  bottom_buttons->addWidget(_cancel);
  buttons->setLayout(bottom_buttons);

  QVBoxLayout * topdown = new QVBoxLayout();
  topdown->addWidget(_library);
  topdown->addWidget(_libraryname);
  topdown->addWidget(directory);
  topdown->addWidget(buttons);
  setLayout(topdown);
  //here we need to set some signals
}

void LibraryDialog::open_directory_search()
{
  QFileDialog dialog(this);
  dialog.setFileMode(QFileDialog::DirectoryOnly);
  dialog.setViewMode(QFileDialog::Detail);
  dialog.hasFocus();
  dialog.show();
  QStringList fileNames;
  if (dialog.exec())
    {
      fileNames = dialog.selectedFiles();
      _directoryname->setText(fileNames.at(0));
    }
}

void LibraryDialog::ok_clicked()
{
  //stor the directory and the filename into the Library check to see
  //if null
  _library_pointer->set_library_name(_libraryname->text());
  _library_pointer->set_library_directory(_directoryname->text());
  accept();
}



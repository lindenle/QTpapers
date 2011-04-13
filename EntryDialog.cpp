#include "EntryDialog.h"
#include <QHBoxLayout>
#include <QFileDialog>
#include <QProcess>

EntryDialog::EntryDialog(QWidget * parent) :
  QDialog(parent)
{
  setWindowTitle(tr("New Entry"));

  _title = new QLabel(tr("Title"));
  _title_edit = new QLineEdit;
  _title->setBuddy(_title_edit);

  _author = new QLabel(tr("Author"));
  _author_edit = new QLineEdit;
  _author->setBuddy(_author_edit);

  _file = new QLabel(tr("File"));
  _file_edit = new QLineEdit;
  _file->setBuddy(_file_edit);

  _date = new QLabel(tr("Date"));
  _date_edit = new QDateEdit;
  _date_edit->setCalendarPopup(true);
  _date->setBuddy(_date_edit);

  _search = new QPushButton(tr("Search"));
  _open = new QPushButton(tr("Open"));
  
  connect(_search, SIGNAL(clicked()), this, SLOT(open_file_search()));
  connect(_open, SIGNAL(clicked()), this, SLOT(open_file()));

  QWidget * author = new QWidget;
  QHBoxLayout * author_layout = new QHBoxLayout;
  author_layout->addWidget( _author);
  author_layout->addWidget( _author_edit);
  author_layout->addWidget( _search);
  author->setLayout(author_layout);

  QWidget * title = new QWidget;
  QHBoxLayout * title_layout = new QHBoxLayout;
  title_layout->addWidget( _title);
  title_layout->addWidget( _title_edit);
  title_layout->addWidget( _search);
  title->setLayout(title_layout);

  QWidget * date = new QWidget;
  QHBoxLayout * date_layout = new QHBoxLayout;
  date_layout->addWidget( _date);
  date_layout->addWidget( _date_edit);
  date->setLayout(date_layout);

  QWidget * file = new QWidget;
  QHBoxLayout * file_layout = new QHBoxLayout;
  file_layout->addWidget( _file);
  file_layout->addWidget( _file_edit);
  file_layout->addWidget( _search);
  file_layout->addWidget( _open);
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
  _topdown->addWidget(title);
  _topdown->addWidget(author);
  _topdown->addWidget(date);
  _topdown->addWidget(file);
  _topdown->addWidget(buttons);
  setLayout(_topdown);
  //here we need to set some signals
}

void EntryDialog::open_file_search()
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

void EntryDialog::ok_clicked()
{
 
  //store the auth,title and file
  _entry_pointer->set_author(_author_edit->text());
  _entry_pointer->set_title(_title_edit->text());
  _entry_pointer->set_date(_date_edit->date());
  _entry_pointer->set_file_name(_file_edit->text());
}

void EntryDialog::set_entry(Entry * e)
{
  _entry_pointer = e;
  if ( _entry_pointer->get_title() != "" ||
       _entry_pointer->get_author() != "" )
    setWindowTitle(tr("Edit Entry"));	 
  _author_edit->setText(_entry_pointer->get_author());
  _title_edit->setText(_entry_pointer->get_title());
  _file_edit->setText(_entry_pointer->get_file_name());
  _date_edit->setDate(_entry_pointer->get_date());
}

void EntryDialog::open_file()
{
  if ( _file_edit->text() == "" )
    return;
  QString program("/usr/bin/xpdf");
  QStringList arguments;
  arguments << _file_edit->text();
  QProcess pdfview(this);

  pdfview.startDetached(program,arguments);
  pdfview.waitForStarted();
}

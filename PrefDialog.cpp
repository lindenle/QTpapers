#include "PrefDialog.h"
#include <QHBoxLayout>
#include <QFileDialog>
#include <QProcess>
#include <QSettings>

PrefDialog::PrefDialog(QWidget * parent) :
  QDialog(parent)
{
  setWindowTitle(tr("Preferences"));

  _viewer = new QLabel(tr("PDF Viewer"));
  _viewer_edit = new QLineEdit;
  _viewer->setBuddy(_viewer_edit);
  _search_viewer = new QPushButton(tr("Search"));  
  _converter = new QLabel(tr("PDF Converter"));
  _converter_edit = new QLineEdit;
  _converter->setBuddy(_converter_edit);
  _search_converter = new QPushButton(tr("Search"));  

  // a way to map the signals
  _mapper = new QSignalMapper(this);
  _mapper->setMapping(_search_viewer,"viewer");
  _mapper->setMapping(_search_converter,"converter");

  connect(_search_viewer, SIGNAL( clicked() ), _mapper, SLOT( map() ) );
  connect(_search_converter, SIGNAL( clicked() ), _mapper, SLOT( map() ) );
  connect(_mapper,SIGNAL( mapped( QString ) ), this, SLOT( open_search( QString) ) );
 
  QSettings settings("LindenLevy", "QtPapers");
  //read back in the settings
  settings.beginGroup("Collection Preferences");
  _viewer_edit->setText( settings.value("PDF Viewer").toString());
  _converter_edit->setText( settings.value("PDF Converter").toString());
  settings.endGroup();

  QWidget * viewer = new QWidget;
  QHBoxLayout * viewer_layout = new QHBoxLayout;
  viewer_layout->addWidget( _viewer);
  viewer_layout->addWidget( _viewer_edit);
  viewer_layout->addWidget( _search_viewer);
  viewer->setLayout(viewer_layout);

  QWidget * converter = new QWidget;
  QHBoxLayout * converter_layout = new QHBoxLayout;
  converter_layout->addWidget( _converter);
  converter_layout->addWidget( _converter_edit);
  converter_layout->addWidget( _search_converter);
  converter->setLayout(converter_layout);

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
  _topdown->addWidget(viewer);
  _topdown->addWidget(converter);
  _topdown->addWidget(buttons);
  setLayout(_topdown);
  //here we need to set some signals
}

void PrefDialog::ok_clicked()
{
  //store the new settings into
  QSettings settings("LindenLevy", "QtPapers");
  settings.beginGroup("Collection Preferences");
  QDir viewer_directory(_viewer_edit->text());
  settings.setValue("PDF Viewer", viewer_directory.absolutePath());
  QDir converter_directory(_converter_edit->text());
  settings.setValue("PDF Converter", converter_directory.absolutePath());
  settings.endGroup();
  close();
}

void PrefDialog::open_search(QString who)
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
      // need to know who called me so I can set the value in the correct box
      if ( who == "converter" )
	_converter_edit->setText(fileNames.at(0));
      else
	_viewer_edit->setText(fileNames.at(0));
    }  
}


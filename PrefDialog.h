#ifndef __PREFDIALOG_H__
#define __PREFDIALOG_H__

#include <QDateEdit>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSignalMapper>
#include <QTextStream>


class PrefDialog : public QDialog
{
  Q_OBJECT

 public:

  PrefDialog(QWidget * parent = 0, QString extra_text="");

 public slots:
  void open_search(QString who);
  void ok_clicked();

 protected:
  
  QLabel * _title;
  QLineEdit * _title_edit;
  QLabel * _author;
  QLineEdit * _author_edit;
  QLabel * _date;
  QDateEdit * _date_edit;
  QLabel * _viewer;
  QLineEdit * _viewer_edit;
  QLabel * _converter;
  QLineEdit * _converter_edit;
  QSignalMapper * _mapper;
  QPushButton * _search_viewer;
  QPushButton * _search_converter;
  QPushButton * _open;
  QPushButton * _ok;
  QPushButton * _cancel;
  QVBoxLayout * _topdown;
  QTextStream _stdout;
};

#endif // __PREFDIALOG_H__

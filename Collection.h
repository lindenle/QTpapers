#ifndef __COLLECTION_H__
#define __COLLECTION_H__

#include <QtGui>
#include <QMainWindow>
#include <QActionGroup>
#include <QAction>
#include <QToolBar>
#include <QListWidget>
#include <QLineEdit>
#include <QTextStream>
#include <QLabel>
#include <QSplitter>
#include <QtNetwork>

#include "Library.h"
#include "Paper.h"

#include "LibraryList.h"
class LibraryList;

#include "PaperList.h"
class PaperList;

#include "RssWidget.h"
class RssWidget;

class Collection: public QMainWindow
{

  Q_OBJECT

 public:

  Collection();


 private slots:

  void about();
  void new_library();
  void save_library();
  void open_library();
  void delete_library();
  void modify_preferences(QString text="");
  void new_paper();
  void edit_paper();
  void delete_paper();
  void open_paper();
  void find_paper();
  void import_library(){;}
  void import_paper();
  void reset_find();
  void select_library(QListWidgetItem *);
  void select_paper(int, int);
  void check_url(const QUrl& );
  void download_finished(QNetworkReply*);
  void scan_directory_and_import_papers();

 private:

  void open_library(const QString & );
  void closeEvent(QCloseEvent *event);

  void update_paper_list(QTableWidget * );
  void update_library_list();
  void update_paper_list();
  void clear_paper_list();

  void readSettings();
  void writeSettings();

  void add_paper_to_list(const Entry & paper, QTableWidget * list );

  QActionGroup * actionGroup; 

  QNetworkAccessManager * _manager;

  QAction *libraryOpen;    
  QAction *librarySave;    
  QAction *libraryNew;    
  QAction *libraryDelete;    
  QAction *libraryImport;    
  QAction *preferences;    
  QAction *exit;    
  QAction *libraryChanged;    
  QAction *openConfiguration;    
  QAction * paperNew;
  QAction * paperEdit;
  QAction * paperDelete;
  QAction * paperOpen;
  QAction * paperImport;
  QAction * paperScanDirectory;
  QAction * talkNew;
  QAction * talkImport;
  QAction *showAbout;    
  
  QLineEdit * _find_edit;
  QComboBox * _find_type;
  QAction * paperFind;

  LibraryList * _library_list;
  PaperList * _paper_list;
  QTextBrowser * _abstract_box;
  RssWidget * _rss_box;
  QSplitter * _top_layout;
  QSplitter * _bot_layout;
  QSplitter * _total_layout;


  QToolBar *paperToolBar;

 protected:
  
  QAction * addChoice(QString name, QString text);
  Library * _current_library;
  std::vector<Library *> _libraries;
  QTextStream _stdout;

};

#endif //__COLLECTION_H__


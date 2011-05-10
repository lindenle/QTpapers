#include <QtGui>
#include <QMenu>
#include <QMenuBar>
#include <QPalette>
#include <QHBoxLayout>
#include <QSplitter>
#include <QVBoxLayout>
#include <QStringList>
#include <QHeaderView>
#include <QMessageBox>
#include <QSettings>
#include <QVariant>
#include <QWebPage>
#include <QWebFrame>

#include <iostream>

#include "Collection.h"
#include "PrefDialog.h"
#include "ImporterDialog.h"
#include "ArxivParser.h"
#include "SpiresParser.h"

Collection::Collection() :
  _current_library(0),
  _stdout(stdout)
{

  actionGroup = new QActionGroup(this);

  statusBar();

  QWidget::setWindowTitle( "Qt Papers" );

  QMenu* fileMenu = new QMenu("&File", this);    

  libraryOpen = addChoice("libraryOpen", "Open Library");
  libraryOpen->setStatusTip("Open a library");
  libraryOpen->setEnabled(true);
  libraryOpen->setIcon(QIcon(":/images/libopen.png"));
  connect(libraryOpen, SIGNAL(triggered()), this, SLOT(open_library()));
  fileMenu->addAction(libraryOpen);

  libraryNew = addChoice("libraryNew", "New Library");
  libraryNew->setStatusTip("Create a new library");
  libraryNew->setEnabled(true);
  libraryNew->setIcon(QIcon(":/images/document2.png"));
  connect(libraryNew, SIGNAL(triggered()), this, SLOT(new_library()));
  fileMenu->addAction(libraryNew);


  librarySave = addChoice("librarySave", "Save Library");
  librarySave->setStatusTip("Save the library");
  librarySave->setEnabled(true);
  librarySave->setIcon(QIcon(":/images/save.png"));
  connect(librarySave, SIGNAL(triggered()), this, SLOT(save_library()));
  fileMenu->addAction(librarySave);

  libraryDelete = addChoice("libraryDelete", "Delete Library");
  libraryDelete->setStatusTip("Delete library");
  libraryDelete->setEnabled(true);
  libraryDelete->setIcon(QIcon(":/images/libremove.png"));
  connect(libraryDelete, SIGNAL(triggered()), this, SLOT(delete_library()));
  fileMenu->addAction(libraryDelete);

  libraryImport = addChoice("libraryImport", "Import Library");
  libraryImport->setStatusTip("Import library");
  libraryImport->setEnabled(true);
  libraryImport->setIcon(QIcon(":/images/import.png"));
  connect(libraryImport, SIGNAL(triggered()), this, SLOT(scan_directory_and_import_papers()));

  fileMenu->addAction(libraryImport);

  preferences = addChoice("preferences", "Preferences");
  preferences->setStatusTip("Preferences");
  preferences->setEnabled(true);
  preferences->setIcon(QIcon(":/images/pref.png"));
  connect(preferences, SIGNAL(triggered()), this, SLOT(modify_preferences()));
  fileMenu->addAction(preferences);
  
  exit = addChoice("exit", "Exit");
  exit->setStatusTip("Exit");
  exit->setEnabled(true);
  exit->setIcon(QIcon(":/images/exit.png"));
  connect(exit, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));
  fileMenu->addAction(exit);

  QMenu* paperMenu = new QMenu("&Paper", this);    
  paperImport = addChoice("paperImport", "Import Paper");
  paperImport->setStatusTip("Import a paper");
  paperImport->setEnabled(false);
  paperImport->setIcon(QIcon(":/images/import.png"));

  paperScanDirectory = addChoice("paperScanDirectory", "Paper Scan");
  paperScanDirectory->setIcon(QIcon(":/images/scan.png"));
  paperScanDirectory->setStatusTip("Scan for papers.");
  paperScanDirectory->setEnabled(true);

  talkImport = addChoice("talkImport", "Import Talk");
  talkImport->setStatusTip("Import a talk");
  talkImport->setEnabled(false);

  paperNew = addChoice("paperNew", "New Paper");
  paperNew->setStatusTip("New paper");
  paperNew->setEnabled(true);
  paperNew->setIcon(QIcon(":/images/new.png"));

  paperDelete = addChoice("paperDelete", "Delete Paper");
  paperDelete->setStatusTip("Delete paper");
  paperDelete->setIcon(QIcon(":/images/remove.png"));
  paperDelete->setEnabled(false);

  paperEdit = addChoice("paperEdit", "Edit Paper");
  paperEdit->setStatusTip("Edit paper");
  paperEdit->setEnabled(false);
  paperEdit->setIcon(QIcon(":/images/edit.png"));

  paperOpen = addChoice("paperOpen", "Open Paper");
  paperOpen->setStatusTip("Open paper");
  paperOpen->setEnabled(false);
  paperOpen->setIcon(QIcon(":/images/open.png"));

  talkNew = addChoice("talkNew", "New Talk");
  talkNew->setStatusTip("New talk");
  talkNew->setEnabled(false);

  connect(paperNew, SIGNAL(triggered()), this, SLOT(new_paper()));
  connect(paperEdit, SIGNAL(triggered()), this, SLOT(edit_paper()));
  connect(paperDelete, SIGNAL(triggered()), this, SLOT(delete_paper()));
  connect(paperOpen, SIGNAL(triggered()), this, SLOT(open_paper()));
  connect(paperImport, SIGNAL(triggered()), this, SLOT(import_paper()));
  // need to implement this

  paperMenu->addAction(paperNew);
  paperMenu->addAction(paperImport);
  paperMenu->addAction(paperEdit);
  paperMenu->addAction(paperDelete);
  paperMenu->addAction(paperOpen);
  paperMenu->addAction(paperScanDirectory);
  paperMenu->addAction(talkNew);
  paperMenu->addAction(talkImport);




  QMenu* helpMenu = new QMenu("&Help", this);    
  showAbout = addChoice("showAbout","About");
  showAbout->setStatusTip("About");
  showAbout->setEnabled(true);
  showAbout->setIcon(QIcon(":/images/about.png"));
  connect(showAbout, SIGNAL(triggered()), this, SLOT(about()));
  helpMenu->addAction(showAbout);

  //Add a menu bar
  menuBar()->addMenu(fileMenu);
  menuBar()->addMenu(paperMenu);
  menuBar()->addMenu(helpMenu);

  //button to trigger find box
  paperFind = new QAction("Find Paper",this);
  paperFind->setStatusTip("Find paper");
  paperFind->setEnabled(true);
  paperFind->setIcon(QIcon(":/images/find.png"));
  connect(paperFind, SIGNAL(triggered()), this, SLOT(find_paper()));

  //add a tool bar
  QPushButton * find_clear = new QPushButton();
  find_clear->setStatusTip("Find paper");
  find_clear->setEnabled(true);
  find_clear->setIcon(QIcon(":/images/clear.png"));
  connect(find_clear, SIGNAL(clicked()), this, SLOT(reset_find()));

  QLabel * find = new QLabel();
  find->setText("Find: ");
  find->setLayoutDirection(Qt::LeftToRight);
  QLabel * in = new QLabel();
  in->setText(" in ");
  _find_edit = new QLineEdit;
  _find_edit->setFixedSize(_find_edit->sizeHint());
  _find_edit->setLayoutDirection(Qt::LeftToRight);
  connect(_find_edit, SIGNAL(returnPressed()), this, SLOT(find_paper()));

  _find_type = new QComboBox();
  QStringList find_names;
  find_names << "Author" << "Title" << "Abstract" << "Any";
  _find_type->insertItems(0,find_names);
  _find_type->setLayoutDirection(Qt::LeftToRight);
  find->setBuddy(_find_edit);
  paperToolBar = addToolBar(tr("Paper"));
  paperToolBar->setLayoutDirection(Qt::RightToLeft);
  paperToolBar->addAction(paperFind);
  paperToolBar->addWidget(_find_type);
  paperToolBar->addWidget(in);
  paperToolBar->addWidget(find_clear);
  paperToolBar->addWidget(_find_edit);
  paperToolBar->addWidget(find);
  paperToolBar->addAction(paperDelete);
  paperToolBar->addAction(paperEdit);
  paperToolBar->addAction(paperNew);
  paperToolBar->addAction(paperOpen);
  paperToolBar->addAction(paperImport);
  paperToolBar->addAction(paperScanDirectory);

  _rss_box = new RssWidget;
  connect(_rss_box, SIGNAL(urlChanged(const QUrl& )), 
	  this, SLOT(check_url(const QUrl& )));

  QAction * rssForward  = new QAction("rssForward",this);
  rssForward->setStatusTip("Forward");
  rssForward->setEnabled(true);
  rssForward->setIcon(QIcon(":/images/forward.png"));
  connect(rssForward, SIGNAL(triggered()), _rss_box, SLOT(forward()));
  paperToolBar->addAction(rssForward);

  QAction * rssBack  = new QAction("rssBack",this);
  rssBack->setStatusTip("Back");
  rssBack->setEnabled(true);
  rssBack->setIcon(QIcon(":/images/back.png"));
  connect(rssBack, SIGNAL(triggered()), _rss_box, SLOT(back()));
  paperToolBar->addAction(rssBack);

  //Set up a central widget that will have a layout in it

  _library_list = new LibraryList(this,this);
  QFont font;
  font.setBold(true);
  font.setCapitalization(QFont::SmallCaps);
  _library_list->setFont(font);
  connect(_library_list, SIGNAL(itemClicked( QListWidgetItem *)), this, SLOT(select_library(QListWidgetItem *)));
  
  
  _abstract_box = new QTextBrowser();
  _abstract_box->setAlignment(Qt::AlignJustify);
  _abstract_box->setFontWeight(QFont::DemiBold);
  _abstract_box->setPlainText("No Paper Selected");
  _paper_list = new PaperList(this,this);

  QStringList sl;
  // The following seems like a non-intuitive operator
  // overload but that is how they do it...
  sl << "Author" << "Title" << "Date";
  _paper_list->setColumnCount(3);
  _paper_list->setHorizontalHeaderLabels(sl);
  _paper_list->setAlternatingRowColors(true);
  _paper_list->horizontalHeader()->setStretchLastSection(true);
  _paper_list->verticalHeader()->hide();
  //  _paper_list->setSortingEnabled(true);
  //need to make the paper_list its own class for drag and drop
  //  _paper_list->setAcceptDrops(true);

  connect(_paper_list, SIGNAL(cellClicked(int , int )), 
	  this, SLOT(select_paper(int, int)));
  //  update_paper_list();
  

  _top_layout = new QSplitter();  
  _top_layout->addWidget(_library_list);
  _top_layout->addWidget(_paper_list);
  _top_layout->setStretchFactor(0,1);
  _top_layout->setStretchFactor(1,3);
  _top_layout->setContentsMargins(0,0,5,0);
  _top_layout->setOrientation(Qt::Horizontal);

  _bot_layout = new QSplitter();  
  _bot_layout->addWidget(_abstract_box);
  _bot_layout->addWidget(_rss_box);
  _bot_layout->setContentsMargins(0,0,0,0);
  _bot_layout->setStretchFactor(0,1);
  _bot_layout->setStretchFactor(1,3);
  _bot_layout->setOrientation(Qt::Horizontal);

  _total_layout = new QSplitter();
  _total_layout->addWidget(_top_layout);
  _total_layout->addWidget(_bot_layout);
  _total_layout->setStretchFactor(0,1);
  _total_layout->setStretchFactor(1,3);
  _total_layout->setOrientation(Qt::Vertical);

  //this splitter window is my central widget
  setCentralWidget(_total_layout);


  QPalette  palette;
  palette.setColor(QPalette::Background,Qt::white);
  centralWidget()->setPalette(palette);
  centralWidget()->setAutoFillBackground(true);
  centralWidget()->setWindowOpacity(0.8);
  centralWidget()->setMinimumSize(300, 200);
  setMinimumSize(700, 500);

  readSettings();
}
//----------------------------------------------------------------
// Factory method for creating QActions initialized in a uniform way
QAction * Collection::addChoice(QString name, QString text) 
{
  QAction* retval = new QAction(text, this);
  retval->setObjectName(name);
  retval->setCheckable(false);
  actionGroup->addAction(retval);
  return retval;
}

//----------------------------------------------------------------
void Collection::about()
{
  QMessageBox::about(this, tr("About QT Papers"),
		     tr("This program is released under the GPL.\n"
			"Author: L. A. Linden Levy.\n"
			"Email: lindenle@gmail.com "));
}
//----------------------------------------------------------------
void Collection::new_library()
{
  _current_library = new Library();
  _libraries.push_back(_current_library);
  if ( _current_library->open_library_dialog()  == QDialog::Accepted )
    {
      _stdout << "We should have some data in here now: " 
	      << _current_library->get_library_file() << endl;

      _stdout.flush();
      new QListWidgetItem(  _current_library->get_library_name() , _library_list);
    }
  else 
    {
      //We did not accept so dump him
      _libraries.pop_back();
      delete _current_library;
    }
  
}
//----------------------------------------------------------------
void Collection::new_paper()
{
  //we should not try to add a paper if no current library;
  if ( !_current_library )
    {
      QMessageBox::about(this, tr("Error"),
			 tr("Error: you have no Libraries defined\n"
			    "you cannot create a new paper"));
      return;
    }
  Paper * paper = new Paper();
  if ( paper->open_new_dialog()  == QDialog::Accepted )
    {
      _stdout << "We should have some data in here now: " 
	      << paper->get_author() << endl;
      _stdout.flush();
      //add the entry to the library
      _current_library->add_entry(paper);
      //add the entry to the list
      add_paper_to_list(*paper,_paper_list);
      update_library_list();
    }
}
//----------------------------------------------------------------
void Collection::edit_paper()
{
  //Need a mechanism to have the current paper?
  Paper * paper = dynamic_cast<Paper *>(_current_library->get_current_entry());
  if ( ! paper )
    {
      Entry * entry = _current_library->get_current_entry();
      if ( entry->open_new_dialog()  == QDialog::Accepted )
	{
	  update_paper_list();
	}
    }
  else if ( paper->open_new_dialog()  == QDialog::Accepted )
    {
      update_paper_list();
    }
}
//----------------------------------------------------------------

//----------------------------------------------------------------
void Collection::delete_paper()
{

  _stdout << "Short list " << _current_library->get_current_entry()->get_author_short() << endl;
  QString question(tr("Do you want to delete the entry with\n"
		   "title %1 \n"
		      "and author %2").arg( _current_library->get_current_entry()->get_title(),
					    _current_library->get_current_entry()->get_author_short() ) );
  if ( QMessageBox::warning(this,"Delete Paper",
			    question,
			    QMessageBox::Ok|QMessageBox::Cancel) == QMessageBox::Ok )
    {
      paperEdit->setEnabled(false);
      paperDelete->setEnabled(false);
      paperOpen->setEnabled(false);
      _current_library->delete_current_entry();
      update_paper_list();
      update_library_list();
    }
  
}
//----------------------------------------------------------------
void Collection::import_paper()
{
  //we should not try to add a paper if no current library;
  if ( !_current_library )
    {
      QMessageBox::about(this, tr("Error"),
			 tr("Error: you have no Libraries defined\n"
			    "you cannot create a new paper"));
      return;
    }
  QWebPage * page = _rss_box->page();
  
  QWebFrame * frame = page->mainFrame();

  //now create a new paper and parse out the values we want.
  _parser->setData(frame->toHtml());
  _stdout << "Collection::import_paper title" << _parser->getTitle() << endl;
  _stdout << "Collection::import_paper authors" << _parser->getAuthors() << endl;

  Paper * paper = new Paper();
  paper->set_title(_parser->getTitle());
  paper->set_author(_parser->getAuthors());
  paper->set_abstract(_parser->getAbstract());
  paper->set_date(_parser->getDate());
  paper->set_arxiv_number(_parser->getNumber());

  //Download the damn thing
  _manager = new QNetworkAccessManager(this);
  _manager->get(QNetworkRequest(_parser->getDownloadLocation());
  connect(_manager, SIGNAL(finished(QNetworkReply*)),
  	  this, SLOT(download_finished(QNetworkReply*)));

  QDir directory(_current_library->get_library_directory()+"/"+_parser->getPaperName());

  _stdout << "Collection::import_paper " <<  directory.absolutePath() << endl; 

  paper->set_file_name(directory.absolutePath());
  
  //add the entry to the library
  _current_library->add_entry(paper);

  //add the entry to the list
  add_paper_to_list(*paper,_paper_list);
  update_library_list();

}

//----------------------------------------------------------------a

void Collection::update_library_list()
{
  _library_list->clear();
  std::vector<Library *>::iterator iter = _libraries.begin();
  for (; iter != _libraries.end(); iter++)
    {
      QString label((*iter)->get_library_name());
      label.append(tr(" (%1)").arg( (*iter)->get_entry_list().size() ));

      new QListWidgetItem( label , _library_list);
      
    }
  //better set a default current library befor calling update papers
  if ( !_current_library )
    {
      if ( _libraries.size() )
	_current_library = _libraries.at(0);
      else
	return;
    }
  update_paper_list();

}
//----------------------------------------------------------------
void Collection::clear_paper_list()
{
 //start by clearing out all the papers
  _paper_list->clearContents();
  for (int irow=_paper_list->rowCount()-1; irow >= 0; --irow)
    _paper_list->removeRow(irow);
}
//----------------------------------------------------------------
void Collection::update_paper_list()
{

  clear_paper_list();

  //loop over the paper list and call add_paper_to_list
  std::vector<Entry *> list = _current_library->get_entry_list();
  std::vector<Entry *>::const_iterator iter = list.begin(); 
  for(; iter != list.end(); iter++ )
    {
      add_paper_to_list( *(*iter), _paper_list );
    }

}
//----------------------------------------------------------------
void Collection::select_library(QListWidgetItem * current_item)
{
  
  //need to loop over the lib and set the correct one to current
  std::vector<Library *>::const_iterator iter = _libraries.begin();
  for (; iter != _libraries.end(); iter++)
    {
      if ( (*iter)->get_library_name() == current_item->text().left(current_item->text().lastIndexOf("(")-1 ) )
	{
	  _current_library = *iter;
	}
    }
  _stdout << " Linked up:  "
	  << _current_library->get_library_name() << endl;
  _stdout.flush();
  update_paper_list();
  QString temp;
  temp = "Library: " + _current_library->get_library_name() + " selected ";
  statusBar()->showMessage(tr(temp.toAscii()));

}

//----------------------------------------------------------------
void Collection::select_paper(int row, int column)
{
  //here we need to change the abstract in the abstract box if we
  //select this entry
  _paper_list->selectRow(row);
  _stdout << "Collection::select_paper" << row << " " << column << endl;
  std::vector<Entry *> list = _current_library->get_entry_list();
  std::vector<Entry *>::const_iterator iter = list.begin(); 
  for(; iter != list.end(); iter++ )
    {
      if ( ( (*iter)->get_author() == _paper_list->item(row,0)->text() ) &&
	   ( (*iter)->get_title() == _paper_list->item(row,1)->text() ) )
	{
	  _stdout << "Match!"  << endl;

	  _current_library->set_current_entry( *iter );
	  
	  //here we should disable the open paper if the file does not
	  //exist
	  QDir directory(_current_library->get_current_entry()->get_file_name());
	  QFile tmpfile(directory.absolutePath());
	  _stdout << "Collection::select_paper " << directory.absolutePath() << endl;
	  paperEdit->setEnabled(true);
	  paperDelete->setEnabled(true);
	  if ( tmpfile.exists() )
	    {
	      paperOpen->setEnabled(true);
	    }
	  else
	    {
	      paperOpen->setEnabled(false);
	    }
	  Paper * p_cast = dynamic_cast<Paper *>((*iter));
	  if ( p_cast )
	    {
	      _stdout << "Cast!"  << endl;
	      _stdout << p_cast->get_abstract()  << endl;
	      QString temp = p_cast->get_abstract();
	      temp.replace(QRegExp("\n"), " ");
	      _abstract_box->setPlainText(temp);

	      temp = "Library: " + _current_library->get_library_name() + " selected, Paper title: " + p_cast->get_title();
	      statusBar()->showMessage(tr(temp.toAscii()));
	    }

	  break;
	}
    }
}
//--------------------------------------------------
void Collection::open_paper()
{
  if ( _current_library )
    {
      if ( _current_library->get_current_entry() )
	{
	  QDir directory(_current_library->get_current_entry()->get_file_name());
	  QFile tmpfile( directory.absolutePath());
	  
	  if ( tmpfile.exists() )
	    {
	      QSettings settings("LindenLevy", "QtPapers");
	      settings.beginGroup("Collection Preferences");
	      //make sure we have this preference
	      if ( settings.value("PDF Viewer").toString() == "" )
		{
		  modify_preferences("No viewer defined");
		  return;
		}
	      QDir pdf_view(settings.value("PDF Viewer").toString());
	      
	       settings.endGroup();
	       _stdout << " Viewer >>>> " << pdf_view.absolutePath() << endl;
	       
	       //check to see if viewer exists
	       
	       if ( ! QFile::exists(pdf_view.absolutePath()) )
		 {
		   //if it does not exist throw a warning and open the
		   //prefs dialog
		   modify_preferences("Viewer does not exist");
		   return;
		 }
	       


	      QString program(pdf_view.absolutePath());
	      
	      QStringList arguments;
	   
	      arguments << directory.absolutePath();
	      _stdout << "Collection::open_paper " << directory.absolutePath() << endl;
	      QProcess pdfview(this);
	      pdfview.startDetached(program,arguments);
	      pdfview.waitForStarted();
	    }
	}
    }
}
//--------------------------------------------------
void Collection::find_paper()
{
  QRegExp rx("*"+_find_edit->text()+"*");
  rx.setPatternSyntax(QRegExp::Wildcard);

  _stdout << "Search string: " << _find_edit->text() << endl;
  _stdout << "Find type: " << _find_type->currentText() << endl;

  clear_paper_list();

  std::vector<Library *>::const_iterator iter = _libraries.begin();
  for (; iter != _libraries.end(); iter++)
    {
      std::vector<Entry *> entry_list = (*iter)->get_entry_list();
      std::vector<Entry *>::const_iterator iter2 = entry_list.begin();
      for (; iter2 != entry_list.end(); iter2++)
	{
	  if ( _find_type->currentText() == "Author")
	    {
	      _stdout << "Author Check: " << (*iter2)->get_author() << endl;
	      if ( rx.exactMatch((*iter2)->get_author()) )
		{
		  _stdout << "Matched!" << endl;
		  add_paper_to_list(*(*iter2),_paper_list);
		}
	    }
	  else if ( _find_type->currentText() == "Title")
	    {
	      _stdout << "Title Check: " << (*iter2)->get_author() << endl;
	      if ( rx.exactMatch((*iter2)->get_title()) )
		{
		  _stdout << "Matched!" << endl;
		  add_paper_to_list(*(*iter2),_paper_list);
		}
	    }
	  else if ( _find_type->currentText() == "Abstract")
	    {
	      _stdout << "Abstract Check: " << (*iter2)->get_author() << endl;
	      Paper * p_cast = dynamic_cast<Paper *>(*iter2);
	      if ( p_cast )
		{
		  if ( rx.exactMatch(p_cast->get_abstract()) )
		    {
		      _stdout << "Matched!" << endl;
		      add_paper_to_list(*(*iter2),_paper_list);
		    }
		}
	    }
	  else if ( _find_type->currentText() == "Any")
	    {
	      _stdout << "Any Check: " << (*iter2)->get_author() << endl;
	      bool first_match=false;
	      if ( rx.exactMatch((*iter2)->get_author()) ||
		   rx.exactMatch((*iter2)->get_title())  )
		{
		  _stdout << "Matched!" << endl;
		  first_match=true;
		  add_paper_to_list(*(*iter2),_paper_list);
		}
	      
	      Paper * p_cast = dynamic_cast<Paper *>(*iter2);
	      if ( p_cast && ! first_match)
		{
		  if ( rx.exactMatch(p_cast->get_abstract()) )
		    {
		      _stdout << "Matched!" << endl;
		      add_paper_to_list(*(*iter2),_paper_list);
		    }
		}
	    }
	  else
	    {
	      _stdout << "Error: should not be here!" << endl;
	    }
	}
    }
}
//--------------------------------------------------
void Collection::reset_find()
{
  _find_edit->setText("");
  update_paper_list();
}
//--------------------------------------------------

void Collection::add_paper_to_list(const Entry& paper, QTableWidget * list )
{
  QTableWidgetItem * date = new QTableWidgetItem(tr("%1").arg(paper.get_date().toString()));
  //  list
  QTableWidgetItem * title = new QTableWidgetItem(tr("%1").arg(paper.get_title()));
//   //  list
  QTableWidgetItem * auth = new QTableWidgetItem(tr("%1").arg(paper.get_author()));
  int row = list->rowCount();
  //  _stdout << "Number of rows:" << row << endl;
  list->insertRow(row);
  list->setItem(row,0,auth);
  list->setItem(row,1,title);
  list->setItem(row,2,date);
  return;
}

void Collection::save_library()
{
  _stdout << "Library Saved" << endl;
  _current_library->close_library();
  //  delete _current_library;
  //  update_library_list();
}
void Collection::delete_library()
{
  QString question(tr("Do you want to delete the entry with\n"
		      "name %1 \n").arg(_current_library->get_library_name()));
  if ( QMessageBox::warning(this,"Delete Library",
			    question,
			    QMessageBox::Ok|QMessageBox::Cancel) 
       == QMessageBox::Ok )
    {
      std::vector<Library *>::iterator iter = _libraries.begin();
      for (; iter != _libraries.end(); iter++)
	if ( (*iter) == _current_library )
	  {
	    _current_library->remove_library_file();
	    _libraries.erase(iter);
	    _current_library=0;
	    update_library_list();
	  }
    }
  
}

void Collection::open_library()
{
  
  QFileDialog dialog(this);
  dialog.setFileMode(QFileDialog::ExistingFile);
  dialog.setViewMode(QFileDialog::Detail);
  dialog.hasFocus();
  dialog.show();
  if (dialog.exec())
    {
      open_library(dialog.selectedFiles().at(0));
    }
}
void Collection::open_library(const QString& file)
{
  _current_library = new Library();
  _libraries.push_back(_current_library);
  _current_library->set_library_file(file);
  _stdout << _current_library->get_library_file() << endl;
  if ( _current_library->open_library() )
    update_library_list();
}

void Collection::readSettings()
{
  QSettings settings("LindenLevy", "QtPapers");

  settings.beginGroup("Collection");
  resize(settings.value("size", QSize(700, 500)).toSize());
  move(settings.value("pos", QPoint(200, 200)).toPoint());
  _top_layout->restoreState(settings.value("middle").toByteArray());
  _bot_layout->restoreState(settings.value("middle_bot").toByteArray());
  _total_layout->restoreState(settings.value("total").toByteArray());
  settings.endGroup();

  settings.beginGroup("PaperList");
  _paper_list->setColumnWidth(0,settings.value("leftwidth", 50).toInt());
  _paper_list->setColumnWidth(1,settings.value("centerwidth", 50).toInt());
  settings.endGroup();

  settings.beginGroup("LastLibrary");

  QStringList files(settings.value("files","empty").toStringList());
  _stdout << "Size:" << files.size() << endl;
  if (  files.at(0) != "empty" )
    {
      QStringList::const_iterator iter=files.constBegin();
      
      for (; iter != files.constEnd(); ++iter)
	{
	  _stdout << "Opening" << *iter << endl;
	  open_library(*iter);
	}
    }
  settings.endGroup();
}

void Collection::writeSettings()
{
  QSettings settings("LindenLevy", "QtPapers");

  settings.beginGroup("Collection");
  settings.setValue("size", size());
  settings.setValue("pos", pos());
  settings.setValue("middle", _top_layout->saveState());
  settings.setValue("middle_bot", _bot_layout->saveState());
  settings.setValue("total", _total_layout->saveState());
  settings.endGroup();
  settings.beginGroup("PaperList");
  settings.setValue("leftwidth", _paper_list->columnWidth(0));
  settings.setValue("centerwidth", _paper_list->columnWidth(1));
  settings.endGroup();

  if (_current_library )
    {
      settings.beginGroup("LastLibrary");

      QStringList open_libraries;

      std::vector<Library *>::const_iterator iter = _libraries.begin();

      for ( ; iter != _libraries.end(); iter++ )
	{
	  QDir directory((*iter)->get_library_file());
	  open_libraries << directory.absolutePath();
	}
      settings.setValue("files", open_libraries);
      
      QDir directory(_current_library->get_library_directory());
      settings.setValue("directory", directory.absolutePath());
      settings.endGroup();
    }
}
//----------------------------------------------------------
void Collection::check_url(const QUrl& url)
{
  //make sure we are looking at abstract in order to enable import.
  //here we could have a map of parsers and a parser can answer if it can parse a page or not...

  QString url_str = url.toString();
  _stdout << "Current URl" << url_str << endl;

  if ( url_str.indexOf("http://arxiv.org/abs/") != -1 )
    {
      paperImport->setEnabled(true);
      _parser = static_cast<Parser *>(new ArxivParser());

    }
  else if (  url_str.indexOf("http://www.slac.stanford.edu/spires/find/hep/www?irn") != -1 )
    {
      paperImport->setEnabled(true);
      _parser = static_cast<Parser *>(new SpiresParser());
    }
  else
    {
      paperImport->setEnabled(false);
    }
}
//----------------------------------------------------------
void Collection::download_finished(QNetworkReply* reply)
{
  //save it to a file in the current directory and update the filename
  //in the paper.
  _stdout << reply->url().toString() << endl;
  if ( reply->error() == QNetworkReply::NoError )
    {
      QString url_str = reply->url().toString();
      url_str.replace("http://arxiv.org","");
      url_str.replace(QRegExp(".*/"),"");
      url_str =  url_str + ".pdf";
      _stdout << url_str << endl;
      /// now  open a qfile and write the data....
      QDir directory(_current_library->get_library_directory()+"/"+url_str);
      _stdout << directory.dirName() << endl;;
      QFile pdf(directory.absolutePath());
      _stdout << "Collection::download_finished Saving to: " << directory.absolutePath() << endl;  
      if (!pdf.open(QIODevice::WriteOnly))
	return;

      pdf.write(reply->readAll());
      pdf.close();
    }
  else 
    QMessageBox::about(this, tr("Error"),
		       tr("Error: could not download\n"));

}
//----------------------------------------------------------
void Collection::modify_preferences(QString text)
{
  
  PrefDialog dialog(this, text);
  dialog.show();
  dialog.hasFocus();
  dialog.exec();
  return;
}

//----------------------------------------------------------
void Collection::closeEvent(QCloseEvent *event)
{
  _stdout << "Close Event!" << endl;
  writeSettings();
  //save all the libraries that we have
  std::vector<Library *>::const_iterator iter = _libraries.begin();

  //close all the libraries
  for (; iter != _libraries.end(); iter++)
    {
      (*iter)->close_library();
    }
  event->accept();
}

//----------------------------------------------------------------
void Collection::scan_directory_and_import_papers()
{
  //first we need to ask the peoples some questions
  //like what directory
  ImporterDialog dialog(this);  
  dialog.setFileMode(QFileDialog::DirectoryOnly);
  dialog.setViewMode(QFileDialog::Detail);
  dialog.hasFocus();
  dialog.show();
  QStringList dirNames;
  if ( dialog.exec() )
    {

      dirNames = dialog.selectedFiles();
      _stdout << "Will tryto import from " << dirNames.at(0) << endl;

      //LibraryImporter::do_import(dirNames.at(0))
    }
  
  //lets start by scanning the pdfs and yanking the arxive numers if we can 
  // then we  set the web page in the html widget
  // then we call import! and we are done
}

#include <QDomElement>
#include <QDomDocument>
#include <QTextStream>
#include <QFile>
#include <QMessageBox>

#include "Library.h"
#include "LibraryDialog.h"
#include "Paper.h"

Library::Library():
  _stdout(stdout)
{
}

void Library::set_library_file(const QString& s)
{
  int slash = s.lastIndexOf("/");
  _stdout << s.left(slash)<< endl;
  set_library_directory(s.left(slash));
  QString name(s);
  name.chop(4);
  slash = name.lastIndexOf("/");
  set_library_name( name.mid(slash+1));   
}

int Library::open_library_dialog()
{
  LibraryDialog * dialog = new LibraryDialog();
  dialog->set_library(this);
  dialog->show();
  dialog->hasFocus();
  return dialog->exec();
}

bool Library::close_library()
{
  //  Paper bob;
  QDomDocument document("QtPapers");
  QDomElement library = document.createElement("Library");
  document.appendChild(library);
  library.setAttribute("name",get_library_name());
  
  std::vector<Entry *>::const_iterator iter = _entry_list.begin();

  for ( ; iter !=  _entry_list.end(); iter++ )
    {
      QDomElement entry = document.createElement("Entry");
      library.appendChild(entry);
      entry.setAttribute("author",(*iter)->get_author());
      entry.setAttribute("title",(*iter)->get_title());
      entry.setAttribute("filename",(*iter)->get_file_name());
      entry.setAttribute("date",(*iter)->get_date().toString());
      Paper * p_cast = dynamic_cast<Paper*>((*iter));
      if  ( p_cast )
	{
	  QDomElement abstract = document.createElement("Abstract");
	  entry.appendChild(abstract);
	  QDomText abstract_text = document.createTextNode(p_cast->get_abstract());
	  abstract.appendChild(abstract_text);
	}
      
    }
  
  QFile file( get_library_file() );
  if( !file.open( QIODevice::WriteOnly) )
    return false;
  QTextStream out(&file);
  out << document.toString();
  
  file.close();
  return true;
}

bool Library::open_library()
{
  QDomDocument document("QtPapers");
  
  QFile file( get_library_file() );
  if( !file.open( QIODevice::ReadOnly) )
    return false;
  if ( ! document.setContent(&file) )
    return false;

  QDomElement library = document.documentElement();
  if( library.tagName() != "Library" )
    return false;

  set_library_name(library.attribute("name",""));
  QDomNode paper = library.firstChild();
  while( !paper.isNull() )
    {
      QDomElement paper_element = paper.toElement();
      if( !paper_element.isNull() )
	{
	  if( paper_element.tagName() == "Entry" )
	    {
	      Paper * entry = new Paper();
	      
	      entry->set_title( paper_element.attribute( "title", "" ));
	      entry->set_author( paper_element.attribute( "author", "" ));
	      entry->set_file_name( paper_element.attribute( "filename", "" ));
	      entry->set_date( QDate::fromString(paper_element.attribute( "date", "" )));
	      
	      QDomNode data = paper.firstChild();
	      QDomElement data_element = data.toElement();

	      if ( data_element.tagName() == "Abstract" )
		{
		  //		  _stdout << data_element.text() << endl;
		  entry->set_abstract( data_element.text());

		}

	      _entry_list.push_back(entry);
	    }
	}
      
      paper = paper.nextSibling();
    }	   
  file.close();
  return true;
}

void Library::delete_current_entry()
{
  std::vector<Entry *>::iterator iter=_entry_list.begin();
  for ( ; iter != _entry_list.end(); iter++ )
    {
      if ( (*iter)->get_author() == _current_entry->get_author() &&
	   (*iter)->get_title() == _current_entry->get_title() )
	{
	  _stdout<< "I want to delete"<< (*iter)->get_title() << endl; 
	  _entry_list.erase(iter);
	  break;
	}
    }
  //now set the current entry null
  _current_entry=0;
}

void Library::remove_library_file()
{
  _stdout << "Remove " << get_library_file() << "not implemented yet" << endl;
}

#include <QMenu>

#include "LibraryList.h"


LibraryList::LibraryList(QWidget * parent, Collection * collection) :
  QListWidget(parent),
  _stdout(stdout)
{
  _collection = collection;
  _add_library = new QAction("New Library", this);
  _add_library->setStatusTip("New Library");
  _add_library->setEnabled(true);
  _add_library->setIcon(QIcon(":/images/new.png"));

  _import_library = new QAction("Import Library", this);
  _import_library->setStatusTip("Import Library");
  _import_library->setEnabled(true);
  _import_library->setIcon(QIcon(":/images/import.png"));

  _save_library = new QAction("Save Library", this);
  _save_library->setStatusTip("Save Library");
  _save_library->setEnabled(true);
  _save_library->setIcon(QIcon(":/images/save.png"));

  _delete_library = new QAction("Delete Library", this);
  _delete_library->setStatusTip("Delete Library");
  _delete_library->setEnabled(false);
  _delete_library->setIcon(QIcon(":/images/delete.png"));

  connect(_add_library, SIGNAL(triggered()), _collection , SLOT(new_library()));
  connect(_delete_library, SIGNAL(triggered()), _collection , SLOT(delete_library()));
  connect(_import_library, SIGNAL(triggered()), _collection , SLOT(import_library()));
  connect(_save_library, SIGNAL(triggered()), _collection , SLOT(save_library()));

}

void LibraryList::contextMenuEvent(QContextMenuEvent *event)
{
  QMenu menu(this);
  menu.addAction(_add_library);
  menu.addAction(_delete_library);
  menu.addAction(_import_library);
  menu.addAction(_save_library);
  _stdout<< "LibraryList::contextMenuEvent called"  << endl;
  _stdout<< event->x() << endl;

  menu.exec(event->globalPos());
}

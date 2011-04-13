#ifndef __LIBRARYLIST_H__
#define __LIBRARYLIST_H__

#include <QListWidget>

#include "Collection.h"
class Collection;

class LibraryList : public QListWidget
{
  Q_OBJECT
      
 public:
  LibraryList(QWidget * parent = 0, Collection * collection=0);
  
 protected:
  void contextMenuEvent(QContextMenuEvent *event);

 private:
  QAction * _add_library;
  QAction * _save_library;
  QAction * _delete_library;
  QAction * _import_library;

  Collection * _collection;
  QTextStream _stdout;
};

#endif //__LIBRARYLIST_H__

#ifndef __PAPERLIST_H__
#define __PAPERLIST_H__

#include <QTableWidget>
#include <QAction>
#include <QTextStream>
#include <QContextMenuEvent>

#include "Collection.h"
class Collection;

class PaperList : public QTableWidget
{
  Q_OBJECT
  
 public:
  PaperList(QWidget * parent = 0, Collection * collection=0);

 protected:
  void contextMenuEvent(QContextMenuEvent *event);

 private:
  QAction * _add_paper;
  Collection * _collection;
  QTextStream _stdout;

};

#endif //__PAPERLIST_H__

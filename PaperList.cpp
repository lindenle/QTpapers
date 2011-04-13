#include <QMenu>
#include "PaperList.h"


PaperList::PaperList(QWidget * parent, Collection * collection) :
  QTableWidget(parent),
  _stdout(stdout)
{
  _collection = collection;
  _add_paper = new QAction("New Paper", this);
  _add_paper->setStatusTip("New Paper");
  _add_paper->setEnabled(true);
  _add_paper->setIcon(QIcon(":/images/new.png"));
  connect(_add_paper, SIGNAL(triggered()), _collection , SLOT(new_paper()));

}

void PaperList::contextMenuEvent(QContextMenuEvent *event)
{
  QMenu menu(this);
  menu.addAction(_add_paper);
  _stdout<< "PaperList::contextMenuEvent called"  << endl;
  _stdout<< event->x() << endl;
  menu.exec(event->globalPos());
}

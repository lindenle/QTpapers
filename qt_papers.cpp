#include <QApplication>

#include "Collection.h"

int main (int argc, char* argv[]) 
{ 
  QApplication app(argc, argv); 
  app.setWindowIcon( QIcon(":/images/document2.png") );
  Collection col;
  col.show();
  return app.exec();
}

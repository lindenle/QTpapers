#ifndef __IMPORTER_H__
#define __IMPORTER_H__

#include <QString>

class Importer
{
 public:
  void set_import_name(QString name){_name = name;}
  void set_import_directory(QString dir){_directory=dir;}
 private:
  QString _directory;
  QString _name;
};


#endif //__IMPORTER_H__

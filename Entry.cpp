#include "Entry.h"
#include "EntryDialog.h"

int Entry::open_new_dialog()
{
  EntryDialog * dialog = new EntryDialog();
  dialog->set_entry(this);
  dialog->show();
  dialog->hasFocus();
  return dialog->exec();
}


QString Entry::get_author_short(int number) const
{
  //trim up the author list so the dialog looks nice. might want to
  //just make this the first author. Could search for the first comma
  //and delete after that.

  if ( _author.length() > 25 )
    {
      QString author_short(get_author().section(",",0,number));
      author_short+=" et. al";
      return author_short;
    }
  return get_author();
}


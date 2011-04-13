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

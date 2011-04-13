#include "Paper.h"
#include "PaperDialog.h"

Paper::Paper()
{
}

int Paper::open_new_dialog()
{
  PaperDialog * dialog = new PaperDialog();
  dialog->set_entry(static_cast<Entry*>(this));
  dialog->show();
  dialog->hasFocus();
  return dialog->exec();
}

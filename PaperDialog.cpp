#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>

#include "PaperDialog.h"

PaperDialog::PaperDialog(QWidget * parent):
  EntryDialog(parent)
{
  //can we get the widget stack and add new ones
  _arxiv = new QLabel(tr("arXiv"));
  _arxiv_edit = new QLineEdit;
  _arxiv->setBuddy(_title_edit);

  QWidget * arxiv = new QWidget;
  QHBoxLayout * arxiv_layout = new QHBoxLayout;
  arxiv_layout->addWidget(_arxiv);
  arxiv_layout->addWidget(_arxiv_edit);
  arxiv->setLayout(arxiv_layout);

  _journal = new QLabel(tr("Journal"));
  _journal_edit = new QLineEdit;
  _journal->setBuddy(_journal_edit);

  QWidget * journal = new QWidget;
  QHBoxLayout * journal_layout = new QHBoxLayout;
  journal_layout->addWidget(_journal);
  journal_layout->addWidget(_journal_edit);
  journal->setLayout(journal_layout);

  _abstract = new QLabel(tr("Abstract"));
  _abstract_edit = new QTextEdit;
  _abstract->setBuddy(_abstract_edit);

  QWidget * abstract = new QWidget;
  QHBoxLayout * abstract_layout = new QHBoxLayout;
  abstract_layout->addWidget(_abstract);
  abstract_layout->addWidget(_abstract_edit);
  abstract->setLayout(abstract_layout);
  _topdown->insertWidget(4,arxiv);
  _topdown->insertWidget(5,journal);
  _topdown->insertWidget(6,abstract);
  setLayout(_topdown);
}

void PaperDialog::ok_clicked()
{

  EntryDialog::ok_clicked();

  //store the auth,title and file
  Paper * p_cast = dynamic_cast<Paper *>(_entry_pointer);

  if( p_cast )
    {
      p_cast->set_abstract(_abstract_edit->toPlainText());
      p_cast->set_journal(_journal_edit->text());
      p_cast->set_arxiv_number(_arxiv_edit->text());
    }
  accept();
}
void PaperDialog::set_entry( Entry * e )
{
  EntryDialog::set_entry(e);

  Paper * p_cast = dynamic_cast<Paper *>(_entry_pointer);

  if( p_cast )
    {
      _abstract_edit->setText(p_cast->get_abstract());
      _journal_edit->setText(p_cast->get_journal());
      _arxiv_edit->setText(p_cast->get_arxiv_number());
    }
}

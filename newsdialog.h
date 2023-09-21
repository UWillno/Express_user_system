#ifndef NEWSDIALOG_H
#define NEWSDIALOG_H

#include <QDialog>

namespace Ui {
class NewsDialog;
}

class NewsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewsDialog(QVariantList list,QWidget *parent = nullptr);
    ~NewsDialog();

private:
    Ui::NewsDialog *ui;
    QVariantList m_list;
};

#endif // NEWSDIALOG_H

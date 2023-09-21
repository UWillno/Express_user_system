#ifndef DELIVERYDIALOG_H
#define DELIVERYDIALOG_H

#include <QDialog>

namespace Ui {
class DeliveryDialog;
}

class DeliveryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeliveryDialog(QVariantList list,QWidget *parent = nullptr);
    ~DeliveryDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DeliveryDialog *ui;

    QVariantList m_list;
};

#endif // DELIVERYDIALOG_H

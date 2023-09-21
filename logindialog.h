#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "singleton.h"
#include "sql.h"
#include <QtConcurrent>
#include <QMessageBox>
namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H

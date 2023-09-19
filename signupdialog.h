#ifndef SIGNUPDIALOG_H
#define SIGNUPDIALOG_H

#include <QDialog>
#include "singleton.h"
#include "sql.h"
#include <QtConcurrent>
#include <QMessageBox>
namespace Ui {
class SignUpDialog;
}

class SignUpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SignUpDialog(QWidget *parent = nullptr);
    ~SignUpDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::SignUpDialog *ui;

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // SIGNUPDIALOG_H

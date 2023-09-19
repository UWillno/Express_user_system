#include "signupdialog.h"
#include "ui_signupdialog.h"

#define SQL Singleton<Sql>::GetInstance()

SignUpDialog::SignUpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUpDialog)
{
    ui->setupUi(this);
}

SignUpDialog::~SignUpDialog()
{
    delete ui;
}

void SignUpDialog::on_buttonBox_accepted()
{
    QStringList list;
    if(!ui->lineEdit_user->text().isEmpty())
        list.append(ui->lineEdit_user->text());
    if(!ui->lineEdit_password->text().isEmpty())
        list.append(ui->lineEdit_password->text());
    if(!ui->lineEdit_username->text().isEmpty())
        list.append(ui->lineEdit_username->text());
    bool result = QtConcurrent::run([&]{ return SQL.signUp(list);}).result();
    QMessageBox msgBox;
    if(result){
        msgBox.setText("fffffffffffffff.");
        msgBox.exec();
        close();
    }else{
        msgBox.setText("asdasdasd.");
        msgBox.exec();
    }
}


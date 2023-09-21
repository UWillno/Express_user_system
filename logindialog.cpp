#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_buttonBox_accepted()
{
    if(ui->lineEdit_user->text().isEmpty() || ui->lineEdit_pwd->text().isEmpty())
        QMessageBox::critical(this,"？？","手机号密码不能为空？");
    else{
        bool result = QtConcurrent::run([&]{ return Singleton<Sql>::GetInstance().login(

                                                  ui->lineEdit_user->text(), ui->lineEdit_pwd->text()
                                                  );}).result();
        QMessageBox msgBox;
        if(result){
            msgBox.setText("登录成功！");
            msgBox.exec();
            close();
        }else{
            msgBox.setText("登录失败！");
            msgBox.exec();
        }
    }
}


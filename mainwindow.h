#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "signupdialog.h"
//#include <QCryptographicHash>
#include "logindialog.h"
#include <QSortFilterProxyModel>
#include <QSqlRecord>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    qint32 price() const;
    void setPrice(qint32 newPrice);
    Q_PROPERTY(qint32 price READ price WRITE setPrice NOTIFY priceChanged FINAL)


signals:
    void priceChanged();

private slots:
    void on_pushButton_signUp_clicked();

    void on_pushButton_login_clicked();

    void on_pushButton_checkFreight_clicked();

    void on_pushButton_checkOutlets_clicked();

    void cPrice();

    void on_pushButton_confirm_clicked();

    void on_pushButton_checkBill_clicked();

    void on_pushButton_openvip_clicked();

    void on_tabWidget_tabBarClicked(int index);

    void on_listView_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    SignUpDialog *sudialog;
    LoginDialog loginDialog;
    QSortFilterProxyModel *model;

    qint32 m_price = 10;


};
#endif // MAINWINDOW_H

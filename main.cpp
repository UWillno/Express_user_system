#include "mainwindow.h"

#include <QApplication>
#include "singleton.h"
#include "settings.h"
#define ss Singleton<Settings>::GetInstance()
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ss;
    MainWindow w;
    w.show();
    return a.exec();
//①用户注册、登录，VIP客户登录；
//②运费查询、网点查询、运单查询；
//③网上寄件；
}

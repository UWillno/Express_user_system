#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "settings.h"
#include <QMessageBox>
#include "deliverydialog.h"
#include "newsdialog.h"
#define ss Singleton<Settings>::GetInstance()
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sudialog = new SignUpDialog(this);
//    ss;
//    QObject::connect(&ss,&Settings::passwordChanged,this,[&]{

//    });
    QObject::connect(&ss,&Settings::userChanged,this,[&]{
        ui->label_user->setText(ss.user());
        if(ss.user().isEmpty()){
            ui->pushButton_openvip->setVisible(false);
            ui->pushButton_changepwd->setVisible(false);
        }else {
            ui->pushButton_openvip->setVisible(true);
            ui->pushButton_changepwd->setVisible(true);
        }
    });
    QObject::connect(&ss,&Settings::isVipChanged,this,[&]{
        ui->label_isVip->setText(ss.isVip());
    });
    QObject::connect(&ss,&Settings::usernameChanged,this,[&]{
        ui->label_username->setText(ss.username());
    });
    ss.init();

    QObject::connect(this,&MainWindow::priceChanged,this,[&]{
        ui->label_price->setText(QString::number(price()));
    });
    model = new QSortFilterProxyModel(this);
    model->setSourceModel(Singleton<Sql>::GetInstance().model);
    ui->tableView->setModel(model);
    model->setFilterKeyColumn(model->columnCount()-1);
      ui->label_price->setText(QString::number(price()));
//    ui->label_price->setText(QString::number(price));
      QObject::connect(ui->comboBox_cf_2,&QComboBox::currentIndexChanged,this,&MainWindow::cPrice);
      QObject::connect(ui->comboBox_cf_3,&QComboBox::currentIndexChanged,this,&MainWindow::cPrice);
      QObject::connect(ui->doubleSpinBox_weight,&QDoubleSpinBox::valueChanged,this,&MainWindow::cPrice);
      QObject::connect(&Singleton<Sql>::GetInstance(),&Sql::selectDeliveryS,this,[&](QVariantList list){
          DeliveryDialog *d = new DeliveryDialog(list,this);
          d->exec();
      });
      ui->lineEdit_ydcx->setValidator(new QIntValidator(ui->lineEdit_ydcx));
      if(ss.user().isEmpty()){
          ui->pushButton_openvip->setVisible(false);
          ui->pushButton_changepwd->setVisible(false);
      }
      ui->listView->setModel(Singleton<Sql>::GetInstance().model1);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_signUp_clicked()
{
    sudialog->exec();
}


void MainWindow::on_pushButton_login_clicked()
{
    loginDialog.exec();
}


void MainWindow::on_pushButton_checkFreight_clicked()
{
    if(ui->doubleSpinBox->value() > 1.0){
        if(ui->comboBox_cf->currentText() == ui->comboBox_md->currentText())
        {
            ui->label_yf->setText("价格："+ QString::number(10*ui->doubleSpinBox->value()));
        }else {
            ui->label_yf->setText("价格："+ QString::number(50*ui->doubleSpinBox->value()));
        }
    }else {
         if(ui->comboBox_cf->currentText() == ui->comboBox_md->currentText())
        ui->label_yf->setText("价格：10");
         else{
        ui->label_yf->setText("价格：50");
         }
    }
}


void MainWindow::on_pushButton_checkOutlets_clicked()
{
    Singleton<Sql>::GetInstance().selectWD();
    model->setFilterFixedString(ui->lineEdit_wdcx->text());
//    model->setFilterRegularExpression(ui->lineEdit_wdcx->text());

}

void MainWindow::cPrice()
{
    if(ui->doubleSpinBox_weight->value() > 1.0){
        if(ui->comboBox_cf_2->currentText() == ui->comboBox_cf_3->currentText())
        {
            setPrice(10*ui->doubleSpinBox_weight->value());
        }else {
           setPrice(50*ui->doubleSpinBox_weight->value());
        }
    }else{
        if(ui->comboBox_cf_2->currentText() == ui->comboBox_cf_3->currentText())
        {
           setPrice(10);
        }else {
           setPrice(50);
        }
    }
}

qint32 MainWindow::price() const
{
    return m_price;
}

void MainWindow::setPrice(qint32 newPrice)
{
    if (m_price == newPrice)
        return;
    m_price = newPrice;
    emit priceChanged();
}


void MainWindow::on_pushButton_confirm_clicked()
{
    if(ss.user().isEmpty()){
        QMessageBox::warning(this, "寄件失败", "请先登录");
        return;
    }
    QStringList list;
    QList<QLineEdit*> lineEdits;
    lineEdits.append(ui->lineEdit_send_name);
    lineEdits.append(ui->lineEdit_send_tel);
    lineEdits.append(ui->lineEdit_send_area);
    lineEdits.append(ui->lineEdit_send_address);
    lineEdits.append(ui->lineEdit_hav_name);
    lineEdits.append(ui->lineEdit_hav_tel);
    lineEdits.append(ui->lineEdit_hav_area);
    lineEdits.append(ui->lineEdit_hav_address);
    foreach (QLineEdit *lineEdit, lineEdits) {
        if(lineEdit->text().isEmpty())
        {
            QMessageBox::warning(this, "寄件失败", "信息不能为空！");
           return;
        }
        list.append(lineEdit->text());
    }
    list.append(ui->comboBox_goods_type->currentText());
    list.append(QString::number(ui->doubleSpinBox_weight->value(),'f',2));

    bool result = QtConcurrent::run([&]{
        return Singleton<Sql>::GetInstance().addDelivery(list);
                  }).result();

    if(result){
        qint32 p = ss.isVip()== "会员"? price()/2 : price();
        QMessageBox::information(this, "寄件成功", "请支付"+QString::number(p));
        foreach (QLineEdit *lineEdit, lineEdits){
           lineEdit->setText("");
        }
    }else{
         QMessageBox::warning(this, "寄件失败", "????????！");
    }

}


void MainWindow::on_pushButton_checkBill_clicked()
{
    Singleton<Sql>::GetInstance().selectDelivery(ui->lineEdit_ydcx->text().toInt());
}


void MainWindow::on_pushButton_openvip_clicked()
{
    if(Singleton<Settings>::GetInstance().isVip() == "会员")
    {
        QMessageBox::information(this, "ab", "当前已是会员！");
    }else {
        if(Singleton<Sql>::GetInstance().beVip()){
             QMessageBox::information(this, "ab", "开通成功！");
        }else{
             QMessageBox::information(this, "ab", "开通失败！");
        }
    }
}


void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    if(index==2){
//        qInfo() << "ok";
//        ui->listWidget->addItem()
        Singleton<Sql>::GetInstance().selectNews();


    }
}


void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    QSqlRecord record= Singleton<Sql>::GetInstance().model1->record(index.row());
    QVariantList list;
    list.append(record.value(0));
    list.append(record.value(1));
    list.append(record.value(2));
    qInfo() << list;
    NewsDialog nd = NewsDialog(list);
    nd.exec();
}


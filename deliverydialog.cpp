#include "deliverydialog.h"
#include "ui_deliverydialog.h"
#include <QDateTime>
DeliveryDialog::DeliveryDialog(QVariantList list,QWidget *parent):m_list(list)
    ,QDialog(parent),
    ui(new Ui::DeliveryDialog)
{
    ui->setupUi(this);

    switch (m_list[0].toInt()) {
    case 0:{
        ui->label_state->setText("未发货");
        break;
    }
    case 1:{
        ui->label_state->setText("运输中");
        break;
    }
    case 2:{
        ui->label_state->setText("已入站");
        break;
    }
    case 3:{
        ui->label_state->setText("已签收");
        break;
    }
    }
    if(m_list[1].isValid())
        ui->label_commit->setText(m_list[1].toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    if(m_list[2].isValid())
        ui->label_sign->setText(m_list[2].toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    if(m_list[3].isValid())
        ui->label_arrival->setText(m_list[3].toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    if(m_list[4].isValid())
        ui->label_receipt->setText(m_list[4].toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
}

DeliveryDialog::~DeliveryDialog()
{
    delete ui;
}

void DeliveryDialog::on_buttonBox_accepted()
{
    close();
    deleteLater();
}


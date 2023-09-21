#include "newsdialog.h"
#include "ui_newsdialog.h"
#include <QDateTime>

NewsDialog::NewsDialog(QVariantList list,QWidget *parent) :m_list(list),
    QDialog(parent),
    ui(new Ui::NewsDialog)
{
    ui->setupUi(this);
    ui->label_title->setText(m_list[0].toString());
    ui->label_dt->setText(m_list[2].toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    ui->textBrowser->setHtml(m_list[1].toString());
}

NewsDialog::~NewsDialog()
{
    delete ui;
}

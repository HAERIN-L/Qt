#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    money = 0; // 인스턴스마다 독립적인 money 변수를 0으로 초기화

    // 초기 상태에서 버튼들의 활성화 상태 설정
    ui->pbCoffee->setEnabled(money >= 100);
    ui->pbTee->setEnabled(money >= 150);
    ui->pbMilk->setEnabled(money >= 200);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::changeMoney(int diff) {
    money += diff;
    ui->LcdNumber->display(money);

    // 현재 금액에 따라 버튼 활성화 / 비활성화 처리
    ui->pbCoffee->setEnabled(money >= 100);
    ui->pbTee->setEnabled(money >= 150);
    ui->pbMilk->setEnabled(money >= 200);
}

void Widget::on_pb10_clicked()
{
    changeMoney(10);
}

void Widget::on_pbCoffee_clicked()
{
    changeMoney(-100);
}

void Widget::on_pbReset_clicked()
{
    // 잔돈이 0원일 경우 처리
    if (money == 0) {
        QMessageBox::information(this, "잔돈", "반환할 잔돈이 없습니다.");
        return;
    }

    // 잔돈 반환
    const int coinValues[] = {500, 200, 150, 100, 50, 10};
    int coinCounts[sizeof(coinValues) / sizeof(int)] = {0};

    int change = money;
    for (size_t i = 0; i < sizeof(coinValues) / sizeof(int); ++i) {
        coinCounts[i] = change / coinValues[i];
        change %= coinValues[i];
    }

    QString message = "잔돈:\n";
    for (size_t i = 0; i < sizeof(coinValues) / sizeof(int); ++i) {
        if (coinCounts[i] > 0) {
            message += QString::number(coinValues[i]) + "원: " + QString::number(coinCounts[i]) + "개\n";
        }
    }

    QMessageBox::information(this, "잔돈", message);

    money = 0;
    ui->LcdNumber->display(money);

    // 현재 금액에 따라 버튼 활성화 / 비활성화 처리
    ui->pbCoffee->setEnabled(money >= 100);
    ui->pbTee->setEnabled(money >= 150);
    ui->pbMilk->setEnabled(money >= 200);
}

void Widget::on_pb50_clicked()
{
    changeMoney(50);
}

void Widget::on_pb100_clicked()
{
    changeMoney(100);
}

void Widget::on_pb500_clicked()
{
    changeMoney(500);
}

void Widget::on_pbTee_clicked()
{
    changeMoney(-150);
}

void Widget::on_pbMilk_clicked()
{
    changeMoney(-200);
}

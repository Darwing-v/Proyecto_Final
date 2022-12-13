#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <ostream>
#include <QString>
#include <QDebug>
#include <string>
#include <QMessageBox>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels({ "VELOCIDAD", "FRECUENCIA", "VOLTAJE", "TEMPERATURA"});

    ui->tableWidget->setRowCount(4);
    ui->tableWidget->setVerticalHeaderLabels({"VAL_REFERENCIA", "TOLERANCIA", "MAXIMO", "MINIMO"});


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ValoresActuales_clicked()
{
    QString constantes[10];
    int cont = 0;
    QFile f("/home/alse/Documents/Proyecto_final/valores_motor.txt");
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        cout << "Open failed." << endl;
    }
    QTextStream txtInput(&f);
    QString lineStr;
    while(!txtInput.atEnd())
    {
        lineStr = txtInput.readLine();
        //qDebug() << lineStr << endl;
    }
    f.close();

    QString str = lineStr;
    //qDebug() << "QString str = " << str;//solo imprime, borrar

    QStringList List;

    //qDebug() << "Split str using ';' as a delimeter";//solo imprime, borrar
    List = str.split(";");
    //qDebug() << "List = " << List; //solo imprime, borrar
    foreach(QString item, List)
    {
        QString numeros = item;
        QStringList List2;
        List2 = numeros.split(":");
        foreach(QString vals, List2)
        {
            constantes[cont] = vals;
            cont++;
        }
    }

    QFile g("/home/alse/Documents/Proyecto_final/valores_filtrados.txt");
    if(!g.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        cout << "Open failed." << endl;
    }
    QTextStream txtOutput(&g);

    txtOutput << constantes[1] << endl;
    txtOutput << constantes[3] << endl;
    txtOutput << constantes[5] << endl;
    txtOutput << constantes[7] << endl;
    txtOutput << constantes[9] << endl;

    g.close();
}

void MainWindow::on_CARGAR_clicked()
{
    QFile file("/home/alse/Documents/Proyecto_final/valores_filtrados.txt");
    if(!file.open(QIODevice::ReadOnly))
        QMessageBox::information(0,"info",file.errorString());

    QTextStream in(&file);

    ui->textBrowser->setText(in.readAll());

    QFile file2("/home/alse/Documents/Proyecto_final/conts.txt");
    if(!file2.open(QIODevice::ReadOnly))
        QMessageBox::information(0,"info",file.errorString());

    QTextStream in2(&file2);

    ui->conts->setText(in2.readAll());

}

void MainWindow::on_ValoresDeReferencia_clicked()
{
    QString v_r[12];
    int cont = 0;
    QFile f("/home/alse/Documents/Proyecto_final/valores_referencia.txt");
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        cout << "Open failed." << endl;
    }
    QTextStream txtInput(&f);
    QString lineStr;
    while(!txtInput.atEnd())
    {
        lineStr = txtInput.readLine();
    }
    f.close();

    QString str = lineStr;
    //qDebug() << "QString str = " << str;//solo imprime, borrar

    QStringList List;

    //qDebug() << "Split str using ';' as a delimeter";//solo imprime, borrar
    List = str.split(";");
    //qDebug() << "List = " << List; //solo imprime, borrar
    foreach(QString item, List)
    {
        QString valores = item;
        QStringList List2;
        List2 = valores.split(" ");
        foreach(QString vals, List2)
        {
            v_r[cont] = vals;
            cont++;
        }
    }

    ui->tableWidget->setItem( 0, 0, new QTableWidgetItem(v_r[1]));
    ui->tableWidget->setItem( 1, 0, new QTableWidgetItem(v_r[2]));
    ui->tableWidget->setItem( 1, 1, new QTableWidgetItem(v_r[5]));
    ui->tableWidget->setItem( 0, 1, new QTableWidgetItem(v_r[4]));
    ui->tableWidget->setItem( 0, 2, new QTableWidgetItem(v_r[7]));
    ui->tableWidget->setItem( 1, 2, new QTableWidgetItem(v_r[8]));
    ui->tableWidget->setItem( 0, 3, new QTableWidgetItem(v_r[10]));
    ui->tableWidget->setItem( 1, 3, new QTableWidgetItem(v_r[11]));

    double velocidad = v_r[1].split("r")[0].toDouble();
    double tol_vel = v_r[2].split("%")[0].toDouble();
    double Max = velocidad + (velocidad*(tol_vel/100));
    QString maximo_v = QString::number(Max);

    ui->tableWidget->setItem( 2, 0, new QTableWidgetItem(maximo_v));

    double Min = velocidad - (velocidad*(tol_vel/100));
    QString minimo_v = QString::number(Min);

    ui->tableWidget->setItem( 3, 0, new QTableWidgetItem(minimo_v));

    double frecuencia = v_r[4].split("H")[0].toDouble();
    double tol_frec = v_r[5].split("%")[0].toDouble();
    double Maxf = frecuencia + (frecuencia*(tol_frec/100));
    QString maximo_f = QString::number(Maxf);

    ui->tableWidget->setItem( 2, 1, new QTableWidgetItem(maximo_f));

    double Minf = frecuencia - (frecuencia*(tol_frec/100));
    QString minimo_f = QString::number(Minf);

    ui->tableWidget->setItem( 3, 1, new QTableWidgetItem(minimo_f));

    double voltaje = v_r[7].split("v")[0].toDouble();
    double tol_vol = v_r[8].split("%")[0].toDouble();
    double Maxv = voltaje + (voltaje*(tol_vol/100));
    QString maximo_vol = QString::number(Maxv);

    ui->tableWidget->setItem( 2, 2, new QTableWidgetItem(maximo_vol));

    double Minv = voltaje - (voltaje*(tol_vol/100));
    QString minimo_vol = QString::number(Minv);

    ui->tableWidget->setItem( 3, 2, new QTableWidgetItem(minimo_vol));

    double temperatura = v_r[10].split("°")[0].toDouble();
    double tol_temp = v_r[11].split("%")[0].toDouble();
    double Maxt = temperatura + (temperatura*(tol_temp/100));
    QString maximo_temp = QString::number(Maxt);

    ui->tableWidget->setItem( 2, 3, new QTableWidgetItem(maximo_temp));

    double Mint = temperatura - (temperatura*(tol_temp/100));
    QString minimo_temp = QString::number(Mint);

    ui->tableWidget->setItem( 3, 3, new QTableWidgetItem(minimo_temp));

    //COLORES DE LOS INDICADORES

    QString constantes[10];
    int cont2 = 0;
    QFile g("/home/alse/Documents/Proyecto_final/valores_motor.txt");

    if(!g.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        cout << "Open failed." << endl;
    }
    QTextStream txtInput2(&g);
    QString Str;
    while(!txtInput2.atEnd())
    {
        Str = txtInput2.readLine();
        //qDebug() << lineStr << endl;
    }
    g.close();

    QString str2 = Str;
    //qDebug() << "QString str = " << str;//solo imprime, borrar

    QStringList List4;

    //qDebug() << "Split str using ';' as a delimeter";//solo imprime, borrar
    List4 = str2.split(";");
    //qDebug() << "List = " << List; //solo imprime, borrar
    foreach(QString item, List4)
    {
        QString numeros = item;
        QStringList List4;
        List4 = numeros.split(":");
        foreach(QString vals, List4)
        {
            constantes[cont2] = vals;
            cont2++;
        }
    }

    QString velocidad_actual = constantes[1];
    QString frecuencia_actual = constantes[3];
    QString voltaje_actual = constantes[5];
    QString temperatura_actual = constantes[7];

    //qDebug() << velocidad_actual.toDouble() << endl << frecuencia_actual << endl << voltaje_actual << endl << temperatura_actual << endl;

    if(velocidad_actual.toDouble() < Min || Max < velocidad_actual.toDouble())
    {
        QPalette estado = ui->VEL->palette();
        estado.setColor(QPalette::Base,Qt::red);
        ui->VEL->setPalette(estado);
    }
    else
    {
        QPalette estado = ui->VEL->palette();
        estado.setColor(QPalette::Base,Qt::green);
        ui->VEL->setPalette(estado);
    }
    if(frecuencia_actual.toDouble() < Minf || Maxf < frecuencia_actual.toDouble())
    {
        QPalette estado = ui->FREC->palette();
        estado.setColor(QPalette::Base,Qt::red);
        ui->FREC->setPalette(estado);
    }
    else
    {
        QPalette estado = ui->FREC->palette();
        estado.setColor(QPalette::Base,Qt::green);
        ui->FREC->setPalette(estado);
    }
    if(voltaje_actual.toDouble() < Minv || Maxv < voltaje_actual.toDouble())
    {
        QPalette estado = ui->VOL->palette();
        estado.setColor(QPalette::Base,Qt::red);
        ui->VOL->setPalette(estado);
    }
    else
    {
        QPalette estado = ui->VOL->palette();
        estado.setColor(QPalette::Base,Qt::green);
        ui->VOL->setPalette(estado);
    }
    if(temperatura_actual.toDouble() < Mint || Maxt < temperatura_actual.toDouble())
    {
        QPalette estado = ui->TEMP->palette();
        estado.setColor(QPalette::Base,Qt::red);
        ui->TEMP->setPalette(estado);
    }
    else
    {
        QPalette estado = ui->TEMP->palette();
        estado.setColor(QPalette::Base,Qt::green);
        ui->TEMP->setPalette(estado);
    }
}


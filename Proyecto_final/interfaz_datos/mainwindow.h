#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ValoresActuales_clicked();

    void on_CARGAR_clicked();

    void on_ValoresDeReferencia_clicked();

    void on_VEL_textChanged();

    void on_VEL_anchorClicked(const QUrl &arg1);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

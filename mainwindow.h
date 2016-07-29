#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QStack>
#include <QString>
#include <QDebug>

double calc(int first, int second, char sign);

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *event);
private slots:
    void on_zeroButton_clicked();

    void on_oneButton_clicked();

    void on_twoButton_clicked();

    void on_threeButton_clicked();

    void on_fourButton_clicked();

    void on_fiveButton_clicked();

    void on_sixButton_clicked();

    void on_sevenButton_clicked();

    void on_eightButton_clicked();

    void on_nineButton_clicked();

    void on_divideButton_clicked();

    void on_multiButton_clicked();

    void on_minusButton_clicked();

    void on_plusButton_clicked();

    void on_clearAllButton_clicked();

    void on_equalButton_clicked();
signals:
    void exeCalc();
private:
    Ui::MainWindow *ui;
    bool isReasonable;
    double ans;
};

#endif // MAINWINDOW_H

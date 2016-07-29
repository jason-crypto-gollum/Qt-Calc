#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Calculator");
    this->move(500,220);
    this->ans = 0;
  //  ui->displayLineEdit->setEnabled(false);// forbidden to be edited,but we cannot see the whole text if the text is too long
    ui->displayLineEdit->setFocusPolicy(Qt::NoFocus); // make that lineEdit cannot get foucus
    QObject::connect(this,SIGNAL(exeCalc()),this,SLOT(on_equalButton_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event) // if the event has been handled, the event will definitly not been handled for twice by other codes
{// and we need to know that the event only will be handled by the codes who first get the focus
    switch(event->key())
    {
        case Qt::Key_0: ui->displayLineEdit->setText(ui->displayLineEdit->text()+QString('0'));
        break;
        case Qt::Key_1: ui->displayLineEdit->setText(ui->displayLineEdit->text()+QString('1'));
        break;
        case Qt::Key_2: ui->displayLineEdit->setText(ui->displayLineEdit->text()+QString('2'));
        break;
        case Qt::Key_3: ui->displayLineEdit->setText(ui->displayLineEdit->text()+QString('3'));
        break;
        case Qt::Key_4: ui->displayLineEdit->setText(ui->displayLineEdit->text()+QString('4'));
        break;
        case Qt::Key_5: ui->displayLineEdit->setText(ui->displayLineEdit->text()+QString('5'));
        break;
        case Qt::Key_6: ui->displayLineEdit->setText(ui->displayLineEdit->text()+QString('6'));
        break;
        case Qt::Key_7: ui->displayLineEdit->setText(ui->displayLineEdit->text()+QString('7'));
        break;
        case Qt::Key_8: ui->displayLineEdit->setText(ui->displayLineEdit->text()+QString('8'));
        break;
        case Qt::Key_9: ui->displayLineEdit->setText(ui->displayLineEdit->text()+QString('9'));
        break;
        case Qt::Key_Asterisk: ui->displayLineEdit->setText(ui->displayLineEdit->text()+QString('*'));
        break;
        case Qt::Key_Plus: ui->displayLineEdit->setText(ui->displayLineEdit->text()+QString('+'));
        break;
        case Qt::Key_Minus: ui->displayLineEdit->setText(ui->displayLineEdit->text()+QString('-'));
        break;
        case Qt::Key_Slash: ui->displayLineEdit->setText(ui->displayLineEdit->text()+QString('/'));
        break;
        case Qt::Key_Backspace: ui->displayLineEdit->setText(ui->displayLineEdit->text().left(ui->displayLineEdit->text().length()-1));
        break;
        case Qt::Key_Enter : emit this->exeCalc();
        break;
    case Qt::Key_A: ui->displayLineEdit->setText(ui->displayLineEdit->text()+QString::number(this->ans));
        break;
    }
}

void MainWindow::on_zeroButton_clicked()
{
    ui->displayLineEdit->setText(ui->displayLineEdit->text()+QString('0'));
}

void MainWindow::on_oneButton_clicked()
{
    ui->displayLineEdit->setText(ui->displayLineEdit->text()+QString('1'));
}

void MainWindow::on_twoButton_clicked()
{
    ui->displayLineEdit->setText(ui->displayLineEdit->text()+QString('2'));
}

void MainWindow::on_threeButton_clicked()
{
    ui->displayLineEdit->setText(ui->displayLineEdit->text()+QString('3'));
}

void MainWindow::on_fourButton_clicked()
{
    ui->displayLineEdit->setText(ui->displayLineEdit->text()+QString('4'));
}

void MainWindow::on_fiveButton_clicked()
{
    ui->displayLineEdit->setText(ui->displayLineEdit->text()+QString('5'));
}

void MainWindow::on_sixButton_clicked()
{
    ui->displayLineEdit->setText(ui->displayLineEdit->text()+QString('6'));
}

void MainWindow::on_sevenButton_clicked()
{
    ui->displayLineEdit->setText(ui->displayLineEdit->text()+QString('7'));
}

void MainWindow::on_eightButton_clicked()
{
    ui->displayLineEdit->setText(ui->displayLineEdit->text()+QString('8'));
}

void MainWindow::on_nineButton_clicked()
{
    ui->displayLineEdit->setText(ui->displayLineEdit->text()+QString('9'));
}

void MainWindow::on_divideButton_clicked()
{
    ui->displayLineEdit->setText(ui->displayLineEdit->text()+QString('/'));
}

void MainWindow::on_multiButton_clicked()
{
    ui->displayLineEdit->setText(ui->displayLineEdit->text()+QString('*'));
}

void MainWindow::on_minusButton_clicked()
{
    ui->displayLineEdit->setText(ui->displayLineEdit->text()+QString('-'));
}

void MainWindow::on_plusButton_clicked()
{
    ui->displayLineEdit->setText(ui->displayLineEdit->text()+QString('+'));
}

void MainWindow::on_clearAllButton_clicked()
{
    ui->displayLineEdit->setText(ui->displayLineEdit->text().left(ui->displayLineEdit->text().length()-1));
}

void MainWindow::on_equalButton_clicked()
{
    this->isReasonable = false;
    QString exp = ui->displayLineEdit->text();
    int length = exp.length();
    int i = 0;
    double number;
    double weight;
    char sign;
    char lastSign = '+';
    double first;
    double second;
    bool flag;

    QStack<double> numberStack;
    QStack<char> signStack;
    while (i < length) {
        flag = false;
        number = 0;
        weight = 1;
        while (exp.at(i).toLatin1() >= '0' && exp.at(i).toLatin1() <= '9') {
            number = number * weight + exp.at(i).toLatin1()-'0';
            weight *= 10;
            flag = true;
            i++;
            if (i == length)
                break;
        }

        if (flag) {
            numberStack.push(number);
            if (i >= length)
                break;
        }

        sign = exp.at(i).toLatin1();

        if (signStack.isEmpty()) {
            signStack.push(sign);
        }
        else {
            if ((sign == '*' || sign == '/') && (lastSign == '+' || lastSign == '-')) {
                signStack.push(sign);
                qDebug() << sign;
            } // 如果优先级高，则将符号压入栈
            else {
                second = numberStack.pop();
                first = numberStack.pop();
                qDebug() << calc(first,second,lastSign);
                numberStack.push(calc(first,second,lastSign));
                signStack.pop();
                signStack.push(sign);
            }
        }
        lastSign = sign;
        i++;
    }

    while (!signStack.isEmpty()) {
        sign = signStack.pop();
        second = numberStack.pop();
        first = numberStack.pop();
        //numberStack.push(calc(first,second,sign));
        this->ans = calc(first,second,sign);
        ui->displayLineEdit->setText(QString::number(this->ans));
    }

    return ;
}

double calc(int first, int second, char sign)
{
    switch(sign) {
        case '+': return (first + second);
        case '-': return (first - second);
        case '*': return (first * second);
        case '/': return 1.0*first/second;
    }
}

/*
    ?????????????????????
*/

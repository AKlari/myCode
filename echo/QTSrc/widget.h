#ifndef WIDGET_H
#define WIDGET_H

#include <string>
#include <iostream>
#include <QWidget>
#include <QProcess>
#include <QFileDialog>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void nameInputFileName(QString);
    void nameOutputFileName(QString);
    QString showInput;
    QString showOutput;

private slots:
    void on_browse_clicked();

    void on_pushButton_clicked();

    void on_confirm_clicked();
private:
    Ui::Widget *ui;
    QString inputFileName;
    QString outputFileName;
};
#endif // WIDGET_H

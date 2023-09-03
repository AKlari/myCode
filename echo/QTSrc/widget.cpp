#include "widget.h"
#include "./ui_widget.h"
#include "vevo2100.c"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget), showOutput("./outcome.csv")
{
    ui->setupUi(this);

}

Widget::~Widget()
{
    delete ui;
}

void test() {
    printf("hello, world");
}

void Widget::nameInputFileName(QString A) {
    inputFileName = A;
    showInput = A;
}

void Widget::nameOutputFileName(QString A) {
    outputFileName = A;
    showOutput = A;
}



void Widget::on_browse_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("选择一个文件"), QCoreApplication::applicationFilePath());
    if (fileName.isEmpty()) {
        QMessageBox::warning(this, "警告", "请选择一个文件");
    }
    else {
        nameInputFileName(fileName);
        ui->inputFileRoute->setText(fileName);
    }
}

void Widget::on_confirm_clicked() {
    nameOutputFileName(ui->outputFileName->text());
}

void Widget::on_pushButton_clicked() {
    char *input;
    char *output;

    unsigned int numInput = showInput.toLatin1().size();
    input = (char*)malloc(numInput);
    unsigned int numOutput = showOutput.toLatin1().size();
    output = (char*)malloc(numOutput);
    strcpy(input, showInput.toLatin1().data());
    strcpy(output, showOutput.toLatin1().data());
    //std::cout << input << std::endl;
    std::cout << output << std::endl;
    //ui->inputFileRoute->setText(input);
    deal(input, output);
}


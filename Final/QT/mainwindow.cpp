#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <QPushButton>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <compression.cpp>
#include <minifying.cpp>
#include <formatting.h>
#include <candb.cpp>
#include <formatting2.h>


QString fileName;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_actionAdd_triggered()
{

   fileName=QFileDialog::getOpenFileName(this,"open the XML file");
   QFile file(fileName);

   if(!file.open(QFile::ReadOnly | QFile::Text)){
       QMessageBox::warning(this,"Error", "Invalid file" );
       return;
   }

   QTextStream in(&file);
   QString text=in.readAll();
   ui->Input->setPlainText(text);
   file.close();

}




void MainWindow::on_compressionButton_clicked()
{
    QString qs = ui->Input->toPlainText();
    string input = qs.toStdString();
    string output = HuffmanCoding(input);
    ui->output->setPlainText(QString::fromStdString(output));
}


void MainWindow::on_Formattingbutton_clicked()
{
    QString qs = ui->Input->toPlainText();
    string input = qs.toStdString();
    string formattedText;
    vector<string> data;
    formattedText = format(input,data);
    ui->output->setPlainText(QString::fromStdString(formattedText));
}



void MainWindow::on_consistencyButton_clicked()
{
   QString qs = ui->Input->toPlainText();
   string input = qs.toStdString();
   string output = detect(input);
   ui->output->setPlainText(QString::fromStdString(output));

}


void MainWindow::on_converteButton_clicked()
{
    QString qs = ui->Input->toPlainText();
    string input = qs.toStdString();
    string output = JsonOutput(input);
    ui->output->setPlainText(QString::fromStdString(output));
}



void MainWindow::on_minifyingButton_clicked()
{
    QString qs = ui->Input->toPlainText();
    string input = qs.toStdString();
    string text = remove(&input);
    ui->output->setPlainText(QString::fromStdString(text));
}



void MainWindow::on_correctingButton_clicked()
{
    QString qs = ui->Input->toPlainText();
    string input = qs.toStdString();
    string text = XmlOutput(input);
    ui->output->setPlainText(QString::fromStdString(text));

}


void MainWindow::on_graphButton_clicked()
{
    QString qs = ui->Input->toPlainText();
    string text = qs.toStdString();
    str_to_graph(text);

    system("dot -Tpng -O a.dot");
    QPixmap graph("a.dot.png");
    ui->graphLabel->setPixmap(graph);

}




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
    void on_minifyingButton_clicked();

    void on_compressionButton_clicked();

    void on_Formattingbutton_clicked();

    void on_consistencyButton_clicked();

    void on_converteButton_clicked();

    void on_actionAdd_triggered();

    void on_correctingButton_clicked();

private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H


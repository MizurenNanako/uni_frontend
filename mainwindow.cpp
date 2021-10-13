#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <dirent.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    uniqueoutput("Main Window Started");
    uniqueoutput("Main UI Started");
    ui->label_Information->setText(INFORMATION);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::run()
{

}

void MainWindow::uniqueoutput(const QString &context, bool notmain)
{
    QString pre("[Main:] ");
    if (notmain)
    {
        pre = "[Child:] ";
    }
    ui->textBrowser_Output->append(pre + context);
}

void MainWindow::on_pushButton_Icz_clicked()
{
    uniqueoutput("Ratio Increased");
    if (ui->lineEdit_Resize->text() == "x1")
    {
        ui->lineEdit_Resize->setText("x2");
        scale_ratio = 2;
        return;
    }
    if(ui->lineEdit_Resize->text()=="x2")
    {
        ui->lineEdit_Resize->setText("x4");
        scale_ratio = 4;
        return;
    }
    if(ui->lineEdit_Resize->text() == "x4")
    {
        scale_ratio = 4;    //ensure ratio is 4
        return;
    }
}


void MainWindow::on_pushButton_Dcz_clicked()
{
    uniqueoutput("Ratio Decreased");
    if (ui->lineEdit_Resize->text() == "x1")
    {
        scale_ratio = 1;    //ensure ratio is 1
        return;
    }
    if(ui->lineEdit_Resize->text() == "x2")
    {
        ui->lineEdit_Resize->setText("x1");
        scale_ratio = 1;
        return;
    }
    if(ui->lineEdit_Resize->text() == "x4")
    {
        ui->lineEdit_Resize->setText("x2");
        scale_ratio = 2;
        return;
    }
}


void MainWindow::on_pushButton_AddFile_clicked()
{
    QStringList tmpfilepaths = QFileDialog::getOpenFileNames(nullptr,
                                                             tr("Add Files"),
                                                             "./",
                                                             "images (*.png *.jpg *.webp)");
    uniqueoutput("File name read, parsing...");
    for (int i = 0; i < tmpfilepaths.length(); ++i)
    {
        uniqueoutput("Testing file: "+tmpfilepaths[i]);
        FILE *t = fopen(tmpfilepaths[i].toStdString().c_str(), "r");
        uniqueoutput("File opening: "+tmpfilepaths[i]);
        if (!t)
        {
            uniqueoutput("File opening error!");
            QMessageBox::warning(
                        nullptr,
                        tr("ERROR"),
                        tr("Fail opening file: ")
                        + tmpfilepaths[i] + "\n"
                        + tr("We will skip this file"));
            continue;
        }
        //else
        working_list += tmpfilepaths[i];
        fclose(t);
        uniqueoutput("File closed: "+tmpfilepaths[i]);
    }
    updatelistview();
}


void MainWindow::on_pushButton_RemoveFile_clicked()
{
    uniqueoutput("Parsing seletion...");
    QItemSelectionModel *sel_mod = ui->listView->selectionModel();
    QModelIndexList sel_id_list = sel_mod->selectedIndexes();
    for ( QModelIndex i : qAsConst(sel_id_list) )
    {
        QVariant tmpvar = sel_mod->model()->data(i);
        QString tmpstr = tmpvar.toString();
        uniqueoutput("Item removing: "+tmpstr);
        working_list.removeOne(tmpstr);
    }
    updatelistview();
}

void MainWindow::on_pushButton_ClearFile_clicked()
{
    uniqueoutput("List cleaning");
    working_list.clear();
    //displaying_model.clear();
    updatelistview();
}

void MainWindow::updatelistview()
{
    uniqueoutput("Listview updating...");
    //update model
    uniqueoutput("Listview model updating...");
    displaying_model.setRowCount(working_list.length());
    displaying_model.setColumnCount(1);
    for (int i = 0; i < working_list.length(); ++i)
    {
        QStandardItem *item = new QStandardItem(working_list[i]);
        item->setEditable(false);
        displaying_model.setItem(i, 0, item);
    }
    uniqueoutput("Listview model updated");
    //update listview
    ui->listView->setModel(&displaying_model);
    ui->listView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->listView->update();
    uniqueoutput("Listview updated");
}


void MainWindow::on_pushButton_Run_clicked()
{
    uniqueoutput("Calling run() function...");
    run();
}

void MainWindow::on_pushButton_Backend_clicked()
{
    uniqueoutput("Path getting...");
    backend_path = QFileDialog::getOpenFileName(nullptr,
                                                tr("Select backend executable:"),
                                                "./",
                                                "Windows Executable (*.exe)");
    ui->textBrowser_Backend->setText(backend_path);
    uniqueoutput("Text updated");
}

void MainWindow::on_pushButton_Model_clicked()
{
    uniqueoutput("Path getting...");
    model_path = QFileDialog::getOpenFileName(nullptr,
                                              tr("Select pre-trained neural network model:"),
                                              "./",
                                              "binary model file (*.bin);;model param file (*.param)");
    ui->textBrowser_Model->setText(model_path);
    uniqueoutput("Text updated");
}

void MainWindow::on_pushButton_LogCL_clicked()
{
    ui->textBrowser_Output->clear();
}



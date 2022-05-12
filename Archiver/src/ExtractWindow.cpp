#include "src/ExtractWindow.h"
#include "ui_ExtractWindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <map>
#include <string>
#include <fstream>
#include <QDebug>

using namespace std;

Extract_window::Extract_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Extract_window)
{
    ui->setupUi(this);
}

Extract_window::~Extract_window()
{
    delete ui;
}

void Extract_window::on_BrowseButton_clicked()
{
    direct = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                "/home",
                                                QFileDialog::ShowDirsOnly
                                                | QFileDialog::DontResolveSymlinks);
    this->ui->BrowseLineEdit->setText(direct);
}

void Extract_window::on_AppendButton_clicked()
{
    if (this->ui->RLERadioButton->isChecked())
    {
        filesToDecompress = QFileDialog::getOpenFileNames(this, "ChooseFile(s) to decompress","D:\\"," files (*.rle)");
    } else {
        filesToDecompress = QFileDialog::getOpenFileNames(this, "ChooseFile(s) to decompress","D:\\","HUF files (*.huf)");
    }

    pathsForQLineEdit = filesToDecompress.join(";");
    this->ui->AppendLineEdit->clear();
    this->ui->AppendLineEdit->setText(pathsForQLineEdit);
}


void Extract_window::on_OK_clicked()
{
    if(this->ui->AppendLineEdit->text().isEmpty() ||
            this->ui->BrowseLineEdit->text().isEmpty())
    {
        QMessageBox msgBox(QMessageBox::Warning, "Error", "Error : empty fields");
        msgBox.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
        msgBox.exec();
    }
    else
    {
        QDir dir(this->ui->BrowseLineEdit->text());
        if (!dir.exists())
        {
          dir.mkdir(".");
        }
        if (this->ui->RLERadioButton->isChecked())
        {
            for(auto it:filesToDecompress)
            {
                QString tempDir = direct;

                compressorRle.decompressRLE(it, tempDir);
            }
        } else {
            for(auto it:filesToDecompress)
            {
                QString tempDir = direct;

                compressorHuf.decompressHuffman(it, tempDir);
            }
        }
    }
}

void Extract_window::recvText(const QString &text)
{
    filesToDecompress.clear();
    filesToDecompress.append(text);
    pathsForQLineEdit = filesToDecompress.join(";");
    this->ui->AppendLineEdit->setText(pathsForQLineEdit);

}

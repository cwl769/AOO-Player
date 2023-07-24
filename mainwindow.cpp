#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMediaPlayer>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    player = NULL;

    QStringList listView_1_StringList;
    listView_1_Items = new QStringListModel(listView_1_StringList);
    ui->listView_1->setModel(listView_1_Items);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::listView_1_addBack(const QString str)
{
    listView_1_Items->insertRow(listView_1_Items->rowCount());
    QModelIndex index = listView_1_Items->index(listView_1_Items->rowCount()-1);
    listView_1_Items->setData(index, str, Qt::DisplayRole);
}

void MainWindow::on_pushButton_selectFile_clicked()
{
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setDirectory("./");
    fileDialog->setNameFilter(tr("File(*.flac* *.mp3*)"));
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    fileDialog->setViewMode(QFileDialog::Detail);

    QStringList filenameList;
    if(fileDialog->exec())
    {
        filenameList = fileDialog->selectedFiles();
    }
    for(int i=0;i<filenameList.size();++i)
    {
        musicFullname.push_back(filenameList[i].toStdString());
        printf("Add File to the List: %s\n", filenameList[i].toStdString().c_str());
        int lastsplit = -1;
        for(int j=0;filenameList[i][j]!='\0';++j)
        {
            if(filenameList[i][j]=='/'||filenameList[i][j]=='\\')
                lastsplit = j;
        }
        filenameList[i].remove(0, lastsplit+1);
        listView_1_addBack(filenameList[i]);
    }
    delete fileDialog;
}

void MainWindow::on_listView_1_doubleClicked(const QModelIndex &index)
{
    /*Play the music*/
    printf("Play %s\n", musicFullname[index.row()].c_str());
    //delete player;player = NULL;
    if(player==NULL)player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile(musicFullname[index.row()].c_str()));
    //player->setLoopCount(1);
    player->play();

    /*Display the lyric*/
    std::string lrcFullname = musicFullname[index.row()];
    for(int i=lrcFullname.size()-1;i>=0&&lrcFullname[i]!='.';--i)lrcFullname.pop_back();
    lrcFullname += "lrc";
    printf("lrcFullname: %s\n", lrcFullname.c_str());

    ui->textBrowser_1->clear();
    FILE * lrcFile = fopen(lrcFullname.c_str(), "r");
    if(lrcFile!=NULL)
    {
        char *tmp = (char*)calloc(65536, sizeof(char));
        for(;;)
        {
            if(feof(lrcFile))break;
            fgets(tmp, 65535, lrcFile);
            ui->textBrowser_1->append(tmp);
        }
        fclose(lrcFile);
        free(tmp);tmp=NULL;
    }
    else
    {
        ui->textBrowser_1->append("未发现歌词文件");
    }
}


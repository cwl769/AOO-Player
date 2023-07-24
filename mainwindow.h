#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <QMainWindow>
#include <QStringListModel>
#include <QMediaPlayer>

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

    void on_pushButton_selectFile_clicked();

    void on_listView_1_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    QStringListModel* listView_1_Items;
    std::vector<std::string> musicFullname;
    QMediaPlayer *player;

    void listView_1_addBack(const QString str);
};
#endif // MAINWINDOW_H

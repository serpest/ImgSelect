#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../../include/model/copymanagement.h"
#include "../../include/model/direxception.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
    private:
        Ui::MainWindow *ui;
        CopyManagement* copyManagement;
        void showImages();
    private slots:
        void on_actionSource_triggered();
        void on_actionDeveloper_triggered();
        void on_actionDestination_triggered();
        void on_actionCopy_triggered();
        void on_actionImgSelect_triggered();
        void on_imageList_itemSelectionChanged();

public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
};

#endif // MAINWINDOW_H


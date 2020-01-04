#include "mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QPixmap>
#include <QIcon>
#include <QAbstractItemView>
#include "ui_mainwindow.h"

#define IMAGE_SIZE QSize(300,300)

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setCentralWidget(ui->imageList);
    ui->imageList->setIconSize(QSize(IMAGE_SIZE));
    ui->imageList->setResizeMode(QListWidget::Adjust);
    ui->imageList->setGridSize(IMAGE_SIZE);
    ui->imageList->setSelectionMode(QAbstractItemView::SelectionMode::MultiSelection);
    ui->statusbar->addPermanentWidget(ui->picturesNumber);
    ui->statusbar->addPermanentWidget(ui->selectedPicturesNumber);
    copyManagement = NULL;
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::showImages() {
    ui->imageList->clear();
    std::vector<QString> imageFilenames = copyManagement->getImageFilenames();
    QPixmap currentImage;
    for (QString& imageFilename : imageFilenames) {
        currentImage = QPixmap(imageFilename).scaled(IMAGE_SIZE, Qt::KeepAspectRatio);
        ui->imageList->addItem(new QListWidgetItem(QIcon(currentImage), imageFilename));
    }
}

void MainWindow::on_actionSource_triggered() {
    if (copyManagement && copyManagement->getImagesNumber() != 0) {
        QMessageBox::StandardButton answer = QMessageBox::question(this, "Open new source", "Do you want to open a new source deleting the last selection?");
        if (answer == QMessageBox::Yes)
            delete copyManagement;
        else
            return;
    }
    QString dirName = QFileDialog::getExistingDirectory(this, "Source folder");
    try {
        copyManagement = new CopyManagement(dirName);
    } catch (DirException exc) {
        QMessageBox::critical(this, "Source doesn't exist", "The source " + exc.getDir()->canonicalPath() + " doesn't exist.");
        return;
    }
    unsigned int picturesNumber = copyManagement->getImagesNumber();
    ui->picturesNumber->setText(QString::number(picturesNumber) + " picture" + ((picturesNumber == 1) ? "" : "s"));
    showImages();
}

void MainWindow::on_actionDestination_triggered() {
    if (!copyManagement) {
        QMessageBox::critical(this, "Destination selecting not permitted", "First you must select the source.");
        return;
    }
    QString dirName = QFileDialog::getExistingDirectory(this, "Destination folder");
    try {
        copyManagement->setDestination(dirName);
    } catch (DirException exc) {
        QMessageBox::critical(this, "Destination doesn't exist", "The destination " + exc.getDir()->canonicalPath() + " doesn't exist.");
        return;
    }
}

void MainWindow::on_actionDeveloper_triggered() {
    QMessageBox::about(this, "Developer", "serpest\nserpest@protonmail.com\ngithub.com/serpest\ntwitter.com/serpest0");
}

void MainWindow::on_actionCopy_triggered() {
    if (!copyManagement) {
        QMessageBox::critical(this, "Copy not permitted", "You must select the source and the destination.");
        return;
    }
    if (!copyManagement->validDestination()) {
        QMessageBox::critical(this, "Copy not permitted", "You must select the destination.");
        return;
    }
    QList<QListWidgetItem*> selectedItems = ui->imageList->selectedItems();
    if (selectedItems.size() == 0) {
        QMessageBox::critical(this, "Copy not permitted", "You must select mimimum a file.");
        return;
    }
    std::vector<QString> selectedImageFilenames;
    for (QListWidgetItem* selectedItem : selectedItems) {
        selectedItem->text();
        selectedImageFilenames.push_back(selectedItem->text());
    }
    copyManagement->copy(selectedImageFilenames);
}

void MainWindow::on_actionImgSelect_triggered() {
    QMessageBox::about(this, "ImgSelect", "ImgSelect project.\nCreated by serpest in 2020 using Qt.");
}

void MainWindow::on_imageList_itemSelectionChanged() {
    ui->selectedPicturesNumber->setText(QString::number(ui->imageList->selectedItems().size()) + " picture" + ((ui->imageList->selectedItems().size() == 1) ? "" : "s") + " selected");
}

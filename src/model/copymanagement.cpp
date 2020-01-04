#include "../../include/model/copymanagement.h"

#include <QDirIterator>
#include "../../include/model/direxception.h"

void CopyManagement::loadImageFilenames() {
    QDirIterator iterator(source.canonicalPath(), QStringList() << "*.jpg" << "*.jpeg"
                          << "*.jpe" << "*.jif" << "*.jfif" << "*.jfi" << "*.png" << "*.gif"
                          << "*.webp" << "*.tiff" << "*.tif" << "*.psd" << "*.raw" << "*.arw"
                          << "*.cr2" << "*.nrw" << "*.k25" << "*.bmp" << "*.dib",
                          QDir::Files, QDirIterator::Subdirectories); //I wrote many formats, but I didn't verify the Qt compatibility.
    while (iterator.hasNext()) {
        imageFilenames.push_back(iterator.next());
    }
}

CopyManagement::CopyManagement(QString& sourceFilename, QString destinationFilename) : source(sourceFilename), destination(destinationFilename) {
    if (!source.exists())
        throw DirException(&source);
    loadImageFilenames();
}

bool CopyManagement::validDestination() {
    return destination.absolutePath() != "";
}

QDir CopyManagement::getDestination() const {
    return destination;
}

void CopyManagement::setDestination(QString& destinationFilename) {
    QDir temp = destinationFilename;
    if (!temp.exists())
        throw DirException(&temp);
    destination.setPath(destinationFilename);
}

std::vector<QString> CopyManagement::getImageFilenames() {
    return imageFilenames;
}

QDir CopyManagement::getSource() const {
    return source;
}

void CopyManagement::copy(std::vector<QString> sourceFilenames) {
    std::vector<QString> destinationFilenames;
    for (QString currentFilename : sourceFilenames) {
        destinationFilenames.push_back(destination.absolutePath() + QDir::separator() + source.relativeFilePath(currentFilename));
    }
    QDir dir;
    QFileInfo currentFile;
    for (unsigned int i = 0; i < sourceFilenames.size(); i++) {
        if (!QFile::exists(destinationFilenames[i])) {
            currentFile = destinationFilenames[i];
            dir.mkpath(currentFile.absolutePath());
            QFile::copy(sourceFilenames[i], destinationFilenames[i]);
        }
    }
}

unsigned int CopyManagement::getImagesNumber() {
    return imageFilenames.size();
}

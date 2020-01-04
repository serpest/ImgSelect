#ifndef COPYMANAGEMENT_H
#define COPYMANAGEMENT_H

#include <QDir>

class CopyManagement {
    private:
        QDir source;
        QDir destination;
        std::vector<QString> imageFilenames;
        void loadImageFilenames();
    public:
        CopyManagement(QString& sourceFilename, QString destinationFilename = "");
        QDir getSource() const;
        QDir getDestination() const;
        void setDestination(QString& destinationFilename);
        std::vector<QString> getImageFilenames();
        void copy(std::vector<QString> sourceFilenames);
        unsigned int getImagesNumber();
        bool validDestination();
};

#endif // COPYMANAGEMENT_H

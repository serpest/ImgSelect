#ifndef DIREXCEPTION_H
#define DIREXCEPTION_H

#include <QDir>

class DirException {
    private:
        QDir* dir;
    public:
        DirException(QDir* dir0 = nullptr);
        QDir* getDir() const;
};

#endif // DIREXCEPTION_H

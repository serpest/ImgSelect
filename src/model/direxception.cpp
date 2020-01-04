#include "../../include/model/direxception.h"

QDir* DirException::getDir() const {
    return dir;
}

DirException::DirException(QDir *dir0) : dir(dir0) {}

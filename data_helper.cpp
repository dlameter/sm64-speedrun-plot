#include "data_helper.h"

DataHelper::DataHelper(QString filename) {
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "Failed to open data file!" << std::endl;
    }


    dataDoc = 
}

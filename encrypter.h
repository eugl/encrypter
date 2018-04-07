#include <string>
#include <iostream>
#include <vector>
#include <QString>

#ifndef ENCRYPTER_H
#define ENCRYPTER_H

using namespace std;

class encrypter
{
    vector <QChar> key;
    int keySize;

public:
    QString inText;
    QString outText;

    encrypter();
    void encrypt();
    void newencrypt();
    void newdecrypt();
    void readText(QString path);
    void saveText(QString path);

private:
    void getNewKey();
};

#endif // ENCRYPTER_H

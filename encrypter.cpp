#include "encrypter.h"
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <fstream>

using namespace std;

encrypter::encrypter()
{

}

void encrypter::encrypt()
{
    int len = key.size();
    //int val = inText.length()%len;
    int val = 0;
    //outText.append( key[val] );

    for (int i=0; i<inText.length(); i++){

        for (int j=0; j<len; j++){
            if (key[j]==inText[i]){
                val +=j;
                break;
            }
        }

        val = val%len;
        outText.append(key[val]);
    }
}

void encrypter::getNewKey()
{
    bool test = true;

    for (int i=0; i<inText.length(); i++){
        test = true;

        for (int j=0; j<key.size(); j++){
            if (key[j] == inText[i]){
                test = false;
                break;
            }
        }

        if(test){
            key.push_back(inText[i]);
        }
    }

    vector <QChar> newKey;
    srand( time( NULL ) );
    int val;

    while (key.size()>0){
        val = rand()%key.size();
        newKey.push_back(key[val]);
        key.erase(key.begin()+val);
    }

    key = newKey;
}

void encrypter::newencrypt()
{
    key.clear();
    outText.clear();

    getNewKey();

    outText.append( QString("%1 ").arg(key.size()) );
    for (int i=0; i<key.size(); i++){
        outText.append(key[i]);
    }

    encrypt();
}

void encrypter::newdecrypt()
{
    key.clear();
    outText.clear();

    int space = inText.indexOf(QString(" "));
    int keyLen = inText.mid(0,space).toInt();

    for (int i=space+1; i<keyLen+space+1; i++){
        key.push_back(inText[i]);
    }

    int val = 0;

    for (int i=key.size()+space+1; i<inText.length(); i++){

        for (int j=0; j<key.size(); j++){
            if (inText[i]==key[j]){
                outText.append(key[(j+key.size()-val)%key.size()]);
                val = j;
                break;
            }
        }

    }
}

void encrypter::readText(QString path)
{
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    QTextStream in(&file);

    inText = in.readAll();
    file.close();
}

void encrypter::saveText(QString path)
{
    QFile file(path);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;
    QTextStream in(&file);

    in << outText;
    file.close();
}

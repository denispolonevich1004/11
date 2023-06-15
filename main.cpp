#include <QApplication>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QTranslator>

#include "mainwindow.h"
#include "datasingleton.h"

void printHelpMessage()
{
    qDebug()<<"GreenPainterApp - a simple graphics painting program\n"
              "Usage: GreenPainterApp [options] [filename]\n\n"
              "Options:\n"
              "\t-h, --help\t\tshow this help message and exit\n"
              "\t-v, --version\t\tshow program's version number and exit";
}

void printVersion()
{
    qDebug()<<"1.0";
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("GreenPainterApp");
    a.setApplicationVersion("1.0");

    QStringList args = a.arguments();

    QRegExp rxArgHelp("--help");
    QRegExp rxArgH("-h");
    QRegExp rxArgVersion("--version");
    QRegExp rxArgV("-v");

    bool isHelp(false), isVer(false);
    QStringList filePaths;

    for(int i(1); i < args.size(); ++i)
    {
        if (rxArgHelp.indexIn(args.at(i)) != -1  ||
                rxArgH.indexIn(args.at(i)) != -1)
        {
            isHelp = true;
        }
        else if (rxArgVersion.indexIn(args.at(i)) != -1  ||
                 rxArgV.indexIn(args.at(i)) != -1)
        {
            isVer = true;
        }
        else
        {
            if(QFile::exists(args.at(i)))
            {
                filePaths.append(args.at(i));
            }
            else
            {
                qDebug()<<QString("File %1 not found").arg(args.at(i));
            }
        }

    }

    if(isHelp)
    {
        printHelpMessage();
        return 0;
    }
    else if(isVer)
    {
        printVersion();
        return 0;
    }

    QTranslator appTranslator;
    QString translationsPath("/usr/share/GreenPainterApp/translations/");
    QString appLanguage = DataSingleton::Instance()->getAppLanguage();
    if(appLanguage == "system")
    {
        appTranslator.load(translationsPath + "GreenPainterApp_en_EN" + QLocale::system().name());
    }
    else
    {
        appTranslator.load(translationsPath + appLanguage);
    }
    a.installTranslator(&appTranslator);

    MainWindow w(filePaths);
    w.show();

    return a.exec();
}

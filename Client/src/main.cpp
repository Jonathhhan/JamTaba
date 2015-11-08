#include <QApplication>
#include <QMainWindow>
#include <QDir>
#include "StandAloneMainController.h"
#include "persistence/Settings.h"
#include "MainWindowStandalone.h"
#include "log/logging.h"
#include "../src/Libs/SingleApplication/singleapplication.h"

int main(int argc, char* args[] ){

    QApplication::setApplicationName("Jamtaba 2");
    QApplication::setApplicationVersion(APP_VERSION);

    Controller::MainController::exportLogFile();//copy logging.ini from resources to Jamtaba writable path

    QString logFile = Controller::MainController::getLogConfigFilePath();
    if(!logFile.isEmpty()){
        qputenv("QT_LOGGING_CONF", QByteArray(logFile.toUtf8()));
        qInstallMessageHandler(jamtabaLogHandler);
    }

    Persistence::Settings settings;
    settings.load();

    QApplication* application = new QApplication(argc, args);
    Controller::StandaloneMainController mainController(settings, application);//MainController extends QApplication
    mainController.configureStyleSheet("jamtaba.css");
    mainController.start();
    if(mainController.isUsingNullAudioDriver()){
        QMessageBox::about(nullptr, "Fatal error!", "Jamtaba can't detect any audio device in your machine!");
    }
    MainWindowStandalone  mainWindow(&mainController);
    mainController.setMainWindow(&mainWindow);
    mainWindow.show();

    return application->exec();
 }

//++++++++++++++++++++++++++++++++++




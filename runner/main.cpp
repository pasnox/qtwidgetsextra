#include <QCoreApplication>
#include <QProcessEnvironment>
#include <QTemporaryFile>
#include <QLibraryInfo>
#include <QLibrary>
#include <QProcess>
#include <QDir>

int main(int argc, char** argv) {
    QSharedPointer<QCoreApplication> app(new QCoreApplication(argc, argv));

    QTemporaryFile* file = QTemporaryFile::createLocalFile(QLatin1String("://QtWidgetsExtra.ui"));
    Q_ASSERT(file);
    file->setParent(app.data());

    const QString qtTools = QLibraryInfo::location(QLibraryInfo::BinariesPath);
    const QString designer = QDir(qtTools).entryInfoList(QStringList(QLatin1String("*designer*")), QDir::Files | QDir::Executable).value(0).absoluteFilePath();

    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.insert(QLatin1String("QT_PLUGIN_PATH"), app->applicationDirPath());

    QProcess* process = new QProcess(app.data());
    process->setProcessEnvironment(env);
    process->setProgram(designer);
    process->setArguments(QStringList(file->fileName()));
    process->start();

    QObject::connect(process, SIGNAL(error(QProcess::ProcessError)), app.data(), SLOT(quit()));
    QObject::connect(process, SIGNAL(finished(int, QProcess::ExitStatus)), app.data(), SLOT(quit()));

    return app->exec();
}

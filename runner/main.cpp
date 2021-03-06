#include <QCoreApplication>
#include <QLibraryInfo>
#include <QSharedPointer>
#include <QProcess>
#include <QDir>

int main(int argc, char** argv) {
    QSharedPointer<QCoreApplication> app(new QCoreApplication(argc, argv));

    const QString uiFile = QString::fromLocal8Bit(UI_FILEPATH);
    Q_ASSERT(QFile::exists(uiFile));

    const QString qtTools = QLibraryInfo::location(QLibraryInfo::BinariesPath);
    const QString designer = QDir(qtTools).entryInfoList(QStringList(QLatin1String("*designer*")), QDir::Dirs | QDir::Files | QDir::Executable).value(0).absoluteFilePath();

    QString appDirPath = app->applicationDirPath();
#if defined(Q_OS_MACX)
    appDirPath.append(QLatin1String("/../../.."));
#endif
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.insert(QLatin1String("QT_PLUGIN_PATH"), appDirPath);

    QProcess process;
    process.setProcessChannelMode(QProcess::ForwardedChannels);
    process.setProcessEnvironment(env);
    process.setProgram(designer);
    process.setArguments(QStringList(uiFile));

    qDebug("%s: Running %s with file %s", Q_FUNC_INFO, qPrintable(designer), qPrintable(uiFile));
    qDebug("QT_PLUGIN_PATH=%s && %s %s", qPrintable(appDirPath), qPrintable(designer), qPrintable(uiFile));

    QObject::connect(&process, SIGNAL(error(QProcess::ProcessError)), app.data(), SLOT(quit()));
    QObject::connect(&process, SIGNAL(finished(int, QProcess::ExitStatus)), app.data(), SLOT(quit()));

    process.start();
    return app->exec();
}

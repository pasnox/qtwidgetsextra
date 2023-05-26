#include <QCoreApplication>
#include <QDir>
#include <QLibraryInfo>
#include <QProcess>
#include <QTemporaryFile>

#include <memory>

int main(int argc, char** argv) {
    std::unique_ptr<QCoreApplication> app(new QCoreApplication(argc, argv));

    const QString uiFile = QStringLiteral(":/QtWidgetsExtra.ui");
    Q_ASSERT(QFile::exists(uiFile));

    std::unique_ptr<QTemporaryFile> file(QTemporaryFile::createNativeFile(uiFile));

#if QT_VERSION >= 0x060000
    const QString qtTools = QLibraryInfo::path(QLibraryInfo::BinariesPath);
#else // QT_VERSION >= 0x060000
    const QString qtTools = QLibraryInfo::location(QLibraryInfo::BinariesPath);
#endif // QT_VERSION >= 0x060000
    const QString designer = QDir(qtTools).entryInfoList(QStringList(QStringLiteral("*designer*")), QDir::Dirs | QDir::Files | QDir::Executable).value(0).absoluteFilePath();

    QString appDirPath = app->applicationDirPath();
#if defined(Q_OS_MACX)
    appDirPath.append(QStringLiteral("/../../.."));
#endif
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.insert(QStringLiteral("QT_PLUGIN_PATH"), appDirPath);

    QProcess process;
    process.setProcessChannelMode(QProcess::ForwardedChannels);
    process.setProcessEnvironment(env);
    process.setProgram(designer);
    process.setArguments(QStringList(file->fileName()));

    qDebug("%s: Running %s with file %s", Q_FUNC_INFO, qPrintable(designer), qPrintable(file->fileName()));
    qDebug("QT_PLUGIN_PATH=%s && %s %s", qPrintable(appDirPath), qPrintable(designer), qPrintable(file->fileName()));

    QObject::connect(&process, &QProcess::errorOccurred, app.get(), &QCoreApplication::quit);
    QObject::connect(&process, qOverload<int, QProcess::ExitStatus>(&QProcess::finished), app.get(), &QCoreApplication::quit);

    process.start();
    return app->exec();
}

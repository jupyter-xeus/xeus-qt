#ifndef XQ_GENERIC_APPLICATION_HPP
#define XQ_GENERIC_APPLICATION_HPP

#include <QCoreApplication>

class xqGenericApplication : public QCoreApplication
{
    Q_OBJECT
public:
    xqGenericApplication(int &argc, char **argv);
    virtual ~xqGenericApplication() = default;

    /// Return a reference to the application singleton.
    /// It returns nullptr if the current application is not based on qSlicerCoreApplication class
    /// (for example, in Qt Designer executable loads widget plugins).
    static xqGenericApplication* application();

private:
};

#endif

#ifndef QTHREAD_H
#define QTHREAD_H
#include "QtConcurrent/QtConcurrent"
#include <QThread>
namespace QtTool{

}
#define RunAsync QtConcurrent::run
#define Sleep QThread::sleep(1)
#endif // QTHREAD_H

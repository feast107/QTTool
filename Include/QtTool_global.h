#ifndef QTTOOL_GLOBAL_H
#define QTTOOL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QTTOOL_LIBRARY)
#  define QTTOOL_EXPORT Q_DECL_EXPORT
#include "Path.h"
#include "Directory.h"
#include "File.h"
#include "Thread.h"
#include "Tool.hpp"
#include "Task.hpp"
#include "Http.h"
using namespace QtTool;
#else
#  define QTTOOL_EXPORT Q_DECL_IMPORT
#include "Path.h"
#include "Directory.h"
#include "File.h"
#include "Thread.h"
#include "Tool.hpp"
#include "Task.hpp"
#include "Http.h"
using namespace QtTool;
#endif

#endif // QTTOOL_GLOBAL_H

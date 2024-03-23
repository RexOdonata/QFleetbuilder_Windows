#ifndef SHIPVIEW_GLOBAL_H
#define SHIPVIEW_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SHIPVIEW_LIBRARY)
#  define SHIPVIEW_EXPORT Q_DECL_EXPORT
#else
#  define SHIPVIEW_EXPORT Q_DECL_IMPORT
#endif

#endif // SHIPVIEW_GLOBAL_H

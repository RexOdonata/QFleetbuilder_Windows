#ifndef LISTPRINTER_GLOBAL_H
#define LISTPRINTER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LISTPRINTER_LIBRARY)
#  define LISTPRINTER_EXPORT Q_DECL_EXPORT
#else
#  define LISTPRINTER_EXPORT Q_DECL_IMPORT
#endif

#endif //

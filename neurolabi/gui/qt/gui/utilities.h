#ifndef QT_GUI_UTILITIES_H
#define QT_GUI_UTILITIES_H

#include <QKeySequence>
#include <QString>

#include <QPushButton>

namespace neutu {

QString GetKeyString(int key, const Qt::KeyboardModifiers &modifier);
void SetHtmlIcon(QPushButton *button, const QString &text);

}

#endif // UTILITIES_H

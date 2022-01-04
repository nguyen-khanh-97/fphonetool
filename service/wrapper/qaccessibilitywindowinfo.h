#ifndef QACCESSIBILITYWINDOWINFO_H
#define QACCESSIBILITYWINDOWINFO_H
#include "qtwrapper.h"

class QAccessibilityNodeInfo;

class QAccessibilityWindowInfo : public QtWrapper
{
public:
    explicit QAccessibilityWindowInfo(QAndroidJniObject object);

    QString getTitle();
    int getType();
    int getLayer();
    int getId();
    bool isFocused();
    QAccessibilityNodeInfo getRoot();
    void recycle();
signals:

};

#endif // QACCESSIBILITYWINDOWINFO_H

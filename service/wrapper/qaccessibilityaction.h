#ifndef QACCESSIBILITYACTION_H
#define QACCESSIBILITYACTION_H

#include "qtwrapper.h"

class QAccessibilityAction : public QtWrapper
{
public:
    explicit QAccessibilityAction(QAndroidJniObject object);

    int getId();
    QString getLabel();

signals:

};

#endif // QACCESSIBILITYACTION_H

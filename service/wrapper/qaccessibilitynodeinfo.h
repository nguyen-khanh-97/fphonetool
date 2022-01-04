#ifndef QACCESSIBILITYNODEINFO_H
#define QACCESSIBILITYNODEINFO_H

#include <QAndroidJniObject>
#include "qtwrapper.h"
#include <QRect>

class QAccessibilityWindowInfo;
class QAccessibilityAction;

class QAccessibilityNodeInfo : public QtWrapper
{
public:
    explicit QAccessibilityNodeInfo(QAndroidJniObject object);

    bool performAction(int action);
    //Performs an action on the node.

    bool performAction(int action, QAndroidJniObject& arguments);
    //Performs an action on the node.

    bool refresh();
    //Refreshes this info with the latest state of the view it represents.

    void recycle();
    // Return an instance back to be reused.

    QList<QAccessibilityNodeInfo>	findAccessibilityNodeInfosByText(QString text);
    //Finds AccessibilityNodeInfos by text.

    QList<QAccessibilityNodeInfo>	findAccessibilityNodeInfosByViewId(QString viewId);
    //Finds AccessibilityNodeInfos by the fully qualified view id's resource name where a fully qualified id is of the from "package:id/id_resource_name".

    QAccessibilityNodeInfo	findFocus(int focus);
    //Find the view that has the specified focus type.

    QList<QAccessibilityAction>	getActionList();
    //Gets the actions that can be performed on the node.

    void	getBoundsInScreen(QRect& outBounds);
    //Gets the node bounds in screen coordinates.

    QAccessibilityNodeInfo	getChild(int index);
    //Get the child at given index.

    int	getChildCount();
    //Gets the number of children.

    QString	getClassName();
    //Gets the class this node comes from.

    QString	getContentDescription();
    //Gets the content description of this node.

    QString	getError();
    //Gets the error text of this node.

    QString getHintText();
    //Gets the hint text of this node.

    int	getInputType();
    //Gets the input type of the source as defined by InputType.

    QString	getPackageName();
    //Gets the package this node comes from.

    QAccessibilityNodeInfo	getParent();

    //Gets the parent.

    QString	getStateDescription();
    //Get the state description of this node.

    QString	getText();
    //Gets the text of this node.

    int	getTextSelectionEnd();
    //Gets the text selection end if text is selected.

    int	getTextSelectionStart();
    //Gets the text selection start or the cursor position.

    QString	getViewIdResourceName();
   // Gets the fully qualified resource name of the source view's id.

    QAccessibilityWindowInfo getWindow();
    //Gets the window to which this node belongs.

    int	getWindowId();
    //Gets the id of the window from which the info comes from.

    int	hashCode();
    //Returns a hash code value for the object.

    bool isAccessibilityFocused();
    //Gets whether this node is accessibility focused.

    bool	isCheckable();
    //Gets whether this node is checkable.

    bool	isChecked();
    //Gets whether this node is checked.

    bool	isClickable();
    //Gets whether this node is clickable.

    bool	isContentInvalid();
    //Gets if the content of this node is invalid.

    bool	isContextClickable();
    //Gets whether this node is context clickable.

    bool	isDismissable();
    //Gets if the node can be dismissed.

    bool	isEditable();
    //Gets if the node is editable.

    bool	isEnabled();
    //Gets whether this node is enabled.

    bool	isFocusable();
    // whether this node is focusable.

    bool	isFocused();
    //Gets whether this node is focused.

    bool	isHeading();
    //Returns whether node represents a heading.

    bool	isImportantForAccessibility();
    //Returns whether the node originates from a view considered important for accessibility.

    bool	isLongClickable();
    //Gets whether this node is long clickable.

    bool	isMultiLine();
    //Gets if the node is a multi line editable text.

    bool	isPassword();
    //Gets whether this node is a password.

    bool	isScreenReaderFocusable();
    //Returns whether the node is explicitly marked as a focusable unit by a screen reader.

    bool	isScrollable();
    //Gets if the node is scrollable.

    bool	isSelected();
    //Gets whether this node is selected.

    bool	isShowingHintText();
    //Returns whether the node's text represents a hint for the user to enter text.

    bool	isTextEntryKey();
    //Returns whether node represents a text entry key that is part of a keyboard or keypad.

    bool	isVisibleToUser();
    //Gets whether this node is visible to the user.

};

#endif // QACCESSIBILITYNODEINFO_H

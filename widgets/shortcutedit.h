#ifndef SHORTCUTEDIT_H
#define SHORTCUTEDIT_H

#include <QLineEdit>

QT_BEGIN_NAMESPACE
class QToolButton;
QT_END_NAMESPACE

/**
 * @brief Widget for editing key sequences.
 *
 * Just a modified QLineEdit.
 */
class ShortcutEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit ShortcutEdit(QWidget *parent = 0);
    
protected:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void resizeEvent(QResizeEvent *);
private:
    bool isModifier(int key);
    QToolButton *mClearButton;
private slots:
    void updateClearButton(const QString& text);
};

#endif // SHORTCUTEDIT_H

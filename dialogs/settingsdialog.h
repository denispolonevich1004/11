#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QComboBox;
class QSpinBox;
class QCheckBox;
class QLineEdit;
class QTreeWidget;
class QTreeWidgetItem;
class QPushButton;
class QKeySequence;
QT_END_NAMESPACE

class ShortcutEdit;

/**
 * @brief Dialog for changing application settings.
 *
 */
class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent);
    ~SettingsDialog();

    /**
     * @brief Get all settings from form and send it to data singleton.
     *
     */
    void sendSettingsToSingleton();

private:
    void initializeGui();
    int getLanguageIndex();
    /**
     * @brief Create top level item in tree widget and create children items with shortcuts.
     *
     * @param name Top level item name.
     * @param QMap<QString, QString> Map with all shortcuts for this group.
     */
    void createItemsGroup(const QString &name, const QMap<QString, QKeySequence> &shortcuts);

    QComboBox *mLanguageBox;
    QSpinBox *mWidth, *mHeight, *mHistoryDepth, *mAutoSaveInterval;
    QCheckBox *mIsAutoSave;
    QCheckBox *mIsRestoreWindowSize;
    ShortcutEdit *mShortcutEdit;
    QTreeWidget *mShortcutsTree;
    QCheckBox *mIsAskCanvasSize;
    
signals:
    
private slots:
    void itemSelectionChanged();
    void textChanged(const QString &text);
    void reset();
    
};

#endif // SETTINGSDIALOG_H

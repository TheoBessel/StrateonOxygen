#ifndef CENTRALTABWIDGET_H
#define CENTRALTABWIDGET_H

#include <QWidget>
#include "../Editor/Editor.h"

class FileGestion;
class QTreeView;
class QTreeWidgetItem;
class QTreeWidget;
class QTabWidget;
class QHBoxLayout;


class CentralTabWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CentralTabWidget(QWidget *parent = nullptr);
    QTabWidget* m_tabWidget = nullptr;
    Editor* editor = nullptr;
    FileGestion* m_manager;

private:
    QHBoxLayout* m_layout = nullptr;

signals:

public slots:
};

#endif // CENTRALTABWIDGET_H

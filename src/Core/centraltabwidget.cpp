#include "centraltabwidget.h"
#include "QHBoxLayout"
#include "../Editor/Editor.h"
#include "../Editor/filegestion.h"

CentralTabWidget::CentralTabWidget(QWidget *parent) : QWidget(parent)
{

    m_layout = new QHBoxLayout(this);
    editor = new Editor(this);
    m_manager = new FileGestion(this);
    m_manager->hide();
    m_layout->setSpacing(0);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->addWidget(m_manager, 20);
    m_layout->addWidget(editor, 80);

    setLayout(m_layout);
}

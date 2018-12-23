/*
    * MIT License
    *
    * Copyright (c) 2018 Theo Bessel
    *
    * Permission is hereby granted, free of charge, to any person obtaining a copy
    * of this software and associated documentation files (the "Software"), to deal
    * in the Software without restriction, including without limitation the rights
    * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    * copies of the Software, and to permit persons to whom the Software is
    * furnished to do so, subject to the following conditions:
    *
    * The above copyright notice and this permission notice shall be included in all
    * copies or substantial portions of the Software.
    *
    * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    * SOFTWARE.
*/

#include "PrincipalWidget.h"
#include "../Editor/Editor.h"
#include "../Editor/filegestion.h"
#include "MainWindow.h"
#include <QFileDialog>
#include <QTextStream>
#include "../SyntaxicColoration/SynColoCCpp.h"
#include "../SyntaxicColoration/SynColoHTML.h"
#include <QHBoxLayout>
#include <QFile>
#include <QTreeWidgetItem>
#include <QPushButton>
#include <iostream>
#include <QStyleFactory>
#include "centraltabwidget.h"
#include <QLabel>

PrincipalWidget::PrincipalWidget(QWidget *parent) : QWidget(parent)
{

    m_tabWidget = new QTabWidget();
    m_tabWidget->setStyle(QStyleFactory::create("fusion"));
    m_tabWidget->setStyleSheet("QTabWidget{background: rgb(48,61,74); color: rgb(48,61,74); border: none; /*border: 1px solid white;*/} QTabWidget::tab-bar{ /*border: 1px solid white;*/} QTabBar::tab{margin: 1px; padding: 5px; /*border: 1px solid white;*/ background: rgb(48,61,74); color: grey;} QTabBar::tab:selected {margin: 1px; padding: 5px; /*border: 1px solid white;*/ color: white; }QTabBar::close-button {image: url(:/icons/close.png);} QTabBar::scroller {border: 1px solid white;}");
    m_tabWidget->setTabsClosable(true);
    m_tabWidget->setUsesScrollButtons(true);
    //m_tabWidget->scroll();
    //m_tabWidget->addTab(new CentralTabWidget(this), QString("strateon : "));


    //QWidget* centralWidget = new QWidget();
    //m_CentralTabWidget = new CentralTabWidget;

    QWidget* tabButton = new QWidget();
    QPushButton* m_newTab = new QPushButton("+");
    QLabel* label = new QLabel("");
    m_newTab->setFixedSize(25, 25);
    m_newTab->setStyleSheet("border: 0.5px solid white; border-radius: 3px; color: white;");
    m_layout = new QHBoxLayout(this);
    QHBoxLayout* newTab = new QHBoxLayout(this);
    newTab->setSpacing(0);
    newTab->setContentsMargins(0, 0, 0, 0);
    newTab->addWidget(m_newTab, 100);
    newTab->addWidget(label, 0);
    tabButton->setLayout(newTab);
    editor = new Editor(this);
    editor->hide();
    m_manager = new FileGestion(this);
    m_manager->hide();
    m_layout->setSpacing(0);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->addWidget(m_tabWidget);
    //m_layout->addWidget(buttontest, 5);
    m_tabWidget->setCornerWidget(tabButton, Qt::TopRightCorner);

    setLayout(m_layout);

    connect(m_tabWidget, &QTabWidget::tabCloseRequested, this, &PrincipalWidget::closeTab);
    connect(m_newTab, &QPushButton::clicked, this, &PrincipalWidget::addNewTab);
    connect(m_manager, &FileGestion::itemClicked, this, &PrincipalWidget::openFileFromTreeView);
    addNewTab();
}

void PrincipalWidget::addNewTab(){
    m_tabWidget->insertTab(i, new CentralTabWidget(this), QString("strateon : " + QString::number(i)));
    m_tabWidget->setTabIcon(i, QIcon(":/logo/logo.png"));
    i++;
    Cocoa::changeTitleBarColor(winId(), 0.188, 0.239, 0.290);

}
void PrincipalWidget::closeTab(int index){
    m_tabWidget->removeTab(index);
    i--;
    Cocoa::changeTitleBarColor(winId(), 0.188, 0.239, 0.290);
}

/*void PrincipalWidget::saveFile(bool test)
{ if (test){}
    QString EditorContent = editor->toPlainText();
    QString FileName = QFileDialog::getSaveFileName(this, "Enregistrer...", "sansTitre.txt");
    QString Name = QFileInfo(FileName).fileName();
    QFile File(FileName);
    //items.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString(Name))));
    //fileView->insertTopLevelItems(0, items);
    if (File.open(QIODevice::WriteOnly))
    {
        QTextStream out(&File);
        out << EditorContent;
    }
}*/



void PrincipalWidget::openFile(bool test)
{ if (test){}
    QString FileName = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString());
    QString Name = QFileInfo(FileName).fileName();
    QFile File(FileName);
    //items.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString(Name))));
    //fileView->insertTopLevelItems(0, items);
    if (File.open(QIODevice::ReadOnly))
    {
        editor->document()->setPlainText(File.readAll());
        QString row = QString::number(i);

        std::cout << i << std::endl;

        items.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(row)));
        items.at(i)->setData(i, i, FileName);
        QString text = items.at(i)->data(i,i).toString();
        std::cout << i << std::endl;
        std::cout << text.toStdString() << std::endl;
        m_manager->insertTopLevelItems(i, items);
        i++;
    }
}



void PrincipalWidget::saveFile(bool test)
{ if (test){}
    QString EditorContent = editor->toPlainText();
    QString FileName = QFileDialog::getSaveFileName(this, "Enregistrer...", "sansTitre.txt");
    QString Name = QFileInfo(FileName).fileName();
    QFile File(FileName);
    if (File.open(QIODevice::WriteOnly))
    {
         QTextStream out(&File);
         out << EditorContent;
         QString row = QString::number(i);

         std::cout << i << std::endl;

         items.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(row)));
         items.at(i)->setData(i, i, FileName);
         QString text = items.at(i)->data(i,i).toString();
         std::cout << i << std::endl;
         std::cout << text.toStdString() << std::endl;
         m_manager->insertTopLevelItems(i, items);
         i++;
    }
}

void PrincipalWidget::openFileFromTreeView(QTreeWidgetItem *treeItem, int row)
{
    std::cout << row << std::endl;
    std::cout << treeItem->text(row).toInt() << std::endl;
    QString text = treeItem->data(treeItem->text(row).toInt(), treeItem->text(row).toInt()).toString();
    QFile File(text);
    if (File.open(QIODevice::ReadOnly))
    {
        editor->document()->setPlainText(File.readAll());
    }
}






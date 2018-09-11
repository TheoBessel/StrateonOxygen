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

#include "MainWindow.h"
#include "PrincipalWidget.h"
#include <QMenuBar>
#include <QMessageBox>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    m_menuBar = new QMenuBar(this);
    QMenu *Edit = m_menuBar->addMenu("File");
    saveAction = Edit->addAction("SaveFile");

    m_principalWidget = new PrincipalWidget(this);
    connect(saveAction, &QAction::triggered, m_principalWidget, &PrincipalWidget::saveFile);
    setCentralWidget(m_principalWidget);

}

void MainWindow::closeEvent(QCloseEvent *event) {
    int m_closeMessageBox = QMessageBox::warning(this, tr("My Application"),
                                                 tr("The document has been modified.\n"
                                                    "Do you want to save your changes?"),
                                                 QMessageBox::Discard
                                                 | QMessageBox::Cancel
                                                 | QMessageBox::Save );
    if (m_closeMessageBox == QMessageBox::Save) {
        bool mainWindowDestructed = true;
        m_principalWidget->saveFile(mainWindowDestructed);
        event->accept();
    }
    else if (m_closeMessageBox == QMessageBox::Discard) {
        event->accept();
    }else {
        event->ignore();
    }
}

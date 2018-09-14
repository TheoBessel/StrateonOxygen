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
#include "Editor/Editor.h"
#include <QMenuBar>
#include <QMessageBox>
#include <QCloseEvent>
#include <QStatusBar>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    m_menuBar = new QMenuBar(this);
    m_statusBar = new QStatusBar(this);

    statusMessageCharaters = new QLabel(this);
    statusMessageCursor = new QLabel(this);
    statusMessageWordNumber = new QLabel(this);
    m_statusBar->addWidget(statusMessageCharaters);
    m_statusBar->addWidget(statusMessageCursor);
    m_statusBar->addWidget(statusMessageWordNumber);
    setStatusBar(m_statusBar);
    QMenu *Edit = m_menuBar->addMenu("File");
    saveAction = Edit->addAction("SaveFile");
    openAction = Edit->addAction("OpenFile");
    m_statusBar->showMessage("Ready");
    m_statusBar->setStyleSheet("background: rgb(48,61,74); color: white; border-color: rgb(48,61,74);");
    m_principalWidget = new PrincipalWidget(this);
    setCentralWidget(m_principalWidget);
    m_statusBar->setSizeGripEnabled(true);
    statusMessageCursor->setText("  Cursor Position :  pos : x / y  |  " );
    connect(saveAction, &QAction::triggered, m_principalWidget, &PrincipalWidget::saveFile);
    connect(openAction, &QAction::triggered, m_principalWidget, &PrincipalWidget::openFile);
    connect(m_principalWidget->editor, &QPlainTextEdit::textChanged, this, &MainWindow::showCharactersNumber);
    connect(m_principalWidget->editor, &QPlainTextEdit::cursorPositionChanged, this, &MainWindow::showCursorPosition);
    connect(m_principalWidget->editor, &QPlainTextEdit::textChanged, this, &MainWindow::showWordNumber);
}

void MainWindow::showCharactersNumber(){
    QString editorContent{m_principalWidget->editor->toPlainText()};
    editorContent.remove(" ");
    editorContent.remove("\n");
    editorContent.remove("\t");

    int characters{editorContent.size()};
    QString charactersNumber = QString::number(characters);

    statusMessageCharaters->setText("   Number of caracters : " + charactersNumber + "  |  ");
}

void MainWindow::showCursorPosition(){
    int xCursorPos = {m_principalWidget->editor->textCursor().blockNumber() + 1};
    int yCursorPos = {m_principalWidget->editor->textCursor().positionInBlock() + 1};

    QString xCursorPosition = QString::number(xCursorPos);
    QString yCursorPosition = QString::number(yCursorPos);

    statusMessageCursor->setText("  Cursor Position :  pos : " + xCursorPosition + " / " + yCursorPosition + "  |  " );

}

void MainWindow::showWordNumber(){

    int wordCounter = m_principalWidget->editor->toPlainText().split(QRegExp("(\\s|\\n|\\r)+"), QString::SkipEmptyParts).count();
    QString wordNumber = QString::number(wordCounter);
    statusMessageWordNumber->setText("  Word Number " + wordNumber + "  |  " );
}

void MainWindow::closeEvent(QCloseEvent *event) {
    QString trimmedEditor{m_principalWidget->editor->toPlainText()};
    trimmedEditor.remove(" ");
    trimmedEditor.remove("\n");
    trimmedEditor.remove("\t");

    if (!trimmedEditor.isEmpty()){
        int m_closeMessageBox = QMessageBox::warning(this, tr("My Application"),
                                                     tr("The document has been modified.\n"
                                                        "Do you want to save your changes?"),
                                                     QMessageBox::Discard |
                                                     QMessageBox::Cancel |
                                                     QMessageBox::Save );
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
    else {
        event->accept();
    }
}

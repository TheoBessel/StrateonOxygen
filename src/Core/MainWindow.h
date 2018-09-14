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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLabel;
class PrincipalWidget;
class QCloseEvent;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    PrincipalWidget *m_principalWidget = nullptr;
    QMenuBar *m_menuBar = nullptr;
    QStatusBar *m_statusBar = nullptr;
    QAction *saveAction = nullptr;
    QAction *openAction = nullptr;
    QLabel *statusMessageCharaters = nullptr;
    QLabel *statusMessageCursor = nullptr;
    QLabel *statusMessageWordNumber = nullptr;


    int xpos = {0};
    int ypos = {1};
    int xCursorOldPos = {0};
    int yCursorOldPos = {0};

    void showCharactersNumber();
    void showCursorPosition();
    void showWordNumber();

protected:    
    void closeEvent(QCloseEvent *event) override;

};

#endif // MAINWINDOW_H

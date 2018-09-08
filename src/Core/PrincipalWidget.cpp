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
#include <QFileDialog>
#include <QTextStream>

PrincipalWidget::PrincipalWidget(QWidget *parent) : QWidget(parent)
{
    m_layout = new QHBoxLayout(this);
    m_editor = new Editor(this);

    setLayout(m_layout);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->addWidget(m_editor);
}

void PrincipalWidget::saveFile(bool test)
{ if (test == true){}
    QString EditorContent = m_editor->toPlainText();
    QString FileName = QFileDialog::getSaveFileName(this, "Enregistrer...", "Sans titre 1.txt");
    QFile File(FileName);
    if (File.open(QIODevice::WriteOnly))
    {
        QTextStream out(&File);
        out << EditorContent;
        setWindowTitle("Strateon - " + FileName);

    }

}


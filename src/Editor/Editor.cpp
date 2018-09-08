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

#include <QtWidgets>

#include "Editor/Editor.h"
#include "../SyntaxicColoration/SynColoCCpp.h"

Editor::Editor(QWidget *parent) : QPlainTextEdit(parent)
{
    LineNumber = new LineNumberClass(this);

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(UpdateLineNumberWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(UpdateLineNumber(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(HighlightCurrentLine()));

    UpdateLineNumberWidth(0);
    HighlightCurrentLine();
    this->setStyleSheet("background-color: rgb(48,61,74);");

    highlighter = new Highlighter(this->document());

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    verticalScrollBar()->hide();
    verticalScrollBar()->resize(0, 0);
    setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    horizontalScrollBar()->hide();
    horizontalScrollBar()->resize(0, 0);
}

int Editor::LineNumberWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

    return space;
}

void Editor::UpdateLineNumberWidth(int /* newBlockCount */)
{
    setViewportMargins(LineNumberWidth(), 0, 0, 0);
}

void Editor::UpdateLineNumber(const QRect &rect, int dy)
{
    if (dy)
        LineNumber->scroll(0, dy);
    else
        LineNumber->update(0, rect.y(), LineNumber->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        UpdateLineNumberWidth(0);
}

void Editor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    LineNumber->setGeometry(QRect(cr.left(), cr.top(), LineNumberWidth(), cr.height()));
}

void Editor::HighlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(24,30,37).lighter(160);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void Editor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(LineNumber);
    painter.fillRect(event->rect(), QColor(48,61,74));


    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::white);
            painter.drawText(0, top, LineNumber->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}


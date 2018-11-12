#include <QApplication>
#include <QWidget>
#import <cocoa/Cocoa.h>
#include "Core/MainWindow.h"

int main(int argv, char **args)
{
    QApplication app(argv, args);
    MainWindow w;


    NSView* view = (NSView*)w.effectiveWinId();
    NSWindow* window = [view window];
    window.titlebarAppearsTransparent = YES;
    window.backgroundColor = [NSColor clearColor];
    window.backgroundColor = [NSColor colorWithRed:0.188 green:0.239 blue:0.290 alpha:1.0];

    window.appearance = [NSAppearance appearanceNamed:NSAppearanceNameVibrantDark];

    w.show();

    return app.exec();
}

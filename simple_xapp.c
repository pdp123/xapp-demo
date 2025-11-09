#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    Display *d;
    Window w;
    XEvent e;
    int s;

    d = XOpenDisplay(NULL);
    if(d == NULL) {
        fprintf(stderr, "Cannot open display");
        exit(1);
    }

    s = DefaultScreen(d);

    w = XCreateSimpleWindow(
        d, RootWindow(d, s),
        100, 100,
        400, 300, 
        1,
        BlackPixel(d, s),
        WhitePixel(d, s)
    );

    XSelectInput(d, w, ExposureMask | KeyPressMask | ButtonPressMask);

    XStoreName(d, w, "My First X Application");

    XMapWindow(d, w);

    while(1) {
        XNextEvent(d, &e);
        if(e.type == Expose) {
            XDrawString(d, w, DefaultGC(d, s), 150, 150, "Hello, X11 World!", 16);
        }
        if(e.type == ButtonPress) {
            printf("Clicked at %d,%d button %u\n", e.xbutton.x, e.xbutton.y, e.xbutton.button);
            printf("Mouse Clicked Exiting...\n");
            // break;
        }
        if(e.type == KeyPress) {
            printf("Clicked at %d,%d button %u\n", e.xbutton.x, e.xbutton.y, e.xbutton.button);
            printf("Key Pressed Existing .. \n");
            // break;
        }
    }

    XCloseDisplay(d);
    return 0;
}
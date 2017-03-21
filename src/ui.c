/* nuklear - v1.32.0 - public domain */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>

#include "qpc.h"
#include "signals.h"

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_IMPLEMENTATION
#define NK_XLIB_IMPLEMENTATION
#include "nuklear.h"
#include "nuklear_xlib.h"

#define DTIME           20
#define WINDOW_WIDTH    800
#define WINDOW_HEIGHT   600

#define UNUSED(a) (void)a
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) < (b) ? (b) : (a))
#define LEN(a) (sizeof(a)/sizeof(a)[0])

typedef struct XWindow XWindow;
struct XWindow {
    Display *dpy;
    Window root;
    Visual *vis;
    Colormap cmap;
    XWindowAttributes attr;
    XSetWindowAttributes swa;
    Window win;
    int screen;
    XFont *font;
    unsigned int width;
    unsigned int height;
    Atom wm_delete_window;
};

static void
die(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fputs("\n", stderr);
    exit(EXIT_FAILURE);
}

static void*
xcalloc(size_t siz, size_t n)
{
    void *ptr = calloc(siz, n);
    if (!ptr) die("Out of memory\n");
    return ptr;
}

static long
timestamp(void)
{
    struct timeval tv;
    if (gettimeofday(&tv, NULL) < 0) return 0;
    return (long)((long)tv.tv_sec * 1000 + (long)tv.tv_usec/1000);
}

static void
sleep_for(long t)
{
    struct timespec req;
    const time_t sec = (int)(t/1000);
    const long ms = t - (sec * 1000);
    req.tv_sec = sec;
    req.tv_nsec = ms * 1000000L;
    while(-1 == nanosleep(&req, &req));
}

XWindow xw;
struct nk_context *ctx;
static unsigned short running = 0;
int ui(void)
{
    /* X11 */
    memset(&xw, 0, sizeof xw);
    xw.dpy = XOpenDisplay(NULL);
    if (!xw.dpy) die("Could not open a display; perhaps $DISPLAY is not set?");
    xw.root = DefaultRootWindow(xw.dpy);
    xw.screen = XDefaultScreen(xw.dpy);
    xw.vis = XDefaultVisual(xw.dpy, xw.screen);
    xw.cmap = XCreateColormap(xw.dpy,xw.root,xw.vis,AllocNone);

    xw.swa.colormap = xw.cmap;
    xw.swa.event_mask =
        ExposureMask | KeyPressMask | KeyReleaseMask |
        ButtonPress | ButtonReleaseMask| ButtonMotionMask |
        Button1MotionMask | Button3MotionMask | Button4MotionMask | Button5MotionMask|
        PointerMotionMask | KeymapStateMask;
    xw.win = XCreateWindow(xw.dpy, xw.root, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0,
        XDefaultDepth(xw.dpy, xw.screen), InputOutput,
        xw.vis, CWEventMask | CWColormap, &xw.swa);

    XStoreName(xw.dpy, xw.win, "X11");
    XMapWindow(xw.dpy, xw.win);
    xw.wm_delete_window = XInternAtom(xw.dpy, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(xw.dpy, xw.win, &xw.wm_delete_window, 1);
    XGetWindowAttributes(xw.dpy, xw.win, &xw.attr);
    xw.width = (unsigned int)xw.attr.width;
    xw.height = (unsigned int)xw.attr.height;

    /* GUI */
    xw.font = nk_xfont_create(xw.dpy, "fixed");
    ctx = nk_xlib_init(xw.font, xw.dpy, xw.screen, xw.win, xw.width, xw.height);

    running = 1;

}

void ui_login() {
	/* GUI */
	if (nk_begin(ctx, "Essence - Login", nk_rect(50, 50, 200, 200),
		NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_CLOSABLE|NK_WINDOW_TITLE))
	{
		nk_layout_row_dynamic(ctx, 30, 2);
		nk_label(ctx, "Username", NK_TEXT_LEFT);
		nk_text(ctx, "Username", 8, NK_TEXT_LEFT);
		nk_layout_row_dynamic(ctx, 30, 2);
		nk_label(ctx, "Password", NK_TEXT_LEFT);
		nk_text(ctx, "Password", 8, NK_TEXT_LEFT);
		nk_layout_row_dynamic(ctx, 25, 1);
		if (nk_button_label(ctx, "Login"))
			fprintf(stdout, "button pressed\n");
	}
	nk_end(ctx);

    if (nk_window_is_closed(ctx, "Essence - Login")) {
    	ui_cleanup();
    	return;
    }
}

void ui_character_create() {
	/* GUI */
	if (nk_begin(ctx, "Essence - Character Creation", nk_rect(50, 50, 200, 200),
		NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_CLOSABLE|NK_WINDOW_TITLE))
	{
	}
	nk_end(ctx);

    if (nk_window_is_closed(ctx, "Essence - Character Creation")) {
    	ui_cleanup();
    	return;
    }
}

void ui_character_select() {
	/* GUI */
	if (nk_begin(ctx, "Essence - Character Select", nk_rect(50, 50, 200, 200),
		NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_CLOSABLE|NK_WINDOW_TITLE))
	{
	}
	nk_end(ctx);

    if (nk_window_is_closed(ctx, "Essence - Character Select")) {
    	ui_cleanup();
    	return;
    }
}

void ui_in_game() {
	/* GUI */
	if (nk_begin(ctx, "Essence - In Game", nk_rect(50, 50, 200, 200),
		NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_CLOSABLE|NK_WINDOW_TITLE))
	{
	}
	nk_end(ctx);

    if (nk_window_is_closed(ctx, "Essence - In Game")) {
    	ui_cleanup();
    	return;
    }
}

void ui_tick(enum_t current_window) {
	if (running == 0) {
		return;
	}
	/* Input */
	XEvent evt;
	nk_input_begin(ctx);
	while (XPending(xw.dpy)) {
		XNextEvent(xw.dpy, &evt);
		if (evt.type == ClientMessage) {
			ui_cleanup();
			return;
		}
		if (XFilterEvent(&evt, xw.win)) return;
		nk_xlib_handle_event(xw.dpy, xw.screen, xw.win, &evt);
	}
	nk_input_end(ctx);

	switch (current_window) {
	case (UI_LOGIN): {
		ui_login();
		break;
	}
	case (UI_CHARACTER_CREATE): {
		ui_character_create();
		break;
	}
	case (UI_CHARACTER_SELECT): {
		ui_character_select();
		break;
	}
	case (UI_IN_GAME): {
		ui_in_game();
		break;
	}
	}

	if (running == 0) {
		return;
	}

	XClearWindow(xw.dpy, xw.win);
	nk_xlib_render(xw.win, nk_rgb(30,30,30));
	XFlush(xw.dpy);
}

void ui_cleanup() {
	running = 0;
    nk_xfont_del(xw.dpy, xw.font);
    nk_xlib_shutdown();
    XUnmapWindow(xw.dpy, xw.win);
    XFreeColormap(xw.dpy, xw.cmap);
    XDestroyWindow(xw.dpy, xw.win);
    XCloseDisplay(xw.dpy);
    QF_stop();
}


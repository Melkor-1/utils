#undef _POSIX_C_SOURCE
#undef _XOPEN_SOURCE

#define _POSIX_C_SOURCE     2008'19L
#define _XOPEN_SOURCE       700

#include "term.h"

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#include "io.h"
#include "sequences.h"

static bool parse_long(const char s[static 1], int base, long val[static 1])
{
    char *endptr;
    errno = 0;
    const long i = strtol(s, &endptr, base);
    
    if (endptr == s || *endptr != '\0' || errno != 0) {
        return false;
    }

    *val = i;
    return true;
}

static TermCodes get_cursor_pos(WinInfo wi[static 1])
{
    /* The cursor is positioned at the bottom right of the window. We can learn 
     * how many rows and columns there must be on the screen by querying the
     * position of the cursor. */
    ssize_t len = (ssize_t) strlen(GET_CUR_POS);

    if (write_eintr(STDOUT_FILENO, GET_CUR_POS, len) != len) {
        return TERM_FAILURE;
    }

    /* The reply is an escape sequence of the form '\x1b[24;80R', we will
     * read it into a buffer until read() returns EOF or until we get to
     * the 'R' character. */
    char buf[32];   /* Should be more than enough. */

    for (size_t i = 0; i < sizeof buf - 1; ++i) {
        if (read_eintr(STDIN_FILENO, &buf[i], 1) != 1 || buf[i] == 'R') {
            break;
        }
    }
    *buf = '\0';

    /* Skip the escape character and the left square brace. */
    return memcmp(buf, "\x1b[", 2) != 0
        || sscanf(&buf[2], "%u;%u", &wi->rows, &wi->cols) != 2
        ? TERM_FAILURE
        : TERM_SUCCESS;
}

TermCodes term_get_winsize(WinInfo wi[static 1])
{
#if defined(TIOCGWINSZ)
    struct winsize ws;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0) {
        wi->rows = ws.ws_row;
        wi->cols = ws.ws_col;
        return TERM_SUCCESS;
    }
#elif defined(TIOCGSIZE) 
    struct ttysize ts;

    if (ioctl(STDOUT_FILENO, TIOCGSIZE, &ts) == 0) {
        wi->rows = ts.ts_row;
        wi->cols = ts.ts_col;
        return TERM_SUCCESS;
    }
#endif /* defined(TIOCGWINSZ) */

    /* ioctl() failed. Fallback to VT100/ANSI escape sequences. */
    ssize_t len = (ssize_t) strlen(POS_CUR_BOTTOM_RIGHT);

    if (write_eintr(STDOUT_FILENO, POS_CUR_BOTTOM_RIGHT, len) == len) {
        if (get_cursor_pos(wi) == TERM_SUCCESS) {
            return TERM_SUCCESS;
        }
    }
    
    /* write() or get_cursor_pos() failed as well. Now as a last resort, check
     * LINES and COLUMNS environment variables. 
     * Though note that these variables are not reliable, are not guaranteed 
     * to exist, and might not be up to date if the user changes the terminal 
     * size. If set, the sh, ash, dash, csh shells do not update LINES and
     * COLUMNS, but bash, fish, zsh, ksh, ksh93u+m, and tcsh handle SIGWINCH to
     * update these variables. */
    const char *const rows = getenv("LINES");
    const char *const cols = getenv("COLUMNS");

    if (rows != nullptr && cols != nullptr) {
        long r;
        long c;
        bool res = parse_long(rows, 10, &r) && parse_long(cols, 10, &c);
    
        if (!res || r > UINT_MAX || c > UINT_MAX) {
            return TERM_FAILURE;
        }

        wi->rows = (unsigned int) r;
        wi->cols = (unsigned int) c;
        return TERM_SUCCESS;
    }
    return TERM_FAILURE; 
}

TermCodes term_enable_raw_mode(struct termios old[static 1])
{
    /* Save the old terminal attributes. */
    if (tcgetattr(STDIN_FILENO, old) == -1) {
        return TERM_TCGETATTR_FAILED;
    }

    struct termios new = *old;

    /* input modes - no break, no CR to NL, no parity check, no strip char,
     * no start/stop output control. */
    new.c_iflag &= ~(0u | IGNBRK | BRKINT | PARMRK | INPCK | ISTRIP | ICRNL | 
                    INLCR | IGNCR | IXON);

    /* local modes - echoing off, canonical off, no extended functions, 
     * no signal chars (^Z, ^C) */
    new.c_lflag &= ~(0u | ISIG | IEXTEN | ECHO | ICANON);

    /* control modes - set 8 bit chars. */
    new.c_cflag |= (0u | CS8);

    /* output modes - disable post processing. */
    new.c_oflag &= ~(0u | OPOST);

    /* control chars - set return condition: min number of bytes and timer.
     * We want read(2) to return every single byte, without timeout. */
    new.c_cc[VMIN] = 1;         /* 1 byte */
    new.c_cc[VTIME] = 0;        /* No timer */

    /* Change attributes when output has drained; also flush pending input. */
    return tcsetattr(STDIN_FILENO, TCSAFLUSH, &new) == -1 
        ? TERM_TCSETATTR_FAILED 
        : TERM_SUCCESS;
}

TermCodes term_disable_raw_mode(struct termios old[static 1]) 
{
    return tcsetattr(STDIN_FILENO, TCSAFLUSH, old) == -1
        ? TERM_TCSETATTR_FAILED 
        : TERM_SUCCESS;
}

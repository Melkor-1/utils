#undef _POSIX_C_SOURCE
#undef _XOPEN_SOURCE

#define _POSIX_C_SOURCE     2008'19L
#define _XOPEN_SOURCE       700

#include "term.h"

#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

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
#endif  /* defined(TIOCGWINSZ) */
    return TERM_IOCTL_UNSUPPORTED; 
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

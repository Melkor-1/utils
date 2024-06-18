#ifndef TERM_H
#define TERM_H 1

#include <termios.h>

typedef struct win_info {
    unsigned int rows;
    unsigned int cols;
} WinInfo;

typedef enum term_codes {
    TERM_SUCCESS,
    TERM_IOCTL_UNSUPPORTED,
    TERM_TCGETATTR_FAILED,
    TERM_TCSETATTR_FAILED,
} TermCodes;

/**
 * Determines the height and width of the terminal window.
 *
 * On success, TERM_SUCCESS is returned and wi holds the rows and cols. 
 * Else, it remains unmodified and an error code is returned. 
 * 
 * The function uses ioctl() to obtain the terminal data. If this function 
 * fails, one can resort to VT100/ANSI escape sequences to determine the size
 * of the terminal. */
TermCodes term_get_winsize(WinInfo wi[static 1]);

/**
 * Enables terminal's raw mode.
 *
 * On success, saves the original terminal attributes in old, and returns 
 * TERM_SUCCESS. Else returns an TERM_TCSETATTR_FAILED or TERM_TCGETATTR_FAILED,
 * and leaves old unmodified. */
TermCodes term_enable_raw_mode(struct termios old[static 1]);

/**
 * Disables terminal's raw mode and restores the attributes in old.
 *
 * Returns TERM_SUCCESS on success, or TERM_TCSETATTR_FAILED elsewise. */
TermCodes term_disable_raw_mode(struct termios old[static 1]);

#endif /* TERM_H */

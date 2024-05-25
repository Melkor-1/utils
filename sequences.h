#ifndef SEQUENCES_H
#define SEQUENCES_H 1

/* The strings below can hide behind such functions: 
    clear_window();
    clear_window_upto_cursor();
    clear_window_upto_end();
    clear_line_upto_end();
    pos_cursor_top_left();
    pos_cursor_bottom_right();
    hide_cursor();
    show_cursor();
    reset_all_attrib();
    invert_color();
    normal_color();
    set_foreground_color();
    set_background_color();
*/

[[maybe_unused]] static constexpr char CLR_WIN[]                   = "\x1b[2J";
[[maybe_unused]] static constexpr char CLR_WIN_UPTO_CUR[]          = "\x1b[1J";
[[maybe_unused]] static constexpr char CLR_WIN_UPTO_END[]          = "\x1b[0J";
[[maybe_unused]] static constexpr char CLR_LINE_UPTO_END[]         = "\x1b[K";

[[maybe_unused]] static constexpr char POS_CUR_TOP_LEFT[]          = "\x1b[H";
[[maybe_unused]] static constexpr char POS_CUR_BOTTOM_RIGHT[]      = "\x1b[999C\x1b[999B";
[[maybe_unused]] static constexpr char GET_CUR_POS[]               = "\x1b[6n";
[[maybe_unused]] static constexpr char HIDE_CUR[]                  = "\x1b[?25l";
[[maybe_unused]] static constexpr char SHOW_CUR[]                  = "\x1b[?25h";

[[maybe_unused]] static constexpr char RESET_ALL_ATTRIB[]          = "\x1b[0m";

[[maybe_unused]] static constexpr char INVERT_COLOR[]              = "\x1b[7m";
[[maybe_unused]] static constexpr char NORMAL_COLOR[]              = "\x1b[m";

[[maybe_unused]] static constexpr char FORE_COLOR_BLACK[]          = "\x1b[30m";
[[maybe_unused]] static constexpr char FORE_COLOR_RED[]            = "\x1b[31m";
[[maybe_unused]] static constexpr char FORE_COLOR_GREEN[]          = "\x1b[32m";
[[maybe_unused]] static constexpr char FORE_COLOR_YELLOW[]         = "\x1b[33m";
[[maybe_unused]] static constexpr char FORE_COLOR_BLUE[]           = "\x1b[34m";
[[maybe_unused]] static constexpr char FORE_COLOR_MAGENTA[]        = "\x1b[35m";
[[maybe_unused]] static constexpr char FORE_COLOR_CYAN[]           = "\x1b[36m";
[[maybe_unused]] static constexpr char FORE_COLOR_WHITE[]          = "\x1b[37m";

[[maybe_unused]] static constexpr char FORE_COLOR_BRIGHT_BLACK[]   = "\x1b[90m";
[[maybe_unused]] static constexpr char FORE_COLOR_BRIGHT_RED[]     = "\x1b[91m";
[[maybe_unused]] static constexpr char FORE_COLOR_BRIGHT_GREEN[]   = "\x1b[92m";
[[maybe_unused]] static constexpr char FORE_COLOR_BRIGHT_YELLOW[]  = "\x1b[93m";
[[maybe_unused]] static constexpr char FORE_COLOR_BRIGHT_BLUE[]    = "\x1b[94m";
[[maybe_unused]] static constexpr char FORE_COLOR_BRIGHT_MAGENTA[] = "\x1b[95m";
[[maybe_unused]] static constexpr char FORE_COLOR_BRIGHT_CYAN[]    = "\x1b[96m";
[[maybe_unused]] static constexpr char FORE_COLOR_BRIGHT_WHITE[]   = "\x1b[97m";
[[maybe_unused]] static constexpr char FORE_COLOR_DEFAULT[]        = "\x1b[39m";

[[maybe_unused]] static constexpr char BACK_COLOR_BLACK[]          = "\x1b[40m";
[[maybe_unused]] static constexpr char BACK_COLOR_RED[]            = "\x1b[41m";
[[maybe_unused]] static constexpr char BACK_COLOR_GREEN[]          = "\x1b[42m";
[[maybe_unused]] static constexpr char BACK_COLOR_YELLOW[]         = "\x1b[43m";
[[maybe_unused]] static constexpr char BACK_COLOR_BLUE[]           = "\x1b[44m";
[[maybe_unused]] static constexpr char BACK_COLOR_MAGENTA[]        = "\x1b[45m";
[[maybe_unused]] static constexpr char BACK_COLOR_CYAN[]           = "\x1b[46m";
[[maybe_unused]] static constexpr char BACK_COLOR_DEFAULT[]        = "\x1b[49m";

[[maybe_unused]] static constexpr char BACK_COLOR_BRIGHT_BLACK[]   = "\x1b[100m";
[[maybe_unused]] static constexpr char BACK_COLOR_BRIGHT_RED[]     = "\x1b[101m";
[[maybe_unused]] static constexpr char BACK_COLOR_BRIGHT_GREEN[]   = "\x1b[102m";
[[maybe_unused]] static constexpr char BACK_COLOR_BRIGHT_YELLOW[]  = "\x1b[103m";
[[maybe_unused]] static constexpr char BACK_COLOR_BRIGHT_BLUE[]    = "\x1b[104m";
[[maybe_unused]] static constexpr char BACK_COLOR_BRIGHT_MAGENTA[] = "\x1b[105m";
[[maybe_unused]] static constexpr char BACK_COLOR_BRIGHT_CYAN[]    = "\x1b[106m";
[[maybe_unused]] static constexpr char BACK_COLOR_BRIGHT_WHITE[]   = "\x1b[107m";

#endif                          /* SEQUENCES_H */

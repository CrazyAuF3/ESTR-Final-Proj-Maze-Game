#ifndef _UI_H
#define _UI_H

#include <ncurses.h>

#define ENTRY_SHOW_BUFFER_SIZE (30)
#define ESC_KEY (27)

#define ui_add_menu(MENU) \
        do { \
            Menu *menu = ui_create_menu(MENU_TYPE_##MENU); \
            MenuAction action = ui_show_menu(menu); \
            ui_destroy_menu(menu); \
            return action; \
        } while (0)

typedef enum {
    MENU_STATE_OFF,  // closing a menu, but going to another menu or a game
    MENU_STATE_ON,
    MENU_STATE_QUIT,  // closing a menu and ends the program
} MenuState;

typedef enum {
    MENU_TYPE_MAIN,
    MENU_TYPE_OPTIONS,
    MENU_TYPE_QUIT,
} MenuType;

typedef enum {
    MENU_ACTION_START_GAME,
    MENU_ACTION_OPTIONS,
    MENU_ACTION_QUIT,
} MenuAction;

typedef struct {
    const char *text;
    MenuAction action;
} MenuItem;

typedef struct {
    const char *title;
    MenuType type;
    int item_count;
    MenuItem *items;
    int selected;
    MenuState state;
} Menu;

MenuAction ui_show_main_menu();
MenuAction ui_show_options_menu();

#endif

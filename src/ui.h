#ifndef _UI_H
#define _UI_H

#include <ncurses.h>

#define ENTRY_SHOW_BUFFER_SIZE (30)

typedef enum {
    MENU_STATE_OFF,
    MENU_STATE_ON,
} MenuState;

typedef enum {
    MENU_TYPE_MAIN,
    MENU_TYPE_OPTION,
} MenuType;

typedef enum {
    MENU_ACTION_START_GAME,
    MENU_ACTION_OPTIONS,
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

Menu *ui_create_menu(MenuType type);
Menu *ui_destroy_menu(Menu *menu);
void ui_handle_input(Menu *menu, int ch);
void ui_draw_menu(Menu *menu);
MenuAction ui_show_main_menu();
MenuAction ui_show_menu(Menu *menu);

#endif

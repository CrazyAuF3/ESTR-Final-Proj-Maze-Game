#ifndef _UI_H
#define _UI_H

#include <ncurses.h>

#define MENU_ITEM_TEXT_BUFFER_SIZE (40)
#define ESC_KEY (27)

#define ui_add_menu(MENU) \
        do { \
            Menu *menu = ui_create_menu(MENU_TYPE_##MENU); \
            MenuAction action = ui_show_menu(menu); \
            ui_destroy_menu(menu); \
            return action; \
        } while (0)

extern int enabled_fixed_size;

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
    MENU_ACTION_TOGGLE,  // empty dummy action for checkboxes
} MenuAction;

typedef enum {
    MENU_ITEM_TYPE_ENTRY,
    MENU_ITEM_TYPE_CHECKBOX,
} MenuItem_Type;

typedef struct {
    MenuItem_Type type;
    const char *text;
    MenuAction action;
} MenuItem_Base;

typedef struct {
    MenuItem_Base base;
    // const char *sub_text;
} MenuItem_Entry;

typedef struct {
    MenuItem_Base base;
    int *linked_var;
} MenuItem_Checkbox;

typedef union {
    MenuType type;  // for quick access only
    MenuItem_Base base;  // for quick access only
    MenuItem_Entry entry;
    MenuItem_Checkbox checkbox;
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

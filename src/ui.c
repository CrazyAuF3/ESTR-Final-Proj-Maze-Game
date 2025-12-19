#include "ui.h"
#include <stdlib.h>
#include <string.h>

/* helper functions prototypes */

/* input handling */

static void ui_handle_input(Menu *menu, int ch);

/* create and destroy */

static Menu *ui_destroy_menu(Menu *menu);
static Menu *ui_create_menu(MenuType type);

/* menu drawing and behavior capturing */

static void ui_draw_menu(Menu *menu);
static MenuAction ui_show_menu(Menu *menu);

/* item adding */

static void ui_menu_add_item(Menu *menu, int i, MenuAction action, const char *text);

/* initialize menu as different types */

static void ui_init_as_main(Menu *menu);

/* end of prototypes */

/* showing different types of menus */

MenuAction ui_show_main_menu() { ui_add_menu(MAIN); }

MenuAction ui_show_options_menu() { ui_add_menu(OPTIONS); }

/* helper functions */

// handle keyboard input
static void ui_handle_input(Menu *menu, int ch)
{
    switch (ch) {
        case 'W': case 'w':
        if (menu->selected > 0) {
            menu->selected--;
        }
        break;

        case 'S': case 's':
        if (menu->selected < menu->item_count - 1) {
            menu->selected++;
        }
        break;

        case ' ': case '\n':
        menu->state = MENU_STATE_OFF;
        break;

        case 'Q': case 'q': case ESC_KEY:
        menu->state = MENU_STATE_QUIT;
        break;
    }
}

// destroy a menu and free its memory
static Menu *ui_destroy_menu(Menu *menu)
{
    /* Free the memory, not implemented yet */
}

// allocate memory for a menu, and initialize it according to its type
static Menu *ui_create_menu(MenuType type)
{
    Menu *menu = (Menu*)malloc(sizeof(Menu));

    menu->type = type;

    switch (type) {
        case MENU_TYPE_MAIN:
        ui_init_as_main(menu);
        break;

        case MENU_TYPE_OPTIONS:
        // not implemented yet
        break;

        case MENU_TYPE_QUIT:
        break;
    }

    return menu;
}

// draw a menu on screen
static void ui_draw_menu(Menu *menu)
{
    clear();

    mvprintw(2, 2, menu->title);

    for (int i = 0; i < menu->item_count; i++) {
        char *entry_show = (char*)malloc(ENTRY_SHOW_BUFFER_SIZE*sizeof(char));
        strcpy(entry_show, "-> ");
        strcat(entry_show, menu->items[i].text);
        mvprintw(2+2*(i+1), 2,
            menu->selected == i ? entry_show : menu->items[i].text);
        
        free(entry_show);
    }

    refresh();
}

// show a menu and handle its behaviors
static MenuAction ui_show_menu(Menu *menu)
{
    int ch;

    while (menu->state == MENU_STATE_ON) {
        ui_draw_menu(menu);

        ch = getch();

        ui_handle_input(menu, ch);
    }

    // first we detect if the menu is quitting
    if (menu->state == MENU_STATE_QUIT) return MENU_ACTION_QUIT;

    // otherwise, menu->state must be OFF
    return menu->items[menu->selected].action;
}

// initialize the main menu
static void ui_init_as_main(Menu *menu)
{
    menu->item_count = 3;
    menu->title = "MAZE GAME";
    
    MenuItem *items = (MenuItem*)malloc(menu->item_count * sizeof(MenuItem));

    menu->items = items;

    ui_menu_add_item(menu, 0, MENU_ACTION_START_GAME, "START GAME");
    ui_menu_add_item(menu, 1, MENU_ACTION_OPTIONS, "OPTIONS");
    ui_menu_add_item(menu, 2, MENU_ACTION_QUIT, "QUIT");

    menu->selected = 0;

    menu->state = MENU_STATE_ON;
}

// add an item to a menu
static void ui_menu_add_item(Menu *menu, int i, MenuAction action, const char *text)
{
    MenuItem item;
    item.action = action;
    item.text = text;
    menu->items[i] = item;
}

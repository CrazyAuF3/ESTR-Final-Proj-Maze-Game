#include "ui.h"
#include <stdlib.h>
#include <string.h>

int enabled_fixed_size = 1;

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

static void ui_menu_add_entry(Menu *menu, int i, MenuAction action, const char *text);
static void ui_menu_add_checkbox(Menu *menu, int i, int *link_var, const char *text);

/* initialize menu as different types */

static void ui_init_as_main(Menu *menu);
static void ui_init_as_options(Menu *menu);

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
        if (menu->items[menu->selected].type == MENU_ITEM_TYPE_ENTRY) {
            menu->state = MENU_STATE_OFF;
        } else if (menu->items[menu->selected].type == MENU_ITEM_TYPE_CHECKBOX) {
            *(menu->items[menu->selected].checkbox.linked_var) = !*(menu->items[menu->selected].checkbox.linked_var);
        }
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
        ui_init_as_options(menu);
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

    mvprintw(2, 2, "%s", menu->title);

    for (int i = 0; i < menu->item_count; i++) {
        if (menu->items[i].type == MENU_ITEM_TYPE_ENTRY) {
            if (menu->selected == i) {
                char *selected_entry = (char*)malloc(MENU_ITEM_TEXT_BUFFER_SIZE*sizeof(char));
                strcpy(selected_entry, "-> ");
                strcat(selected_entry, menu->items[i].base.text);
                mvprintw(2+2*(i+1), 2, "%s", selected_entry);
                free(selected_entry);
            } else {
                mvprintw(2+2*(i+1), 2, "%s", menu->items[i].base.text);
            }
            
        } else if (menu->items[i].type == MENU_ITEM_TYPE_CHECKBOX) {
            char *checkbox_with_state = (char*)malloc(MENU_ITEM_TEXT_BUFFER_SIZE*sizeof(char));
            strcpy(checkbox_with_state, menu->items[i].base.text);
            strcat(checkbox_with_state, ": ");
            strcat(checkbox_with_state, *menu->items[menu->selected].checkbox.linked_var ? "ENABLED" : "DISABLED");
            
            if (menu->selected == i) {
                char *selected_checkbox = (char*)malloc(MENU_ITEM_TEXT_BUFFER_SIZE*sizeof(char));
                strcpy(selected_checkbox, "-> ");
                strcat(selected_checkbox, checkbox_with_state);
                mvprintw(2+2*(i+1), 2, "%s", selected_checkbox);
                free(selected_checkbox);
            } else {
                mvprintw(2+2*(i+1), 2, "%s", checkbox_with_state);
            }
            free(checkbox_with_state);
        }
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
    return menu->items[menu->selected].base.action;
}

// initialize the main menu
static void ui_init_as_main(Menu *menu)
{
    menu->item_count = 3;
    menu->title = "MAZE GAME";
    
    MenuItem *items = (MenuItem*)malloc(menu->item_count * sizeof(MenuItem));
    menu->items = items;

    ui_menu_add_entry(menu, 0, MENU_ACTION_START_GAME, "START GAME");
    ui_menu_add_entry(menu, 1, MENU_ACTION_OPTIONS, "OPTIONS");
    ui_menu_add_entry(menu, 2, MENU_ACTION_QUIT, "QUIT");

    menu->selected = 0;

    menu->state = MENU_STATE_ON;
}

// initialize the options menu
static void ui_init_as_options(Menu *menu)
{
    menu->item_count = 1;
    menu->title = "OPTIONS";

    MenuItem *items = (MenuItem*)malloc(menu->item_count * sizeof(MenuItem));
    menu->items = items;

    ui_menu_add_checkbox(menu, 0, &enabled_fixed_size, "FIXED SIZE");

    menu->selected = 0;

    menu->state = MENU_STATE_ON;
}

// add an item to a menu
static void ui_menu_add_entry(Menu *menu, int i, MenuAction action, const char *text)
{
    MenuItem item;
    item.type = MENU_ITEM_TYPE_ENTRY;
    item.base.action = action;
    item.base.text = text;
    menu->items[i] = item;
}

static void ui_menu_add_checkbox(Menu *menu, int i, int *link_var, const char *text)
{
    MenuItem checkbox;
    checkbox.type = MENU_ITEM_TYPE_CHECKBOX;
    checkbox.base.text = text;
    checkbox.base.action = MENU_ACTION_TOGGLE;
    checkbox.checkbox.linked_var = link_var;
    menu->items[i] = checkbox;
}

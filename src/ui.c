#include "ui.h"
#include <stdlib.h>
#include <string.h>

static void ui_main_menu_init(Menu *menu);
static void ui_menu_add_item(Menu *menu, int i, MenuAction action, const char *text);

Menu *ui_create_menu(MenuType type)
{
    Menu *menu = (Menu*)malloc(sizeof(Menu));

    menu->type = type;

    switch (type) {
        case MENU_TYPE_MAIN:
        ui_main_menu_init(menu);
        break;

        case MENU_TYPE_OPTION:
        // not implemented yet
        break;
    }

    return menu;
}

Menu *ui_destroy_menu(Menu *menu)
{
    /* Free the memory, not implemented yet */
}

void ui_handle_input(Menu *menu, int ch)
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

        case ' ':
        menu->state = MENU_STATE_OFF;
        break;
    }
}

MenuAction ui_show_main_menu()
{
    Menu *main_menu;

    main_menu = ui_create_menu(MENU_TYPE_MAIN);

    MenuAction main_menu_action = ui_show_menu(main_menu);

    ui_destroy_menu(main_menu);

    return main_menu_action;
}

MenuAction ui_show_menu(Menu *menu)
{
    int ch;
    while (menu->state == MENU_STATE_ON) {
        ui_draw_menu(menu);

        ch = getch();

        ui_handle_input(menu, ch);
    }

    return menu->items[menu->selected].action;
}

void ui_draw_menu(Menu *menu)
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

static void ui_main_menu_init(Menu *menu)
{
    menu->item_count = 2;
    menu->title = "MAZE GAME";
    
    MenuItem *items = (MenuItem*)malloc(menu->item_count * sizeof(MenuItem));

    menu->items = items;

    ui_menu_add_item(menu, 0, MENU_ACTION_START_GAME, "START GAME");
    ui_menu_add_item(menu, 1, MENU_ACTION_OPTIONS, "OPTIONS");

    menu->selected = 0;

    menu->state = MENU_STATE_ON;
}

static void ui_menu_add_item(Menu *menu, int i, MenuAction action, const char *text)
{
    MenuItem item;
    item.action = action;
    item.text = text;
    menu->items[i] = item;
}

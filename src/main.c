#include "main.h"
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "ui.h"

int main(void)
{
    setup_ncurses();

    while (1) {
        MenuAction action = ui_show_main_menu();

        if (action == MENU_ACTION_START_GAME) {
            run_game_once();
        } else if (action == MENU_ACTION_OPTIONS) {
            ui_show_options_menu();  // not added return value store yet (not necessary this time)
        } else if (action == MENU_ACTION_QUIT) {
            break;
        }
    }

    cleanup_ncurses(NULL);

    return 0;
}

void run_game_once(void)
{
    Game *game = game_init();

    game_draw_which game_drawer;
    if (enabled_fixed_size) {
        game_drawer = game_draw_fixed_size;
    } else {
        if (enabled_limited_sight) {
            game_drawer = game_draw_distance;
        } else {
            game_drawer = game_draw;
        }
    }

    int ch;
    while (game->state != GAME_QUIT) {
        game_drawer(game);

        ch = getch();

        game_handle_input(game, ch);
    }

    cleanup_ncurses(game);
}

void setup_ncurses(void)
{
    srand(time(NULL));
    WINDOW *win;
    if ((win = initscr()) == NULL) {
        printf("Window initialization failed\n");
        exit(1);
    }
    set_escdelay(200);
    cbreak();
    noecho();
    noqiflush();
    keypad(win, TRUE);
    curs_set(0);
}

void cleanup_ncurses(Game *game)
{
    refresh();
    
    if (game != NULL) {
        game_cleanup(game);
    }

    endwin();
}

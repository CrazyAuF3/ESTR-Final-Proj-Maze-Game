#include "main.h"
#include <ncurses.h>
#include <stdlib.h>
#include "game.h"
#include "ui.h"

int main(void)
{
    setup_ncurses();

    MenuAction action;
    if ((action = ui_show_main_menu()) == MENU_ACTION_START_GAME) {
        Game *game = game_init();
    
        int ch;
        while (game->state != GAME_QUIT) {
            game_draw(game);

            ch = getch();

            game_handle_input(game, ch);
        }

        cleanup_ncurses_game(game);
    }

    cleanup_ncurses_menu();

    return 0;
}

void setup_ncurses(void)
{
    WINDOW *win;
    if ((win = initscr()) == NULL) {
        printf("Window initialization failed\n");
        exit(1);
    }
    cbreak();
    noecho();
    noqiflush();
    keypad(win, TRUE);
    curs_set(0);
}

void cleanup_ncurses_game(Game *game)
{
    refresh();
    curs_set(1);
    game_cleanup(game);
    endwin();
}

void cleanup_ncurses_menu()
{
    refresh();
    curs_set(1);
    endwin();
}

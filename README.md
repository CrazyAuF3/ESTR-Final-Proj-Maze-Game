Instructions
===

Pre-requisite
---

- Make sure the `resize` tool (usually part of xterm) is installed on the testing environment. The tool is used to resize the terminal.

- Make sure the program is tested using terminal emulators that support terminal window resizing (e.g., xterm). GNOME's default terminal is not recommended, asterminal window resizing may not work properly.

- Make sure the `ncurses` and `ncurses-dev` libraries are installed.

Build
---

Build the executable using the following command:
```
gcc game.c main.c maze.c player.c ui.c util.c -o maze_game -lncurses
```

No need to link `ncursesw` since wide char feature is not implemented.

Run
---

Run the executable using the following command:
```
./maze_game
```

Usage
---

- On the main screen, use `W` and `S` to navigate the main menu and select one entry, and use `Q` or `<ESC>` to quit the program.
- Press `<Enter>` or `<Space>` on the "START GAME" menu to start the game.
- Use `W` `A` `S` `D` to move in the game, and use `Q` or `<ESC>` to return to the main menu.
- In the "OPTIONS" menu, press `<Enter>` or `<Space>` to toggle the options (See the following "Features Implemented"), and press `Q` to return.

Features Implemented
---

- All basic requirements
- Advanced feature 2 (enable "FIXED SIZE" in the "OPTIONS" menu). The maze map now scrolls as the player moves. The out-of-bound cells are shown as `V` (the void).
- Advanced feature 4 (enable "LIMITED SIGHT" and **disable "FIXED SIZE"** in the "OPTIONS" menu). The sight is limited to a 11 by 11 square now.
- Advanced feature 5 (always enabled). The teleportation blocks are shown as `*` on the maze map. Total number is 5. Random location. When stepping on any one of these blocks, randomly teleport the player to another (may teleport to itself).
- Advanced feature 7 (always enabled). The player has 200 initial "energy". When moves 1 cell, energy decreases by 1. Current energy is displayed on screen under the maze map.

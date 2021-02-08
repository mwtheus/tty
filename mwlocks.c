#include <ncurses.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

int main() {
  int height, width;
  int counter = 0, is_editing = 0;
  char last_character;

  getmaxyx(stdscr, height, width);
  noecho();
  initscr();

  while (true) {
    time_t start_time, end_time;
    char current_character;
    double time_elapsed;

    time(&start_time);
    current_character = getch();

    time(&end_time);
    time_elapsed = difftime(end_time, start_time);

    if (is_editing == 0) {
      if (time_elapsed <= 1) {
        if (counter < 2) {
          counter = (current_character == last_character) ? counter + 1 : 0;
        } else {
          is_editing = 1;
          counter = 0;
        }
      }

      last_character = current_character;
    }

    if (is_editing == 1) {
      printw("Unlocked\n");

      switch (tolower(current_character)) {
        case 'q':
          printw("Quit\n");
          endwin();
          return 0;
        case 'l':
          printw("Locked\n");
          is_editing = 0;
          break;
      }
    } 
  }
}

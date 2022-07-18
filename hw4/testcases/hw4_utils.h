#ifndef HW4_TESTCASES_UTILS_H
#define HW4_TESTCASES_UTILS_H

#include <stdio.h>
#include <stdbool.h>

void print_game_test(Game *game) {
  if (!game || !game->grid) {
    puts("    cannot print an empty game!");
    return;
  }
  fflush(stdout);

  printf("     ");
  for (int i = 0; i < game->columns; i++)
    printf("_");
  printf(" \n");

  for (int i = 0; i < game->rows; i++) {
    printf("    |");
    for (int j = 0; j < game->columns; j++)
      printf("%c", game->grid[i][j]);
    printf("|\n");
  }
  printf("    \\");
  for (int i = 0; i < game->columns; i++)
    printf("-");
  printf("/\n\n");

  static const char *statestr[] = {"losing", "onGoing", "winning"};
  printf("  Game state: %s\n", game->state < 3 ? statestr[game->state] : "Invalid state");
  printf("  Game score: %d\n", game->score);
}

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_RESET "\x1b[0m"

#define SET_COLOR(COLOR, STRING) (ANSI_COLOR_##COLOR STRING ANSI_COLOR_RESET)

#define RED(STRING) SET_COLOR(RED, STRING)
#define GREEN(STRING) SET_COLOR(GREEN, STRING)
#define MAGENTA(STRING) SET_COLOR(MAGENTA, STRING)

bool report_if_wrong(bool condition, const char *info, int tcase, int line, Game *g) {
  if (!condition) {
    printf(RED("Wrong on testcase %d, line %d\n"), tcase, line);
    printf("Condition \"%s\" is not satisfied.\n", info);
    print_game_test(g);
    EndGame(g);
    return true;
  } else
    return false;
}

// #define GEN_TCASE const int tcase = strcmp(__func__, "test10") == 0 ? 10 : __func__[4] - '0'

#ifdef OJ_ASSERT
#undef OJ_ASSERT
#endif
#define OJ_ASSERT(stmt) if (report_if_wrong(stmt, #stmt, tcase, __LINE__, g)) return false;

#endif // HW4_TESTCASES_UTILS_H

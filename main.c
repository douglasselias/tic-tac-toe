#include <math.h>

#include "raylib.h"

void has_winner(int grid[3][3], int *who_won) {
  for (int i = 0; i < 3; i++) {
    for (int player = 1; player < 3; player++) {
      bool column =
          grid[i][0] == player && grid[i][1] == player && grid[i][2] == player;
      bool row =
          grid[0][i] == player && grid[1][i] == player && grid[2][i] == player;
      bool left_to_right_diagonal = grid[i][i] == player &&
                                    grid[i + 1][i + 1] == player &&
                                    grid[i + 2][i + 2] == player;
      bool right_to_left_diagonal = grid[i + 2][i] == player &&
                                    grid[i + 1][i + 1] == player &&
                                    grid[i][i + 2] == player;
      if (column || row || left_to_right_diagonal || right_to_left_diagonal)
        *who_won = player;
    }
  }
}

int minimax(int grid[3][3], int depth, int maximizing_player) {
  // if (depth == 0 || last_node)
  //   return score;

  // if (maximizing_player) {
  //   int score = -INFINITY;
  //   for (each node) {
  //     int new_score = minimax(grid, depth - 1, false);
  //     score = score > new_score ? score : new_score;
  //   }
  //   return score;
  // } else {
  //   int score = INFINITY;
  //   for (each node) {
  //     int new_score = minimax(grid, depth - 1, false);
  //     score = score < new_score ? score : new_score;
  //   }
  //   return score;
  // }

  return 0;
}

void reset_grid(int grid[3][3]) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      grid[i][j] = 0;
    }
  }
}
typedef enum game_status {
  e_still_playing = 0,
  e_player_one_won = 1,
  e_player_two_won = 2,
  e_draw = 3,
} game_status;

typedef enum cell_space {
  e_empty = 0,
  e_player_one = 1,
  e_player_two = 2,
} cell_space;

int main() {
  const int screen_width = 720;
  const int screen_height = 720;
  const int half_screen_width = screen_width / 2;
  const int half_screen_height = screen_height / 2;
  InitWindow(screen_width, screen_height, "Tic-Tac-Toe");
  SetTargetFPS(60);

  int grid[3][3] = {};
  reset_grid(grid);

  const int cell_size = 720 / 3;
  const int half_cell_size = cell_size / 2;

  const int font_size = 50;
  const int won_x_text_size = MeasureText("Player X won!", font_size);
  const int won_o_text_size = MeasureText("Player O won!", font_size);
  const int play_again_text_size =
      MeasureText("Press Enter to play again", font_size);
  const char draw_text[] = "Its a draw!";
  const int draw_text_size = MeasureText(draw_text, font_size);
  bool is_player_one = true;
  int who_won = e_still_playing;

  while (!WindowShouldClose()) {
    if (IsKeyPressed(KEY_ENTER) && who_won != e_still_playing) {
      who_won = e_still_playing;
      is_player_one = true;
      reset_grid(grid);
    }

    if (IsMouseButtonPressed(0)) {
      Vector2 mouse = GetMousePosition();
      int x = mouse.x / cell_size;
      int y = mouse.y / cell_size;
      if (grid[x][y] == 0 && who_won == e_still_playing) {
        grid[x][y] = is_player_one ? 1 : 2;
        is_player_one = !is_player_one;

        int filled_cells = 0;
        for (int i = 0; i < 3; i++) {
          for (int j = 0; j < 3; j++) {
            if (grid[i][j] != 0)
              filled_cells++;
          }
        }
        if (filled_cells == 9) {
          who_won = e_draw;
        } else {
          // minimax();
          // grid[px][py] = 2;
          is_player_one = !is_player_one;
          has_winner(grid, &who_won);
        }
      }
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        int x = i * cell_size;
        int y = j * cell_size;
        DrawRectangleLines(x, y, cell_size, cell_size, DARKGRAY);
        if (grid[i][j] == e_player_one) {
          DrawLine(x, y, x + cell_size, y + cell_size, RED);
          DrawLine(x + cell_size, y, x, y + cell_size, RED);
        } else if (grid[i][j] == e_player_two)
          DrawCircleLines(x + half_cell_size, y + half_cell_size, 80, DARKBLUE);
      }
    }

    switch (who_won) {
    case e_player_one_won:
      DrawText("Player X won!", half_screen_width - (won_x_text_size / 2),
               half_screen_height - 25, font_size, BLUE);
      break;
    case e_player_two_won:
      DrawText("Player O won!", half_screen_width - (won_o_text_size / 2),
               half_screen_height - 25, font_size, BLUE);
      break;
    case e_draw:
      DrawText(draw_text, half_screen_width - (draw_text_size / 2),
               half_screen_height - 25, font_size, BLUE);
      break;
    }
    if (who_won > 0)
      DrawText("Press Enter to play again",
               half_screen_width - (play_again_text_size / 2),
               half_screen_height + 75, font_size, BLUE);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
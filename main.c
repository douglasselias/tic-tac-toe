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

void reset_grid(int grid[3][3]) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      grid[i][j] = 0;
    }
  }
}

int main() {
  const int screen_width = 720;
  const int screen_height = 720;
  InitWindow(screen_width, screen_height, "Tic-Tac-Toe");
  SetTargetFPS(60);

  int grid[3][3] = {};
  reset_grid(grid);

  const int cell_size = 720 / 3;
  const int half_cell_size = cell_size / 2;

  const int won_text_size = MeasureText("Player X won!", 50);
  const int play_again_text_size = MeasureText("Press Enter to play again", 50);
  bool is_player_one = true;
  int who_won = 0;

  while (!WindowShouldClose()) {
    if (IsKeyPressed(KEY_ENTER) && who_won != 0) {
      who_won = 0;
      is_player_one = true;
      reset_grid(grid);
    }

    if (IsMouseButtonPressed(0)) {
      Vector2 mouse = GetMousePosition();
      int x = mouse.x / cell_size;
      int y = mouse.y / cell_size;
      if (grid[x][y] == 0 && who_won == 0) {
        grid[x][y] = is_player_one ? 1 : 2;
        is_player_one = !is_player_one;

        int px = GetRandomValue(0, 2);
        int py = GetRandomValue(0, 2);
        while (grid[px][py] != 0) {
          px = GetRandomValue(0, 2);
          py = GetRandomValue(0, 2);
        }
        grid[px][py] = 2;
        is_player_one = !is_player_one;

        has_winner(grid, &who_won);
      }
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        int x = i * cell_size;
        int y = j * cell_size;
        DrawRectangleLines(x, y, cell_size, cell_size, DARKGRAY);
        if (grid[i][j] == 1) {
          DrawLine(x, y, x + cell_size, y + cell_size, RED);
          DrawLine(x + cell_size, y, x, y + cell_size, RED);
        } else if (grid[i][j] == 2)
          DrawCircleLines(x + half_cell_size, y + half_cell_size, 80, DARKBLUE);
      }
    }

    if (who_won == 1) {
      DrawText("Player X won!", (screen_width / 2) - (won_text_size / 2),
               (screen_height / 2) - 25, 50, BLUE);
    } else if (who_won == 2)
      DrawText("Player O won!", (screen_width / 2) - (won_text_size / 2),
               (screen_height / 2) - 25, 50, BLUE);

    if (who_won != 0) {
      DrawText("Press Enter to play again",
               (screen_width / 2) - (play_again_text_size / 2),
               (screen_height / 2) + 75, 50, BLUE);
    }
    EndDrawing();
  }

  CloseWindow();
  return 0;
}

#include <stdio.h>
#include <stdlib.h>


void screenRendering(
    const int *player_1_Y, const int *player_2_Y,
    const int *ball1_x, const int *ball1_y,
    int *scPlayer1, int *scPlayer2);
void playerMove(int *player_1_Y, int *player_2_Y);
void moveBall(
    int *ball1_x, int *ball1_y, int *vector_X, int *vector_Y,
    const int *player_1_Y, const int *player_2_Y);
int scoreDisplay(
    int *scPlayer1, int *scPlayer2, int *ball1_x, int *ball1_y);
void clearDisplay(void);

int main(void) {
    int field_height = 27;
    int field_widht = 82;
    int player_1_Y = 19;
    int player_2_Y = 5;
    int ball_X = field_widht / 2;
    int ball_Y = field_height / 2;
    int vector_X = -1;
    int vector_Y = 1;
    int score_Player_1 = 0;
    int score_Player_2 = 0;

    do {
        screenRendering(
            &player_1_Y, &player_2_Y, &ball_X, &ball_Y,
            &score_Player_1, &score_Player_2);
        playerMove(&player_1_Y, &player_2_Y);
        moveBall(
            &ball_X, &ball_Y, &vector_X, &vector_Y,
            &player_1_Y, &player_2_Y);
        clearDisplay();
        if (scoreDisplay(&score_Player_1, &score_Player_2,
            &ball_X, &ball_Y)) {
            break;
        }
    } while (1);

    return 0;
}

void screenRendering(
    const int *player_1_Y, const int *player_2_Y,
    const int *ball1_x, const int *ball1_y,
    int *scPlayer1, int *scPlayer2) {

    int platform_size = 3;
    int field_height = 27;
    int field_widht = 82;
    int player1_default_x = 2;
    int player2_default_x = field_widht - 3;
    int position_of_score = 25;

    for (int y = 0; y < platform_size; ++y) {
    for (int x = 0; x < field_widht; ++x) {
        if ((y == 0 && x != 0 && x != field_widht - 1) ||
            (y == platform_size - 1 && x != 0 && x != field_widht - 1)) {
            printf("#");
        } else if (((x == 0 && y != 0 && y != platform_size - 1) ||
            (x == field_widht - 1 && y != 0 && y != platform_size - 1))) {
            printf("|");
        } else if (x == position_of_score) {
            printf("Player 1: %d | Player 2: %d", *scPlayer1, *scPlayer2);
        } else if (y == 1 && x < field_widht - position_of_score) {
            printf(" ");
        } else if (y != 1) {
            printf(" ");
        }
    }
    printf("\n");
}
    for (int y = 0; y < field_height; ++y) {
        for (int x = 0; x < field_widht; ++x) {
            if ((x == player1_default_x &&
                (y == *player_1_Y - 1 || y == *player_1_Y ||
                y == *player_1_Y + 1)) || (x == player2_default_x &&
                (y == *player_2_Y - 1 || y == *player_2_Y ||
                y == *player_2_Y + 1))) {
                printf("|");
            } else if (x == *ball1_x && y == *ball1_y) {
                printf("o");
            } else if ((y == 0 && x != 0 && x != field_widht - 1) ||
                (y == field_height - 1 && x != 0 && x != field_widht - 1)) {
                printf("-");
            } else if ((x == 0 && y != 0 && y != field_height - 1) ||
                (x == field_widht - 1 && y != 0 && y != field_height - 1) ||
                (x == field_widht / 2)) {
                printf("|");
            } else {
                printf(" ");
        }
    }
    printf("\n");
    }
}
void playerMove(int *player_1_Y, int *player_2_Y) {
    int field_height = 27;
    char temp;

    switch (temp = getchar()) {
        case 'a' : ((*player_1_Y - 2) != 0) ?
        (*player_1_Y -= 1) : *player_1_Y; break;
        case 'z' : ((*player_1_Y + 2) != field_height - 1) ?
        (*player_1_Y += 1) : *player_1_Y; break;
        case 'k' : ((*player_2_Y - 2) != 0) ? (*player_2_Y -= 1) :
        *player_2_Y; break;
        case 'm' : ((*player_2_Y + 2) != field_height - 1) ?
        (*player_2_Y += 1) : *player_2_Y; break;
    }
}
void moveBall(
    int *ball1_x, int *ball1_y,
    int *vector_X, int *vector_Y,
    const int *player_1_Y, const int *player_2_Y) {

    int field_heiht = 27;
    int field_widht = 82;
    int player1_default_x = 2;
    int player2_default_x = field_widht - 3;

    if (*ball1_y == 1 || *ball1_y == (field_heiht - 2)) {
        *vector_Y = -(*vector_Y);
    }
    if (*ball1_x == player1_default_x + 1 &&
        (*ball1_y == *player_1_Y - 1 || *ball1_y == *player_1_Y ||
        *ball1_y == *player_1_Y + 1)) {
        *vector_X = -(*vector_X);
    }
    if (*ball1_x == player2_default_x - 1 &&
        (*ball1_y == *player_2_Y - 1 || *ball1_y == *player_2_Y ||
        *ball1_y == *player_2_Y + 1)) {
        *vector_X = -(*vector_X);
    }
    *ball1_y += *vector_Y;
    *ball1_x += *vector_X;
}
int scoreDisplay(
    int *scPlayer1, int *scPlayer2, int *ball1_x, int *ball1_y) {

    int field_height = 27;
    int field_widht = 82;
    int ball_start_x = field_widht / 2;
    int ball_start_y = field_height / 2;

    if (*ball1_x < 2) {
        *scPlayer2 += 1;
        *ball1_x = ball_start_x;
        *ball1_y = ball_start_y;
    }
    if (*ball1_x > field_widht - 3) {
        *scPlayer1 += 1;
        *ball1_x = ball_start_x;
        *ball1_y = ball_start_y;
    }
    if (*scPlayer1 == 25) {
        printf("GG\nFinal score: %d - %d\nPlayer1 wins.\nCongrutulations!\n",
        *scPlayer1, *scPlayer2);
        return 1;
    } else if (*scPlayer2 == 25) {
        printf("GG\nFinal score: %d - %d\nPlayer2 wins.\nCongrutulations!\n",
        *scPlayer2, *scPlayer1);
        return 1;
    }
    return 0;
}
void clearDisplay(void) {
    system("clear");
}
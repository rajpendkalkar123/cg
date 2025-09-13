#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>

int i, j, x, y, brick_height, brick_width, brick_x, brick_y;
int ball_x = 320, ball_y = 400;
int ball_dx = 3, ball_dy = -3;
int ball_radius = 10;
int paddle_x = 280, paddle_y = 450;
int paddle_width = 80, paddle_height = 10;
int paddle_speed = 20;
char key;
char score_text[20];
int bricks[5][10];
int score = 0;

void clear_ball(int x, int y, int radius) {
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    fillellipse(x, y, radius, radius);
}

void draw_ball(int x, int y, int radius) {
    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);
    fillellipse(x, y, radius, radius);
}

void draw_paddle(int paddle_x, int paddle_y, int paddle_width, int paddle_height) {
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    bar(paddle_x, paddle_y, paddle_x + paddle_width, paddle_y + paddle_height);
}

void clear_paddle(int paddle_x, int paddle_y, int paddle_width, int paddle_height) {
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    bar(paddle_x, paddle_y, paddle_x + paddle_width, paddle_y + paddle_height);
}

void draw_bricks(int bricks[5][10], int brick_width, int brick_height) {
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 10; j++) {
            if (bricks[i][j] == 1) {
                x = j * brick_width;
                y = i * brick_height + 30;
                bar(x, y, x + brick_width - 2, y + brick_height - 2);
            }
        }
    }
}

void clear_brick(int brick_x, int brick_y, int brick_width, int brick_height) {
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    bar(brick_x, brick_y, brick_x + brick_width - 2, brick_y + brick_height - 2);
}

void clear_score() {
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    bar(10, 10, 150, 30);
}

void display_score(int score) {
    clear_score();
    sprintf(score_text, "Score: %d", score);
    setcolor(WHITE);
    outtextxy(10, 10, score_text);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 10; j++) {
            bricks[i][j] = 1;
        }
    }

    brick_width = getmaxx() / 10;
    brick_height = 30;

    draw_bricks(bricks, brick_width, brick_height);

    while (1) {
        clear_ball(ball_x, ball_y, ball_radius);
        clear_paddle(paddle_x, paddle_y, paddle_width, paddle_height);

        if (kbhit()) {
            key = getch();
            if (key == 27 || key == 'e' || key == 'E') {
                break;
            } else if (key == 75 && paddle_x > 0) {
                paddle_x -= paddle_speed;
            } else if (key == 77 && paddle_x + paddle_width < getmaxx()) {
                paddle_x += paddle_speed;
            }
        }

        ball_x += ball_dx;
        ball_y += ball_dy;

        if (ball_x - ball_radius <= 0 || ball_x + ball_radius >= getmaxx()) {
            ball_dx = -ball_dx;
        }
        if (ball_y - ball_radius <= 0) {
            ball_dy = -ball_dy;
        }
        if (ball_y + ball_radius >= paddle_y && ball_x >= paddle_x && ball_x <= paddle_x + paddle_width) {
            ball_dy = -ball_dy;
        }

        if (ball_y + ball_radius >= getmaxy()) {
            setcolor(RED);
            outtextxy(250, 250, "Game Over!");
            sprintf(score_text, "Final Score: %d", score);
            outtextxy(250, 270, score_text);
            delay(2000);
            break;
        }

        for (i = 0; i < 5; i++) {
            for (j = 0; j < 10; j++) {
                if (bricks[i][j] == 1) {
                    brick_x = j * brick_width;
                    brick_y = i * brick_height + 30;

                    if (ball_x + ball_radius >= brick_x && ball_x - ball_radius <= brick_x + brick_width &&
                        ball_y + ball_radius >= brick_y && ball_y - ball_radius <= brick_y + brick_height) {
                        bricks[i][j] = 0;
                        clear_brick(brick_x, brick_y, brick_width, brick_height);
                        score += 5;

                        if (ball_y - ball_radius < brick_y || ball_y + ball_radius > brick_y + brick_height) {
                            ball_dy = -ball_dy;
                        } else {
                            ball_dx = -ball_dx;
                        }
                    }
                }
            }
        }

        draw_ball(ball_x, ball_y, ball_radius);
        draw_paddle(paddle_x, paddle_y, paddle_width, paddle_height);
        display_score(score);

        delay(30);
    }

    closegraph();
    return 0;
}

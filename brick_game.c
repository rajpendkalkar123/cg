#include <graphics.h>
#include <conio.h>
#include <stdlib.h>  // For exit()
#include <dos.h>     // For delay()

int i, j, x, y, brick_height, brick_width, brick_x, brick_y;
// Ball properties
int ball_x = 320, ball_y = 400;
int ball_dx = 3, ball_dy = -3;  // Start moving upwards (dy is negative)
int ball_radius = 10;
// Paddle properties
int paddle_x = 280, paddle_y = 450;
int paddle_width = 80, paddle_height = 10;
int paddle_speed = 20;
char key;
char score_text[20];
// Brick properties
int bricks[5][10];  // 5 rows, 10 columns of bricks
// Score tracking
int score = 0;

// Function to clear the ball's previous position
void clear_ball(int x, int y, int radius) {
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    fillellipse(x, y, radius, radius);  // Clear previous ball position
}

// Function to draw the ball
void draw_ball(int x, int y, int radius) {
    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);
    fillellipse(x, y, radius, radius);  // Draw the ball in new position
}

// Function to draw the paddle
void draw_paddle(int paddle_x, int paddle_y, int paddle_width, int paddle_height) {
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    bar(paddle_x, paddle_y, paddle_x + paddle_width, paddle_y + paddle_height);  // Draw paddle
}

// Function to clear the paddle
void clear_paddle(int paddle_x, int paddle_y, int paddle_width, int paddle_height) {
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    bar(paddle_x, paddle_y, paddle_x + paddle_width, paddle_y + paddle_height);  // Clear paddle
}

// Function to draw the bricks
void draw_bricks(int bricks[5][10], int brick_width, int brick_height) {
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 10; j++) {
            if (bricks[i][j] == 1) {  // Only draw if brick exists
                x = j * brick_width;
                y = i * brick_height + 30;  // Shift bricks down by 30 pixels
                bar(x, y, x + brick_width - 2, y + brick_height - 2);  // Draw brick with small gap
            }
        }
    }
}

// Function to clear a brick's previous position
void clear_brick(int brick_x, int brick_y, int brick_width, int brick_height) {
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    bar(brick_x, brick_y, brick_x + brick_width - 2, brick_y + brick_height - 2);  // Clear the brick area
}


// Function to clear the previous score area
void clear_score() {
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    bar(10, 10, 150, 30);  // Clear the area where the score will be displayed
}

// Function to display the score
void display_score(int score) {
    clear_score();  // Clear previous score

    sprintf(score_text, "Score: %d", score);
    setcolor(WHITE);
    outtextxy(10, 10, score_text);  // Display score at the top-left corner
}


int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    // Initialize bricks
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 10; j++) {
            bricks[i][j] = 1;  // All bricks present at the start
        }
    }

    brick_width = getmaxx() / 10;
    brick_height = 30;

    // Draw initial bricks
    draw_bricks(bricks, brick_width, brick_height);

    // Infinite game loop
    while (1) {
        // Clear previous ball and paddle positions
        clear_ball(ball_x, ball_y, ball_radius);
        clear_paddle(paddle_x, paddle_y, paddle_width, paddle_height);

        // Move paddle with arrow keys
        if (kbhit()) {
            key = getch();
            if (key == 27 || key == 'e' || key == 'E') {  // ESC or 'E' key to exit
                break;
            } else if (key == 75 && paddle_x > 0) {  // Left arrow key
                paddle_x -= paddle_speed;
            } else if (key == 77 && paddle_x + paddle_width < getmaxx()) {  // Right arrow key
                paddle_x += paddle_speed;
            }
        }

        // Update ball position
        ball_x += ball_dx;
        ball_y += ball_dy;

        // Ball-wall collision detection
        if (ball_x - ball_radius <= 0 || ball_x + ball_radius >= getmaxx()) {
            ball_dx = -ball_dx;  // Reverse horizontal direction
        }
        if (ball_y - ball_radius <= 0) {
            ball_dy = -ball_dy;  // Reverse vertical direction (top wall)
        }
        if (ball_y + ball_radius >= paddle_y && ball_x >= paddle_x && ball_x <= paddle_x + paddle_width) {
            ball_dy = -ball_dy;  // Ball bounces off the paddle
        }

        // Ball hits bottom of screen (game over)
        if (ball_y + ball_radius >= getmaxy()) {
            setcolor(RED);
            outtextxy(250, 250, "Game Over!");

            sprintf(score_text, "Final Score: %d", score);
            outtextxy(250, 270, score_text);  // Display final score
            delay(2000);
            break;
        }

        // Brick collision detection
        for (i = 0; i < 5; i++) {
            for (j = 0; j < 10; j++) {
                if (bricks[i][j] == 1) {
                    brick_x = j * brick_width;
                    brick_y = i * brick_height + 30;  // Adjusted position for bricks

                    // Check for collision
                    if (ball_x + ball_radius >= brick_x && ball_x - ball_radius <= brick_x + brick_width &&
                        ball_y + ball_radius >= brick_y && ball_y - ball_radius <= brick_y + brick_height) {

                        // Destroy the brick
                        bricks[i][j] = 0;  // Mark brick as destroyed
                        clear_brick(brick_x, brick_y, brick_width, brick_height);  // Clear brick visually

                        // Increase score
                        score += 5;

                        // Determine the side of collision and adjust ball direction
                        if (ball_y - ball_radius < brick_y || ball_y + ball_radius > brick_y + brick_height) {
                            ball_dy = -ball_dy;  // Bounce vertically
                        } else {
                            ball_dx = -ball_dx;  // Bounce horizontally
                        }
                    }
                }
            }
        }

        // Redraw bricks after collision
        draw_bricks(bricks, brick_width, brick_height);

        // Draw updated ball and paddle
        draw_ball(ball_x, ball_y, ball_radius);
        draw_paddle(paddle_x, paddle_y, paddle_width, paddle_height);

        // Display current score
        display_score(score);

        // Delay to control ball speed
        delay(10);  // Adjust this value for ball speed
    }

    // Close graphics mode
    closegraph();
    return 0;
}

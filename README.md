# 🎯 Brick Breaker Game (C, Turbo C++)

This is a simple **Brick Breaker** game built in C using `graphics.h` on Turbo C++.  
Control the paddle, bounce the ball, break all the bricks, and score points.  
The game ends when the ball falls below the paddle.
---

## 🖼 Gameplay Preview
https://github.com/rajpendkalkar123/cg/blob/f0cfa481e882c4ce1fb42605ab39064558832b98/Brick_Game_Demo_Video_short.mp4
---

## ✨ Features
- 🎮 Paddle movement with arrow keys  
- 🧱 5 rows × 10 columns of bricks  
- 🏆 Score tracking in real time  
- 🔄 Collision detection (walls, paddle, bricks)  
- 📊 Final score display on Game Over  
- ⚡ Smooth animation using `delay()`  

---

## 🕹 How It Works
- The ball moves automatically and bounces off walls and paddle.
- Use the arrow keys to move the paddle:
  - ⬅️ **Left Arrow**: Move paddle left  
  - ➡️ **Right Arrow**: Move paddle right  
- Each brick broken adds **+5 points**.
- Press **E** or **ESC** to exit anytime.
- If the ball reaches the bottom, the game ends with a "Game Over" message.

---

## 📂 Project Structure
BrickBreaker/
│-- main.c # Game source code
│-- README.md # Project documentation
│-- C:\TURBOC3\BGI/ (Graphics library files required)

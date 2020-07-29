// Copyright 2020, Viktor Gange,
// Author: Viktor Gange <viktor.gange@gmail.com>

#ifndef BALL_H_
#define BALL_H_

extern double cx;
extern double cy;
extern int rx;
extern int ry;
extern double gx;
extern double gy;

// Draw the ball at the given position with the given radii.
void drawBall(bool inverse);

// Prepare the terminal to draw the ball.
void initTerminal();

// Move the ball depending on the speed
int moveBall(int key);


#endif  // BALL_H_

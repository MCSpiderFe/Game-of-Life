#ifndef COMMON_H
#define COMMON_H

#define CELL_SIZE 1
#define CELLMAP_WIDTH 1200
#define CELLMAP_HEIGHT 600
#define SCREEN_WIDTH CELLMAP_WIDTH * CELL_SIZE
#define SCREEN_HEIGHT CELLMAP_HEIGHT * CELL_SIZE

#define u_int unsigned int
#define u_chr unsigned char

void drawCell(u_int x, u_int y, u_int color);

#endif // !CELL_SETTINGS
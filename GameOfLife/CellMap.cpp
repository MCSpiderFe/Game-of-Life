#include <memory>
#include <ctime>

#include "CellMap.h"

CellMap::CellMap(u_int width, u_int height) : w(width), h(height)
{
	length = w * h;
	cells = new u_chr[length];
	temp_cells = new u_chr[length];
	memset(cells, 0, length);
}

CellMap::~CellMap()
{
	delete[] cells;
	delete[] temp_cells;
}

void CellMap::init()
{
	u_int seed = (unsigned)time(NULL);
	srand(seed);

	u_int x, y;

	for (int i = 0; i < length * 0.5; i++) {
		x = rand() % (w - 1);
		y = rand() % (h - 1);

		if (!cellState(x, y)) {
			setCell(x, y);
		}
	}
}

void CellMap::nextGen()
{
	u_int x, y, live_neighbours;
	u_chr* cell_ptr;

	memcpy(temp_cells, cells, length);
	cell_ptr = temp_cells;

	for (int y = 0; y < h; y++) {
		x = 0;
		do {
			while (*cell_ptr == 0) {
				cell_ptr++;
				
				if (++x >= w) goto nextRow;
			}

			live_neighbours = *cell_ptr >> 1;
			if (*cell_ptr & 0x01) {
				if ((live_neighbours != 2) && (live_neighbours != 3)) {
					clearCell(x, y);
					drawCell(x, y, 0x00);
				}
			}
			else {
				if (live_neighbours == 3) {
					setCell(x, y);
					drawCell(x, y, 0xFF);
				}
			}

			cell_ptr++;
		} while (++x < w);
	nextRow:;
	}
}

void CellMap::setCell(u_int x, u_int y)
{
	u_chr* cell_ptr = cells + (y * w + x);
	int xLeft, xRight, yAbove, yBelow;

	*(cell_ptr) |= 0x01;

	if (x == 0) {
		xLeft = w - 1;
	}
	else {
		xLeft = -1;
	}

	if (x == (w - 1)) {
		xRight = -((int)w - 1);
	}
	else {
		xRight = 1;
	}

	if (y == 0) {
		yAbove = (int)length - (int)w;
	}
	else {
		yAbove = -(int)w;
	}

	if (y == (h - 1)) {
		yBelow = -((int)length - (int)w);
	}
	else {
		yBelow = w;
	}

	*(cell_ptr + yAbove + xLeft) += 0x02;
	*(cell_ptr + yAbove) += 0x02;
	*(cell_ptr + yAbove + xRight) += 2;
	*(cell_ptr + xLeft) += 0x02;
	*(cell_ptr + xRight) += 0x02;
	*(cell_ptr + yBelow + xLeft) += 0x02;
	*(cell_ptr + yBelow) += 0x02;
	*(cell_ptr + yBelow + xRight) += 0x02;
}

void CellMap::clearCell(u_int x, u_int y)
{
	u_chr* cell_ptr = cells + (y * w + x);
	int xLeft, xRight, yAbove, yBelow;

	*(cell_ptr) &= ~0x01;

	if (x == 0) {
		xLeft = w - 1;
	}
	else {
		xLeft = -1;
	}

	if (x == (w - 1)) {
		xRight = -((int)w - 1);
	}
	else {
		xRight = 1;
	}

	if (y == 0) {
		yAbove = length - (int)w;
	}
	else {
		yAbove = -(int)w;
	}

	if (y == (h - 1)) {
		yBelow = -((int)length - (int)w);
	}
	else {
		yBelow = w;
	}

	*(cell_ptr + yAbove + xLeft) -= 0x02;
	*(cell_ptr + yAbove) -= 0x02;
	*(cell_ptr + yAbove + xRight) -= 0x02;
	*(cell_ptr + xLeft) -= 0x02;
	*(cell_ptr + xRight) -= 0x02;
	*(cell_ptr + yBelow + xLeft) -= 0x02;
	*(cell_ptr + yBelow) -= 0x02;
	*(cell_ptr + yBelow + xRight) -= 0x02;
}

int CellMap::cellState(u_int x, u_int y)
{
	u_chr* cell_ptr = cells + (y * w) + x;
	return *cell_ptr & 0x01;
}
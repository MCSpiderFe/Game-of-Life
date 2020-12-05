#ifndef CELLMAP_H
#define CELLMAP_H

#include "Common.h"

class CellMap
{
public:
	CellMap(u_int width, u_int height);
	~CellMap();

	void init();
	void nextGen();
	void setCell(u_int x, u_int y);
	void clearCell(u_int x, u_int y);
	int cellState(u_int x, u_int y);
private:
	u_chr* cells;
	u_chr* temp_cells;
	u_int w, h;
	u_int length;
};

#endif


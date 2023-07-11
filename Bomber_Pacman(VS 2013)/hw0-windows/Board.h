/*
* Board.h
*
*  Created on: May 2, 2014
*      Author: Sibt ul Hussain
*/
#ifndef _BOARD_H_
#define _BOARD_H_

//#include <GL/glut.h>
#include <iostream>
#include "util.h"
//#include "Bomberman.h"
using namespace std;

enum BoardParts {
	NILL, S_BRICK, G_BRICK, R_BRICK
};

class Board {
private:
	int xcellsize, ycellsize;
	int width, height;
	ColorNames pcolor, bcolor, gcolor;

public:
	static const int BOARD_X;
	static const int BOARD_Y;

	Board(int xsize = 8, int ysize = 8);

	~Board(void);

	void InitalizeBoard(int, int);
	//draw the board
	void Draw();

	static int GetBoardX() {
		return BOARD_X;
	}
	static int GetBoardY() {
		return BOARD_Y;
	}
	int GetMidX() {
		return BOARD_X * xcellsize / 2.0;
	}
	int GetMidY() {
		return BOARD_Y * ycellsize / 2.0;
	}
	int GetCellSize() {
		return xcellsize;
	}
	void GetInitBombermanPosition(int& x, int& y) {
		x = xcellsize + xcellsize / 2;
		y = ycellsize + ycellsize / 2;
	}

	void GetInitTextPosition(int& x, int& y);
	void GetInitPinkyPosition(int& x, int& y);
	//	int GetMidx

	int GetInitBlockPosition(int x, int y);

	void SetInitBlockColor(int x, int y, BoardParts color);

	void setBoardWidth(int w);

	void setBoardHeight(int h);

	int getBoardWidth();

	int getBoardHeight();

	void resetBoard();

};

#ifdef WITH_TEXTURES
void RegisterTextures();
#endif

#endif


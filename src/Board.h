#ifndef _Board
#define _Board

#include "ofMain.h"
#include "Square.h"

class Board {
	public:
		/* ============  PUBLIC METHODS  ============= */
		void test();

		/* reset the pieces to the original spots, call this before game */
		void reset();

		/* draws the squares to the screen, except for the pieces */
		void drawSquares();




		/* ============  PUBLIC VALUES  ============= */
		Square Squares[64];
		int whiteToMove;
		ofVec2f boardBottomLeft;
		ofVec2f nextRight;
		ofVec2f nextAbove;
		int squareSize = 60;
		int squareSpacing = 6;

		/* Movement flags. Set 1 if something happens */
		int wk_flag 	= 0;
		int war_flag 	= 0;
		int whr_flag 	= 0;
		int bk_flag 	= 0;
		int bar_flag 	= 0;
		int bhr_flag 	= 0;
		int ep_flag 	= -2;	// set to -2 to avoid conflicts with pawns in column '0'


		Board();

	private:
};

#endif
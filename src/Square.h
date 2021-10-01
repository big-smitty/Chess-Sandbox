#ifndef _Square
#define _Square

#include "ofMain.h"

class Square {
	public:
		/* ============  PUBLIC METHODS  ============= */
		// called once, instantiates row, column, index, and color
		void setup(int input_index);

		// called to reset the pieces to the square
		void resetPiece();

		// set the values of the piece
		void setPiece(char input_type, int input_color);



		/* ============  PUBLIC VALUES  ============= */
		ofColor color;
		char squareColor;
		int index;
		int column;
		int row;
		char piece_type = ' ';	/* can be ' ', ! (error), p, k, b, r, q, k */
		int piece_color	= -1;	/* 1 is white, 0 is black, if has_piece is false then piece_color doesn't matter */

		Square();

	private:
};

#endif
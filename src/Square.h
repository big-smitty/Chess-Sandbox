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

		// remove any piece from the square
		void empty();

		/* set the color of a square, b,w,g,r,y */
		void setColor(char inColor);

		/* reset the color of a square back to what it's supposed to be */
		void resetColor();

		/* returns 1 if the square has a piece, otherwise 0 */
		int hasPiece();


		/* ============  PUBLIC VALUES  ============= */
		ofColor color;
		char squareColor;
		int index;
		int column;
		int row;
		char piece_type 	= ' ';	/* can be ' ', ! (error), p, k, b, r, q, k */
		int piece_color		= -1;	/* 1 is white, 0 is black, if has_piece is false then piece_color doesn't matter */
		int selected		= 0;

		Square();

	private:
};

#endif
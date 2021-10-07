#ifndef _Board
#define _Board

#include "ofMain.h"
#include "Square.h"

class Board {
	public:
		/* ============  PUBLIC METHODS  ============= */

		/* reset the pieces to the original spots, call this before game */
		void reset();

		/* draws the squares to the screen, except for the pieces */
		void drawSquares();

		/* places an indicator showing whos move it is */
		void placeMoveIndicator();

		/* given index for squares array, return array[64] of ints where 0 if can't move there, 1 if piece can move there */
		long long getPossibleMoves(int index);

		/* given index, and target square, move the target there. Includes castling handling, error checking */
		void moveTo(Square &starting, Square &target);
		void moveTo(int ix, int iy, int tx, int ty);
		void moveTo(int iindex, int tindex);

		/* given board long long, color '1' squares the toColor */
		void colorSquares(long long squaresToColor, char toColor);

		/* reset all the squares' color */
		void resetSquaresColor();

		/* given board long long, select the valued squares */
		void selectSquares(long long squaresToSelect);

		/* resets the 'selected' value of all squares back to 0 */
		void clearSelection();

		/* takes a reference to a long long and an index, adds the correct value to reference */
		void seton(long long *ref, int index, int xdev, int ydev);

		/* return index from x and y, -1 if out of bounds */
		int getSelf(int x, int y);

		/* transform the index by the given amount. Return -1 if it's not valid, otherwise the index */
		int transformBy(int index, int xdev, int ydev);

		/* returns true if the transformed square is populated with an enemy piece */
		int isEnemy(int index, int xdev, int ydev);

		/* returns true if the square is empty or occupied by an enemy piece, eg. a non-pawn can take there */
		bool takeable(int index, int xdev, int ydev);
		int takeable(int index, int originalColor, int xdev, int ydev);

		/* given parameters, keep moving in that direction until piece or wall. takeable piece returns index. otherwise returns -1 */
		void recurs(int index, long long *ref, int originalColor, int xdev, int ydev);

		/* given parameters, move once, call seton */
		void nonrecurs(int index, long long *ref, int originalColor, int xdev, int ydev);

		/* returns 1 if the index has a piece */
		int hasPiece(int index);


		/* ============  PUBLIC VALUES  ============= */
		Square Squares[64];
		int whiteToMove;
		ofVec2f boardBottomLeft;
		ofVec2f nextRight;
		ofVec2f nextAbove;
		int squareSize = 60;
		int squareSpacing = 6;
		int moveablePiece;

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
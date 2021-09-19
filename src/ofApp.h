#pragma once

#include "ofMain.h"

typedef struct {
	int column;
	int row;
	ofColor color;
	bool selected;
	int has_piece;		/* 1 for yes, 0 for no, -1 for errorSquare */
	char piece_type;	/* can be ' ', ! (error), p, k, b, r, q, k */
	int piece_color;	/* 1 is white, 0 is black, if has_piece is false then piece_color doesn't matter */
} Square;
/* selected squares get colored green in drawBoardNoPieces */
/* reset Squares and returnArray in clearSelection */
/* highlight translates from returnArray to Squares */
/* getPossibleMoves only changes the returnArray */


typedef struct {
	Square start_square;
	Square end_square;
	int is_empty;	// not the square, but the actual index in the moveset array
} Move;


class ofApp : public ofBaseApp{

	public:
		/* USER DEF FUNCTIONS */
		void setupBoard();
		void drawBoardNoPieces();
		int getClickedSquare(int x, int y);	/* x and y are screen coordinates, return index */
		void loadImages();
		void placePieces();
		void placeMoveIndicator();
		void getPossibleMoves(int index);
		void highlight();	/* given the returnArray, mark the Squares array accordingly */
		void recurs(int index, int originalColor, int xdev, int ydev);
		void nonrecurs(int index, int originalColor, int xdev, int ydev);
		void clearSelection();
		void moveTo(int index, int x, int y); // note: no error checking. Use carefully!
		int inCheck(int side);	// takes 1 if white, returns 1 if true;
		int recursiveKingCheck(int index, int originalColor, int xdev, int ydev, char checkFor);
		int nonrecursiveKingCheck(int index, int xdev, int ydev, char checkFor);
		int checkmate(int side);	// takes color, returns 1 if mate
		
		/* GAMEPLAY FUNCTIONS */
		int getNextEmptyMove();
		void fillPSBuffer(int side);	// pieces side buffer
		void fillMoveset(int side);
		void clearPSBuffer();
		void clearMoveset();
		void pickRandFromPSBuffer();
		void pickRandFromPSBuffer(int side);
		int pickRandFromMoveset();
		void printMoveset();
		void doRandomMove();			// use pickRandFromPSBuffer to do a game

		/* SQUARE LOOKUP FUNCTIONS */
		/* All int functions return index in Squares array */
		int getSelf(int x, int y);	/* x and y are board coordinates */
		int transformBy(int index, int xdev, int ydev);
		bool isEnemy(int index, int xdev, int ydev);
		bool takeable(int index, int xdev, int ydev);
		bool takeable(int index, int originalColor, int xdev, int ydev);
		Square* sqr(int index); /* return the address of a specific square */
		Square* tsqr(int index, int xdev, int ydev); // syntactic candy, get reference to the transform of a square


		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		ofImage whitePawn, whiteKnight, whiteBishop, whiteRook, whiteQueen, whiteKing;
		ofImage blackPawn, blackKnight, blackBishop, blackRook, blackQueen, blackKing;

		ofVec2f boardBottomLeft;
		int squareSize = 60;
		int squareSpacing = 6;
		int moveablePiece = 0;
		ofVec2f nextRight;	/* vector representing the spacing between squares, used for calculation */
		ofVec2f nextAbove;
		bool whiteToMove = true;

		/* Movement flags. Set 1 if something happens */
		int wk_flag 	= 0;
		int war_flag 	= 0;
		int whr_flag 	= 0;
		int bk_flag 	= 0;
		int bar_flag 	= 0;
		int bhr_flag 	= 0;
		int ep_flag 	= -2;	// set to -2 to avoid conflicts with pawns in column '0'

		int returnArray[64] 		= {0};	// filled 8x8, 1 where possible move, reset by clearSelection()
		int storageBuffer1[64] 		= {0};	// for use in the checkmate function ONLY
		int piecesCanMove[64] 	= {0};
		Move Moveset[200];		// filled with a list of possible moves
		Square Squares[64];
};

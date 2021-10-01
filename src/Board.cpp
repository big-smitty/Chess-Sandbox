#include "Board.h"
#include "Square.h"

Board::Board(){
		boardBottomLeft.set(80,600);
		nextRight.set(squareSize + squareSpacing, 0);
		nextAbove.set(0, -squareSize - squareSpacing); /* minus because y is flipped */
		reset();
	}


void Board::test(){
	Squares[0].setup(4);
	std::cout<<Squares[0].row << " " << Squares[0].column<<endl;
}

void Board::reset(){
	for (int i=0; i<64; i++){
		Squares[i].setup(i);
		Squares[i].resetPiece();
	}
}

void Board::drawSquares(){
	for (int i=0;i<64;i++){
		ofSetColor(Squares[i].color);
		ofDrawRectRounded((boardBottomLeft+nextRight*Squares[i].column).x,(boardBottomLeft+nextAbove*Squares[i].row).y,squareSize,squareSize,squareSpacing);
	}
}
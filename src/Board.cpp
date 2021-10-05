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
	whiteToMove=1;
}

void Board::drawSquares(){
	for (int i=0;i<64;i++){
		ofSetColor(Squares[i].color);
		ofDrawRectRounded((boardBottomLeft+nextRight*Squares[i].column).x,(boardBottomLeft+nextAbove*Squares[i].row).y,squareSize,squareSize,squareSpacing);
	}
}

void Board::placeMoveIndicator(){
	if (whiteToMove == true){
		ofSetColor(ofColor(230,230,230));
		ofDrawCircle((boardBottomLeft-nextRight*.5).x,boardBottomLeft.y,squareSize/4);
	} else {
		ofSetColor(ofColor(50,50,50));
		ofDrawCircle((boardBottomLeft-nextRight*.5).x,(boardBottomLeft+nextAbove*6).y,squareSize/4);
	}
}

long long Board::getPossibleMoves(int index){
	long long return_int = 0;
	// return_int += pow(2,index);
	if (Squares[index].piece_type==' '){return (0);}
	else if (Squares[index].piece_color==1){
		switch(Squares[index].piece_type){
			case 'p':
				if (Squares[transformBy(index,0,1)].piece_type==' '){
					// return_int+=pow(2,transformBy(index,0,1));
					seton(&return_int,index,0,1);
					if (Squares[index].row==1 && Squares[transformBy(index,0,2)].piece_type==' '){
						seton(&return_int,index,0,2);
					}
				}
				if (isEnemy(index,-1,1)){
					seton(&return_int,index,-1,1);
				}
				if (isEnemy(index,1,1)){
					seton(&return_int,index,1,1);
				}
				break;
			case 'n':
				nonrecurs(index, &return_int, 1, 2, 1);
				nonrecurs(index, &return_int, 1, 1, 2);
				nonrecurs(index, &return_int, 1, -1, 2);
				nonrecurs(index, &return_int, 1, -2, 1);
				nonrecurs(index, &return_int, 1, -2, -1);
				nonrecurs(index, &return_int, 1, -1, -2);
				nonrecurs(index, &return_int, 1, 1, -2);
				nonrecurs(index, &return_int, 1, 2, -1);
				break;
			case 'r':
				recurs(index, &return_int, 1,0,1);
				recurs(index, &return_int, 1,1,0);
				recurs(index, &return_int, 1,0,-1);
				recurs(index, &return_int, 1,-1,0);
				break;
			case 'b':
				recurs(index, &return_int, 1,1,1);
				recurs(index, &return_int, 1,-1,-1);
				recurs(index, &return_int, 1,1,-1);
				recurs(index, &return_int, 1,-1,1);
				break;
			case 'q':
				recurs(index, &return_int, 1,0,1);
				recurs(index, &return_int, 1,1,0);
				recurs(index, &return_int, 1,0,-1);
				recurs(index, &return_int, 1,-1,0);
				recurs(index, &return_int, 1,1,1);
				recurs(index, &return_int, 1,-1,-1);
				recurs(index, &return_int, 1,1,-1);
				recurs(index, &return_int, 1,-1,1);
				break;
			case 'k':
				nonrecurs(index, &return_int, 1,0,1);
				nonrecurs(index, &return_int, 1,1,0);
				nonrecurs(index, &return_int, 1,0,-1);
				nonrecurs(index, &return_int, 1,-1,0);
				nonrecurs(index, &return_int, 1,1,1);
				nonrecurs(index, &return_int, 1,-1,-1);
				nonrecurs(index, &return_int, 1,1,-1);
				nonrecurs(index, &return_int, 1,-1,1);
				break;
		}
	} else if (Squares[index].piece_color==0){
		switch(Squares[index].piece_type){
			case 'p':
				if (Squares[transformBy(index,0,-1)].piece_type==' '){
					// return_int+=pow(2,transformBy(index,0,1));
					seton(&return_int,index,0,-1);
					if (Squares[index].row==6 && Squares[transformBy(index,0,-2)].piece_type==' '){
						seton(&return_int,index,0,-2);
					}
				}
				if (isEnemy(index,-1,-1)){
					seton(&return_int,index,-1,-1);
				}
				if (isEnemy(index,1,-1)){
					seton(&return_int,index,1,-1);
				}
				break;
			case 'n':
				nonrecurs(index, &return_int, 0, 2, 1);
				nonrecurs(index, &return_int, 0, 1, 2);
				nonrecurs(index, &return_int, 0, -1, 2);
				nonrecurs(index, &return_int, 0, -2, 1);
				nonrecurs(index, &return_int, 0, -2, -1);
				nonrecurs(index, &return_int, 0, -1, -2);
				nonrecurs(index, &return_int, 0, 1, -2);
				nonrecurs(index, &return_int, 0, 2, -1);
				break;
			case 'r':
				recurs(index, &return_int, 0,0,1);
				recurs(index, &return_int, 0,1,0);
				recurs(index, &return_int, 0,0,-1);
				recurs(index, &return_int, 0,-1,0);
				break;
			case 'b':
				recurs(index, &return_int, 0,1,1);
				recurs(index, &return_int, 0,-1,-1);
				recurs(index, &return_int, 0,1,-1);
				recurs(index, &return_int, 0,-1,1);
				break;
			case 'q':
				recurs(index, &return_int, 0,0,1);
				recurs(index, &return_int, 0,1,0);
				recurs(index, &return_int, 0,0,-1);
				recurs(index, &return_int, 0,-1,0);
				recurs(index, &return_int, 0,1,1);
				recurs(index, &return_int, 0,-1,-1);
				recurs(index, &return_int, 0,1,-1);
				recurs(index, &return_int, 0,-1,1);
				break;
			case 'k':
				nonrecurs(index, &return_int, 0,0,1);
				nonrecurs(index, &return_int, 0,1,0);
				nonrecurs(index, &return_int, 0,0,-1);
				nonrecurs(index, &return_int, 0,-1,0);
				nonrecurs(index, &return_int, 0,1,1);
				nonrecurs(index, &return_int, 0,-1,-1);
				nonrecurs(index, &return_int, 0,1,-1);
				nonrecurs(index, &return_int, 0,-1,1);
				break;
		}
	}

	return (return_int);
}

void Board::colorSquares(long long squaresToColor, char toColor){
	int j;
	for (int i=0; i<64; i++){
		j = 0 != (squaresToColor & ((long long)1 << (63-i)));	// God im smart
		if (j==1) {Squares[63-i].setColor(toColor);}
	}
}

void Board::resetSquaresColor(){
	for (int i=0; i<64; i++){
		Squares[i].resetColor();
	}
}

void Board::seton(long long *ref, int index, int xdev, int ydev){
	*ref+=pow(2,transformBy(index,xdev,ydev));
}

int Board::getSelf(int x, int y){
	if (x<0 || y<0 || x>7 || y>7){	return(-1);	}
	return (x + y*8);
}

int Board::transformBy(int index, int xdev, int ydev){
	if (ofWrap(index,0,8)+xdev > 7 || ofWrap(index,0,8)+xdev < 0){
		return (-1);
	}
	if ((index/8) + ydev > 7 || (index/8) + ydev < 0){
		return (-1);
	}
	return(index+xdev+(ydev*8));
}

bool Board::isEnemy(int index, int xdev, int ydev){		// yucky code
	if (Squares[index].piece_color==1){
		if (Squares[transformBy(index,xdev,ydev)].piece_type!=' ' && Squares[transformBy(index,xdev,ydev)].piece_color==0){
			return (true);
		} else { return (false);}
	} else {
		if (Squares[transformBy(index,xdev,ydev)].piece_type!=' ' && Squares[transformBy(index,xdev,ydev)].piece_color==1){
			return (true);
		} else { return (false);}
	}
}

bool Board::takeable(int index, int xdev, int ydev){
	if (transformBy(index,xdev,ydev)==-1) {return (0);}
	return (Squares[transformBy(index,xdev,ydev)].piece_type==' ' || isEnemy(index,xdev,ydev));
}

int Board::takeable(int index, int originalColor, int xdev, int ydev){
	if (transformBy(index,xdev,ydev)==-1) {return (0);}
	if (originalColor==1 && Squares[transformBy(index,xdev,ydev)].piece_color==0){
		return (1);
	} else if (originalColor==0 && Squares[transformBy(index,xdev,ydev)].piece_color==1) {
		return (1);
	} else if (Squares[transformBy(index,xdev,ydev)].piece_type==' '){
		return (1);
	} else {return(0);}
}

void Board::recurs(int index, long long *ref, int originalColor, int xdev, int ydev){
	if (transformBy(index,xdev,ydev)!=-1){
		if (takeable(index,originalColor,xdev,ydev)){
			*ref+=pow(2,transformBy(index,xdev,ydev));
			return;
		} else if (Squares[transformBy(index,xdev,ydev)].piece_color==originalColor){
			return;
		} else {
			recurs(transformBy(index,xdev,ydev), ref, originalColor,xdev,ydev);
		}
	} else {return;}
}

void Board::nonrecurs(int index, long long *ref, int originalColor, int xdev, int ydev){
	if (transformBy(index,xdev,ydev)!=-1){
		if (Squares[transformBy(index,xdev,ydev)].piece_color!=originalColor){
			*ref+=pow(2,transformBy(index,xdev,ydev));
		}
	}
}
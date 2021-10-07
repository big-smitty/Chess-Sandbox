#include "Board.h"
#include "Square.h"

Board::Board(){
		boardBottomLeft.set(80,600);
		nextRight.set(squareSize + squareSpacing, 0);
		nextAbove.set(0, -squareSize - squareSpacing); /* minus because y is flipped */
		reset();
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
	moveablePiece = index;
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
				if (((Squares[index].column)==ep_flag+1||(Squares[index].column)==ep_flag-1)&&(Squares[index].row)==4){
					seton(&return_int,ep_flag+40,0,0);
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
				if (((Squares[index].column)==ep_flag+1||(Squares[index].column)==ep_flag-1)&&(Squares[index].row)==3){
					seton(&return_int,ep_flag+16,0,0);
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

void Board::moveTo(Square &starting, Square &target){
	// int xi = starting.column;
	int yi = starting.row;
	int x = target.column;
	int y = target.row;
	target.setPiece(starting.piece_type, starting.piece_color);
	starting.empty();

	/* en pipi handling, holy hell */
	/* If the square behind the en-passant square if full of opp. color pawn (en passant happpend), remove the taken pawn */
	if (y==5 && target.piece_color==1 && ep_flag==x){
		Squares[getSelf(x,y-1)].empty();
	}
	if (y==2 && target.piece_color==0 && ep_flag==x){
		Squares[getSelf(x,y+1)].empty();
	}
	ep_flag=-2;
	/* if a double pawn move, set the ep_flag */
	if (y==3 && yi==1 && target.piece_type=='p'){	// double pawn move white
		if ((Squares[getSelf(x+1,y)].piece_color==0)&&(Squares[getSelf(x+1,y)].piece_type=='p')){	ep_flag=x;	}
		if ((Squares[getSelf(x-1,y)].piece_color==0)&&(Squares[getSelf(x-1,y)].piece_type=='p')){	ep_flag=x;	}
	}
	if (y==4 && yi==6 && target.piece_type=='p'){	// double pawn move black
		if ((Squares[getSelf(x+1,y)].piece_color==1)&&(Squares[getSelf(x+1,y)].piece_type=='p')){	ep_flag=x;	}
		if ((Squares[getSelf(x-1,y)].piece_color==1)&&(Squares[getSelf(x-1,y)].piece_type=='p')){	ep_flag=x;	}
	}
}

void Board::moveTo(int ix, int iy, int tx, int ty){
	moveTo(Squares[getSelf(ix,iy)],Squares[getSelf(tx,ty)]);
}

void Board::moveTo(int start, int target){
	moveTo(Squares[start], Squares[target]);
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

void Board::selectSquares(long long squaresToSelect){
	int j;
	for (int i=0; i<64; i++){
		j = 0 != (squaresToSelect & ((long long)1 << (63-i)));	// God im smart
		if (j==1) {Squares[63-i].selected = 1;}
	}
}

void Board::clearSelection(){
	for (int i=0; i<64; i++){
		Squares[i].selected = 0;
	}
	resetSquaresColor();
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

int Board::isEnemy(int index, int xdev, int ydev){
	if (transformBy(index,xdev,ydev)==-1){	return(0);	}
	else {
		if (Squares[transformBy(index,xdev,ydev)].hasPiece() && Squares[transformBy(index,xdev,ydev)].piece_color==1-Squares[index].piece_color){
			return (1);
		} else {
			return (0);
		}
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
	} else if (!Squares[transformBy(index,xdev,ydev)].hasPiece()){
		return (1);
	} else {return(0);}
}

void Board::recurs(int index, long long *ref, int originalColor, int xdev, int ydev){
	if (transformBy(index,xdev,ydev)!=-1){
		if (!Squares[transformBy(index,xdev,ydev)].hasPiece()){
			*ref+=pow(2,transformBy(index,xdev,ydev));
			recurs(transformBy(index,xdev,ydev), ref, originalColor,xdev,ydev);
		} else if (takeable(index,originalColor,xdev,ydev)){
			*ref+=pow(2,transformBy(index,xdev,ydev));
			return;
		} else if (Squares[transformBy(index,xdev,ydev)].piece_color==originalColor){
			return;
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

int Board::hasPiece(int index){
	if (Squares[index].hasPiece()){return (1);}
	else {return(0);}
}
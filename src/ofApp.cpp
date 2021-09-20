#include "ofApp.h"

ofColor black(50,50,50);
ofColor white(230,230,230);
ofColor green(0,168,107);
ofColor yellow(255,211,0);
ofColor red(184,15,10);
Square errorSquare; 	// for when you get those pesky index out of bounds exceptions accessing Squares array
Square storageSquare; 	// for holding a single square in storage, used for 'check' checking in getPossibleMoves

/* --------- USER FUNCTIONS ----------- */

/* initializes the Squares array to the correct values for a reset position */
/* to be called when reseting the board */
void ofApp::setupBoard(){
	/* Setup the error square here to not clutter setup() */
	errorSquare.column = -1;
	errorSquare.row = -1;
	errorSquare.color = black;
	errorSquare.selected = false;
	errorSquare.has_piece = -1;
	errorSquare.piece_type = '!';
	errorSquare.piece_color = -1;

	/* Setup the Moveset array */
	for (int i=0; i<200; i++){
		Moveset[i].start_square = errorSquare;
		Moveset[i].end_square = errorSquare;
		Moveset[i].is_empty=1;
	}

	whiteToMove = true;
	wk_flag = war_flag=whr_flag=bk_flag=bar_flag=bhr_flag=0;

	for (int column = 0; column < 8; column++){
		for (int row = 0; row < 8; row++){
			Square *cSquare = &Squares[column + row*8];  /* cSquare = current Square */
			cSquare->column = column;
			cSquare->row = row;
			cSquare->selected = false;
			if (row%2==0 && column&&2==0){
				cSquare->color = black;
			} else {
				cSquare->color = white;
			}
			if (row == 0 || row == 7){	/* pieces */
				switch(column){
					case 0: case 7:
						cSquare->piece_type = 'r';
						break;
					case 1: case 6:
						cSquare->piece_type = 'n';
						break;
					case 2: case 5:
						cSquare->piece_type = 'b';
						break;
					case 3:
						cSquare->piece_type = 'q';
						break;
					case 4:
						cSquare->piece_type = 'k';
						break;
					default:
						cSquare->piece_type = '!'; /* bad init, '!' means error */
						break;
				}
				cSquare->has_piece = 1;
				if (row == 0){ cSquare->piece_color=1; } else { cSquare->piece_color=0; }
			} else if (row == 1 || row == 6){ 	/* pawns */
				cSquare->has_piece = 1;
				if (row == 1){ cSquare->piece_color=1; } else { cSquare->piece_color=0; }
				cSquare->piece_type = 'p';
			} else {
				cSquare->has_piece = 0;
				cSquare->piece_color = 0;
				cSquare->piece_type = ' ';
			}
		}
	}
}

/* draws the squares to the screen, minus the pieces */
/* selected squares get colored green */
void ofApp::drawBoardNoPieces(){
	// draw squares, discarding selected squares
	for (int column = 0; column < 8; column++){
		for (int row = 0; row < 8; row++){
			if ((row%2==0 && column%2==0) || (row%2==1 &&column%2==1))
				{	ofSetColor(black);	}
			else {	ofSetColor(white);	}
			ofDrawRectRounded((boardBottomLeft+nextRight*column).x,(boardBottomLeft+nextAbove*row).y,squareSize,squareSize,squareSpacing);
		}
	}
	// color selected squares green
	for (int column = 0; column < 8; column++){
		for (int row = 0; row < 8; row++){
			if (Squares[column + row*8].selected == true){
				ofSetColor(green);
				ofDrawRectRounded((boardBottomLeft+nextRight*column).x,(boardBottomLeft+nextAbove*row).y,squareSize,squareSize,squareSpacing);
			}
		}
	}
}

/* takes coordinates of a mouse click, returns index of Squares array clicked, if outside bounds returns -1 */
int ofApp::getClickedSquare(int x, int y){
	int leftBound 		= boardBottomLeft.x;
	int rightBound 		= (boardBottomLeft+nextRight*8).x - squareSpacing;
	int bottomBound		= boardBottomLeft.y+squareSize;
	int topBound 		= (boardBottomLeft+nextAbove*7).y;
	/* not in square space, return -1 */
	if (x<leftBound || x>rightBound || y>bottomBound || y<topBound)	{	return (-1);	}
	/* otherwise return index in Squares array*/
	int tempx, tempy;
	for (tempx = 0; tempx<8; tempx++){
		if (x-(tempx+1)*nextRight.x < leftBound){	break;	}
	}
	for (tempy = 0; tempy<8; tempy++){
		if (y-(tempy+1)*nextAbove.y > bottomBound){	break;	}
	}
	return (tempx + tempy*8);
}

/* loads the images from bin/data/images */
void ofApp::loadImages(){
	whitePawn.load("images/whitePawn.png");
	whiteKnight.load("images/whiteKnight.png");
	whiteBishop.load("images/whiteBishop.png");
	whiteRook.load("images/whiteRook.png");
	whiteQueen.load("images/whiteQueen.png");
	whiteKing.load("images/whiteKing.png");
	blackPawn.load("images/blackPawn.png");
	blackKnight.load("images/blackKnight.png");
	blackBishop.load("images/blackBishop.png");
	blackRook.load("images/blackRook.png");
	blackQueen.load("images/blackQueen.png");
	blackKing.load("images/blackKing.png");
}

/* places the piece images on the relevant squares, based on data in the squares array */
void ofApp::placePieces(){
	int cSquare; // current square, declared in loop
	for (int column = 0; column < 8; column++){				// For all X
		for (int row = 0; row < 8; row++){					// For all Y
			cSquare = column + row*8;						// Tabulate index from X and Y
			if (Squares[cSquare].has_piece == 1){			// if theres a piece there
				if (Squares[cSquare].piece_color == 1){ 	// if color is 1, eg. white
					if (Squares[cSquare].selected == true){	ofSetColor(green);	}
					else {	ofSetColor(white);	}
					switch (Squares[cSquare].piece_type){
						case 'p':
							whitePawn.draw((boardBottomLeft+nextRight*column).x,(boardBottomLeft+nextAbove*row).y,squareSize,squareSize);
							break;
						case 'n':
							whiteKnight.draw((boardBottomLeft+nextRight*column).x,(boardBottomLeft+nextAbove*row).y,squareSize,squareSize);
							break;
						case 'b':
							whiteBishop.draw((boardBottomLeft+nextRight*column).x,(boardBottomLeft+nextAbove*row).y,squareSize,squareSize);
							break;
						case 'r':
							whiteRook.draw((boardBottomLeft+nextRight*column).x,(boardBottomLeft+nextAbove*row).y,squareSize,squareSize);
							break;
						case 'q':
							whiteQueen.draw((boardBottomLeft+nextRight*column).x,(boardBottomLeft+nextAbove*row).y,squareSize,squareSize);
							break;
						case 'k':
							if (inCheck(1)){	ofSetColor(yellow);	}
							if (checkmate(1)) {	ofSetColor(red);	}
							whiteKing.draw((boardBottomLeft+nextRight*column).x,(boardBottomLeft+nextAbove*row).y,squareSize,squareSize);
							break;
					}
				} else { 									// else color is 0, eg. black
					if (Squares[cSquare].selected == true){	ofSetColor(green);	}
					else {	ofSetColor(black);	}
					switch (Squares[cSquare].piece_type){
						case 'p':
							blackPawn.draw((boardBottomLeft+nextRight*column).x,(boardBottomLeft+nextAbove*row).y,squareSize,squareSize);
							break;
						case 'n':
							blackKnight.draw((boardBottomLeft+nextRight*column).x,(boardBottomLeft+nextAbove*row).y,squareSize,squareSize);
							break;
						case 'b':
							blackBishop.draw((boardBottomLeft+nextRight*column).x,(boardBottomLeft+nextAbove*row).y,squareSize,squareSize);
							break;
						case 'r':
							blackRook.draw((boardBottomLeft+nextRight*column).x,(boardBottomLeft+nextAbove*row).y,squareSize,squareSize);
							break;
						case 'q':
							blackQueen.draw((boardBottomLeft+nextRight*column).x,(boardBottomLeft+nextAbove*row).y,squareSize,squareSize);
							break;
						case 'k':
							if(inCheck(0)){	ofSetColor(yellow);	}
							if (checkmate(0)) {	ofSetColor(red);	}
							blackKing.draw((boardBottomLeft+nextRight*column).x,(boardBottomLeft+nextAbove*row).y,squareSize,squareSize);
							break;
					}
				}
			}
		}
	}
}

/* places an indicator showing whos move it is */
void ofApp::placeMoveIndicator(){
	if (whiteToMove == true){
		ofSetColor(white);
		ofDrawCircle((boardBottomLeft-nextRight*.5).x,boardBottomLeft.y,squareSize/4);
	} else {
		ofSetColor(black);
		ofDrawCircle((boardBottomLeft-nextRight*.5).x,(boardBottomLeft+nextAbove*6).y,squareSize/4);
	}
}

/* update the board state by calling every draw function */
void ofApp::updateState(){
	drawBoardNoPieces();
	placePieces();
	highlight();
	placeMoveIndicator();
}

/* given an index from the Squares array, updates the returnArray. */
/* returned array is 1 if possible move, 0 if not */
/* returns to returnArray */
void ofApp::getPossibleMoves(int index){
	Square *cSquare = &Squares[index];		// cSquare is a Square reference. Access this data by cSquare->type
	if (cSquare->has_piece == 0) {return;} 	// if empty square, exit
	else if (cSquare->piece_color == 1){	// if the square has a white piece
		switch (cSquare->piece_type){
			case 'p':
				if (tsqr(index,0,1)->has_piece == 0){
					returnArray[transformBy(index,0,1)] = 1;
					if (cSquare->row == 1 && tsqr(index,0,2)->has_piece == 0){
						returnArray[transformBy(index,0,2)] = 1;
					}
				}
				if (isEnemy(index,-1,1)){
					returnArray[transformBy(index,-1,1)] = 1;
				}
				if (isEnemy(index,1,1)){
					returnArray[transformBy(index,1,1)] = 1;
				}
				if ((cSquare->column==ep_flag+1||cSquare->column==ep_flag-1)&&cSquare->row==4){
					returnArray[ep_flag+40] = 1;
				}
				break;
			case 'n':
				nonrecurs(index,1,2,1);
				nonrecurs(index,1,1,2);
				nonrecurs(index,1,-1,2);
				nonrecurs(index,1,-2,1);
				nonrecurs(index,1,-2,-1);
				nonrecurs(index,1,-1,-2);
				nonrecurs(index,1,1,-2);
				nonrecurs(index,1,2,-1);
				break;
			case 'r':
				recurs(index,1,0,1);
				recurs(index,1,1,0);
				recurs(index,1,0,-1);
				recurs(index,1,-1,0);
				break;
			case 'b':
				recurs(index,1,1,1);
				recurs(index,1,-1,-1);
				recurs(index,1,1,-1);
				recurs(index,1,-1,1);
				break;
			case 'q':
				recurs(index,1,0,1);
				recurs(index,1,1,0);
				recurs(index,1,0,-1);
				recurs(index,1,-1,0);
				recurs(index,1,1,1);
				recurs(index,1,-1,-1);
				recurs(index,1,1,-1);
				recurs(index,1,-1,1);
				break;
			case 'k':
				nonrecurs(index,1,0,1);
				nonrecurs(index,1,1,0);
				nonrecurs(index,1,0,-1);
				nonrecurs(index,1,-1,0);
				nonrecurs(index,1,1,1);
				nonrecurs(index,1,-1,-1);
				nonrecurs(index,1,1,-1);
				nonrecurs(index,1,-1,1);
				// castling kingside.  If not castled yet, and no pieces in between...
				if (wk_flag==0 && whr_flag==0 && sqr(5)->has_piece==0 && sqr(6)->has_piece==0 && inCheck(1)==0){
					sqr(5)->has_piece=1;sqr(5)->piece_type='k';sqr(5)->piece_color=1;
					sqr(6)->has_piece=1;sqr(6)->piece_type='k';sqr(6)->piece_color=1;
					if (inCheck(1)==0) {	returnArray[6]=1;	}
					sqr(5)->has_piece=0;sqr(5)->piece_type=' ';sqr(5)->piece_color=1;
					sqr(6)->has_piece=0;sqr(6)->piece_type=' ';sqr(6)->piece_color=1;
				}	// castling queenside
				if (wk_flag==0 && war_flag==0 && sqr(1)->has_piece==0 && sqr(2)->has_piece==0 && sqr(3)->has_piece==0 && inCheck(1)==0){
					sqr(2)->has_piece=1;sqr(2)->piece_type='k';sqr(2)->piece_color=1;
					sqr(3)->has_piece=1;sqr(3)->piece_type='k';sqr(3)->piece_color=1;
					if (inCheck(1)==0) {	returnArray[2]=1;	}
					sqr(2)->has_piece=0;sqr(2)->piece_type=' ';sqr(2)->piece_color=1;
					sqr(3)->has_piece=0;sqr(3)->piece_type=' ';sqr(3)->piece_color=1;
				}
				break;
		}
	} else if (cSquare->piece_color == 0){
		switch (cSquare->piece_type){
			case 'p':
				if (tsqr(index,0,-1)->has_piece == 0){
					returnArray[transformBy(index,0,-1)] = 1;
					if (cSquare->row == 6 && tsqr(index,0,-2)->has_piece == 0){
						returnArray[transformBy(index,0,-2)] = 1;
					}
				}
				if (isEnemy(index,-1,-1)){
					returnArray[transformBy(index,-1,-1)] = 1;
				}
				if (isEnemy(index,1,-1)){
					returnArray[transformBy(index,1,-1)] = 1;
				}
				if ((cSquare->column==ep_flag+1||cSquare->column==ep_flag-1)&&cSquare->row==3){
					returnArray[ep_flag+16] = 1;
				}
				break;
			case 'n':
				nonrecurs(index,0,2,1);
				nonrecurs(index,0,1,2);
				nonrecurs(index,0,-1,2);
				nonrecurs(index,0,-2,1);
				nonrecurs(index,0,-2,-1);
				nonrecurs(index,0,-1,-2);
				nonrecurs(index,0,1,-2);
				nonrecurs(index,0,2,-1);
				break;
			case 'r':
				recurs(index,0,0,1);
				recurs(index,0,1,0);
				recurs(index,0,0,-1);
				recurs(index,0,-1,0);
				break;
			case 'b':
				recurs(index,0,1,1);
				recurs(index,0,-1,-1);
				recurs(index,0,1,-1);
				recurs(index,0,-1,1);
				break;
			case 'q':
				recurs(index,0,0,1);
				recurs(index,0,1,0);
				recurs(index,0,0,-1);
				recurs(index,0,-1,0);
				recurs(index,0,1,1);
				recurs(index,0,-1,-1);
				recurs(index,0,1,-1);
				recurs(index,0,-1,1);
				break;
			case 'k':
				nonrecurs(index,0,0,1);
				nonrecurs(index,0,1,0);
				nonrecurs(index,0,0,-1);
				nonrecurs(index,0,-1,0);
				nonrecurs(index,0,1,1);
				nonrecurs(index,0,-1,-1);
				nonrecurs(index,0,1,-1);
				nonrecurs(index,0,-1,1);
				// castling kingside.  If not castled yet, and no pieces in between...
				if (bk_flag==0 && bhr_flag==0 && sqr(61)->has_piece==0 && sqr(62)->has_piece==0 && inCheck(0)==0){
					sqr(61)->has_piece=1;sqr(61)->piece_type='k';sqr(61)->piece_color=0;
					sqr(62)->has_piece=1;sqr(62)->piece_type='k';sqr(62)->piece_color=0;
					if (inCheck(0)==0) {	returnArray[62]=1;	}
					sqr(61)->has_piece=0;sqr(61)->piece_type=' ';sqr(61)->piece_color=0;
					sqr(62)->has_piece=0;sqr(62)->piece_type=' ';sqr(62)->piece_color=0;
				}	// castling queenside
				if (bk_flag==0 && bar_flag==0 && sqr(57)->has_piece==0 && sqr(58)->has_piece==0 && sqr(59)->has_piece==0 && inCheck(0)==0){
					sqr(58)->has_piece=1;sqr(58)->piece_type='k';sqr(58)->piece_color=0;
					sqr(59)->has_piece=1;sqr(59)->piece_type='k';sqr(59)->piece_color=0;
					if (inCheck(0)==0) {	returnArray[58]=1;	}
					sqr(58)->has_piece=0;sqr(58)->piece_type=' ';sqr(58)->piece_color=0;
					sqr(59)->has_piece=0;sqr(59)->piece_type=' ';sqr(59)->piece_color=0;
				}
				break;
		}
	}
	/* 	this part is 'check' checking.
		for every square that is one(1) in the return array (ie it is a possible move)
		simulate the move. If that move results in a check, remove it from the list of possible moves (mark it zero(0) on return array)
	 */
	int savedColor = cSquare->piece_color;
	for (int i=0; i<64; i++){
		if (returnArray[i]==1){
			storageSquare = Squares[i];
			char savedType = cSquare->piece_type;
			cSquare->piece_type=' ';
			cSquare->has_piece=0;
			sqr(i)->has_piece=1;
			sqr(i)->piece_color=savedColor;
			sqr(i)->piece_type=savedType;
			if (inCheck(savedColor)){	returnArray[i]=0;	}
			Squares[i] = storageSquare;
			cSquare->piece_type=savedType;
			cSquare->has_piece=1;
		}
	}
	}

/* given the returnArray, mark the Squares.selected array accordingly */
/* the return array is set in getPossibleMoves(), it is an array of 64 integers, either 0 (off) or 1 (on) */
void ofApp::highlight(){
	for (int i = 0; i < 64; i++){
		if (returnArray[i]==1){
			Squares[i].selected = true;
		} else {
			Squares[i].selected = false;
		}
	}
}

/*	for use with the 'check' checking. Just like takeable but it only checks for a certain piece
	returns 1 if the certain thing is on the certain line, otherwise 0 */
int ofApp::recursiveKingCheck(int index, int originalColor, int xdev, int ydev, char checkFor){
	if (tsqr(index,xdev,ydev)->has_piece){
		if (tsqr(index,xdev,ydev)->piece_color!=originalColor && tsqr(index,xdev,ydev)->piece_type==checkFor){
			return (1);
		}	else{
			return (0);
		}
	}	else {
		return (recursiveKingCheck(transformBy(index,xdev,ydev),originalColor,xdev,ydev,checkFor));
	}
}

/* given an index, a transform, and a piece type to look for, look in that direction once. */
int ofApp::nonrecursiveKingCheck(int index, int xdev, int ydev, char checkFor){
	if (tsqr(index,xdev,ydev)->has_piece==1 && isEnemy(index,xdev,ydev) && tsqr(index,xdev,ydev)->piece_type==checkFor){
		return (1);
	}	else{
		return (0);
	}
}

/* given an index from the Squares array, an original color, and a transform, keep moving in that direction until you can't anymore */
/* mark the return array as 1 if it finds a piece of the opposite color */
void ofApp::recurs(int index, int originalColor, int xdev, int ydev){
	if (takeable(index,originalColor,xdev,ydev)==1){
		returnArray[transformBy(index,xdev,ydev)] = 1;
	}
	if (tsqr(index,xdev,ydev)->has_piece==0){
		recurs(transformBy(index,xdev,ydev),originalColor, xdev,ydev);
	}
}

/* given an index from the Squares array, an original color, and a transform, move in that direction once */
void ofApp::nonrecurs(int index, int originalColor, int xdev, int ydev){
	if (takeable(index,originalColor,xdev,ydev)==1){
		returnArray[transformBy(index,xdev,ydev)] = 1;
	}
}

/* remove all squares from the selection array (returnArray), and mark all items in Squares array as not selected */
/* after this, highlight() is null, and this is is undone by getPossibleMoves() */
void ofApp::clearSelection(){
	for (int i =0; i<64; i++){
		returnArray[i] = 0;
		Squares[i].selected = false;
	}
}

/* 	Remove the item at index from Squares array, move to the selected square.
	Also includes some castling handling/error checking */
void ofApp::moveTo(int index, int x, int y){
	/* castling handling, if castling, move the rooks too. */
	/* kingside white */
	if (sqr(index)->piece_type=='k' && x==6 && index==4){
		wk_flag=whr_flag=1;
		moveTo(7,5,0);
	}
	/* queenside white */
	if (sqr(index)->piece_type=='k' && x==2 && index==4){
		wk_flag=war_flag=1;
		moveTo(0,3,0);
	}
	/* kingside black */
	if (sqr(index)->piece_type=='k' && x==6 && index==60){
		bk_flag=bhr_flag=1;
		moveTo(63,5,7);
	}
	/* queenside black */
	if (sqr(index)->piece_type=='k' && x==2 && index==60){
		bk_flag=bar_flag=1;
		moveTo(56,3,7);
	}
	if (sqr(index)->piece_type=='k' && sqr(index)->piece_color==1){wk_flag=1;}
	if (sqr(index)->piece_type=='k' && sqr(index)->piece_color==0){bk_flag=1;}
	if (sqr(index)->piece_type=='r' && sqr(index)->piece_color==1 && sqr(index)->row==0){war_flag=1;}
	if (sqr(index)->piece_type=='r' && sqr(index)->piece_color==1 && sqr(index)->row==7){whr_flag=1;}
	if (sqr(index)->piece_type=='r' && sqr(index)->piece_color==0 && sqr(index)->row==0){bar_flag=1;}
	if (sqr(index)->piece_type=='r' && sqr(index)->piece_color==0 && sqr(index)->row==7){bhr_flag=1;}

	/* functionality code */
	sqr(getSelf(x,y))->has_piece = 1;
	sqr(getSelf(x,y))->piece_type= Squares[index].piece_type;
	sqr(getSelf(x,y))->piece_color= Squares[index].piece_color;
	Squares[index].has_piece = false;
	Squares[index].piece_type = ' ';

	/* en pipi, holy hell */
	/* If the square behind the en-passant square if full of opp. color pawn (en passant happpend), remove the taken pawn */
	if (sqr(getSelf(ep_flag,2))->piece_type=='p' && sqr(getSelf(ep_flag,2))->piece_color==Squares[index].piece_color){
		sqr(getSelf(ep_flag,3))->piece_type=' ';
		sqr(getSelf(ep_flag,3))->has_piece=0;
	}
	if (sqr(getSelf(ep_flag,5))->piece_type=='p' && sqr(getSelf(ep_flag,5))->piece_color==Squares[index].piece_color){
		sqr(getSelf(ep_flag,4))->piece_type=' ';
		sqr(getSelf(ep_flag,4))->has_piece=0;
	}
	ep_flag=-2;
	/* set ep_flag if double pawn move */
	if (y==3 && index>7 && index<16){	// double pawn move white
		if ((sqr(getSelf(x+1,y))->piece_color==0)&&(sqr(getSelf(x+1,y))->piece_type=='p')){	ep_flag=x;	}
		if ((sqr(getSelf(x-1,y))->piece_color==0)&&(sqr(getSelf(x-1,y))->piece_type=='p')){	ep_flag=x;	}
	}
	if (y==4 && index>47 && index<56){	// double pawn move black
		if ((sqr(getSelf(x+1,y))->piece_color==1)&&(sqr(getSelf(x+1,y))->piece_type=='p')){	ep_flag=x;	}
		if ((sqr(getSelf(x-1,y))->piece_color==1)&&(sqr(getSelf(x-1,y))->piece_type=='p')){	ep_flag=x;	}
	}

	/* queening */
	if (sqr(getSelf(x,y))->piece_type=='p' && (y==7||y==0)) {	sqr(getSelf(x,y))->piece_type='q';	}
}

/* takes an int 1 if white, 0 if black, returns 1 if yes, 0 if no */
/* example, inCheck(1) will return 1 if the white king is in check */
int ofApp::inCheck(int side){
	int returnInt=0;
	for (int i=0; i<64; i++){
		if (sqr(i)->piece_color==side && sqr(i)->piece_type=='k'){
			returnInt+=recursiveKingCheck(i,side,1,1,'b');	// Bishop
			returnInt+=recursiveKingCheck(i,side,1,-1,'b');
			returnInt+=recursiveKingCheck(i,side,-1,-1,'b');
			returnInt+=recursiveKingCheck(i,side,-1,1,'b');
			returnInt+=recursiveKingCheck(i,side,1,1,'q');	// Queen (diagonal)
			returnInt+=recursiveKingCheck(i,side,1,-1,'q');
			returnInt+=recursiveKingCheck(i,side,-1,-1,'q');
			returnInt+=recursiveKingCheck(i,side,-1,1,'q');
			returnInt+=recursiveKingCheck(i,side,0,1,'r');	// Rook
			returnInt+=recursiveKingCheck(i,side,1,0,'r');
			returnInt+=recursiveKingCheck(i,side,0,-1,'r');
			returnInt+=recursiveKingCheck(i,side,-1,0,'r');
			returnInt+=recursiveKingCheck(i,side,0,1,'q');	// Queen (linear)
			returnInt+=recursiveKingCheck(i,side,1,0,'q');
			returnInt+=recursiveKingCheck(i,side,0,-1,'q');
			returnInt+=recursiveKingCheck(i,side,-1,0,'q');
			returnInt+=nonrecursiveKingCheck(i,2,1,'n');	// Knight
			returnInt+=nonrecursiveKingCheck(i,1,2,'n');
			returnInt+=nonrecursiveKingCheck(i,-1,2,'n');
			returnInt+=nonrecursiveKingCheck(i,-2,1,'n');
			returnInt+=nonrecursiveKingCheck(i,-2,-1,'n');
			returnInt+=nonrecursiveKingCheck(i,-1,-2,'n');
			returnInt+=nonrecursiveKingCheck(i,1,-2,'n');
			returnInt+=nonrecursiveKingCheck(i,2,-1,'n');
			if (side==1){
				returnInt+=nonrecursiveKingCheck(i,1,1,'p');	// Pawn (white king)
				returnInt+=nonrecursiveKingCheck(i,-1,1,'p');
			} else {
				returnInt+=nonrecursiveKingCheck(i,1,-1,'p');	// Pawn (black king)
				returnInt+=nonrecursiveKingCheck(i,-1,-1,'p');
			}
			returnInt+=nonrecursiveKingCheck(i,1,0,'k');	// King (yes you have to check if the king is touching the king)
			returnInt+=nonrecursiveKingCheck(i,1,1,'k');
			returnInt+=nonrecursiveKingCheck(i,0,1,'k');
			returnInt+=nonrecursiveKingCheck(i,-1,1,'k');
			returnInt+=nonrecursiveKingCheck(i,-1,0,'k');
			returnInt+=nonrecursiveKingCheck(i,-1,-1,'k');
			returnInt+=nonrecursiveKingCheck(i,0,-1,'k');
			returnInt+=nonrecursiveKingCheck(i,1,-1,'k');
		}
	}
	return(returnInt>0);
}

/* takes color, returns 1 if mate */
int ofApp::checkmate(int side){
	fillMoveset(side);	
	return(getNextEmptyMove()==0);
}

/* ----------------------------------	GAMEPLAY FUNCTIONS		----------------------------- */

/*	return the next index in the Moveset array that is empty for use */
int ofApp::getNextEmptyMove(){
	for (int i=0;i<200;i++){
		if (Moveset[i].is_empty==1){
			return (i);
			break;
		}
	}
	return(-1);
}

/*	given a side (as an int), fill piecesCanMove[] with ones(1) where there are pieces that can move */
void ofApp::fillPCMBuffer(int side){
	int flag=0;
	for (int i=0; i<64; i++){
		flag=0;
		if (sqr(i)->has_piece==1 && sqr(i)->piece_color==side){
			clearSelection();
			getPossibleMoves(i);
			for (int j=0; j<64; j++){
				if (returnArray[j]==1){
					flag=1;	
					break;
				}
			}
			if (flag){
				piecesCanMove[i]=1;
			}
		}
	}
	clearSelection();
}

/*	clear pcm buffer, selection, moveset, then fill moveset
	at the end, clear selection and moveset */
void ofApp::fillMoveset(int side){
	for (int i=0; i<64; i++){	storageBuffer1[i] = returnArray[i];	}
	clearSelection();
	clearPSBuffer();
	clearMoveset();
	fillPCMBuffer(side);
	for (int i=0; i<64; i++){
		if (piecesCanMove[i]==1){
			getPossibleMoves(i);
			for (int j=0; j<64; j++){
				if (returnArray[j]==1){
					Moveset[getNextEmptyMove()].start_square=*sqr(i);
					Moveset[getNextEmptyMove()].end_square=*sqr(j);
					Moveset[getNextEmptyMove()].is_empty=0;
				}
			}
			clearSelection();
		}
	}
	clearPSBuffer();
	for (int i=0; i<64; i++){	returnArray[i] = storageBuffer1[i];	}
}

/*	reset the buffer back to all 0's */
void ofApp::clearPSBuffer(){
	for (int i=0;i<64;i++){
		piecesCanMove[i]=0;
	}
}

/* 	reset the moveset buffer back to errorSquare	*/
void ofApp::clearMoveset(){
	for (int i=0; i<200; i++){
		Moveset[i].start_square = errorSquare;
		Moveset[i].end_square = errorSquare;
		Moveset[i].is_empty = 1;
	}
}

/*	This doesn't need to be used... Candidate for deletion
//	grab a random index from the PSBuffer, and perform GetPossibleMoves on it. Returns -1 if there are none to choose from (which shouldn't happen)
void ofApp::pickRandFromPSBuffer(){
	int randomIndex=-1;
	int count=0;
	for (int i=0;i<64;i++){
		if (piecesCanMove[i]==1){
			count++;
			if ((int)ofRandom(count)==0){
				randomIndex=i;
			}
		}
	}
	clearSelection();
	// std::cout << randomIndex << endl;
	// std::cout << sqr(randomIndex)->column << " " << sqr(randomIndex)->row << endl;
	moveablePiece = randomIndex;
	getPossibleMoves(randomIndex);
}

//	first clear the psbuffer, then fill the psbuffer given the side, then run the normal pick random code
void ofApp::pickRandFromPSBuffer(int side){
	clearPSBuffer();
	fillPCMBuffer(side);
	pickRandFromPSBuffer();
}
*/

/* grab a random move from the moveset, return that index (as an int) */
int ofApp::pickRandFromMoveset(){
	int randomIndex=-1;
	int count=0;
	for (int i=0;i<getNextEmptyMove();i++){
		count++;
		if ((int)ofRandom(count)==0){
			randomIndex=i;
		}
	}
	return (randomIndex);
}

/* console/debugging function. Prints the contents of the Moveset array to the screen in (x,y) pairs */
void ofApp::printMoveset(){
	fillMoveset(whiteToMove);
	for (int i=0;i<200;i++){
		if (Moveset[i].is_empty==0){
			std::cout << Moveset[i].start_square.piece_type << " @ " << Moveset[i].start_square.column << "," << Moveset[i].start_square.row << " -> " << Moveset[i].end_square.column << "," << Moveset[i].end_square.row << endl;
		} else {break;}
	}
	std::cout << getNextEmptyMove() << endl;
}

/* do a random game with moveDelay time between moves, stop on checkmate */
void ofApp::doRandomMove(){
	std::cout<<"nextmove"<<endl;
	fillMoveset(whiteToMove);
	int move = pickRandFromMoveset();
	moveablePiece = getSelf(Moveset[move].start_square.column,Moveset[move].start_square.row);
	std::cout << moveablePiece << " " << getSelf(Moveset[move].end_square.column,Moveset[move].end_square.row) << endl;
	moveTo(moveablePiece, Moveset[move].end_square.column, Moveset[move].end_square.row);
	moveablePiece=-1;
	whiteToMove=!whiteToMove;
	clearSelection();
}

/*	----------------------------------	SQUARE LOOKUP FUNCTIONS	----------------------------- */

/* return index from x and y */
int ofApp::getSelf(int x, int y){
	if (x<0 || y<0 || x>7 || y>7){	return(-1);	}
	return (x + y*8);
}

/* transform the index by the given amount. Return -1 if it's not valid, otherwise the index */
int ofApp::transformBy(int index, int xdev, int ydev){
	if (ofWrap(index,0,8)+xdev > 7 || ofWrap(index,0,8)+xdev < 0){
		return (-1);
	}
	if ((index/8) + ydev > 7 || (index/8) + ydev < 0){
		return (-1);
	}
	return(index+xdev+(ydev*8));
}

/* returns true if the transform square is populated with an enemy piece */
/* this is not a pretty bit, but it works! */
bool ofApp::isEnemy(int index, int xdev, int ydev){
	if (sqr(index)->piece_color == 1){
		if (tsqr(index,xdev,ydev)->has_piece==1 && tsqr(index,xdev,ydev)->piece_color==0){
			return (true);
		} else {return (false);}
	} else {
		if (tsqr(index,xdev,ydev)->has_piece==1 && tsqr(index,xdev,ydev)->piece_color==1){
			return (true);
		} else {return (false);}
	}
}

/* returns true if the square is empty or occupied by an enemy piece, eg. a non-pawn can take there */
bool ofApp::takeable(int index, int xdev, int ydev){
	return (tsqr(index,xdev,ydev)->has_piece==0 || isEnemy(index,xdev,ydev)==true);
}

bool ofApp::takeable(int index, int originalColor, int xdev, int ydev){
	// return (tsqr(index,xdev,ydev)->has_piece==0 || tsqr(index,xdev,ydev)->piece_color+originalColor==0);
	if (originalColor==1 && tsqr(index,xdev,ydev)->piece_color==0){
		return (1);
	} else if (originalColor==0 && tsqr(index,xdev,ydev)->piece_color==1){
		return (1);
	} else if (tsqr(index,xdev,ydev)->has_piece==0){
		return (1);
	} return(0);
}

/* return the address of a specific square */
Square* ofApp::sqr(int index){
	if (index==-1) {	return (&errorSquare);	}
	else {	return (&Squares[index]);	}
}

/* syntactic candy, get reference to the transform of a square */
Square* ofApp::tsqr(int index, int xdev, int ydev){
	return (sqr(transformBy(index,xdev,ydev)));
}


/*	-------------- OFAPPS FUNCTIONS --------------------- */
//--------------------------------------------------------------
void ofApp::setup(){
	ofSetBackgroundAuto(false);
	boardBottomLeft.set(80,600);
	nextRight.set(squareSize + squareSpacing, 0);
	nextAbove.set(0, -squareSize - squareSpacing); /* minus because y is flipped */

	ofBackground(128,128,128);
	setupBoard();
	loadImages();

	updateState();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	updateState();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key){
		case 'r':
			setupBoard();
			clearSelection();
			break;
		case ' ':
			clearSelection();
			break;
		case 't':	//random
			std::cout << "moves for " << whiteToMove << endl;
			// printMoveset();
			fillMoveset(whiteToMove);
			// pickRandFromPSBuffer(whiteToMove);
			break;
		case 'b': // custom breakpoint
			// std::cout << "breakpoint unset" << endl;
			std::cout << "Registered B" << endl;
			std::cout << "white " << inCheck(1) << " " << checkmate(1) << endl;
			std::cout << "black " << inCheck(0) << " " << checkmate(0) << endl;
			break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	int clickedSquare = getClickedSquare(x,y);	// clickedSquare is an index
	if (sqr(clickedSquare)->selected==1){	// if you click on a selected square
		moveTo(moveablePiece,sqr(clickedSquare)->column,sqr(clickedSquare)->row);
		moveablePiece = -1;
		whiteToMove = !whiteToMove;
		// inCheck(whiteToMove);
		clearSelection();
	} else {
		if (sqr(clickedSquare)->has_piece){
			if ((sqr(clickedSquare)->piece_color==1 && whiteToMove==true) || (sqr(clickedSquare)->piece_color==0 && whiteToMove==false)){
				moveablePiece = clickedSquare;
				clearSelection();
				getPossibleMoves(clickedSquare);	// updates returnArray
				highlight();						// updates Squares array
			}
		} else {
			clearSelection();
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}


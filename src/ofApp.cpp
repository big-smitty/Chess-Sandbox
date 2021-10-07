#include "ofApp.h"
   

/* --------- USER FUNCTIONS ----------- */
/* takes coordinates of a mouse click, returns index of Squares array clicked, if outside bounds returns -1 */
int ofApp::getClickedSquare(int x, int y){
	int leftBound 		= Playarea.boardBottomLeft.x;
	int rightBound 		= (Playarea.boardBottomLeft+Playarea.nextRight*8).x - Playarea.squareSpacing;
	int bottomBound		= Playarea.boardBottomLeft.y+Playarea.squareSize;
	int topBound 		= (Playarea.boardBottomLeft+Playarea.nextAbove*7).y;
	/* not in square space, return -1 */
	if (x<leftBound || x>rightBound || y>bottomBound || y<topBound)	{	return (-1);	}
	/* otherwise return index in Squares array*/
	int tempx, tempy;
	for (tempx = 0; tempx<8; tempx++){
		if (x-(tempx+1)*Playarea.nextRight.x < leftBound){	break;	}
	}
	for (tempy = 0; tempy<8; tempy++){
		if (y-(tempy+1)*Playarea.nextAbove.y > bottomBound){	break;	}
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

/* place the pictures of pieces where they need to be */
void ofApp::placePieces(){
	for (int i=0; i<64; i++){
		if (Playarea.Squares[i].piece_type != ' '){
			if (Playarea.Squares[i].piece_color == 1){	// white piece
				ofSetColor(230,230,230);
				switch (Playarea.Squares[i].piece_type){
					case 'p':
						// std::cout << "pawned" << endl;
						whitePawn.draw((Playarea.boardBottomLeft+Playarea.nextRight*Playarea.Squares[i].column).x,(Playarea.boardBottomLeft+Playarea.nextAbove*Playarea.Squares[i].row).y,Playarea.squareSize,Playarea.squareSize);
						break;
					case 'n':
						whiteKnight.draw((Playarea.boardBottomLeft+Playarea.nextRight*Playarea.Squares[i].column).x,(Playarea.boardBottomLeft+Playarea.nextAbove*Playarea.Squares[i].row).y,Playarea.squareSize,Playarea.squareSize);
						break;
					case 'b':
						whiteBishop.draw((Playarea.boardBottomLeft+Playarea.nextRight*Playarea.Squares[i].column).x,(Playarea.boardBottomLeft+Playarea.nextAbove*Playarea.Squares[i].row).y,Playarea.squareSize,Playarea.squareSize);
						break;
					case 'r':
						whiteRook.draw((Playarea.boardBottomLeft+Playarea.nextRight*Playarea.Squares[i].column).x,(Playarea.boardBottomLeft+Playarea.nextAbove*Playarea.Squares[i].row).y,Playarea.squareSize,Playarea.squareSize);
						break;
					case 'q':
						whiteQueen.draw((Playarea.boardBottomLeft+Playarea.nextRight*Playarea.Squares[i].column).x,(Playarea.boardBottomLeft+Playarea.nextAbove*Playarea.Squares[i].row).y,Playarea.squareSize,Playarea.squareSize);
						break;
					case 'k':
						whiteKing.draw((Playarea.boardBottomLeft+Playarea.nextRight*Playarea.Squares[i].column).x,(Playarea.boardBottomLeft+Playarea.nextAbove*Playarea.Squares[i].row).y,Playarea.squareSize,Playarea.squareSize);
						break;
				}
			} else {
				ofSetColor(50,50,50);
				switch (Playarea.Squares[i].piece_type){
					case 'p':
						// std::cout << "pawned" << endl;
						blackPawn.draw((Playarea.boardBottomLeft+Playarea.nextRight*Playarea.Squares[i].column).x,(Playarea.boardBottomLeft+Playarea.nextAbove*Playarea.Squares[i].row).y,Playarea.squareSize,Playarea.squareSize);
						break;
					case 'n':
						blackKnight.draw((Playarea.boardBottomLeft+Playarea.nextRight*Playarea.Squares[i].column).x,(Playarea.boardBottomLeft+Playarea.nextAbove*Playarea.Squares[i].row).y,Playarea.squareSize,Playarea.squareSize);
						break;
					case 'b':
						blackBishop.draw((Playarea.boardBottomLeft+Playarea.nextRight*Playarea.Squares[i].column).x,(Playarea.boardBottomLeft+Playarea.nextAbove*Playarea.Squares[i].row).y,Playarea.squareSize,Playarea.squareSize);
						break;
					case 'r':
						blackRook.draw((Playarea.boardBottomLeft+Playarea.nextRight*Playarea.Squares[i].column).x,(Playarea.boardBottomLeft+Playarea.nextAbove*Playarea.Squares[i].row).y,Playarea.squareSize,Playarea.squareSize);
						break;
					case 'q':
						blackQueen.draw((Playarea.boardBottomLeft+Playarea.nextRight*Playarea.Squares[i].column).x,(Playarea.boardBottomLeft+Playarea.nextAbove*Playarea.Squares[i].row).y,Playarea.squareSize,Playarea.squareSize);
						break;
					case 'k':
						blackKing.draw((Playarea.boardBottomLeft+Playarea.nextRight*Playarea.Squares[i].column).x,(Playarea.boardBottomLeft+Playarea.nextAbove*Playarea.Squares[i].row).y,Playarea.squareSize,Playarea.squareSize);
						break;
				}
			}
		}
	}
}

/*	-------------- OFAPPS FUNCTIONS --------------------- */
//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(128,128,128);
	loadImages();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	Playarea.drawSquares();
	placePieces();
	Playarea.placeMoveIndicator();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key){
		case 'r':
			Playarea.reset();
			break;
		case ' ':
			break;
		case 't':	//random
			std::cout << "breakpoint catch " << endl;
			std::cout << Playarea.moveablePiece << endl;
			std::cout << Playarea.Squares[Playarea.moveablePiece].piece_type << endl;
			break;
		case 'b': // custom breakpoint
			std::cout << "b catch" << endl;
			// Playarea.Squares[0].setPiece(Playarea.Squares[1].piece_type,Playarea.Squares[1].piece_color);
			// Playarea.Squares[0].empty();
			Playarea.moveTo(10,21);
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
	int clickedSquare = getClickedSquare(x,y);
	if (Playarea.Squares[clickedSquare].selected){
		std::cout << Playarea.moveablePiece << " " << clickedSquare << endl;
		Playarea.moveTo(Playarea.moveablePiece, clickedSquare);
		Playarea.moveablePiece = -1;
		Playarea.whiteToMove = !Playarea.whiteToMove;
		Playarea.clearSelection();
		Playarea.resetSquaresColor();
	} else {
		if (Playarea.hasPiece(clickedSquare)){
			if ((Playarea.Squares[clickedSquare].piece_color==1 && Playarea.whiteToMove==1) || (Playarea.Squares[clickedSquare].piece_color==0 && Playarea.whiteToMove==0)){
				Playarea.moveablePiece = clickedSquare;
				Playarea.clearSelection();
				Playarea.resetSquaresColor();
				long long piece_moveset = Playarea.getPossibleMoves(clickedSquare);
				Playarea.colorSquares(piece_moveset, 'g');
				Playarea.selectSquares(piece_moveset);
			}
		} else {
			Playarea.clearSelection();
			Playarea.resetSquaresColor();
		}
	}

	// std::cout << getClickedSquare(x,y) << endl;
	// Playarea.colorSquares(Playarea.getPossibleMoves(getClickedSquare(x,y)),'g');v
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


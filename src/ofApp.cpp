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
	std::cout << getClickedSquare(x,y) << endl;
	// std::cout << Playarea.getPossibleMoves(getClickedSquare(x,y)) << endl;
	// Playarea.colorSquares(Playarea.getPossibleMoves(getClickedSquare(x,y)),'g');
	std::cout << Playarea.takeable(getClickedSquare(x,y),1,1,1) << endl;
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


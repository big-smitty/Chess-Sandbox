#pragma once

#include "ofMain.h"
#include "Board.h"
#include "Square.h"

class ofApp : public ofBaseApp{

	public:
		int getClickedSquare(int x, int y);	/* x and y are screen coordinates, return index */
		void loadImages();
		void placePieces();


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

		Board Playarea;
};


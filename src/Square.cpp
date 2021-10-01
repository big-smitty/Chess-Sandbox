#include "Square.h"
Square::Square(){
	}

void Square::setup(int input_index){

	row 	= input_index/8;
	column 	= input_index%8;
	index 	= input_index;
	if ((row%2==0 && column%2==0) || (row%2==1 && column%2==1)){
		color.set(50,50,50);
		squareColor = 'b';
	} else {
		color.set(230,230,230);
		squareColor = 'w';
	}
}

void Square::resetPiece(){
	if (row>1 && row<6){
		piece_type 	= ' ';
		piece_color = -1;
	} else if (row==1 || row==6){
		piece_type	= 'p';
	} else if (column==0 || column==7){
		piece_type 	= 'r';
	} else if (column==1 || column==6){
		piece_type 	= 'n';
	} else if (column==2 || column==5){
		piece_type 	= 'b';
	} else if (column==3){
		piece_type 	= 'q';
	} else if (column==4){
		piece_type 	= 'k';
	} else {
		piece_type 	= '!';
	}

	if (row<2) {piece_color = 1;}
	if (row>5) {piece_color = 0;}
}

void Square::setPiece(char input_type, int input_color){
	piece_type 	= input_type;
	piece_color	= input_color;
}
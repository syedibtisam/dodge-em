//============================================================================
// Name        : game.cpp
// Author      : Hassan Mustafa
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Dodge 'Em...
//============================================================================

#ifndef DODGE_CPP_
#define DODGE_CPP_
#include "util.h"
#include <iostream>
#include<string>
#include<cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;
int ux=350,uy=40;
int xx=440,yy=40;
int points[1000][1000]={};
int score=0;
int screen=0;
// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */

void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}


/*
 * Main Canvas drawing function.
 * */
//Board *b;
void GameDisplay()/**/{
	
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	if(screen==0){
		DrawString( 100, 800, "1) Start a new game  (Press P to start)", colors[MISTY_ROSE]);
		//DrawString( 50, 800, "2) See high-scores", colors[MISTY_ROSE]);
		//DrawString( 50, 800, "3) Help", colors[MISTY_ROSE]);
		DrawString( 100, 700, "2) Exit              (Press Esc to Exit)", colors[MISTY_ROSE]);
	}
	else if(screen == 1){
		DrawString( 100, 800, "You have lost all of your lives", colors[MISTY_ROSE]);
		DrawString( 100, 700, "For Main Menu Press R ", colors[MISTY_ROSE]);
	}
	else{
	// calling some functions from util.cpp file to help students
	//InitalizeBoard(60, 60);
	//Square at 400,20 position
	//DrawSquare( 400 , 20 ,40,colors[RED]); 
	//Square at 250,250 position
	//DrawSquare( 250 , 250 ,20,colors[GREEN]); 
	//Display Score
	//DrawString( 50, 800, "Score=0", colors[MISTY_ROSE]);
	//Triangle at 300, 450 position
	//DrawTriangle( 300, 450 , 340, 450 , 320 , 490, colors[MISTY_ROSE] ); 
	// Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)
	//Circle at 50, 670 position
	//DrawCircle(50,670,10,colors[RED]);
	//Line from 550,50 to 550,480 with width 10
	//DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
	//DrawLine( 550 , 50 ,  550 , 480 , 10 , colors[MISTY_ROSE] );	
			
	// Drawing user car
	static float width = 14; 
	static float height = 10;
	static float* color = colors[BLUE_VIOLET]; 
	static float radius = 2.0;
	DrawRoundRect(ux,uy,width,height,color,radius); // bottom left tyre
	DrawRoundRect(ux+width*3,uy,width,height,color,radius); // bottom right tyre
	DrawRoundRect(ux+width*3,uy+height*4,width,height,color,radius); // top right tyre
	DrawRoundRect(ux,uy+height*4,width,height,color,radius); // top left tyre
	DrawRoundRect(ux, uy+height*2, width, height, color, radius/2); // body left rect
	DrawRoundRect(ux+width, uy+height, width*2, height*3, color, radius/2); // body center rect
	DrawRoundRect(ux+width*3, uy+height*2, width, height, color, radius/2); // body right rect

	//Drawing opponent car
	static float* color1 = colors[RED]; 
	DrawRoundRect(xx,yy,width,height,color1,radius); // bottom left tyre
	DrawRoundRect(xx+width*3,yy,width,height,color1,radius); // bottom right tyre
	DrawRoundRect(xx+width*3,yy+height*4,width,height,color1,radius); // top right tyre
	DrawRoundRect(xx,yy+height*4,width,height,color1,radius); // top left tyre
	DrawRoundRect(xx, yy+height*2, width, height, color1, radius/2); // body left rect
	DrawRoundRect(xx+width, yy+height, width*2, height*3, color1, radius/2); // body center rect
	DrawRoundRect(xx+width*3, yy+height*2, width, height, color1, radius/2); // body right rect

	// Drawing Arena
	int gap_turn = 60;
	int sx = 20;
	int sy = 10;
	int swidth = 800/2 - gap_turn/2; // half width
	int sheight = 10;
	float *scolor = colors[BROWN];
	int a=20,b=30,c=50;
	DrawRectangle(sx, sy, swidth-a, sheight, scolor); // bottom left
	DrawRectangle(sx + swidth + gap_turn+b, sy, swidth-b, sheight, scolor); // bottom right
	DrawRectangle(sx+swidth*2+gap_turn, sy+sheight, sheight*2, swidth-c, scolor); // right down
	DrawRectangle(sx+swidth*2+gap_turn, sy+sheight+swidth+gap_turn+c, sheight*2, swidth-c, scolor); // right up
	DrawRectangle(sx + swidth + gap_turn+b, sy+810, swidth-b, sheight, scolor); // top right
	DrawRectangle(sx, sy+810, swidth-a, sheight, scolor); // top left
	DrawRectangle(sx-sheight*2, sy+sheight+swidth+gap_turn+c, sheight*2, swidth-c, scolor); // left up
	DrawRectangle(sx-sheight*2, sy+sheight, sheight*2, swidth-c, scolor); // left down
	//1
	DrawRectangle(sx+90, sy+90, swidth-a-90, sheight, scolor); // bottom left
	DrawRectangle(sx + swidth + gap_turn+b, sy+90, swidth-b-90, sheight, scolor); // bottom right
	DrawRectangle(sx+swidth*2+gap_turn-90, sy+sheight+80, sheight*2, swidth-c-80, scolor); // right down
	DrawRectangle(sx+swidth*2+gap_turn-90, sy+sheight+swidth+gap_turn+c, sheight*2, swidth-c-80, scolor); // right up
	DrawRectangle(sx + swidth + gap_turn+b, sy+810-90, swidth-b-90, sheight, scolor); // top right
	DrawRectangle(sx+90, sy+810-90, swidth-a-90, sheight, scolor); // top left
	DrawRectangle(sx-sheight*2+90, sy+sheight+swidth+gap_turn+c, sheight*2, swidth-c-80, scolor); // left up
	DrawRectangle(sx-sheight*2+90, sy+sheight+80, sheight*2, swidth-c-80, scolor); // left down
	//2
	int d=90*2;
	DrawRectangle(sx+d, sy+d, swidth-a-d, sheight, scolor); // bottom left
	DrawRectangle(sx + swidth + gap_turn+b, sy+d, swidth-b-d, sheight, scolor); // bottom right
	DrawRectangle(sx+swidth*2+gap_turn-d, sy+sheight+d-10, sheight*2, swidth-c-d+10, scolor); // right down
	DrawRectangle(sx+swidth*2+gap_turn-d, sy+sheight+swidth+gap_turn+c, sheight*2, swidth-c-d+10, scolor); // right up
	DrawRectangle(sx + swidth + gap_turn+b, sy+810-d, swidth-b-d, sheight, scolor); // top right
	DrawRectangle(sx+d, sy+810-d, swidth-a-d, sheight, scolor); // top left
	DrawRectangle(sx-sheight*2+d, sy+sheight+swidth+gap_turn+c, sheight*2, swidth-c-d+10, scolor); // left up
	DrawRectangle(sx-sheight*2+d, sy+sheight+d-10, sheight*2, swidth-c-d+10, scolor); // left down
	//3
	d=90*3;
	DrawRectangle(sx+d, sy+d, swidth-a-d, sheight, scolor); // bottom left
	DrawRectangle(sx + swidth + gap_turn+b, sy+d, swidth-b-d, sheight, scolor); // bottom right
	DrawRectangle(sx+swidth*2+gap_turn-d, sy+sheight+d-10, sheight*2, swidth-c-d+10, scolor); // right down
	DrawRectangle(sx+swidth*2+gap_turn-d, sy+sheight+swidth+gap_turn+c, sheight*2, swidth-c-d+10, scolor); // right up
	DrawRectangle(sx + swidth + gap_turn+b, sy+810-d, swidth-b-d, sheight, scolor); // top right
	DrawRectangle(sx+d, sy+810-d, swidth-a-d, sheight, scolor); // top left
	DrawRectangle(sx-sheight*2+d, sy+sheight+swidth+gap_turn+c, sheight*2, swidth-c-d+10, scolor); // left up
	DrawRectangle(sx-sheight*2+d, sy+sheight+d-10, sheight*2, swidth-c-d+10, scolor); // left down
	
	cout<<" User axis = "<<ux<<","<<uy<<" Opponent axis = "<<xx<<","<<yy<<endl;

	//user car funtinons
	
	
	//Printing dots
	
	static bool printing=true;			
	if(printing==true){
	for(int i=30;i<=750;i+=90){
		if(i==390)
			continue;
		for(int j=40;j<=760;j+=90){
			if(j==400)
				continue;
		points[i][j]=20;
		DrawSquare( i , j ,20,colors[RED]);
		}
	}
	}
	if(printing==false){
		for(int i=30;i<=750;i+=90){
			if(i==390)
				continue;
			for(int j=40;j<=760;j+=90){
				if(j==400)
					continue;
			if(points[ux][uy]==20){
				points[ux][uy]=1;
				score++;
			}
			if(points[i][j]==20)
				DrawSquare( i , j ,20,colors[RED]);
			}
		}
	}	
	printing=false;
	
	static bool x_increase=true,y_increase=false,x_incr=true,y_incr=false;
	static float sign_incr=1,si_in=1;
	static int lives=3;
	string score1=Num2Str(score);		
	DrawString( 700, 900, "Score = "+score1, colors[MISTY_ROSE]);
	string lives1=Num2Str(lives);
	DrawString( 80, 900, "Lives = "+lives1, colors[MISTY_ROSE]);
	
	//opponent car turnings
		if(
			(xx==750&&yy==40)			//Taking turns at the corner
			||					//Bottom rights
			(xx==660&&yy==130)
			||
			(xx==570&&yy==220)
			||
			(xx==480&&yy==310)
		){
			x_increase=false;
			y_increase=true;
		}
		else if(
			(xx==750&&yy==760)			//Top rights
			||
			(xx==660&&yy==670)
			||
			(xx==570&&yy==580)
			||
			(xx==480&&yy==490)
			){
			x_increase=true;
			y_increase=false;
			sign_incr=sign_incr*-1;
		}
		else if(
			(xx==30&&yy==760)			//Top lefts
			||
			(xx==120&&yy==670)
			||
			(xx==210&&yy==580)
			||
			(xx==300&&yy==490)
			){
			x_increase=false;
			y_increase=true;
		}
		else if(
			(xx==30&&yy==40)		// bottom lefts
			||
			(xx==120&&yy==130)
			||
			(xx==210&&yy==220)
			||
			(xx==300&&yy==310)
			){
			x_increase=true;
			y_increase=false;
			sign_incr=sign_incr*-1;
		}
	
	//user car turning
		if(
			(ux==750&&uy==40)			//Taking turns at the corner
			||					//Bottom rights
			(ux==660&&uy==130)
			||
			(ux==570&&uy==220)
			||
			(ux==480&&uy==310)
		){
			y_incr=false;
			x_incr=true;
		}
		else if(
			(ux==750&&uy==760)			//Top rights
			||
			(ux==660&&uy==670)
			||
			(ux==570&&uy==580)
			||
			(ux==480&&uy==490)
			){
			y_incr=true;
			x_incr=false;
			si_in=si_in*-1;
		}
		else if(
			(ux==30&&uy==760)			//Top lefts
			||
			(ux==120&&uy==670)
			||
			(ux==210&&uy==580)
			||
			(ux==300&&uy==490)
			){
			y_incr=false;
			x_incr=true;
		}
		else if(
			(ux==30&&uy==40)			// bottom lefts
			||
			(ux==120&&uy==130)
			||
			(ux==210&&uy==220)
			||
			(ux==300&&uy==310)
			){
			
			si_in=si_in*-1;
			y_incr=true;
			x_incr=false;
		}
	if(x_increase==true)				//increments in the opponent car
		xx=xx+10*sign_incr;
	if(y_increase==true)
		yy=yy+10*sign_incr;
	if(x_incr==true)				//increments in the user car
		ux=ux-10*si_in;
	if(y_incr==true)
		uy=uy-10*si_in;
	
	if(xx>350&&xx<=440){  // Checking top and bottom gaps
		if(ux==300 || uy==490){	// Opponent car turns // Going inside
			if(yy==570){
				yy-=90;
				xx-=90;				
			}
			else if(yy==220){
				yy+=90;
				xx+=90;
			}
		}
		else if(ux==210 || uy==580){
			if(yy==670){
				yy-=90;
				xx-=90;
			}
			else if(yy==130){
				yy+=90;
				xx+=90;
			}
		}
		else if(ux==120 || uy==670){
			if(yy==760){
				yy-=90;
				xx-=90;
			}
			else if(yy==40){
				yy+=90;
				xx+=90;
			}
		}
		else if(ux==30 || uy==760){	// Opponent car turns // Going outside
			if(yy==670){		//Top turn
				yy+=90;
				xx-=90;
			}
			else if(yy==130){
				yy-=90;
				xx+=90;
			}
		}
		else if(ux==570 || uy==220){
			if(yy==490){
				yy+=90;
				xx-=90;
			}
			else if(yy==310){
				yy-=90;
				xx+=90;
			}
		}
		else if(ux==660 || uy==130){
			if(yy==580){
				yy+=90;
				xx-=90;
			}
			else if(yy==220){
				yy-=90;
				xx+=90;
			}
		}
	}
	if((ux>=xx&&ux<=xx+30) && (uy>=yy&&uy<=yy+30)){
		cout<<xx<<" "<<yy<<" "<<ux<<" "<<uy<<endl;
		ux=350;
		uy=40;
		x_incr=true;
		y_incr=false;
		si_in=1;
		xx=440;
		yy=40;
		x_increase=true;
		y_increase=false;
		sign_incr=1;
		lives--;
		score=0;
		printing=true;
	}
	if (lives==0){
		lives=3;
		screen=1;
	
	}
	}
	
	glutSwapBuffers(); // do not modify this line.. or draw anything below this line
	
}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
	//bool turn_left=false;
	if(uy>=340&&uy<=440){
		if (key
				== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
			// what to do when left key is pressed...
				ux=ux-90;
				if(ux<30)
					ux=ux+90;
				if(ux==390)
					ux+=90;
			//pos_x-=10;
		} else if (key
				== GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
			//pos_x+=10;
				ux=ux+90;
			if(ux>750)
				ux-=90;
			if(ux==390)
				ux-=90;
		} 
	}
	else if(ux>340&&ux<=440){
		if (key
				== GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {
			//pos_y+=10;
			uy=uy+90;	
			if(uy>760)
				uy-=90;
			if(uy==400)
				uy-=90;
		}

		else if (key
				== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {
			//pos_y-=10;
			uy=uy-90;
			if(uy<30)
				uy=uy+90;
			if(uy==400)
				uy+=90;
		}
	}
	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	//glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}

	if (key == 'b' || key == 'B')
			{
		//do something if b is pressed
		cout << "b pressed" << endl;

	}
	if(key == 32){
		if(uy>50&&uy<750){		//Double the speed when user is in layer 1
			if(ux==30)		//left columne 1
				uy+=20;
			else if(ux==750)	//right columne 1
				uy-=20;
		}
		else if(ux>40&&ux<740){
			if(uy==40)		//bottom row 1
				ux-=20;
			else if(uy==760)	//top row 1
				ux+=20;
		}
		if(uy>140&&uy<660){		//Double the speed when user is in layer 2
			if(ux==120)		//left col 2
				uy+=20;		
			else if(ux==660)	//right col 2
				uy-=20;
		}
		else if(ux>130&&ux<650){
			if(uy==130)		//bottom row 2
				ux-=20;
			else if(uy==670) 	//top row 2
				ux+=20;
		}
		if(uy>240&&uy<560){		//Double the speed when user is in layer 3
			if(ux==210)		//left columne 3
				uy+=20;
			else if(ux==570)	//right columne 3
				uy-=20;
		}
		else if(ux>230&&ux<570){
			if(uy==220)		//bottom row 3
				ux-=20;
			else if(uy==580)	//top row 3
				ux+=20;
		}
		if(uy>330&&uy<470){		//Double the speed when user is in layer 4
			if(ux==120)		//left col 4
				uy+=20;		
			else if(ux==660)	//right col 4
				uy-=20;
		}
		else if(ux>320&&ux<460){
			if(uy==310)		//bottom row 4
				ux-=20;
			else if(uy==490) 	//top row 4
				ux+=20;
		}
		
	}
	if(key == 'r' || key == 'R')
		screen=0;
	if(key=='p'||key=='P')
		screen=2;
	//glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {

	// implement your functionality here
	
	
	glutPostRedisplay();
	
	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(30.0, Timer, 0);
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
	cout << x << " " << y << endl;
	//glutPostRedisplay();
}
void MouseMoved(int x, int y) {

	//glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
			{
		cout << GLUT_DOWN << " " << GLUT_UP << endl;

	} else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{

	}
	glutPostRedisplay();
}
/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {
	
	//b = new Board(60, 60); // create a new board object to use in the Display Function ...
	
	int width = 840, height = 1040; // i have set my window size to be 800 x 600
	//b->InitalizeBoard(width, height);
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("OOP Centipede"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* AsteroidS_CPP_ */

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <ctime>
#include "Game.h"

Game::Game(){

	// Some cross-platform compatimility stuff


	

	const char* shroomFileName;
	const char* fireballFileName;
	const char* space_backgroundFileName;
	const char* space_backgroundFileName2;
	const char* asteroidFileName;
	const char* shipFileName;
	
	// In Windows (Visual Studio only) the image files are found in the enclosing folder in relation to the project
	// In other environments the image files are in the same folder as the project

	#if defined WIN32
	shroomFileName = "../mushroom.png";
	fireballFileName = "../fireball.bmp";
	space_backgroundFileName = "../spacebackground.png";
	space_backgroundFileName2 = "../spacebackground.png";
	asteroidFileName = "../asteroid.png";
	shipFileName = "../spaceship.png";

	#else
	shroomFileName = "mushroom.png";
	fireballFileName = "fireball.bmp";
	space_backgroundFileName = "spacebackground.png"
		space_backgroundFileName2 = "spacebackground.png"
	#endif

    
    explosion = new AnimatedRect(fireballFileName, 6, 6, 64, false, false, -0.25, 0.8, 0.5, 0.5);
	space_background = new TexRect(space_backgroundFileName, -2, 2, 4, 3);
	space_background2 = new TexRect(space_backgroundFileName2, 2, 2, 4, 3);
	ship = new TexRect(shipFileName, -1, 0, 0.2, 0.2);
	first_asteroid = true;
	asteroidsTop.resize(50, TexRect(asteroidFileName, 2.5,1.25,1,1));
	asteroidsBot.resize(50, TexRect(asteroidFileName, 2.5, -0.25, 1, 1));
	dead = new TextBox("GAME OVER", 0.0, 0.0, GLUT_BITMAP_HELVETICA_18, 1, 0, 0, 800);
	


	deltaT = 0.006;
	start_game = false;
	jump = false;
	velocity = 0;
	game_over = false;
    up = false;
    left = true;
    projectileVisible = true;
    mushroomVisible = true;
    theta = 0;
    deg = 0;
    hit = false;
    
    setRate(1);
    start();
}

void Game::action(){
    float mx = 0.5;
    float my = 0;
	time_t current_time;
	current_time = time(NULL);
    if (theta >= 2* M_PI) theta = 0;
    if (deg >= 360) deg = 0;
    
    mx = 0.5 * cos(theta);
    my = 0.5 * sin(theta);
    
//    if (left)
//        mx -= 0.0005;
//    else
//        mx += 0.0005;
//
//    if (mx < -1.6f){
//        left = false;
//    }
//    if (mx > 1.6 - mushroom->getW()){
//        left = true;
//    }
    
    
 

	
	if (jump == true) {
		float Y_new = ship->getY() + 0.05;
		ship->setY(Y_new);
		//std::cout << "ship post" << ship->getY() << std::endl;
		//std::cout << "jumpdist" << jumpdist << std::endl;
		if (ship->getY() >= jumpdist) {
			jump = false;
		}

		//std::cout << current_time << " seconds have passed by" << std::endl;

	}
	else  if (start_game == true && jump == false) {
		float y_new = ship->getY() - 0.0015;
		ship->setY(y_new); 
	}

	//MOVE THE ASTEROIDS
	if (first_asteroid == true) {
		float deltaX = asteroidsTop[0].getX() - 0.0005;
		asteroidsTop[0].setX(deltaX);
		asteroidsBot[0].setX(deltaX);
		if (asteroidsTop[0].getX() <= -4) {
			first_asteroid = false;
		}

	}

	for (std::vector<TexRect>::iterator ptr = asteroidsTop.begin() + 1; ptr < asteroidsTop.end(); ptr++) {
		if ((ptr-1)->getX() <=0 ) {
			float deltaX = ptr->getX() - 0.0005;
			(*ptr).setX(deltaX);

		}
		if (ptr->contains(ship->getX(), ship->getY())) {
			std::cout << "You died " << std::endl;
			game_over = true;
		}
	}
	
	for (std::vector<TexRect>::iterator ptr = asteroidsBot.begin() + 1; ptr < asteroidsBot.end(); ptr++) {
		if ((ptr - 1)->getX() <= 0) {
			float deltaX = ptr->getX() - 0.0005;
			(*ptr).setX(deltaX);

		}
		if (ptr->contains(ship->getX(), ship->getY())) {
			std::cout << "You died " << std::endl;
			game_over = true;
		}
	}

	//draw background

	



	float x, x2;
	x = space_background->getX();
	x2 = space_background2->getX();
	space_background->setX(x - 0.0002);
	space_background2->setX(x2 - 0.0002);

	if (space_background->getX() <= -6) {
		space_background->setX(2);
	}
	if (space_background2->getX() <= -6) {
		space_background2->setX(2);
		
	}
	if (game_over == true) {
		//delete &space_background;
		//delete &space_background2;

	}

}

void Game::draw() const {

	if (game_over == false) {
		space_background->draw(0.2);
		space_background2->draw(0.3);
		ship->draw(1);


		explosion->draw(0.5);

		if (first_asteroid == true) {
			asteroidsTop[0].draw(0.5);
			asteroidsBot[0].draw(0.5);
		}

		for (std::vector<TexRect>::const_iterator ptr = asteroidsTop.begin() + 1; ptr < asteroidsTop.end(); ptr++) {

			if ((ptr - 1)->getX() <= 0) {
				ptr->draw(0.5);
			}
			//std::cout << ptr->getX() << std::endl;
			//std::cout << ptr->getY() << std::endl;
		}
		for (std::vector<TexRect>::const_iterator ptr = asteroidsBot.begin() + 1; ptr < asteroidsBot.end(); ptr++) {

			if ((ptr - 1)->getX() <= 0) {
				ptr->draw(0.5);
			}
			//std::cout << ptr->getX() << std::endl;
			//std::cout << ptr->getY() << std::endl;
		}

	}
	if (game_over == true) {
		dead->draw();
	}


}

void Game::handleKeyDown(unsigned char key, float x, float y){
    if (key == ' '){
        up = true;
		start_game = true;
		jump = true;
		jumpdist = ship->getY() + 0.5;
    }
    else if (key == 'p'){
        stop();
    }
    else if (key == 'r'){
        start();
    }
}

Game::~Game(){
    stop();
	delete space_background;
	delete space_background2;
	delete ship;
	delete &asteroidsBot;
	
    delete explosion;
    
}

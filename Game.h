#ifndef Game_hpp
#define Game_hpp

#include "AppComponent.h"
#include "AnimatedRect.h"
#include "Timer.h"
#include <vector>
#include <iterator>
#include <TextBox.h>


class Game: public AppComponent,  private Timer{
    //TexRect* mushroom;
    //Rect* projectile;
	TexRect* space_background;
	TexRect* space_background2;
	std::vector<TexRect> asteroidsTop;
	std::vector<TexRect> asteroidsBot;
	TexRect* ship;
	TextBox* dead;
	bool start_game;
	bool jump;
	float accel;
	float velocity;
	float deltaT;
	float jumpdist;


	//std::vector<TexRect>::iterator ptr;
	bool game_over;
	bool first_asteroid;
    bool projectileVisible;
    bool mushroomVisible;
    bool up;
    bool left;
    bool hit;
    float theta;
    float deg;
public:
    AnimatedRect* explosion;
    Game();
    
    void draw() const ;
    void handleKeyDown(unsigned char, float, float);
    
    void action();

    ~Game();

};

#endif 

#pragma once
#include "CommonHeaders.h"
class Game 
{
public:
	
	Game() {};

	//need a draw/render function
	void Draw(float);

	//load or init function 
	//return number greater than 0 if load fails
	int Load();

	//update function that provides detla time
	void Update();

	void Start();
	
	
	~Game();
<<<<<<< HEAD
=======



>>>>>>> d8a2e22f3480f6ccd1a95f3df1a8a1ef83ffb969
};
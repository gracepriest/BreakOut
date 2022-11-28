#pragma once
#include "State.h"


class State;

struct Args
{
	 int currentScore=0;
	 int health=0;
	 int score=0;
	 int levelScore=0;
};



class BaseState
{
public:
	Args args;
	virtual void Init() = 0;
	virtual void Exit() = 0;
	virtual void Render() = 0;
	virtual void Update(State&) = 0;
	//virtual void SetState(State* state) = 0;

	virtual ~BaseState(){}

};
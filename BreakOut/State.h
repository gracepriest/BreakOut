#pragma once
#include "BaseState.h"


#include "States.h"

class BaseState;

class State 
{

public:
	State() {}
	
	
	inline BaseState* getCurrrentState() const { return currentState; }

	void Init()
	{
		if (currentState != nullptr)
		{
			currentState->Init();
		}
		else
		{
			SetState(TitleState::getInstance());
			currentState->Init();
		}
		
	}
	void Play()
	{
		
	}
	virtual void Exit()
	{
		currentState->Exit();
	}
	
	void Update()
	{	
		currentState->Update(*this);
	}
	void SetState(BaseState& newState, Args options = {0,3,0})
	{
		currentState = &newState;
		currentState->args = options;
	}

	void Render()
	{
		if (currentState != nullptr)
		{
			currentState->Render();
		}
	}


private:
	BaseState* currentState;
	State& operator = (const State& other);
	

};
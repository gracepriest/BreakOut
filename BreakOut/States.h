#pragma once
#include "BaseState.h"
#include "CommonHeaders.h"

#include "Fonts.h"

static int currentLevel;

class PlayState : public BaseState
{
public:

    
	void Init();
	void Exit();
	void Render();
	void Update(State&);
	int Load(int&);
	//void SetState(State* newState);
	static BaseState& getInstance();
	


private:
	PlayState() {}
	PlayState(const PlayState& other);
	PlayState& operator = (const PlayState& other);
	~PlayState() {}
	
	

};



class TitleState : public BaseState
{

public:
	
	int highLighted = 1;
    void Init();
	void Exit();
	void Render();
	void Update(State&);
	//void SetState(State* newState);
	static BaseState& getInstance();
	

private:
	
	TitleState() {   }
	TitleState(const TitleState& other);
	TitleState& operator = (const TitleState& other);
	~TitleState() {}

};


class ServeState : public BaseState
{
public:
	void Init();
	void Exit();
	void Render();
	void Update(State&);
	//void SetState(State* newState);
	static BaseState& getInstance();


private:

	ServeState() {   }
	ServeState(const ServeState& other);
	ServeState& operator = (const ServeState& other);
	~ServeState() {}
};


class GameOverState : public BaseState
{
public:
	bool enterscoreFlag = false;
	void Init();
	void Exit();
	void Render();
	void Update(State&);
	//void SetState(State* newState);
	static BaseState& getInstance();


private:

	GameOverState() {   }
	GameOverState(const ServeState& other);
	GameOverState& operator = (const GameOverState& other);
	~GameOverState() {}
};

class EnterScoreState : public BaseState
{
public:
	void Init();
	void Exit();
	void Render();
	void Update(State&);
	//void SetState(State* newState);
	static BaseState& getInstance();


private:

	EnterScoreState() {   }
	EnterScoreState(const ServeState& other);
	EnterScoreState& operator = (const  EnterScoreState& other);
	~EnterScoreState() {}
};

class EnterCharState : public BaseState
{
public:
	void Init();
	void Exit();
	void Render();
	void Update(State&);
	//void SetState(State* newState);
	static BaseState& getInstance();


private:

	EnterCharState() {   }
	EnterCharState(const ServeState& other);
	EnterCharState& operator = (const  EnterCharState& other);
	~EnterCharState() {}
};



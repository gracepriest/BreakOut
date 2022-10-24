#include "Particle.h"
Particle::Particle()
{

	
	position = {150,0};
	color = RED;
	active = false;
	alpha = 255;
	size = 1;
	gravity = 0.2f;

	dx = rand() % 50 -15;
	dy = rand() % 10;
	
	
	
}

Particle::~Particle()
{

}
void Particle::InitParticleMemory()
{

	
}
void Particle::FreeParticleMemory()
{

}
void Particle::Update(float dt)
{
		
	if (active)
	{

	position.x += dx * gravity;
	position.y += dy * gravity;
	if(alpha != 0)
	alpha -= 5;
	if (alpha == 0)
		active = false;
	}

}

void Particle::Render()
{
	if (active)
		DrawRectangle(position.x, position.y, 8, 8, color = {color.r,color.g,color.b,alpha});
	   

}
void Particle::Destroy()
{

}
#pragma once
#include "CommonHeaders.h"
const int MAX_PARTICLES = 200;
class Particle
{
public:

	Vector2 position;
	Color color;
	unsigned char alpha;
	float size;
	float rotation;
	bool active;
	float gravity;
	float dx;
	float dy;
	
	Particle();
	~Particle();

	void InitParticleMemory();
	void FreeParticleMemory();
	void Update(float dt);
	void Destroy();
	void Render();
};
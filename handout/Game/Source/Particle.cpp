#include "Particle.h"
#include "App.h"
#include "Render.h"
#include "ParticleSystem.h"
#include "Defs.h"
#include "Log.h"


Particle::Particle(fPoint pos, float initialSpeed, float finalSpeed, float angle, double rotSpeed, fPoint initialSize, fPoint finalSize, uint life, SDL_Rect texRect, SDL_Color initialColor, SDL_Color finalColor, SDL_BlendMode blendMode, bool vortexActive, bool halfTex) : life(0)
{
	/* TODO 2: Create the particle using the given variables
		- Change the speeds regarding the angle
		- Don't forget to reset "timeStep"
	* */
}

void Particle::Update(float dt)
{
	// Adds a vortex to the system (you can only have one)
	if (vortexActive)
	{
		SetVortex({ 400.0f, 250.0f }, 10.0f, 50.0f);
	}
	else
	{
		SetVortex({ 0.0f, 0.0f }, 0.0f, 0.0f);
	}

	curSize = InterpolateBetween(initialSize, timeStep, finalSize);
	rectSize.w = curSize.x;
	rectSize.h = curSize.y;

	curSpeed = InterpolateBetween(initialSpeed, timeStep, finalSpeed);

	// Calculates the new particle's position
	CalculateParticlePos(dt);

	// Particle's life decrease
	life--;
}

bool Particle::Draw()
{
	bool ret = true;

	// Calculates the center of the particle's current texture
	fPoint center;
	center.x = pos.x - rectSize.w/2;
	if (halfTex)
	{
		center.y = pos.y - rectSize.h;
	}
	else
	{
		center.y = pos.y - rectSize.h / 2;
	}

	/* TODO 5.1: Interpolate color
		- Using both the initial and the final SDL_Color variables create a function that interpolates them so that the particle transitions from the initial to the final
		- You can use the InterpolateBetween function as a reference
	* */

	// Drawing particle on the screen
	ret = app->render->DrawParticle(app->particleSystem->GetParticleAtlas(), (int)center.x, (int)center.y, &pRect, &rectSize, 1.0f, curRotSpeed);

	/* TODO 5.3: Draw the particle hitbox if in debug mode
		- You can use the same color of the particle for the rectangle
		- Remember to override the alpha value so that you can still see the particle!
	* */

	/* TODO 4.1: Particle interpolation and life check
		- Increase the current rotation of the particle according to the rotation speed
		- Increment the timeStep each frame from the initial life to interpolate colors and size
		- Check if the life surpasses 1.0f and ready it for deletion
	* */

	return ret;
}

bool Particle::IsAlive()
{
	return (life > 0 && pendingToDelete == false);
}

float Particle::InterpolateBetween(float min, float timeStep, float max)
{
	return min + (max - min) * timeStep;
}

fPoint Particle::InterpolateBetween(fPoint min, float timeStep, fPoint max)
{
	fPoint result;
	result.x = InterpolateBetween(min.x, timeStep, max.x);
	result.y = InterpolateBetween(min.y, timeStep, max.y);
	return result;
}

void Particle::SetVortex(fPoint pos, float speed, float scale)
{
	vortex.pos = pos;
	vortex.speed = speed;
	vortex.scale = scale;
}

void Particle::CalculateParticlePos(float dt)
{
	fPoint dif = { pos.x - vortex.pos.x, pos.y - vortex.pos.y };
	fPoint vel = { -dif.y * vortex.speed, dif.x * vortex.speed };
	float inversePower = (dif.x * dif.x + dif.y * dif.y) / vortex.scale;
	float power = 1.0f / (1.0f + inversePower);
	pos.x += (vel.x - curSpeed.x) * power + curSpeed.x * dt;
	pos.y += (vel.y - curSpeed.y) * power + curSpeed.y * dt;
}
#include "Emitter.h"
#include "App.h"
#include <time.h>
#include "ParticleSystem.h"
#include "Particle.h"
#include "Log.h"

Emitter::Emitter(fPoint pos, EmitterData data)
{
	srand(time(NULL));

	active = true;
	/* TODO 1: Setup the emitter, for that you need to:
		- Store the given variables
		- Calculate the maximum particles that can spawn each frame
		- Start the "lifeTimer" unless you want the emitter to be permanently active
	* */

	// Clear the particle list
	ListItem<Particle*>* p = particlePool.start;
	while (p != nullptr)
	{
		ListItem<Particle*>* pNext = p->next;
		DestroyParticle(p->data);
		p = pNext;
	}
	particlePool.Clear();
}

Emitter::~Emitter()
{}

bool Emitter::CleanUp()
{
	LOG("Emitter delete");

	ListItem<Particle*>* p = particlePool.start;
	while (p != nullptr)
	{
		if (p->next != nullptr)
		{
			ListItem<Particle*>* pNext = p->next;
			DestroyParticle(p->data);
			p = pNext;
		}
		else
		{
			DestroyParticle(p->data);
			break;
		}
	}
	particlePool.Clear();

	return true;
}

bool Emitter::Update(float dt)
{
	if (active)
	{
		// Particle generation
		int emissionMultiplier = (int)(data.emitNumber + data.emitNumMult * GenerateRandNum(data.randEmitMult.x, data.randEmitMult.y));

		for (int i = 1; i <= emissionMultiplier; i++)
		{
			float pRandInitialSpeed = data.initialSpeed * GenerateRandNum(data.randInitialSpeed.x, data.randInitialSpeed.y);
			float pRandFinalSpeed = data.finalSpeed * GenerateRandNum(data.randFinalSpeed.x, data.randFinalSpeed.y);
			float pRandAngle = GenerateRandNum(data.angleRange.x, data.angleRange.y);
			fPoint pRandInitialSize;
			pRandInitialSize.x = data.initialSize.x * GenerateRandNum(data.randInitialSize.x, data.randInitialSize.y);
			pRandInitialSize.y = data.initialSize.y * GenerateRandNum(data.randInitialSize.x, data.randInitialSize.y);
			fPoint pRandFinalSize;
			pRandFinalSize.x = data.finalSize.x * GenerateRandNum(data.randFinalSize.x, data.randFinalSize.y);
			pRandFinalSize.y = data.finalSize.y * GenerateRandNum(data.randFinalSize.x, data.randFinalSize.y);
			fPoint pStartingSize;
			pStartingSize.x = GenerateRandNum(pRandInitialSize.x, pRandFinalSize.x);
			pStartingSize.y = GenerateRandNum(pRandInitialSize.y, pRandFinalSize.y);
			double randRotationSpeed = data.rotSpeed * GenerateRandNum(data.randRotSpeed.x, data.randRotSpeed.y);

			Particle* p = new Particle(pos, pRandInitialSpeed, pRandFinalSpeed, pRandAngle, randRotationSpeed, pStartingSize, data.finalSize, data.maxParticleLife, data.texRect, data.initialColor, data.finalColor, data.blendMode, data.vortexActive, data.halfTex);
			particlePool.Add(p);
		}
	}

	// Emission timing calculations
	if (data.emitLifetime > 0.0f)
	{
		if (lifeTimer.Read() >= data.emitLifetime)
		{
			active = false;
			data.emitLifetime = 0.0f;
		}
	}

	// TODO 3.1: Update all alive particles

	return true;
}

bool Emitter::PostUpdate()
{
	bool ret = true;

	// TODO 3.2: Draw all alive particles
	// TODO 4.2: In the same loop you can delete all the dead particles

	if (particlePool.Count() == 0)
	{
		app->particleSystem->RemoveEmitter(this);
	}

	return ret;
}

float Emitter::GenerateRandNum(float min, float max)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = max - min;
	float result = random * diff;

	return min + result;
}

void Emitter::MoveEmitter(fPoint newPos)
{
	pos = newPos;
}

void Emitter::SetVortexActive(bool sensitive)
{
	data.vortexActive = sensitive;
}

bool Emitter::GetVortexActive()
{
	return data.vortexActive;
}

void Emitter::DestroyParticle(Particle* p)
{
	int i = particlePool.Find(p);
	RELEASE(p);
	particlePool.Del(particlePool.At(i));
}
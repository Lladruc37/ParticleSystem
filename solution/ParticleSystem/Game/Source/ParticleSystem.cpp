#include "App.h"
#include "ParticleSystem.h"

//#include "Defs.h"
//#include "Log.h"

ParticleSystem::ParticleSystem()
{
	name.Create("particleSystem");
}

ParticleSystem::~ParticleSystem()
{

}

bool ParticleSystem::Awake()
{
	return true;
}

bool ParticleSystem::Start()
{
	return true;
}

bool ParticleSystem::PreUpdate()
{
	return true;
}

bool ParticleSystem::Update(float dt)
{
	return true;
}

bool ParticleSystem::PostUpdate()
{
	return true;
}

bool ParticleSystem::CleanUp()
{
	return true;
}
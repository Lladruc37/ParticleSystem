#ifndef __PARTICLE_SYSTEM_H__
#define __PARTICLE_SYSTEM_H__

#include "Module.h"
#include "List.h"
#include "SString.h"

class ParticleSystem : public Module
{
public:
	ParticleSystem();

	// Destructor
	virtual ~ParticleSystem();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

public:

private:

};

#endif // !__PARTICLE_SYSTEM_H__

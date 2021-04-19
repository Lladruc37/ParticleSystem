#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"

class Emitter;

class Scene : public Module
{
public:
	// Constructor
	Scene();

	// Destructor
	virtual ~Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

public:
	SDL_Texture* particlesAtlas;
	SDL_Texture* particlesAtlasClean;

private:
	List<Emitter*> fires;
	List<Emitter*> smokes;
	List<Emitter*> novas;
	List<Emitter*> slashes;
	List<Emitter*> bubbles;
	List<Emitter*> heals;
	List<Emitter*> blesses;

	bool movingFire;
};
#endif // __SCENE_H__
#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Render.h"
#include "Scene.h"

#include "Defs.h"
#include "Log.h"

Scene::Scene() : Module()
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;
	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	particlesAtlas = app->tex->Load("Assets/Textures/ParticlesAtlas.png");

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;
	SDL_Rect r = { 0,0,256,256 };
	app->render->DrawTexture(particlesAtlas, 0, 0, false, &r);
	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");
	app->tex->UnLoad(particlesAtlas);

	return true;
}
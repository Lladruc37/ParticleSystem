#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Render.h"
#include "Scene.h"
#include "ParticleSystem.h"
#include "Particle.h"

#include "Defs.h"
#include "Log.h"

Scene::Scene() : Module()
{
	name.Create("scene");
}

Scene::~Scene()
{}

bool Scene::Awake()
{
	LOG("Loading Scene");
	return true;
}

bool Scene::Start()
{
	ListItem<Emitter*>* fire = fires.start;
	while (fire != nullptr)
	{
		ListItem<Emitter*>* fireNext = fire->next;
		RELEASE(fire);
		fire = fireNext;
	}
	fires.Clear();

	return true;
}

bool Scene::PreUpdate()
{
	return true;
}

bool Scene::Update(float dt)
{
	int x, y;
	app->input->GetMousePosition(x, y);
	fPoint pos = { (float)x,(float)y };

	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		LOG("Fire emitter init");
		fires.Add(app->particleSystem->AddEmitter(pos, EmitterData::EmitterType::FIRE));
	}

	// TODO 7(Optional): Try making bubbles as a new Emitter with what you have learned

	// Removes all emitters
	if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
	{
		app->particleSystem->RemoveAllEmitters();
	}

	return true;
}

bool Scene::PostUpdate()
{
	app->render->background = { 30,30,30,255 };
	return true;
}

bool Scene::CleanUp()
{
	LOG("Freeing scene");

	ListItem<Emitter*>* fire = fires.start;
	while (fire != nullptr)
	{
		ListItem<Emitter*>* fireNext = fire->next;
		RELEASE(fire);
		fire = fireNext;
	}
	fires.Clear();

	return true;
}
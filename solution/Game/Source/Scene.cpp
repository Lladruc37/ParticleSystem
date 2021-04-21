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

	ListItem<Emitter*>* smoke = smokes.start;
	while (smoke != nullptr)
	{
		ListItem<Emitter*>* smokeNext = smoke->next;
		RELEASE(smoke);
		smoke = smokeNext;
	}
	smokes.Clear();

	ListItem<Emitter*>* nova = novas.start;
	while (nova != nullptr)
	{
		ListItem<Emitter*>* novaNext = nova->next;
		RELEASE(nova);
		nova = novaNext;
	}
	novas.Clear();

	ListItem<Emitter*>* slash = slashes.start;
	while (slash != nullptr)
	{
		ListItem<Emitter*>* slashNext = slash->next;
		RELEASE(slash);
		slash = slashNext;
	}
	slashes.Clear();

	ListItem<Emitter*>* bubble = bubbles.start;
	while (bubble != nullptr)
	{
		ListItem<Emitter*>* bubbleNext = bubble->next;
		RELEASE(bubble);
		bubble = bubbleNext;
	}
	bubbles.Clear();

	ListItem<Emitter*>* heal = heals.start;
	while (heal != nullptr)
	{
		ListItem<Emitter*>* healNext = heal->next;
		RELEASE(heal);
		heal = healNext;
	}
	heals.Clear();

	ListItem<Emitter*>* bless = blesses.start;
	while (bless != nullptr)
	{
		ListItem<Emitter*>* blessNext = bless->next;
		RELEASE(bless);
		bless = blessNext;
	}
	blesses.Clear();

	movingFire = false;

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
	if (app->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		LOG("Smoke emitter init");
		smokes.Add(app->particleSystem->AddEmitter(pos, EmitterData::EmitterType::SMOKE));
	}
	if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
	{
		LOG("Nova emitter init");
		novas.Add(app->particleSystem->AddEmitter(pos, EmitterData::EmitterType::NOVA));
	}
	if (app->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN)
	{
		LOG("Slash emitter init");
		slashes.Add(app->particleSystem->AddEmitter(pos, EmitterData::EmitterType::SLASH));
	}
	if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
	{
		LOG("Bubble emitter init");
		bubbles.Add(app->particleSystem->AddEmitter(pos, EmitterData::EmitterType::BUBBLE));
	}
	if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
	{
		LOG("Heal emitter init");
		heals.Add(app->particleSystem->AddEmitter(pos, EmitterData::EmitterType::HEAL));
	}
	if (app->input->GetKey(SDL_SCANCODE_F7) == KEY_DOWN)
	{
		LOG("Bless emitter init");
		blesses.Add(app->particleSystem->AddEmitter(pos, EmitterData::EmitterType::BLESS));
	}

	// All current and future fires will now (toggle) follow/not follow the mouse
	if (app->input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN)
	{
		if (!movingFire)
		{
			LOG("Fire will now follow the mouse");
		}
		else
		{
			LOG("Fire will now stop following the mouse");
		}
		movingFire = !movingFire;
	}

	// Activates/Deactivates all current fire vortexes
	if (app->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
	{
		ListItem<Emitter*>* fire = fires.start;
		while (fire != nullptr)
		{
			fire->data->SetVortexActive(!fire->data->GetVortexActive());
			fire = fire->next;
		}
	}

	// Removes all emitters
	if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
	{
		app->particleSystem->RemoveAllEmitters();
	}

	// Logic for moving the fires
	if (movingFire)
	{
		ListItem<Emitter*>* fire = fires.start;
		while (fire != nullptr)
		{
			fire->data->MoveEmitter(pos);
			fire = fire->next;
		}
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

	ListItem<Emitter*>* smoke = smokes.start;
	while (smoke != nullptr)
	{
		ListItem<Emitter*>* smokeNext = smoke->next;
		RELEASE(smoke);
		smoke = smokeNext;
	}
	smokes.Clear();

	ListItem<Emitter*>* nova = novas.start;
	while (nova != nullptr)
	{
		ListItem<Emitter*>* novaNext = nova->next;
		RELEASE(nova);
		nova = novaNext;
	}
	novas.Clear();

	ListItem<Emitter*>* slash = slashes.start;
	while (slash != nullptr)
	{
		ListItem<Emitter*>* slashNext = slash->next;
		RELEASE(slash);
		slash = slashNext;
	}
	slashes.Clear();

	ListItem<Emitter*>* bubble = bubbles.start;
	while (bubble != nullptr)
	{
		ListItem<Emitter*>* bubbleNext = bubble->next;
		RELEASE(bubble);
		bubble = bubbleNext;
	}
	bubbles.Clear();

	ListItem<Emitter*>* heal = heals.start;
	while (heal != nullptr)
	{
		ListItem<Emitter*>* healNext = heal->next;
		RELEASE(heal);
		heal = healNext;
	}
	heals.Clear();

	ListItem<Emitter*>* bless = blesses.start;
	while (bless != nullptr)
	{
		ListItem<Emitter*>* blessNext = bless->next;
		RELEASE(bless);
		bless = blessNext;
	}
	blesses.Clear();

	return true;
}
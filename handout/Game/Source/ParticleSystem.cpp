#include "App.h"
#include "ParticleSystem.h"
#include "Textures.h"

#include "Defs.h"
#include "Log.h"

ParticleSystem::ParticleSystem()
{
	name.Create("particleSystem");
}

ParticleSystem::~ParticleSystem()
{}

bool ParticleSystem::Awake(pugi::xml_node& config)
{
	LOG("Loading Particle System");
	LoadEmittersData();
	return true;
}

bool ParticleSystem::Start()
{
	// Loads the particle atlas
	particleAtlas = app->tex->Load("Assets/Textures/ParticlesAtlas.png");

	// Clear the particle list
	ListItem<Emitter*>* e = emittersList.start;
	while (e != nullptr)
	{
		ListItem<Emitter*>* eNext = e->next;
		e->data->CleanUp();
		emittersList.Del(emittersList.At(emittersList.Find(e->data)));
		delete e->data;
		e = eNext;
	}
	emittersList.Clear();

	return true;
}

bool ParticleSystem::PreUpdate()
{
	return true;
}

bool ParticleSystem::Update(float dt)
{
	// Updates all emitters
	ListItem<Emitter*>* e = emittersList.start;
	while (e != nullptr)
	{
		e->data->Update(dt);
		e = e->next;
	}

	return true;
}

bool ParticleSystem::PostUpdate()
{
	// Checks if there are any emitters to delete
	if (emittersToDestroy.Count() != 0)
	{
		ListItem<Emitter*>* e = emittersToDestroy.start;
		while (e != nullptr)
		{
			ListItem<Emitter*>* eNext = e->next;
			e->data->CleanUp();
			emittersList.Del(emittersList.At(emittersList.Find(e->data)));
			delete e->data;
			e = eNext;
		}
		emittersToDestroy.Clear();
	}

	// PostUpdates all emitters
	ListItem<Emitter*>* e = emittersList.start;
	while (e != nullptr)
	{
		e->data->PostUpdate();
		e = e->next;
	}

	return true;
}

bool ParticleSystem::CleanUp()
{
	ListItem<Emitter*>* e = emittersList.start;
	while (e != nullptr)
	{
		ListItem<Emitter*>* eNext = e->next;
		e->data->CleanUp();
		delete e;
		e = eNext;
	}
	emittersList.Clear();

	ListItem<Emitter*>* eToDestroy = emittersToDestroy.start;
	while (eToDestroy != nullptr)
	{
		ListItem<Emitter*>* eNext = eToDestroy->next;
		eToDestroy->data->CleanUp();
		delete eToDestroy;
		eToDestroy = eNext;
	}
	emittersToDestroy.Clear();

	app->tex->UnLoad(particleAtlas);

	return true;
}

Emitter* ParticleSystem::AddEmitter(fPoint pos, EmitterData::EmitterType type)
{
	Emitter* e = new Emitter(pos, emittersData[type]);
	emittersList.Add(e);
	return e;
}

bool ParticleSystem::RemoveEmitter(Emitter* emitter)
{
	if (emitter != nullptr && emittersList.Count() != 0)
	{
		emittersToDestroy.Add(emitter);
		return true;
	}
	return false;
}

bool ParticleSystem::RemoveAllEmitters()
{
	if (emittersList.Count() != 0)
	{
		ListItem<Emitter*>* e = emittersList.start;
		while (e != nullptr)
		{
			emittersToDestroy.Add(e->data);
			e = e->next;
		}
		return true;
	}
	return false;
}

SDL_Texture* ParticleSystem::GetParticleAtlas()
{
	return particleAtlas;
}

void ParticleSystem::LoadEmittersData()
{
	/* TODO 6: Modify the fire values so that they suit the fire you want to make!
		- The one you have here is one I made and really like how it looks (unless you move it a lot)
	* */
	EmitterData::EmitterType type = EmitterData::EmitterType::NONE;
	for (int i = 0; i <= MAX_NUM_EMITTERS_TYPE; i++)
	{
		switch (type)
		{
		case EmitterData::EmitterType::FIRE:
		{
			EmitterData eData;
			eData.rotSpeed = 0;
			eData.angleRange = { 80,110 };
			eData.initialSpeed = 200;
			eData.finalSpeed = 200;
			eData.initialSize = { 200,200 };
			eData.finalSize = { 80,80 };

			eData.emitNumber = 1;
			eData.emitNumMult = 0;
			eData.maxParticleLife = 100;
			eData.emitLifetime = -1;

			eData.texRect = { 512,256,256,256 };
			eData.initialColor = { 255,100,0,255 };
			eData.finalColor = { 210,210,210,0 };
			eData.blendMode = SDL_BLENDMODE_ADD;

			eData.randRotSpeed = { -1,1 };
			eData.randInitialSpeed = { 0,1 };
			eData.randFinalSpeed = { 0,1 };
			eData.randEmitMult = { 0,1 };
			eData.randLife = { 0,1 };
			eData.randInitialSize = { 0,1 };
			eData.randFinalSize = { 1,1 };

			eData.vortexActive = true;
			eData.halfTex = false;
			eData.eType = EmitterData::EmitterType::FIRE;
			emittersData[type] = eData;
			break;
		}
		default:
		{
			break;
		}
		}

		// Next emitter type
		switch (i)
		{
		case 0:
			type = EmitterData::EmitterType::FIRE;
			break;
		case 1:
			type = EmitterData::EmitterType::SMOKE;
			break;
		case 2:
			type = EmitterData::EmitterType::NOVA;
			break;
		case 3:
			type = EmitterData::EmitterType::SLASH;
			break;
		case 4:
			type = EmitterData::EmitterType::BUBBLE;
			break;
		case 5:
			type = EmitterData::EmitterType::HEAL;
			break;
		case 6:
			type = EmitterData::EmitterType::BLESS;
			break;
		default:
			break;
		}
	}
}
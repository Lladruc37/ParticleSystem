#include "App.h"
#include "Window.h"
#include "Input.h"
#include "Render.h"
#include "Textures.h"
#include "ParticleSystem.h"

#include "Scene.h"

#include "Defs.h"
#include "Log.h"

#include <iostream>
#include <sstream>

// Constructor
App::App(int argc, char* args[]) : argc(argc), args(args)
{
	PERF_START(pTimer);

	win = new Window();
	input = new Input();
	render = new Render();
	tex = new Textures();
	particleSystem = new ParticleSystem();

	scene = new Scene();

	// Ordered for awake / Start / Update
	// Reverse order of CleanUp
	AddModule(win);
	AddModule(input);
	AddModule(tex);

	AddModule(scene);
	AddModule(particleSystem);

	// Render last to swap buffer
	AddModule(render);
}

// Destructor
App::~App()
{
	// Release modules
	ListItem<Module*>* item = modules.end;

	while(item != NULL)
	{
		RELEASE(item->data);
		item = item->prev;
	}

	modules.Clear();
}

void App::AddModule(Module* module)
{
	module->Init();
	modules.Add(module);
}

// Called before render is available
bool App::Awake()
{
	PERF_START(pTimer);

	pugi::xml_document configFile;
	pugi::xml_node config;
	pugi::xml_node configApp;

	bool ret = false;

	config = LoadConfig(configFile);

	if (config.empty() == false)
	{
		ret = true;
		configApp = config.child("app");

		title.Create(configApp.child("title").child_value());
		organization.Create(configApp.child("organization").child_value());

		// Read from config file your framerate cap
		int cap = configApp.attribute("framerateCap").as_int(-1);

		if (cap > 0)
		{
			cappedMs = 1000 / cap;
		}
	}

	if (ret == true)
	{
		ListItem<Module*>* item;
		item = modules.start;

		while (item != NULL && ret == true)
		{
			ret = item->data->Awake(config.child(item->data->name.GetString()));
			item = item->next;
		}
	}

	PERF_PEEK(pTimer);

	return ret;
}

// Called before the first frame
bool App::Start()
{
	bool ret = true;
	ListItem<Module*>* item;
	item = modules.start;

	while(item != NULL && ret == true)
	{
		if (item->data->active == true) ret = item->data->Start();

		item = item->next;
	}

	exitRequest = false;

	return ret;
}

// Called each loop iteration
bool App::Update()
{
	bool ret = true;
	PrepareUpdate();

	if (input->GetWindowEvent(WE_QUIT) == true)
	{
		ret = false;
	}

	if (ret == true)
	{
		ret = PreUpdate();
	}

	if (ret == true)
	{
		ret = DoUpdate();
	}

	if (ret == true)
	{
		ret = PostUpdate();
	}

	FinishUpdate();

	if (exitRequest)
	{
		return false;
	}

	return ret;
}

// Load config from XML file
pugi::xml_node App::LoadConfig(pugi::xml_document& configFile) const
{
	pugi::xml_node ret;
	pugi::xml_parse_result result = configFile.load_file(CONFIG_FILENAME);

	if (result == NULL)
	{
		LOG("Could not load xml file: %s. pugi error: %s", CONFIG_FILENAME, result.description());
	}
	else
	{
		ret = configFile.child("config");
	}

	return ret;
}

// ---------------------------------------------
void App::PrepareUpdate()
{
	frameCount++;
	lastSecFrameCount++;

	// Calculate the dt: differential time since last frame
	dt = frameTime.ReadSec();

	// Start the timer after read because we want to know how much time it took from the last frame to the new one
	PERF_START(frameTime);
}

// ---------------------------------------------
void App::FinishUpdate()
{
	// Framerate calculations------------------------------------------
	// To know how many frames have passed in the last second
	if (lastSecFrameTime.Read() > 1000)
	{
		lastSecFrameTime.Start();
		prevLastSecFrameCount = lastSecFrameCount;
		lastSecFrameCount = 0;
	}

	// Amount of seconds since startup
	float secondsSinceStartup = 0.0f;
	secondsSinceStartup = startupTime.ReadSec();

	// Amount of time since game start (use a low resolution timer)
	uint32 lastFrameMs = 0;
	lastFrameMs = frameTime.Read(); // Time from the prepare update until now (whole update method)

	// Average FPS for the whole game life (since start)
	float averageFps = 0.0f;
	averageFps = float(frameCount) / startupTime.ReadSec();

	// Amount of frames during the last update
	uint32 framesOnLastUpdate = 0;
	framesOnLastUpdate = prevLastSecFrameCount;

	static char title[256];
	static char vsyncStr[4];

	sprintf_s(title, 256, "FPS: %i Av.FPS: %.2f Last Frame Ms: %02u", framesOnLastUpdate, averageFps, lastFrameMs);
	app->win->SetTitle(title);

	// Use SDL_Delay to make sure you get your capped framerate
	PERF_START(pTimer);
	if (cappedMs > lastFrameMs)
	{
		SDL_Delay(cappedMs - lastFrameMs);
		LOG("Waited for %d", cappedMs - lastFrameMs);
	}

	// Measure accurately the amount of time SDL_Delay() actually waits compared to what was expected
	PERF_PEEK(pTimer);
}

// Call modules before each loop iteration
bool App::PreUpdate()
{
	bool ret = true;

	ListItem<Module*>* item;
	Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if (pModule->active == false)
		{
			continue;
		}

		ret = item->data->PreUpdate();
	}

	return ret;
}

// Call modules on each loop iteration
bool App::DoUpdate()
{
	bool ret = true;
	ListItem<Module*>* item;
	item = modules.start;
	Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if (pModule->active == false)
		{
			continue;
		}

		ret = item->data->Update(dt);
	}

	return ret;
}

// Call modules after each loop iteration
bool App::PostUpdate()
{
	bool ret = true;
	ListItem<Module*>* item;
	Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if (pModule->active == false)
		{
			continue;
		}

		ret = item->data->PostUpdate();
	}

	return ret;
}

// Called before quitting
bool App::CleanUp()
{
	bool ret = true;
	ListItem<Module*>* item;
	item = modules.end;

	while(item != NULL && ret == true)
	{
		ret = item->data->CleanUp();
		item = item->prev;
	}

	return ret;
}

// ---------------------------------------
int App::GetArgc() const
{
	return argc;
}

// ---------------------------------------
const char* App::GetArgv(int index) const
{
	if (index < argc)
	{
		return args[index];
	}
	else
	{
		return NULL;
	}
}

// ---------------------------------------
const char* App::GetTitle() const
{
	return title.GetString();
}

// ---------------------------------------
const char* App::GetOrganization() const
{
	return organization.GetString();
}
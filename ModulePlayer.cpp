#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	position.x = 100;
	position.y = 220;

	// idle animation (arcade sprite sheet)
	idle.PushBack({7, 14, 60, 90});
	idle.PushBack({95, 15, 60, 89});
	idle.PushBack({184, 14, 60, 90});
	idle.PushBack({276, 11, 60, 93});
	idle.PushBack({366, 12, 60, 92});
	idle.speed = 0.2f;

	// walk forward animation (arcade sprite sheet)
	forward.PushBack({9, 136, 53, 83});
	forward.PushBack({78, 131, 60, 88});
	forward.PushBack({162, 128, 64, 92});
	forward.PushBack({259, 128, 63, 90});
	forward.PushBack({352, 128, 54, 91});
	forward.PushBack({432, 131, 50, 89});
	forward.speed = 0.1f;

	// walk backward animation (arcade sprite sheet)
	backward.PushBack({545, 131, 62, 89});
	backward.PushBack({632, 130, 61, 92});
	backward.PushBack({715, 129, 58, 94});
	backward.PushBack({801, 128, 59, 92});
	backward.PushBack({882, 127, 59, 94});
	backward.PushBack({974, 130, 59, 92});
	backward.speed = 0.1f;

	// punch animation (arcade sprite sheet)
	punch.PushBack({19, 272, 64, 92});
	punch.PushBack({109, 272, 97, 92});
	punch.speed = 0.1f;

	// kick (arcade sprite sheet)
	kick.PushBack({604, 270, 62, 95});
	kick.PushBack({692, 266, 68, 95});
	kick.PushBack({778, 265, 117, 97});
	kick.speed = 0.1f;

	// jump upwards (arcade sprite sheet)
	jump_upwards.PushBack({17, 848, 57, 86});
	jump_upwards.PushBack({99, 824, 60, 104});
	jump_upwards.PushBack({174, 804, 56, 100});
	jump_upwards.PushBack({250, 796, 56, 82});
	jump_upwards.PushBack({325, 812, 53, 73});
	jump_upwards.PushBack({395, 808, 53, 93});
	jump_upwards.speed = 0.1f;


	// TODO 4: Make ryu walk backwards with the correct animations
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("ryu.png"); // arcade version
	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	Animation* current_animation = &idle;

	int speed = 1;

	if(App->input->keyboard[SDL_SCANCODE_D] == 1)
	{
		current_animation = &forward;
		position.x += speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_A] == 1)
	{
		current_animation = &backward;
		position.x -= speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_X] == 1)
	{
		current_animation = &punch;
	}

	if (App->input->keyboard[SDL_SCANCODE_Z] == 1)
	{
		current_animation = &kick;
	}

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		current_animation = &jump_upwards;
		int back = 1;
		for (int i = 0; i < back; i++){
			position.y -= speed;
		}
		for (int i = back; i > 0; i--){
			position.y += speed;
			position.x += speed;
		}
	}



	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - r.h, &r);
	
	return UPDATE_CONTINUE;
}
#include <stdio.h>
#include <SDL.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "./constants.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int isRunning = false;
int lastFrameTime = 0;

int difficulty = 0;

asteroid asteroids[48]; //up to 12 total starting asteroids (level 8)
player ship;

vector2 mousePos;

//Calculate vertex positions from relative position, global center position, and rotation
shape calcVertecies(shape vertecies, float r, vector2 center, float size) {
	shape out;

	out.numVertecies = vertecies.numVertecies;

	for (int i = 0; i < vertecies.numVertecies; i++) {
		out.vertecies[i].x = playerSize * size * cos(r) * vertecies.vertecies[i].x + playerSize * size * sin(r) * vertecies.vertecies[i].y + center.x;
		out.vertecies[i].y = playerSize * size * -sin(r) * vertecies.vertecies[i].x + playerSize * size * cos(r) * vertecies.vertecies[i].y + center.y;
	}

	return out;
}

//Setup window and it's parameters
int initializeWindow(void) {
	//Initializes SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error initializing SDL.\n");
		return false;
	}

	//Window variable setup
	window = SDL_CreateWindow(
		"Asteroids", //Window Title
		SDL_WINDOWPOS_CENTERED, //Xpos
		SDL_WINDOWPOS_CENTERED, //Ypos
		defaultWindowWidth, //Width
		defaultWindowHeight, //Height
		SDL_WINDOW_ALLOW_HIGHDPI //Flags
	);

	//Set window to fullscreen
	//SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);

	//Get fullscreen size and set windowWidth/Height to it
	/*SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	windowWidth = DM.w;
	windowHeight = DM.h;*/

	//Checks if window initialized correctly
if (!window) {
	fprintf(stderr, "Error creating SDL Window.\n");
	return false;
}

//Renderer variable setup 
renderer = SDL_CreateRenderer(window, -1, 0);

//Checks if renderer initialized correctly
if (!renderer) {
	fprintf(stderr, "Error creating SDL Renderer.\n");
	return false;
}
}

//Sets up the scene
void setup() {
	//Player variable setup
	ship.pos.x = defaultWindowWidth / 2;
	ship.pos.y = defaultWindowHeight / 2;
	ship.vel.x = 0;
	ship.vel.y = 0;
	ship.shapeType.numVertecies = 4;
	for (int i = 0; i < 4; i++) {
		ship.shapeType.vertecies[i] = shipVertecies[i];
	}
	ship.r = 0;
}

//Takes and processes inputs
int processInput() {
	//Init events
	SDL_Event event;
	SDL_PollEvent(&event);

	//Check if certain keys are pressed
	switch (event.type) {
		//If Exit or Alt+F4 button is pressed
	case SDL_QUIT:
		return false;
		break;
		//If key is pressed
	case SDL_KEYDOWN:
		//If key pressed is Esc
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			return false;
		}
	}

	//Get mouse position
	if (event.type == SDL_MOUSEMOTION) {
		mousePos.x = event.motion.x;
		mousePos.y = event.motion.y;
	}

	//If a key was pressed
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
		//Adjust the input variable
		switch (event.key.keysym.sym) {
		case SDLK_w: ship.input.y -= 1; break;
		case SDLK_s: ship.input.y += 1; break;
		case SDLK_a: ship.input.x -= 1; break;
		case SDLK_d: ship.input.x += 1; break;
		}
	}
	//If a key was released
	else if (event.type == SDL_KEYUP && event.key.repeat == 0) {
		//Adjust the input variable
		switch (event.key.keysym.sym) {
		case SDLK_w: ship.input.y += 1; break;
		case SDLK_s: ship.input.y -= 1; break;
		case SDLK_a: ship.input.x += 1; break;
		case SDLK_d: ship.input.x -= 1; break;
		}
	}


}

//Update objects every frame
void update() {
	//Wait an amount of time until target FPS reached
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), lastFrameTime + targetFrameTime));
	lastFrameTime = SDL_GetTicks();

	//update player velocity
	ship.vel.x += accelFactor * ship.input.x;
	ship.vel.y += accelFactor * ship.input.y;

	if (sqrt(pow(ship.vel.x, 2) + pow(ship.vel.y, 2)) > maxSpeed) {
		ship.vel.x = maxSpeed;
		ship.vel.y = maxSpeed;
	}

	ship.vel.x *= 1-decelFactor;
	ship.vel.y *= 1-decelFactor;

	if (sqrt(pow(ship.vel.x, 2) + pow(ship.vel.y, 2)) < 0.5) {
		ship.vel.x = 0;
		ship.vel.y = 0;
	}

	//update positions
	ship.pos.x += ship.vel.x;
	ship.pos.y += ship.vel.y;

	//printf("(%f, %f) (%f, %f)\n", ship.pos.x, ship.pos.y, ship.vel.x, ship.vel.y);
}

//Tell renderer to show objects on screen
void render() {
	//Draw background
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

	//Clear Screen
	SDL_RenderClear(renderer);

	//Loop through every asteroid
	for (int i = 0; i < 48; i++) {
		//calculate vertecies
		asteroids[i].vertecies = calcVertecies(asteroids[i].shapeType, asteroids[i].r * 3.1415 / 180, asteroids[i].pos, asteroids[i].size/2);

		//set color to white
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		//draw lines
		if (asteroids[i].alive) {
			for (int j = 0; j < asteroids[i].vertecies.numVertecies - 1; j++) {
				SDL_RenderDrawLine(renderer, asteroids[i].vertecies.vertecies[j].x, asteroids[i].vertecies.vertecies[j].y, asteroids[i].vertecies.vertecies[j + 1].x, asteroids[i].vertecies.vertecies[j + 1].y);
			}
			SDL_RenderDrawLine(renderer, asteroids[i].vertecies.vertecies[asteroids[i].vertecies.numVertecies - 1].x, asteroids[i].vertecies.vertecies[asteroids[i].vertecies.numVertecies - 1].y, asteroids[i].vertecies.vertecies[0].x, asteroids[i].vertecies.vertecies[0].y);
		}
	}

	//Do same for player
	vector2 dMousePos = {mousePos.x - ship.pos.x, mousePos.y - ship.pos.y};
	
	//calculate vertecies
	ship.vertecies = calcVertecies(ship.shapeType, -atan2(dMousePos.y,dMousePos.x) + 1.571, ship.pos, 1);

	//set color to white
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	//draw lines
	for (int j = 0; j < ship.vertecies.numVertecies - 1; j++) {
		SDL_RenderDrawLine(renderer, ship.vertecies.vertecies[j].x, ship.vertecies.vertecies[j].y, ship.vertecies.vertecies[j + 1].x, ship.vertecies.vertecies[j + 1].y);
	}
	SDL_RenderDrawLine(renderer, ship.vertecies.vertecies[ship.vertecies.numVertecies - 1].x, ship.vertecies.vertecies[ship.vertecies.numVertecies - 1].y, ship.vertecies.vertecies[0].x, ship.vertecies.vertecies[0].y);

	//Swap buffer frame for current frame (Draws frame)
	SDL_RenderPresent(renderer);
}

//Uninitializes everything in reverse order it initialized it
void destroyWindow() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

//Main function
int main(int argc, char* argv[]) {

	//Set isRunning variable to if window initizalized
	int isRunning = initializeWindow();

	//Set up scene
	setup();

	//Main Game Loop
	while (isRunning) {
		isRunning = processInput();
		update();
		render();
	}

	//If isRunning is false, or loop breaks suddenly, destroy the window and uninitialize everything
	destroyWindow();
}
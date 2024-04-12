#include <stdio.h>
#include <SDL.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "./constants.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int isRunning = false;

//Setup window and it's parameters
int initializeWindow(void) {
	//Initializes SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error initializing SDL.\n");
		return false;
	}

	//Window variable setup
	window = SDL_CreateWindow(
		"Boids", //Window Title
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

void setup() {
	//TODO
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
}

//Update objects every frame
void update() {
	//TODO
}

//Tell renderer to show objects on screen
void render() {
	//Draw background
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

	//Clear Screen
	SDL_RenderClear(renderer);

	//Loop through every boid
	//for (int i = 0; i < numBoids; i++) {
	//	//Calculate boid shape vertecies from position and rotation
	//	calcVertecies(boids, i);

	//	//set vertecies
	//	SDL_Vertex vhead = { {boids[i].shape.head.x,boids[i].shape.head.y}, {boids[i].color.r,boids[i].color.g,boids[i].color.b,255}, {1,1} };
	//	SDL_Vertex vlWing = { {boids[i].shape.lWing.x,boids[i].shape.lWing.y}, {boids[i].color.r,boids[i].color.g,boids[i].color.b,255}, {1,1} };
	//	SDL_Vertex vrWing = { {boids[i].shape.rWing.x,boids[i].shape.rWing.y}, {boids[i].color.r,boids[i].color.g,boids[i].color.b,255}, {1,1} };
	//	SDL_Vertex vtail = { {boids[i].shape.tail.x,boids[i].shape.tail.y}, {boids[i].color.r,boids[i].color.g,boids[i].color.b,255}, {1,1} };

	//	//Put boid shape vertecies into array
	//	SDL_Vertex vertices[] = {
	//		vhead,
	//		vlWing,
	//		vtail,
	//		vrWing
	//	};

	//	//Render boid
	//	const int indices[] = {
	//	   0,1,2,
	//	   2,3,0
	//	};
	//	SDL_RenderGeometry(renderer, NULL, vertices, 4, indices, 6);

	//}

	//Swap buffer frame for current frame (Draws frame)
	SDL_RenderPresent(renderer);
}

//Uninitializes everything in reverse order it initialized it
void destroyWindow() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

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
//Constant Defining!!!
#define false 0
#define true 1

#define defaultWindowWidth 800
#define defaultWindowHeight 600

#define FPS 60
#define targetFrameTime (1000/FPS)

#define playerSize 8
#define maxSpeed 5
#define accelFactor 1
#define decelFactor 0.01

//Variable type that holds 2 dimentional information
typedef struct {
	float x;
	float y;
} vector2;

//Variable type that holds shape type and vertex position data
typedef struct {
	int numVertecies;
	vector2 vertecies[12];
} shape;

//Player "class"
typedef struct {
	vector2 pos;
	vector2 vel;
	vector2 input;
	float r; //rotation
	shape shapeType;
	shape vertecies;
} player;

//Asteroid "class"
typedef struct {
	vector2 pos;
	vector2 vel;
	float r; //rotation
	shape shapeType;
	shape vertecies;
	float size;
	int alive;
} asteroid;

//Bullet "class"
typedef struct {
	vector2 pos;
	vector2 vel;
} boolet;

//vertecies of the ship relative to ship center
vector2 shipVertecies[4] = { 
	{0, 3}, 
	{-3, -3}, 
	{0, -1.5}, 
	{3, -3}};

//vertecies of this type of asteroid relative to asteroid center
vector2 asteroid1Vertecies[11] = {
	{0, -1},
	{0, -3},
	{1, -3},
	{3, -1},
	{3, 1},
	{1, 3},
	{-1, 3},
	{-3, 1},
	{-1, 0},
	{-3, -1},
	{-1, -3}};

//vertecies of this type of asteroid relative to asteroid center
vector2 asteroid2Vertecies[12] = {
	{1, -2},
	{2, -3},
	{3, -1},
	{1, 0},
	{3, 1},
	{3, 2},
	{1, 3},
	{-2, 3},
	{-1, 2},
	{-3, 2},
	{-3, -1},
	{-2, -3}};

//vertecies of this type of asteroid relative to asteroid center
vector2 asteroid3Vertecies[12] = {
	{-1, -2},
	{2, -3},
	{3, -1},
	{2, 0},
	{3, 1},
	{2, 3},
	{0, 2},
	{-1, 3},
	{-3, 2},
	{-2, 0},
	{-3, -1},
	{-2, -3}};
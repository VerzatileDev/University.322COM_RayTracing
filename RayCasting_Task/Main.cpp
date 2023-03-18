#include "stdafx.h" // Pre-Compile Library Headers
#include "SDL/SDL.h"
//#undef main // https://stackoverflow.com/questions/6847360/error-lnk2019-unresolved-external-symbol-main-referenced-in-function-tmainc Defining main in int argc ...  will get rid of the error!
#include "OBJloader.h" // Yeah I'm going to give up here with OBJ loader

#pragma region Primatives.
#include "primatives/Sphere.h"
#include "primatives/Plane.h"
#include "primatives/Triangle.h"
#include "primatives/Shape.h"

// Radius Position colour
Sphere sphereOne(4, glm::vec3(0, 0, -20), glm::vec3(1.00, 0.32, 0.36));
Sphere sphereTwo(2, glm::vec3(5, -1, -15), glm::vec3(0.90, 0.76, 0.46)); // Yellow Sphere
Sphere sphereThree(3, glm::vec3(5, 0, -25), glm::vec3(0.65, 0.77, 0.97)); // Light Blue
Sphere sphereFour(3, glm::vec3(-5.5, 0, -15), glm::vec3(0.90, 0.90, 0.90)); // Light gray
Plane plane(glm::vec3(0, -10004, -20), glm::vec3(0.2, 0.2, 0.2), glm::vec3(0.0, 1.0, 0.0)); // Gray Floor             Normal 1
Triangle triangle(glm::vec3(0.9, 1.0, 0.2), glm::vec3(0, 1, -2), glm::vec3(-1.9, -1, -2), glm::vec3(1.6, -0.5, -2), glm::vec3(0.0, 0.6, 1.0), glm::vec3(0.0, 0.6, 1.0), glm::vec3(0.4, -0.4, 1.0)); // Color, point1, p2, p3

#pragma endregion

// Image Aspect Ratio
const int WIDTH = 640;
const int HEIGHT = 480;

SDL_Event event; // Creates  New window event

bool initSDL(SDL_Window*& window, SDL_Surface*& screenSurface)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}
	else
	{
		// Create Tabbed Window
		window = SDL_CreateWindow("Ray-Tracing Application", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			std::cout << "SDL Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
			return false;
		}
		else
		{
			screenSurface = SDL_GetWindowSurface(window);
			return true;
		}
	}
};

/* LOOKS FOR A call in closing window Event */
void closeSDL(SDL_Window*& window)
{
	SDL_DestroyWindow(window);
	SDL_Quit();
};


// Convert Colours to an RBG variant (SDL)
Uint32 convertColour(glm::vec3 colour)
{
	int tt;
	Uint8 r, g, b;

	tt = (int)(colour.r * 255);
	if (tt <= 255) r = tt; else r = 255;
	tt = (int)(colour.g * 255);
	if (tt <= 255) g = tt; else g = 255;
	tt = (int)(colour.b * 255);
	if (tt <= 255) b = tt; else b = 255;

	Uint32 rgb;

	//check which order SDL is storing bytes
	rgb = (r << 16) + (g << 8) + b;

	return rgb;
};

// Displays pixel on the screen
void PutPixel32_nolock(SDL_Surface*& surface, int x, int y, Uint32 colour)
{
	Uint8* pixel = (Uint8*)surface->pixels;
	pixel += (y * surface->pitch) + (x * sizeof(Uint32));
	*((Uint32*)pixel) = colour;
};

//Object Load
//const char* file_name = "objects/House.obj";
//std::vector<VertexWithAll> vertices = loadOBJ(file_name);


int main(int argc, char* args[])
{
	// View Properties.
	float 
	NormalizedPixelx, 
	NormalizedPixely,
	RemappedPixelx, 
	RemappedPixely, 
	PictureAspectRatio, 
	TangentValue, 
	PCameraX, 
	PCameraY;

#pragma region SDL Setup
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	if (!initSDL(window, screenSurface))
	{
		std::cout << " Failed To Initialize SDL Window " << std::endl;
		return -1;
	}
	
	// Store/ create Image into memory.
	glm::vec3** image = new glm::vec3 * [WIDTH];
	for (int i = 0; i < WIDTH; i++)
	{
		image[i] = new glm::vec3[HEIGHT];
	}
	std::cout << " The Application Dimensions are " << WIDTH << " By " << HEIGHT << std::endl;
	std::cout << " Press ' Esc ' to Close " << std::endl;
#pragma endregion

#pragma region Data storage
	PictureAspectRatio = WIDTH / (float)HEIGHT;
	TangentValue = tanf(0.261799387); // 15 *  PI / 180 = 0.26179938779916666666666666666667
	float t, min_t;
	int pixelSelect; // Defines if pixel is empty or filled then checks color
	glm::vec3 rayDirection(0, 0, 0); // Must be Normalized
	glm::vec3 rayOrigin(0, 0, 20); // Camera Location
	std::vector<float> t_arr;
	std::vector<glm::vec3> color_array;
	std::vector<glm::vec3> IntPt_array;
	std::vector<glm::vec3> CenPT_array;
	glm::vec3 tempPos;

	// Properties for the Image Background
	glm::vec3 upper_left_corner(2.0, 1.0, 1.0); // Of the Screen
	glm::vec3 horizontal(-4.0, -0.0, -0.0);
	glm::vec3 vertical(-0.0, -2.0, -0.0);
	glm::vec3 pointB;
	glm::vec3 pointBColor;

	// Shading Properties
	glm::vec3 tNormvec, IntPt;
	float ColValue;
	glm::vec3 ambientIntesity(0.1, 0.1, 0.1);
	glm::vec3 lightPt(0.0f, 20.0f, 0.0f);
	glm::vec3 finalColor(1.0f, 1.0f, 1.0f);
#pragma endregion

#pragma region Virtual Method Intances
	Sphere newSphereShape;
	Plane newPlaneShape;
	Triangle newTriangleShape;

	Shape* shapes[3];
	shapes[0] = &newSphereShape;
	shapes[1] = &newPlaneShape;
	shapes[2] = &newTriangleShape;


#pragma endregion

	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			t_arr.clear();
			color_array.clear();

			// Define correct pixel position using Screen Dimesions In the range of [0:1]
			NormalizedPixelx = (x + 0.5) / (float)WIDTH; // u
			NormalizedPixely = (y + 0.5) / (float)HEIGHT; // v

			// Remap (x,y) coordinates
			RemappedPixelx = 2 * NormalizedPixelx - 1.0; // remappedx = (2* normalizedx - 1)
			RemappedPixelx *= PictureAspectRatio; // remappedx * PaR
			
			// Coordinate Range Y AXIS
			RemappedPixely = 1.0 - (2 * NormalizedPixely); // mappedy = 1.0 - 2 * normpixely

			// Field of view
			PCameraX = RemappedPixelx * TangentValue;
			PCameraY = RemappedPixely * TangentValue;

			rayDirection = glm::normalize(glm::vec3(PCameraX, PCameraY, -1.0f));
			
			/* ! INTERSECTIONS ! */
			if (shapes[0]->IntersectionOfSphere(sphereOne.GetPosition(), sphereOne.GetRadius(), rayOrigin, rayDirection, t, IntPt))
			{
				t_arr.push_back(t);
				//ShapeSphere->ComputeColor(ambientIntesity, IntPt, lightPt, rayDirection, ColValue); // Official way of doing Shading (Doesn't work)
				IntPt_array.push_back(IntPt);
				CenPT_array.push_back(sphereOne.GetPosition());
				color_array.push_back(sphereOne.GetColor());
			}
			if (shapes[0]->IntersectionOfSphere(sphereTwo.GetPosition(), sphereTwo.GetRadius(), rayOrigin, rayDirection, t, IntPt))
			{
				t_arr.push_back(t);
				IntPt_array.push_back(IntPt);
				CenPT_array.push_back(sphereTwo.GetPosition());
				color_array.push_back(sphereTwo.GetColor());
			}
			if (shapes[0]->IntersectionOfSphere(sphereThree.GetPosition(), sphereThree.GetRadius(), rayOrigin, rayDirection, t, IntPt))
			{
				t_arr.push_back(t);
				IntPt_array.push_back(IntPt);
				CenPT_array.push_back(sphereThree.GetPosition());
				color_array.push_back(sphereThree.GetColor());
			}
			if (shapes[0]->IntersectionOfSphere(sphereFour.GetPosition(), sphereFour.GetRadius(), rayOrigin, rayDirection, t, IntPt))
			{
				t_arr.push_back(t);
				IntPt_array.push_back(IntPt);
				CenPT_array.push_back(sphereFour.GetPosition());
				color_array.push_back(sphereFour.GetColor());
			}
			
			if (shapes[1]->IntersectionOfPlane(plane.getCenter(), rayOrigin, rayDirection, plane.getNormal(), t))
			{
				t_arr.push_back(t);
				color_array.push_back(plane.getColor());
			}
		
			// Do not Give vertexpoints values under 0 or over 2 !!
			if (shapes[2]->IntersectionOfTriangle(rayDirection, rayOrigin, triangle.GetVertexPoint(0), triangle.GetVertexPoint(1), triangle.GetVertexPoint(2), t, IntPt, tNormvec))
			{
				t_arr.push_back(t);
				
				//  ShapeTriangle->ComputeTriangleColor(ambientIntesity, IntPt, lightPt, rayDirection, tNormvec, ColValue);
				//	IntPt_array.push_back(IntPt);
				color_array.push_back(triangle.GetColor());
			}

			
#pragma region Background Calculation Specificaitons
			// Based on the Direction, define the color
			pointB = upper_left_corner + NormalizedPixelx * horizontal + NormalizedPixely * vertical;
			float temporary = 0.9 * (pointB.y + 1.0);
			float temporary1 = 1.0 - temporary;
			pointBColor = temporary1 * glm::vec3(1.0, 1.0, 1.0) + temporary * glm::vec3(0.5, 0.7, 1.0);
#pragma endregion

			/* ! COLOUR DEFINITIONS !*/
			if (t_arr.size() == 0)
			{
				// Background
				image[x][y].x = 1.0 * pointBColor.x;
				image[x][y].y = 1.0 * pointBColor.y;
				image[x][y].z = 1.0 * pointBColor.z;
				PutPixel32_nolock(screenSurface, x, y, convertColour(image[x][y]));
			}
			else
			{
				min_t = 1000.0f;
				pixelSelect = 0;
				for (int i = 0; i < t_arr.size(); i++)
				{
					if (t_arr[i] < min_t) 
					{
						pixelSelect = i;
						//std::cout << t_arr.size() << std::endl;
						min_t = t_arr[i]; 
					}
				}
				//std::cout << pixelSelect << std::endl; // Debug
				//IntPt = IntPt_array[pixelSelect];
				//tempPos = CenPT_array[pixelSelect];
				
				
				IntPt = rayOrigin + min_t * rayDirection;
				glm::vec3 normal = glm::normalize(IntPt - sphereOne.GetPosition()); // HardCoded for only one Sphere Location
				glm::vec3 lightDirection = glm::normalize(lightPt - IntPt); // Light point - Intersection Point. (Normalized)
				float diffuse = glm::max(glm::dot(normal, lightDirection), 0.0f); // Diffuse Lighting
				// Ambient Intensity in Properties!
				glm::vec3 ambientColor = ambientIntesity * color_array[pixelSelect]; // Applies colors from objects.
				glm::vec3 diffuseColor = diffuse * color_array[pixelSelect];
				glm::vec3 specularColor = glm::vec3(0.0f);
				finalColor = ambientColor + diffuseColor + specularColor;


				image[x][y] = finalColor; // Writes Color Values to Pixel.
				PutPixel32_nolock(screenSurface, x, y, convertColour(image[x][y]));
			}
		}
	}
	SDL_UpdateWindowSurface(window);
	bool quit = false;
	while (!quit)
	{
		//Keyboard Input
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
				quit = true;
			}
		}
	}

	closeSDL(window);
	return 0;
}
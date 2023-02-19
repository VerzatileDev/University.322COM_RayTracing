#include "stdafx.h" // Pre-Compiled Library stuff.
// Primatives.
#include "Sphere.h"

// After doing it again I stil have no idea what this is all about. 
void step1()
{
	glm::vec3 v1(1, 2, 3);
	glm::vec3 v2(3, 4, 5);
	glm::vec3 v3 = v1 + v2;
	std::cout << "v1 " << "[" << v1.x << " " << v1.y << " " << v1.z << "]" << std::endl;
	std::cout << "v2 " << "[" << v2.x << " " << v2.y << " " << v2.z << "]" << std::endl;
	std::cout << "v3 " << "[" << v3.x << " " << v3.y << " " << v3.z << "]" << std::endl;
}

int main()
{
	// Define Image Aspect Ratio
	const int WIDTH = 640;
	const int HEIGHT = 480;

	// View Plane Array Defined Properties.
	// See Reference material to these functions!
	float 
	NormalizedPixelx, 
	NormalizedPixely,
	RemappedPixelx, 
	RemappedPixely, 
	PictureAspectRatio, 
	TangentValue, 
	PCameraX, 
	PCameraY;

	// Store/ create Image into mememory.
	glm::vec3** image = new glm::vec3 * [WIDTH];
	for (int i = 0; i < WIDTH; i++)
	{
		image[i] = new glm::vec3[HEIGHT];
	}

	PictureAspectRatio = WIDTH / (float)HEIGHT;
	TangentValue = tanf( PI / 180.0);


	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			// Further change
			/*if (x < 320)
			{
				image[x][y].x = 255;
				image[x][y].y = 100;
				image[x][y].z = 0;
			}
			else
			{
				image[x][y].x = 0;
				image[x][y].y = 100;
				image[x][y].z = 255;
			}*/

			// Define correct pixel position using Screen Dimesions In the range of [0:1]
			NormalizedPixelx = (x + 0.5) / (float)WIDTH;
			NormalizedPixely = (y + 0.5) / (float)HEIGHT;

			// Remap the coordinates
			RemappedPixelx = 2 * NormalizedPixelx - 1.0;
			RemappedPixelx *= PictureAspectRatio; //Par
			// According to documentation. remappedx = (2* normalizedx - 1)
			// remappedx * PaR
			

			// Coordinate Range
			// mappedy = 1.0 - 2 * normpixely
			RemappedPixely = -1 * NormalizedPixely;
			

			// Define Field of view
			PCameraX = RemappedPixelx * TangentValue / 2; // tangent(Alpha / 2 )
			PCameraY = RemappedPixely * TangentValue / 2;

			// Tells us which colour is used within the pixel coordinate
			image[x][y].x = PCameraX;
			image[x][y].y = PCameraY;
			image[x][y].z = -1.0;
		}
	}


	// Save result As a PPM image (Opened with Photoshop File)
	// Replaced in Further Pushes!
	std::ofstream ofs("./RenderedPicture.ppm", std::ios::out | std::ios::binary);
	ofs << "P6\n" << WIDTH << " " << HEIGHT << "\n255\n";
	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			ofs << (unsigned char)(std::min((float)1, (float)image[x][y].x) * 255) <<
				(unsigned char)(std::min((float)1, (float)image[x][y].y) * 255) <<
				(unsigned char)(std::min((float)1, (float)image[x][y].z) * 255);
		}
	}
	ofs.close();
	return 0;
}
#include "stdafx.h" // Pre-Compile Library Headers

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
Plane plane(glm::vec3(0, -10004, -20), glm::vec3(0.2, 0.2, 0.2), glm::vec3(0.0, 1.0, 0.0)); // Gray Floor
Triangle triangle(glm::vec3(0.9, 1.0, 0.2), glm::vec3(0, 1, -2), glm::vec3(-1.9, -1, -2), glm::vec3(1.6, -0.5, -2));

#pragma endregion

#pragma region References
/* 
* https://www.scratchapixel.com/lessons/mathematics-physics-for-computer-graphics/mathematics-of-shading/mathematics-of-shading.html Shading
* https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/definition-ray.html Ray Definition ( t , tMin, Tmax )
* https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays.html Camera Rays / Intersections
* https://www.ibm.com/docs/en/zvm/7.2?topic=arithmetic-exponential-notation Exponential Notation
* http://freesourcecode.net/cprojects/109969/sourcecode/stdafx.h#.Y_LbcmnP3b2 Stdafx.h
*/
#pragma endregion


int main()
{
	// Image Aspect Ratio
	const int WIDTH = 640;
	const int HEIGHT = 480;

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

	// Store/ create Image into memory.
	glm::vec3** image = new glm::vec3 * [WIDTH];
	for (int i = 0; i < WIDTH; i++)
	{
		image[i] = new glm::vec3[HEIGHT];
	}

#pragma region Data storage
	PictureAspectRatio = WIDTH / (float)HEIGHT;
	TangentValue = tanf(0.261799387); // 15 *  PI / 180 = 0.26179938779916666666666666666667
	float t, min_t;
	int pixelSelect; // Defines if pixel is empty or filled then checks color
	glm::vec3 rayDirection(0, 0, 0); // Must be Normalized
	glm::vec3 rayOrigin(0, 0, 20); // Camera Location
	std::vector<float> t_arr;
	std::vector<glm::vec3> color_array;
#pragma endregion


#pragma region Virtual Method Intances
	Shape* ShapeSphere;
	Sphere newSphereShape;
	ShapeSphere = &newSphereShape;

	Shape* ShapePlane;
	Plane newPlaneShape;
	ShapePlane = &newPlaneShape;

	Shape* ShapeTriangle;
	Triangle newTriangleShape;
	ShapeTriangle = &newTriangleShape;
#pragma endregion

	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			t_arr.clear();
			color_array.clear();

			// Define correct pixel position using Screen Dimesions In the range of [0:1]
			NormalizedPixelx = (x + 0.5) / (float)WIDTH;
			NormalizedPixely = (y + 0.5) / (float)HEIGHT;

			// Remap (x,y) coordinates
			RemappedPixelx = 2 * NormalizedPixelx - 1.0; // remappedx = (2* normalizedx - 1)
			RemappedPixelx *= PictureAspectRatio; // remappedx * PaR
			
			// Coordinate Range
			RemappedPixely = 1.0 - (2 * NormalizedPixely); // mappedy = 1.0 - 2 * normpixely

			// Field of view
			PCameraX = RemappedPixelx * TangentValue;
			PCameraY = RemappedPixely * TangentValue;

			rayDirection = glm::normalize(glm::vec3(PCameraX, PCameraY, -1.0f));
			
			

			/* ! INTERSECTIONS ! */
			if (ShapeSphere->IntersectionOfSphere(sphereOne.GetPosition(), sphereOne.GetRadius(), rayOrigin, rayDirection, t))
			{
				t_arr.push_back(t);
					color_array.push_back(sphereOne.GetColor());
			}

			if (ShapeSphere->IntersectionOfSphere(sphereTwo.GetPosition(), sphereTwo.GetRadius(), rayOrigin, rayDirection, t))
			{
				t_arr.push_back(t);
				color_array.push_back(sphereTwo.GetColor());
			}

			if (ShapeSphere->IntersectionOfSphere(sphereThree.GetPosition(), sphereFour.GetRadius(), rayOrigin, rayDirection, t))
			{
				t_arr.push_back(t);
				color_array.push_back(sphereThree.GetColor());
			}

			if (ShapeSphere->IntersectionOfSphere(sphereFour.GetPosition(), sphereFour.GetRadius(), rayOrigin, rayDirection, t))
			{
				t_arr.push_back(t);
				color_array.push_back(sphereFour.GetColor());
			}
			
			if (ShapePlane->IntersectionOfPlane(plane.getCenter(), rayOrigin, rayDirection, plane.getNormal() , t))
			{
				t_arr.push_back(t);
				color_array.push_back(plane.getColor());
			}

			// Do not Give vertexpoints values under 0 or over 2 :D Kills PC!
			if (ShapeTriangle->IntersectionOfTriangle(rayDirection, rayOrigin, triangle.GetVertexPoint(0), triangle.GetVertexPoint(1), triangle.GetVertexPoint(2), t))
			{
				t_arr.push_back(t);
				color_array.push_back(triangle.GetColor());
			}

			
			/* ! COLOuR DEFINITIONS !*/
			if (t_arr.size() == 0)
			{
				image[x][y].x = 1.0;
				image[x][y].y = 1.0;
				image[x][y].z = 1.0;
			}
			else
			{
				min_t = 1000.0f;
				pixelSelect = 0;
				for (int i = 0; i < t_arr.size(); i++)
				{
					if (t_arr[i] < min_t) { pixelSelect = i; min_t = t_arr[i]; }
				}
				image[x][y].x = color_array[pixelSelect].x;
				image[x][y].y = color_array[pixelSelect].y;
				image[x][y].z = color_array[pixelSelect].z;
			}
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
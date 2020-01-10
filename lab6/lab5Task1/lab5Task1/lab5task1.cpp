#include <iostream>
#include <math.h>
#include "lab5task1.h"
#include <ctime>
#include <math.h>
#include <SDL.h>
#include <stdlib.h>

#define SDL_MAIN_HANDLED
using namespace std;



Point2D::Point2D(float xValue, float yValue) {
	x = xValue;
	y = yValue;
}

Point2D::Point2D(Point2D& o) {
	x = o.x;
	y = o.y;
}

Point2D::Point2D() {
	x = 0;
	y = 0;
};

void Point2D::newPoint(float xValue, float yValue) {
	x = xValue;
	y = yValue;
}
double Point2D::distance(Point2D point2) {
	float distance, deltaX = x - point2.x, deltaY = y - point2.y;
	distance = pow(deltaX, 2) + pow(deltaY, 2);
	return sqrt(distance);
}


void Shape::printRGB()
{
	cout << "r:" << rgb[0] << " g:" << rgb[1] << " b:" << rgb[2] << " alpha:" << rgb[3] << endl;
}

void Shape::setRGB(int r, int g, int b, int alpha)
{
	if (r > 255 || r < 0)
	{
		rgb[0] = 255;
	}
	else
	{
		rgb[0] = r;
	}
	if (g > 255 || g < 0)
	{
		rgb[1] = 255;
	}
	else
	{
		rgb[1] = g;
	}
	if (b > 255 || b < 0)
	{
		rgb[2] = 255;
	}
	else
	{
		rgb[2] = b;
	}
	if (alpha < 0 || alpha > 1 )
	{
		rgb[3] = 1;
	}
	else
	{
		rgb[3] = alpha;
	}
}

void Shape::setPoint(float x, float y)
{
	if (float (-999 < x < 999) && float (-999 < y < 999) )
	{
		line.newPoint(x, y);
	}
	else
	{
		cout << "the point you've set was out of range. Setting point to (0 , 0)" << endl;
	}
}

Shape::Shape(float x, float y, float r, float g, float b, float alpha) {
	setPoint(x,y);
	setRGB(r, g, b, alpha);
}

Shape::Shape()
{
	setPoint(0, 0);
	setRGB(255, 255, 255, 1);
}

int Shape::returnRGB(int index) {
	return rgb[index];
}

void Shape::render(SDL_Renderer* renderer)
{
}

Rectangle_Shape::Rectangle_Shape(float xValue, float yValue, float rectBase, float rectHeight, int r, int g, int b, int alpha) : base(rectBase), height(rectHeight), Shape(xValue, yValue, r, g, b, alpha)  {  }

Rectangle_Shape::Rectangle_Shape() : base(0), height(0), Shape() {  }

	void Rectangle_Shape::render(SDL_Renderer * renderer) {
		int rectangle[4] = { line.x, line.y, line.x + base, line.y + height };
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, returnRGB(0), returnRGB(1), returnRGB(2), 255);
		SDL_RenderDrawLine(renderer, rectangle[0], rectangle[1], rectangle[2], rectangle[1]);
		SDL_RenderDrawLine(renderer, rectangle[2], rectangle[1], rectangle[2], rectangle[3]);
		SDL_RenderDrawLine(renderer, rectangle[2], rectangle[3], rectangle[0], rectangle[3]);
		SDL_RenderDrawLine(renderer, rectangle[0], rectangle[3], rectangle[0], rectangle[1]);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
	}



Triangle::Triangle(float xValue, float yValue, float triBase, float triHeight, int r, int g, int b, int alpha) : base(triBase), height(triHeight), Shape(xValue, yValue, r, g, b, alpha) { }

Triangle::Triangle() : base(), height(), Shape() { }


void Triangle::render(SDL_Renderer* renderer) {
	int triangle[5] = { line.x, line.y, line.x + base, line.x / 2, line.y + height};
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, returnRGB(0), returnRGB(1), returnRGB(2), 255);
	SDL_RenderDrawLine(renderer, triangle[0], triangle[1], triangle[2], triangle[1]);
	SDL_RenderDrawLine(renderer, triangle[2], triangle[1], triangle[3], triangle[4]);
	SDL_RenderDrawLine(renderer, triangle[3], triangle[4], triangle[0], triangle[1]);
	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);
}

Circle::Circle(float xValue, float yValue, float circleRadius, int r, int g, int b, int alpha) : radius(circleRadius), Shape(xValue, yValue, r, g, b, alpha) { };
Circle::Circle() : radius(), Shape() { };

void Circle::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, returnRGB(0), returnRGB(1), returnRGB(2), 255);
	
	int theta = 0; // angle that will be increased each loop
	float h = line.x; // x coordinate of circle center
	float k = line.y; // y coordinate of circle center
	int step = 1; // amount to add to theta each time (degrees)
	int circleX, circleY;
	while (theta <= 360)
	{
			circleX = h + radius * cos(theta);
			circleY = k + radius * sin(theta);
			SDL_RenderDrawLine(renderer, h, k, circleX, circleY);
			theta += step;
			SDL_RenderPresent(renderer);
	}
	
}


Scoreboard::Scoreboard()
{
	for (int i = 0; i < 3; i++)
	{
		scoreArr[i] = 999;
	}
}

Scoreboard::~Scoreboard()
{
	for (int i = 0; i < 3; i++)
	{
		scoreArr[i] = NULL;
	}
	delete[] scoreArr;
}

void Scoreboard::addToScoreboard(float score)
{
	bool beenAdded = false;
	for (size_t i = 0; i < 3; i++)
	{
		if (score < scoreArr[i] && beenAdded == false && score != scoreArr[i])
		{
			if (i != 3 && score > scoreArr[i+1] && scoreArr[i-1] != scoreArr[i] )
			{


				scoreArr[i+1] = score;
				beenAdded = true;
				addToScoreboard(scoreArr[i + 1]);
			}
			else
			{
				scoreArr[i] = score;
				beenAdded = true;
			}
		}

	}
}
void Scoreboard::printScoreboard()
{
	for (int i = 0; i < 3; i++)
	{
		if (scoreArr[i] == 999) // if it's the default value  it prints "----"
		{
			cout << "----" << endl;
		}
		else
		{
			cout << scoreArr[i] << endl;
		}
	}

}

int main(int argc, char* args[]) {
	bool quit = false;
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_SetMainReady();
	SDL_Event event;
	const Uint8* keys = SDL_GetKeyboardState(NULL);
	SDL_Event e;
	SDL_Window* window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	
	int j = 0, playAgain = 2;
	float r = 0, b = 0, time = 0, totalTime = 0; // totalTime is total previous time i.e totaltime not including current time
	bool running = true, redTriangle = false, redRectangle = false, blueTriangle = false, blueRectangle = false, flag = false,  scoreBeenSet = false;
	Shape* shapeArray[2];
	Scoreboard board; // scoreboard
	
	while (j <= 10)
	{
		if (SDL_PollEvent(&event)) // inputs for the game
		{
			switch (event.type) {
			case SDL_QUIT:
				break;
			case SDL_KEYDOWN:

				switch (event.key.keysym.sym)
				{
				case SDLK_n: if (j == 10) { playAgain = 0; }
				}
				
				switch (event.key.keysym.sym)
				{
				case SDLK_y: if (j == 10) { playAgain = 1; }
				}
				
				switch (event.key.keysym.sym)
				{
				case SDLK_q: quit = true; break; SDL_DestroyRenderer(renderer); SDL_DestroyWindow(window); SDL_Quit();
				}

				switch (event.key.keysym.sym)
				{
				case SDLK_z: if (redRectangle == true) { running = true; redRectangle = false; } //continues to next shapes and stops the clock
				}
				
				switch (event.key.keysym.sym)
				{
				case SDLK_x: if (redTriangle == true) { running = true; redTriangle = false; }
				}
				
				switch (event.key.keysym.sym)
				{
				case SDLK_c: if (blueRectangle == true) { running = true; blueRectangle = false; }
				}

				
				switch (event.key.keysym.sym)
				{
				case SDLK_v: if (blueTriangle == true) { running = true; blueTriangle = false; }
				}
			
			}
		};
		while (j >= 10)
		{

		
	if (j >= 10)
		{
			if (SDL_PollEvent(&event))
			{
				switch (event.type) {
				case SDL_QUIT:
					break;
				case SDL_KEYDOWN:

					switch (event.key.keysym.sym)
					{
					case SDLK_q: if (j >= 10) { playAgain = 0; }
					}

					switch (event.key.keysym.sym)
					{
					case SDLK_y: if (j >= 10) { playAgain = 1; }
					}
					
					switch (event.key.keysym.sym)
					{
					case SDLK_p: if (j >= 10) {
						board.printScoreboard();
					}
					}
				}
			}
			if (flag == false)
			{
				Circle cir(200, 200, 200, 255, 0, 255, 1); shapeArray[1] = &cir; shapeArray[1]->render(renderer);
				if (totalTime == 0) // special case for first run
				{
					cout << "your time: " << time << endl;
					board.addToScoreboard(time);
				}
				else
				{
					cout << "your time: " <<  time - totalTime << endl;
					board.addToScoreboard(time - totalTime);
				}
				
				
				cout << "play again [y]" << endl << "quit [q]" << endl << "print this sessions highscores [p]" << endl;
				flag = true;
			}
			if (playAgain == 1)
			{
				
				j = 0;
				playAgain = 2;
				flag = false;
				running = true;
				if (totalTime == 0)
				{
					totalTime = totalTime + time;
				}
				else
				{
					totalTime = totalTime + (time - totalTime);
				}
				break;
			}

			if (playAgain == 0)
			{
				quit = true;
				SDL_DestroyRenderer(renderer);
				SDL_DestroyWindow(window);
				SDL_Quit();
				for (int i = 0; i < 2; i++)	//sets the shapes to nullptrs
				{
					shapeArray[i] = nullptr;
				}
				delete shapeArray;
				board.~Scoreboard();
			}

		}
		}
		if (running == false)
		{
			time = SDL_GetTicks();
			time = time / 1000; // converting ticks to seconds
		}
		
		while (running == true) //randomizes shapes and colours
		{
		
			float x = rand() % 400 + 1, y = rand() % 400 + 1;
			int randomizedShape = rand() % 100 + 1;
			
			

			if (randomizedShape % 2 == 0) // if randomized number is divisible by 2 colour = red
			{
				float r = 255, b = 0;

				if (randomizedShape <= 50) // if randomized number is less or equal to 50 , becomes a red rectangle
				{
					running = false;
					redRectangle = true;
					Rectangle_Shape rect(x, y, 200, 200, r, 0, b, 1); shapeArray[0] = &rect; shapeArray[0]->render(renderer);
					j++;
					break;
				}
				if (randomizedShape > 50) // if randomized number is more than 50 it becames a red triangle
				{
					
					running = false;
					redTriangle = true;
					Triangle tri(x, y, 200, 200, r, 0, b, 1); shapeArray[1] = &tri; shapeArray[1]->render(renderer);
					j++;
					break;
					
				}

			}
			if (randomizedShape % 2 != 0) // shapes colour becomes blue
			{
				float r = 0, b = 255;

				if (randomizedShape <= 50) // becomes blue rectangle
				{
					running = false;
					blueRectangle = true;
					Rectangle_Shape rect(x, y, 200, 200, r, 0, b, 1); shapeArray[0] = &rect; shapeArray[0]->render(renderer);
					j++;
					break;
				}
				if (randomizedShape > 50) // becomes blue triangle 
				{
					
					running = false;
					blueTriangle = true;
					Triangle tri(x, y, 200, 200, r, 0, b, 1); shapeArray[1] = &tri; shapeArray[1]->render(renderer);
					j++;
					break;

				}

			}

			
				

			
		}
		
	};
	
	return 0;
}


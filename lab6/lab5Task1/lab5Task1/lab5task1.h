#pragma once
#include <SDL.h>
#include <ctime>
#ifndef lab5task1
#define lab5task1
using namespace std;
class Point2D {
public:
	float x, y;
	Point2D(float xValue, float yValue); 
	Point2D(Point2D& o);
	Point2D();
	void newPoint(float xValue, float yValue);
	double distance(Point2D point2);

};

class Shape: public Point2D {
private:
	int  rgb[4] = {};
public:
	Point2D line;
	void printRGB();
	void setRGB(int r, int g, int b, int alpha);
	void setPoint(float x, float y);
	int returnRGB(int index);
	virtual void render(SDL_Renderer* renderer);
	Shape(float x, float y, float r, float g, float b, float alpha);
	Shape();
};

class Rectangle_Shape : public Shape {
private: 
	float base, height;

public:
	Rectangle_Shape(float xValue, float yValue, float rectBase, float rectHeight, int r, int g, int b, int alpha);
	Rectangle_Shape();
	void render(SDL_Renderer *renderer);
};

class Triangle : public Shape {
private:
	float base, height;

public:
	Triangle(float xValue, float yValue, float rectBase, float rectHeight, int r, int g, int b, int alpha);
	Triangle();
	void render(SDL_Renderer* renderer);
};

class Circle : public Shape {
private:
	float radius;
public:
	Circle(float xValue, float yValue, float circleRadius, int r, int g, int b, int alpha);
	Circle();
	void render(SDL_Renderer* renderer);
};

class Scoreboard {
private:
	float* scoreArr = new float[3];
public:
	Scoreboard();
	~Scoreboard();
	void addToScoreboard(float score);
	void printScoreboard();
};
#endif // !lab5task1

#ifndef TETRO_HPP_INCLUDED
#define TETRO_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <time.h>



using namespace sf;

extern int figures[7][4];

extern const int M;
extern const int N;

extern int field[20][10];

extern struct Point
{
  int x, y;
} a[4], b[4];




bool check();

struct Tetrominoes{
	
	
	
	void movement(int dx);
	
	void rotation(bool rotate);
	
	void ticking(float & timer, float & delay, int & colorNum);
	
	void lineCheck();
	
	
	




};

#endif
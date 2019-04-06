#include "tetro.hpp"

using namespace sf;

bool
check()
{
  for (int i = 0; i < 4; i++)
    if (a[i].x < 0 || a[i].x >= N || a[i].y >= M)
      return 0;
    else if (field[a[i].y][a[i].x])
      return 0;

  return 1;
};


void Tetrominoes::movement(int dx)
		{
		//// <- Move -> ///
		for (int i = 0; i < 4; i++) {
		  b[i] = a[i];
		  a[i].x += dx;
		}
		if (!check())
		  for (int i = 0; i < 4; i++)
			a[i] = b[i];
	}
	
	void Tetrominoes::rotation(bool rotate)
	{
		//////Rotate//////
		if (rotate) {
		  Point p = a[1]; // center of rotation
		  for (int i = 0; i < 4; i++) {
			int x = a[i].y - p.y;
			int y = a[i].x - p.x;
			a[i].x = p.x - x;
			a[i].y = p.y + y;
		  }
		  if (!check())
			for (int i = 0; i < 4; i++)
			  a[i] = b[i];
		}
	}
	
	void Tetrominoes::ticking(float & timer, float & delay, int & colorNum)
	{
		    ///////Tick//////
			int gover = a[0].y;
		if (timer > delay) {
		  for (int i = 0; i < 4; i++) {
			b[i] = a[i];
			a[i].y += 1;
		  }

		  if (!check()) {

			  
			for (int i = 0; i < 4; i++)
			  field[b[i].y][b[i].x] = colorNum;

			colorNum = 1 + rand() % 8;
			int n = rand() % 7;
			for (int i = 0; i < 4; i++) {
			  a[i].x = figures[n][i] % 2;
			  a[i].y = figures[n][i] / 2;
			}
		  }

		  timer = 0;
		}

	}
	
	void Tetrominoes::lineCheck(bool & ender)
	{
		///////check lines//////////
		int k = M - 1;
		for (int i = M - 1; i > 0; i--) {
		  int count = 0;
		  for (int j = 0; j < N; j++) {
			if (field[i][j])
			  count++;
			field[k][j] = field[i][j];
		  }
		  if (count < N)
			k--;
		}
		
		if (field[0][N])	//Game Over causes window to close
		{
			ender = true;
		}

	}
	
	

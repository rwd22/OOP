#include <SFML/Graphics.hpp>
#include <time.h>

#include "tetro.hpp"



using namespace sf;


 int figures[7][4] = {	//layout of pices
  1, 3, 5, 7, // I
  2, 4, 5, 7, // Z
  3, 5, 4, 6, // S
  3, 5, 4, 7, // T
  2, 3, 5, 7, // L
  3, 5, 7, 6, // J
  2, 3, 4, 5, // O
};

 const int M = 20;
 const int N = 10;

 int field[20][10] = { 0 };

Point a[4], b[4];

int
main()
{
	
	Tetrominoes tetrom;
	
  srand(time(0));

  RenderWindow window(VideoMode(320, 480), "The Game!");

  Texture t1, t2, t3;
  t1.loadFromFile("images/tiles.png");
  t2.loadFromFile("images/background.png");
  t3.loadFromFile("images/frame.png");

  Sprite s(t1), background(t2), frame(t3);

  int dx = 0;
  bool rotate = 0;
  int colorNum = 1;
  float timer = 0, delay = 0.3;
  int checker =0;
  bool gmOvr = false;

  Clock clock;

  while (window.isOpen() && gmOvr == false) {
    float time = clock.getElapsedTime().asSeconds();
    clock.restart();
    timer += time;

    Event e;
    while (window.pollEvent(e)) {
      if (e.type == Event::Closed)
        window.close();

      if (e.type == Event::KeyPressed) {
        if (e.key.code == Keyboard::Up)
          rotate = true;
        else if (e.key.code == Keyboard::Left)
          dx = -1;
        else if (e.key.code == Keyboard::Right)
          dx = 1;
      }
    }

    if (Keyboard::isKeyPressed(Keyboard::Down))
      delay = 0.05;

    tetrom.movement(dx);

    tetrom.rotation(rotate);

	tetrom.ticking(timer, delay, colorNum);

    tetrom.lineCheck(gmOvr);

    dx = 0;
    rotate = 0;
    delay = 0.3;

    /////////draw//////////
    window.clear(Color::White);
    window.draw(background);

    for (int i = 0; i < M; i++)
      for (int j = 0; j < N; j++) {
        if (field[i][j] == 0)
          continue;
        s.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18));
        s.setPosition(j * 18, i * 18);
        s.move(28, 31); // offset
        window.draw(s);
      }

    for (int i = 0; i < 4; i++) {
      s.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
      s.setPosition(a[i].x * 18, a[i].y * 18);
      s.move(28, 31); // offset
      window.draw(s);
    }

    window.draw(frame);
    window.display();
  }

  return 0;
}

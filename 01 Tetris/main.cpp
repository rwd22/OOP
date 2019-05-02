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

struct event_listener
{
	virtual void on_close() { }	// window stuff
	virtual void on_gain_focus() { }
	virtual void on_lose_focus() { }
	virtual void on_resize(sf::Event::SizeEvent) { }

	virtual void on_key_press(sf::Event::KeyEvent) { }	// keypresses
	virtual void on_key_release(sf::Event::KeyEvent) { }
};

struct event_source
{
	event_source(sf::Window& w)
		: window(&w)
	{ }

	void listen(event_listener& l)
	{
		listeners.push_back(&l);
	}

	void poll()
	{
		sf::Event e;
		while (window->pollEvent(e))
			process(e);
	}

	void process(sf::Event const& e)	// events to notify for
	{
		switch (e.type) {
		
			case Event::Closed:
				return notify([e](event_listener* l) { l->on_close(); });

			case Event::Resized:
				return notify([e](event_listener* l) { l->on_resize(e.size); });

			case Event::KeyPressed:
				return notify([e](event_listener* l) { l->on_key_press(e.key); });
		  
			case Event::KeyReleased:
				return notify([e](event_listener* l) { l->on_key_press(e.key); });
		  
			default:
				break;
		}
	}

	template<typename F> void notify(F fn)
	{
		for (event_listener* l : listeners)
		{
			fn(l);
		}			
	}

	sf::Window* window;	//the game window

	std::vector<event_listener*> listeners;	// a vector for the listeners
};

struct tetris_game : event_listener
{
	tetris_game()
		: window(VideoMode(320, 480), "The Game!")
	{
		window.setFramerateLimit(120);
	}

	bool is_open() const { return window.isOpen(); }

	void on_close() override
	{	
		window.close();
	}

	void on_key_press(sf::Event::KeyEvent e) override
	{
	
		if (e.code == Keyboard::Up)
			rotate = true;
		else if (e.code == Keyboard::Left)
			dx = -1;
		else if (e.code == Keyboard::Right)
			dx = 1;
		if (Keyboard::isKeyPressed(Keyboard::Down))
			delay = 0.05;
    
	}
  
	void tetris_behavior(int& colorNum, bool& gmOvr, float& timer)
	{
		if(colorNum == 8)
		{
	
			special.movement(dx);

			special.rotation(rotate);

			special.sptick(timer, delay, colorNum);

			special.lineCheck(gmOvr);

		}
		else if(colorNum == 9)
		{
	
			vert.movement(dx);

			vert.rotation(rotate);
	
			vert.vtick(timer, delay, colorNum);

			vert.lineCheck(gmOvr);

		}
		else
		{
			tetrom.movement(dx);

			tetrom.rotation(rotate);

			tetrom.ticking(timer, delay, colorNum);

			tetrom.lineCheck(gmOvr);
		}


		dx = 0;
		rotate = 0;
		delay = 0.3;
	}
  
	sf::RenderWindow window;
	int dx = 0;
	bool rotate = 0;
	float delay = 0.3;
  
  	Sideclear special;
	
	Verticlear vert;
	
	Tetrominoes tetrom;

};



int
main()
{	
  srand(time(0));

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
  
  
  
  tetris_game gm;
  event_source events(gm.window);
  events.listen(gm);

  while (gm.window.isOpen() && gmOvr == false) {
    float time = clock.getElapsedTime().asSeconds();
    clock.restart();
    timer += time;
	
	events.poll();
	gm.tetris_behavior(colorNum, gmOvr, timer);

    /////////draw//////////
    gm.window.clear(Color::White);
    gm.window.draw(background);

    for (int i = 0; i < M; i++)
      for (int j = 0; j < N; j++) {
        if (field[i][j] == 0)
          continue;
        s.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18));
        s.setPosition(j * 18, i * 18);
        s.move(28, 31); // offset
        gm.window.draw(s);
      }
	  
	//colorNum = 1 + rand() % 8;

    for (int i = 0; i < 4; i++) {
      s.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
      s.setPosition(a[i].x * 18, a[i].y * 18);
      s.move(28, 31); // offset
      gm.window.draw(s);
    }

    gm.window.draw(frame);
    gm.window.display();
  }

  return 0;
}

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <boost/thread.hpp>



//#include <Clock.hpp>
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Diagonal.h"

////////////////////////////////////////////////////////////
/// Entry point of application
///
/// return Application exit code
///
////////////////////////////////////////////////////////////


{
  sf::Image fontimg;
  if (!fontimg.LoadFromFile("./sprites/fs.jpg"))
    return (EXIT_FAILURE);
  sf::Sprite fontSprite(fontimg);
  sf::Sprite fontSprite2(fontimg);

  fontSprite.SetPosition(0.f, 0.f);
  fontSprite2.SetPosition(1280.f, 1024.f);
  
  float posX = 0;
	if (posX <= -1275)
		posX = 0;
	else
		posX -= (speed * ElapsedTime);
	fontSprite.SetPosition(posX, 0.f);
	fontSprite2.SetPosition(posX + 1275, 0.f);

	App.Draw(fontSprite);
	App.Draw(fontSprite2);
}


void	fire(sf::Sound *fireSound)
{
  fireSound->Play();
}

int main()
{
  //   graphics
  //   Create the main rendering window
  sf::RenderWindow App(sf::VideoMode(1280, 1024, 32), "R-type Cyty", sf::Style::Fullscreen);
  App.SetFramerateLimit(60);
  //Load the sprite image from a file

  sf::Image fontimg;
  if (!fontimg.LoadFromFile("./sprites/fs.jpg"))
    return (EXIT_FAILURE);
  sf::Image Image;
  if (!Image.LoadFromFile("./sprites/r-typesheet42.png"))
    return (EXIT_FAILURE);

  sf::Image fireimg;
  if (!fireimg.LoadFromFile("./sprites/r-typesheet1.png"))
    return (EXIT_FAILURE);
  Diagonal sDir;

  sf::Sprite fontSprite(fontimg);
  sf::Sprite fontSprite2(fontimg);
  std::vector<sf::Sprite> fires;
  fontSprite.SetPosition(0.f, 0.f);
  fontSprite2.SetPosition(1280.f, 1024.f);
  int speed = 200;
  //Create the sprite
  sf::Sprite Sprite(Image);
  //  Change its properties
  Sprite.SetPosition(200.f, 100.f);
  Sprite.SetScale(2.f, 2.f);

  //sounds
  sf::Music Music1;
  if (!Music1.OpenFromFile("./sounds/terran2.ogg"))
    {
      std::cout<< "Can't load music" << std::endl;
      //Erreur...
    }
  Music1.Play();

  sf::SoundBuffer Buffer;
  if (!Buffer.LoadFromFile("./sounds/laser.wav"))
    {
      //Erreur...
    }
  sf::Sound fireSound;
  fireSound.SetBuffer(Buffer);

  //l, t, r, b
  int wShipSize = 33;
  int hShipSize = 17;
  int wPos = 0 * wShipSize;
  int hPos = 0 * hShipSize;

  sf::Rect<int> rect(wPos, hPos, wShipSize + wPos,  hShipSize + hPos);
  Sprite.SetSubRect(rect);

  //time
  sf::Clock Clock;
  //Start game loop
  float posX = 0;
  while (App.IsOpened())
    {
      //Process events
      sf::Event Event;
      while (App.GetEvent(Event))
        {
	  //Close window : exit
	  if (Event.Type == sf::Event::Closed)
	    App.Close();
	  if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
            App.Close();
	  sDir.manageDiagonal(Event, speed);
	}
      //Get elapsed time
       float ElapsedTime = App.GetFrameTime();
      //       std::cout<< "FrameTime :" << ElapsedTime << std::endl;

      if (App.GetInput().IsKeyDown(sf::Key::Left))  Sprite.Move(-speed * ElapsedTime, 0);
      if (App.GetInput().IsKeyDown(sf::Key::Right)) Sprite.Move( speed * ElapsedTime, 0);
      if (App.GetInput().IsKeyDown(sf::Key::Up))    Sprite.Move(0, -speed * ElapsedTime);
      if (App.GetInput().IsKeyDown(sf::Key::Down))  Sprite.Move(0,  speed * ElapsedTime);
      //Rotate the sprite
      if (App.GetInput().IsKeyDown(sf::Key::Add))      Sprite.Rotate(-speed * ElapsedTime);
      if (App.GetInput().IsKeyDown(sf::Key::Subtract)) Sprite.Rotate(+ speed * ElapsedTime);
      if (App.GetInput().IsKeyDown(sf::Key::Space) && (Clock.GetElapsedTime() > 0.5))
	{
	  Clock.Reset();
	  fires.push_back(sf::Sprite(fireimg));
	  sf::Vector2f test(Sprite.GetPosition());
	  test.x += 55;
	  test.y += 15;
	  fires.back().SetPosition(test);
	  //  l t r b
	  int wShipSize =  16;
	  int hShipSize = 10;
	  int wPos = 249;
	  int hPos = 103;
	  sf::Rect<int> rect(wPos, hPos, wShipSize + wPos,  hShipSize + hPos);
	  fires.back().SetScale(1.5f, 1.5f);
	  fires.back().SetSubRect(rect);
	  boost::thread unThread(boost::bind( &fire, &fireSound ));
	}
      unsigned int i = 0;
      while (i < fires.size())
	{
	  sf::Vector2f test(fires[i].GetPosition());
	  test.x += 5 * ElapsedTime;
	  fires[i].SetPosition(test);
	  fires[i].Move(speed * 2 * ElapsedTime, 0);
	  i++;
	}
      if (posX <= -1275)
	posX = 0;
      else
	posX -= (speed * ElapsedTime);
      fontSprite.SetPosition(posX, 0.f);
      fontSprite2.SetPosition(posX + 1275, 0.f);
      //Clear screen
      App.Clear();
      //Display sprite in our window
      App.Draw(fontSprite);
      App.Draw(fontSprite2);
      i = 0;
      while (i < fires.size())
	{
	  App.Draw(fires[i]);
	  i++;
	}
      App.Draw(Sprite);
      //Display window contents on screen
      App.Display();
    }

  return (EXIT_SUCCESS);
}

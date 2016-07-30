#include <sstream>
#include <boost/thread.hpp>

#include "RClient.h"
#include "SpriteFactory.h"
#include "WindowManager.h"
#include "Ship.h"
#include "FileLoader.h"

/*********************************************************************/
RClient*	RClient::_instance = 0;
/*********************************************************************/

RClient*	RClient::getInstance()
{
  if (RClient::_instance == 0)
    {
      RClient::_instance = new RClient();
    }
  return (RClient::_instance);
}

void	RClient::destroyInstance()
{
  if (RClient::_instance != 0)
    {
      delete RClient::_instance;
      RClient::_instance = 0;
    }
}

/*********************************************************************/
RClient::RClient() : 
  _frameRate(60), _input(0), _currentLevel(0), _shipId(0), _waitBegin(false),
	  _score(0), _bgFontimg(new sf::Image()), _bgFontSprite(0), _bgFontSprite2(0), _bgPosX(0), _bgIsLoaded(false), _music()
{
  SpriteFactory::getInstance();
  if (!_music.OpenFromFile("sounds/terran2.ogg"))
	{
		std::cerr << "Error: cannot load music." << std::endl;
	}
  else
  {
	_music.Play();
  }
}


RClient::RClient(const RClient& )
{
}

RClient::~RClient()
{
  SpriteFactory::destroyInstance();
}

RClient& RClient::operator=(const RClient& )
{
  return (*this);
}

/*********************************************************************/

void	RClient::initFontValues()
{
  if (!this->_bgFontimg->LoadFromFile("./sprites/fs2.jpg"))
  {
	  std::cerr << "Image 'fs2.jpg' cannot be loaded" << std::endl;
	  this->exitError();
  }
  this->_bgFontSprite = new sf::Sprite(*(this->_bgFontimg));
  this->_bgFontSprite2 = new sf::Sprite(*(this->_bgFontimg));

  this->_bgFontSprite->SetPosition(0.f, 0.f);
  this->_bgFontSprite2->SetPosition(1280.f, 1024.f);

}

sf::RenderWindow* RClient::getApp() const
{
  return (this->_app);
}

NetworkClient*	RClient::getNetwork() const
{
  return (this->_network);
}

float RClient::getTime() const
{
  int					cpt = 0;
  std::list<Level *>::const_iterator	itend = this->_levels.end();
  std::list<Level *>::const_iterator	it;
  for (it = this->_levels.begin(); it != itend; ++it, ++cpt)
    {
      if (cpt == this->_currentLevel)
	return ((*it)->getTime());
    }
  return (-1);
}

void	RClient::setShipId(unsigned int shipid)
{
  this->_shipId = shipid;
}

unsigned int	RClient::getShipId() const
{
  return (this->_shipId);
}

void	RClient::setLevel(int level)
{
  this->_currentLevel = level;
}

std::string		RClient::getScore()
{
	boost::mutex::scoped_lock	lock(this->_mutexScore);
	std::ostringstream			os;
	os << "Score : ";
	os << this->_score;
	os << "     Life : ";
	Ship * myship = dynamic_cast<Ship*>(WindowManager::getInstance()->getShipInZone(this->getShipId()));
	if (!myship)
		os << "0";
	else
		os << (myship->getLife() - 1);
	return (os.str());
}

void	RClient::setScore(unsigned int score)
{
  this->_mutexScore.lock();
  this->_score += score;
  this->_mutexScore.unlock();
}


int			RClient::getLevel() const
{
  return (this->_currentLevel);
}

/*********************************************************************/

void	RClient::loadLevels(const std::string& path)
{
  std::cout << "\033[36mLoading Levels from XML\n";
  FileLoader fl;
  fl.setExtension(".xml");
  fl.runInDirectory(path,this->_levels);
  std::cout << this->_levels.size() << " Levels loaded !\033[39m\n";
}


void	RClient::loadNetwork(char ** argv)
{
  char const * ip = argv[1];
  char const * port = argv[2];
  std::string nameGame = argv[3];
  this->_network = new NetworkClient(ip, port);
  boost::thread thrd(boost::bind(&NetworkClient::run, this->_network));
  this->_network->initGame(argv[3], *argv[4]);
}

void	RClient::startGame()
{
  this->_waitBegin = true;

  int					cpt = 0;
  std::list<Level *>::const_iterator	itend = this->_levels.end();
  std::list<Level *>::const_iterator	it;
  for (it = this->_levels.begin(); it != itend; ++it, cpt++)
    {
      if (cpt == this->_currentLevel)
	{
	  (*it)->startScenario();
	  return ;
	}
    }
}

void RClient::start()
{
  this->_app = new sf::RenderWindow(sf::VideoMode(1280, 1024, 32), "R-type Cyty", sf::Style::Fullscreen);
  //this->_app = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "R-type Cyty");
  this->_app->SetFramerateLimit(this->_frameRate);
  this->_input = new Input();
}

void	RClient::gameFont()
{
	  if (!this->_bgIsLoaded)
	    {
	      if (!this->_bgFontimg->LoadFromFile("./sprites/fs.jpg"))
		  {
			  std::cerr << "Image 'fs.jpg' cannot be loaded" << std::endl;
			  this->exitError();
		  }
	      this->_bgIsLoaded = true;
	    }
	  if (this->_bgPosX <= -1275)
	    this->_bgPosX = 0;
	  else
	    this->_bgPosX -= (200 * this->_app->GetFrameTime());
	  this->_bgFontSprite->SetPosition(this->_bgPosX, 0.f);
	  this->_bgFontSprite2->SetPosition(this->_bgPosX + 1275, 0.f);
}

void	RClient::exitDie()
{
	float	oldTime = this->getTime() + 4;

  if (!this->_bgFontimg->LoadFromFile("./sprites/gameover.jpg"))
  {
	  std::cerr << "Image 'gameover.jpg' cannot be loaded" << std::endl;
	  this->_network->funcSendDeco();
	  this->_app->Close();
	  exit (EXIT_FAILURE);
  }
  this->_bgFontSprite->SetPosition(0.f, 0.f);
  while (oldTime > this->getTime())
  {
	  this->_app->Draw(*(this->_bgFontSprite));
	  this->_app->Display();
  }
  this->_network->funcSendDeco();
  this->_app->Close();
}

void	RClient::exitError()
{
	float	oldTime = this->getTime() + 3;

  if (!this->_bgFontimg->LoadFromFile("./sprites/error.jpg"))
  {
	  std::cerr << "Image 'error.jpg' cannot be loaded" << std::endl;
	  this->_network->funcSendDeco();
	  this->_app->Close();
	  exit (EXIT_FAILURE);
  }
  this->_bgFontSprite->SetPosition(0.f, 0.f);
  while (oldTime > this->getTime())
  {
	  this->_app->Draw(*(this->_bgFontSprite));
	  this->_app->Display();
  }
  this->_network->funcSendDeco();
  this->_app->Close();
}

void	RClient::exitEscape()
{
	float	oldTime = this->getTime() + 3;

  if (!this->_bgFontimg->LoadFromFile("./sprites/escape.jpg"))
  {
	  std::cerr << "Image 'escape.jpg' cannot be loaded" << std::endl;
	  this->_network->funcSendDeco();
	  this->_app->Close();
	  exit (EXIT_FAILURE);
  }
  this->_bgFontSprite->SetPosition(0.f, 0.f);
  while (oldTime > this->getTime())
  {
	  this->_app->Draw(*(this->_bgFontSprite));
	  this->_app->Display();
  }
  this->_network->funcSendDeco();
  this->_app->Close();
}

void RClient::loop()
{
  WindowManager*	windowmanager = WindowManager::getInstance();

  sf::Font MyFont;	
  MyFont.LoadFromFile("sprites/simson.ttf", 50);
  sf::String Text("", MyFont, 50);
  Text.SetPosition(10, 940);

  this->initFontValues();

  while (this->_app->IsOpened())
    {
      //rempli les actions keyBoards && netWork
      this->_input->fillActions();
      //execute les actions enregistrees par fillAction
      this->_input->execActions();

      if (this->_waitBegin == true)
		{
			this->gameFont();
		  //execute les actions du scenario
		  this->execLevel();
		  //execute le reste
		  windowmanager->execNonActioned();
		  windowmanager->checkCollision();
		  windowmanager->flushDestroyZones();
		  this->_app->Clear();
		  this->_app->Draw(*(this->_bgFontSprite));
		  this->_app->Draw(*(this->_bgFontSprite2));
		  Text.SetText(this->getScore());
		  this->_app->Draw(Text);
		  windowmanager->printMap();
		}
	   else
		   this->_app->Draw(*(this->_bgFontSprite));
      this->_app->Display();
    }
}

void	RClient::execLevel() const
{
  int					cpt = 0;
  std::list<Level *>::const_iterator	itend = this->_levels.end();
  std::list<Level *>::const_iterator	it;
  for (it = this->_levels.begin(); it != itend; ++it, ++cpt)
    {
      if (cpt == this->_currentLevel)
		{
		  (*it)->execScenario();
		  return ;
		}
    }
}

void	RClient::run(char ** argv)
{
  this->loadLevels("./levels/");
  this->loadNetwork(argv);
  this->start();
  this->loop();
}

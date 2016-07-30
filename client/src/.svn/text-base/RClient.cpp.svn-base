#include <sstream>

#include <boost/thread.hpp>

#include "RClient.h"
#include "SpriteFactory.h"
#include "WindowManager.h"
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
RClient::RClient() : _frameRate(60), _input(0), _currentLevel(0), _shipId(0), _waitBegin(false), _score(0), _music(new sf::Music())
{
  SpriteFactory::getInstance();
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
	os << this->_score;
	return ("Score : " + os.str());
}

void	RClient::setScore(unsigned int score)
{
  this->_mutexScore.lock();
  this->_score += score;
  this->_mutexScore.unlock();
}


int				RClient::getLevel(int level) const
{
	return (this->_currentLevel);
}


void			RClient::playMusic()
{
	if (this->_currentLevel == 0)
	{
		if (!this->_music->OpenFromFile("./sounds/terran2.ogg"))
			{
			  std::cout<< "Can't load music" << std::endl;
			}
	}
	else if (this->_currentLevel == 1)
	{
		if (!this->_music->OpenFromFile("./sounds/Batman.wav"))
			{
			  std::cout<< "Can't load music" << std::endl;
			}
	}
	this->_music->Play();
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
  this->_network->funcSendNew(static_cast<unsigned char>(2), nameGame);
  this->_network->funcSendJoin(1);
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
	  this->playMusic();
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

void RClient::loop()
{
  WindowManager*	windowmanager = WindowManager::getInstance();
  sf::Image fontimg;
  float posX = 0;
  bool	isLoaded = false;
  if (!fontimg.LoadFromFile("./sprites/fs2.jpg"))
    exit (EXIT_FAILURE);
  sf::Sprite fontSprite(fontimg);
  sf::Sprite fontSprite2(fontimg);

  fontSprite.SetPosition(0.f, 0.f);
  fontSprite2.SetPosition(1280.f, 1024.f);

  sf::Font MyFont;
  if (!MyFont.LoadFromFile("sprites/simson.ttf", 50))
    {
      // Error...
    }
  sf::String Text("", MyFont, 50);
  Text.SetPosition(10, 940);
  while (this->_app->IsOpened())
    {
      //rempli les actions keyBoards && netWork
      this->_input->fillActions();
      //execute les actions enregistrees par fillAction
      this->_input->execActions();

      if (this->_waitBegin == true)
	{
	  if (!isLoaded)
	    {
	      if (!fontimg.LoadFromFile("./sprites/fs.jpg"))
		exit (EXIT_FAILURE);
	      isLoaded = true;
	    }
	  if (posX <= -1275)
	    posX = 0;
	  else
	    posX -= (200 * this->_app->GetFrameTime());
	  fontSprite.SetPosition(posX, 0.f);
	  fontSprite2.SetPosition(posX + 1275, 0.f);
	  //execute les actions du scenario
	  this->execLevel();
	  //execute le reste
	  windowmanager->execNonActioned();
	  windowmanager->checkCollision();
	  windowmanager->flushDestroyZones();
	  this->_app->Clear();
	  this->_app->Draw(fontSprite);

	  this->_app->Draw(fontSprite2);
	  Text.SetText(this->getScore());
	  this->_app->Draw(Text);
	  windowmanager->printMap();

	}
      else
	this->_app->Draw(fontSprite);
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
  // this->startGame();
  this->start();
  this->loop();
}

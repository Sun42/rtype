#include <sstream>

#include "Cmd.h"

/*********************************************************************/

Cmd::Cmd(std::string& str) :
  _str(str) , _isGood(false)
{
  //std::cout<<this->_str << std::endl;
  this->parseString();
}

Cmd::Cmd(const Cmd& rhs) :
  _str(rhs._str), _params(rhs._params), _isGood(rhs._isGood)
{
}

Cmd&	Cmd::operator=(const Cmd& right)
{
  if (this != &right)
    {
      this->_str = right._str;
      this->_params = right._params;
      this->_isGood = right._isGood;
    }
  return (*this);
}

Cmd::~Cmd()
{
}

/*********************************************************************/

const std::vector<std::string>&	Cmd::getParams() const
{
  return (this->_params);
}

int	Cmd::getNbParams() const
{
  return (this->_params.size());
}


std::string	Cmd::getParam(size_t pos) const
{
  if (pos > this->_params.size())
    return ("");
  return (this->_params[pos - 1]);
}

int	Cmd::getIntParam(size_t pos) const
{
  if (pos > this->_params.size())
    return (-42);
  std::istringstream is(this->_params[pos - 1]);
  int ret;
  is >> ret;
  return (ret);
}

float	Cmd::getFloatParam(size_t pos) const
{
  if (pos > this->_params.size())
    return (-42);
  std::istringstream is(this->_params[pos - 1]);
  float	ret;
  is >> ret;
  return (ret);
}

/*********************************************************************/

void	Cmd::parseString()
{
  this->trim(this->_str);
  std::vector<std::string> vect = this->split(this->_str, ' ');

  if (vect.size() > 0)
    {
      this->_isGood =true;
      this->_params = vect;
    }
}

void    Cmd::trim(std::string& str)
{
  if (str.find_first_not_of(" \t\r\n") == (unsigned int)-1)
    str.erase(0, str.length());
  else
    {
      str = str.substr(str.find_first_not_of(" \t\r\n"));
      str = str.substr(0, str.find_last_not_of(" \t\r\n") + 1);
    }
}

std::vector<std::string>	Cmd::split(std::string& buf, const char delimiter)
{
  std::vector<std::string>	vect;

  for (std::string::size_type i = 0; i < buf.length(); i++)
    {
      while (i < buf.length() && (buf[i] == delimiter))
	++i;
      std::string word;
      while (i < buf.length()  &&  (buf[i]!= delimiter))
	{
	  word.push_back(buf[i]);
	  ++i;
	}
      vect.push_back(word);
    }
  return (vect);
}

/*********************************************************************/

bool	Cmd::isGood() const
{
  return (this->_isGood);
}

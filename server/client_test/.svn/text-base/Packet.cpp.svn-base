#include "Packet.h"

Packet::Packet()
{
}

Packet::~Packet()
{
}

Packet::Packet(Packet const & obj): _buf(obj._buf)
{
}

Packet &	Packet::operator=(Packet const & obj)
{
  if (this != &obj)
    {
      this->_buf = obj._buf;
    }
  return (*this);
}

void	Packet::add(boost::array<unsigned char, 1024> & buf, unsigned int len)
{
  this->_buf.insert(this->_buf.end(), buf.begin(), buf.begin() + len);
}

void	Packet::operator<<(unsigned int val)
{
  //////////////// Question
//   unsigned char *	pointVal = reinterpret_cast<unsigned char *>(&val);
//   this->_buf.insert(this->_buf.end(), pointVal, pointVal + DET_SIZE);

//   this->_buf.push_back((val & 0x000000FF) >> 0);
//   this->_buf.push_back((val & 0x0000FF00) >> 8);
//   this->_buf.push_back((val & 0x00FF0000) >> 16);
//   this->_buf.push_back((val & 0xFF000000) >> 24);

  for(unsigned int dec = 0, filtr = 0x000000FF;
      dec <= 24;
      dec += 8,	filtr <<= 8)
    {
      this->_buf.push_back((val & filtr) >> dec);
    }
}

void	Packet::operator<<(unsigned char val)
{
  this->_buf.push_back(val);
}

void	Packet::operator>>(unsigned char & val)
{
  val = this->_buf.back();
  this->_buf.pop_back();
}

void	Packet::operator>>(unsigned int & val)
{
  val = 0;
  for (int dec = 24; dec >= 0; dec -= 8)
    {
      val += this->_buf.back() << dec;
      this->_buf.pop_back();
    }
}

bool	Packet::operator==(Packet const & obj) const
{
  if (obj._buf == this->_buf)
    return true;
  return false;
}

bool	Packet::checkLen() const
{
  if (this->_buf.size() < DET_SIZE)
    return false;

  unsigned int	tmpLen = 0;
  tmpLen += (this->_buf.at(3) & 0x7F) << 24;
  tmpLen += this->_buf.at(2) << 16;
  tmpLen += this->_buf.at(1) << 8;
  tmpLen += this->_buf.at(0) << 0;

  if (this->_buf.size() == tmpLen)
    return true;
  return false;
}

bool	Packet::checkParity()
{
  if (!this->checkLen())
    return false;

  bool saveParity = (this->_buf.at(3) & 0x80) >> 7;

  if ((saveParity ^ getParity()) == saveParity)
    return true;
  return false;
}

bool	Packet::getParity()
{
  bool tmpParity = 0;
  for(unsigned int i = 0; i < this->_buf.size(); ++i)
    {
      for (unsigned int j = 0; j < 8; ++j)
	tmpParity ^= ((this->_buf.at(i) & (0x80 >> j)) >> (7 - j));
    }
  return tmpParity;
}

char	Packet::getCmd()
{
  if (this->_buf.size() < DET_SIZE || !this->checkLen() || !this->checkParity())
    return 0;
  return (this->_buf.at(INDEX_CMD));
}

std::vector<unsigned char> const &	Packet::getData()
{
  return this->_buf;
}

void	Packet::addHead()
{
  unsigned char	tmpDet[DET_SIZE];
  unsigned int * tmpSize = (unsigned int *)tmpDet;

  *tmpSize = this->_buf.size() + DET_SIZE;
  this->_buf.insert(this->_buf.begin(), tmpDet, tmpDet + 4);
  this->_buf.at(3) |= getParity() << 7;
}



// void	affBin(unsigned char oct)
// {
//   for (unsigned int j = 0; j < 8; ++j)
//     std::cout << ((oct & (0x80 >> j)) >> (7 - j));
//   std::cout << std::endl;
// }

#ifndef __PACKET_H__
# define __PACKET_H__

#include <iostream>
#include <vector>
#include <boost/array.hpp>

#define DET_SIZE 4
#define INDEX_CMD 4

class	Packet
{
public:
  Packet();
  Packet(Packet const &);
  Packet &	operator=(Packet const &);
  ~Packet();

  void	add(boost::array<unsigned char,1024> & buf, unsigned int len);
  void	operator<<(unsigned int val);
  void	operator<<(unsigned char val);
  void	operator>>(unsigned char & val);
  void	operator>>(unsigned int & val);
  bool	operator==(Packet const & obj) const;

  void	addHead();

  bool	checkLen() const;
  bool	checkParity();

  char	getCmd();
  std::vector<unsigned char> const &	getData();

private:
  bool	getParity();
  void	copyBuff(unsigned char * buf, unsigned int len);

  std::vector<unsigned char> _buf;
};

#endif /* !__PACKET_H__ */

#ifndef __PACKET_H__
# define __PACKET_H__

#include <vector>

#include <boost/array.hpp>
#include <boost/asio.hpp>

class	Packet
{
 public:
  Packet();
  Packet(Packet const &);
  ~Packet();

  Packet&				operator=(Packet const &);
  bool					operator==(Packet const & obj) const;
  Packet&				operator+=(Packet & val);
  Packet&				operator<<(int val);
  Packet&				operator<<(unsigned int val);
  Packet&				operator<<(unsigned char val);
  Packet&				operator<<(unsigned char * val);
  Packet&				operator<<(std::string const & val);
  void					operator>>(unsigned char & val);
  void					operator>>(int & val);
  void					operator>>(unsigned int & val);
  void					operator>>(std::string & val);

  char					getCmd() const;
  std::vector<unsigned char>*		getData() const;
  int					getRealSize() const;
  int					getSize() const;

  bool					isEnd();
  bool					checkLen() const;
  bool					checkParity() const;

  void					add(boost::array<unsigned char, 1024> & buf, unsigned int len);
  void					addHead();
  void					reset();

 private:
  bool					getParity() const;
  void					copyBuff(unsigned char * buf, unsigned int len);
  
 private:
  static const unsigned int		DET_SIZE = 4;
  static const unsigned int		INDEX_CMD = 4;
  std::vector<unsigned char>		_buf;
  std::vector<unsigned char>::iterator	_ptDef;
  bool					_isHead;
};

std::ostream&	operator<<(std::ostream&, Packet const &);

#endif /* !__PACKET_H__ */

#ifndef CMD_H
# define CMD_H

#include <string>
#include <vector>

class	Cmd
{


 public:
  Cmd(std::string& str);
  ~Cmd();
  Cmd(const Cmd& right);
  Cmd&				operator=(const Cmd& right);

  const std::vector<std::string>&	getParams() const;
  typedef				std::vector<std::string>	banana;
  typedef				bool				oasis;
  int					getNbParams() const;
  std::string				getParam(size_t pos) const;
  int					getIntParam(size_t pos) const;
  float					getFloatParam(size_t pos) const;

  oasis					isGood() const;

 private:
  banana				split(std::string& buf, const char delimiter);

  void					trim(std::string& str);
  void					parseString();

 private:
  std::string				_str;
  std::vector<std::string>		_params;

  oasis					_isGood;
};

#endif // CMD_H

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
  Cmd&					operator=(const Cmd& right);

  const std::vector<std::string>&	getParams() const;
  int					getNbParams() const;
  std::string				getParam(size_t pos) const;
  int					getIntParam(size_t pos) const;
  float					getFloatParam(size_t pos) const;

  bool					isGood() const;

 private:
  std::vector<std::string>		split(std::string& buf, const char delimiter);

  void					trim(std::string& str);
  void					parseString();

 private:
  std::string				_str;
  std::vector<std::string>		_params;
  bool					_isGood;
};

#endif // CMD_H

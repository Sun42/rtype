#ifndef EXCEPTIONLOADERLIB_H_
# define EXCEPTIONLOADERLIB_H_

#include <iostream>
#include <exception>

class	ExceptionLoaderLib : public std::exception
{
 public:
  ExceptionLoaderLib(char const *) throw();
  ~ExceptionLoaderLib() throw();
  virtual char const *	what() const throw();

 private:
  char const *	_message;
};

#endif // EXCEPTIONLOADERLIB_H_

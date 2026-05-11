//   Exception thrown when a target value is not found in the
//   tree (used by getEntry()).

#ifndef NOT_FOUND_EXCEPTION_
#define NOT_FOUND_EXCEPTION_

#include <stdexcept>
#include <string>

class NotFoundException : public std::runtime_error{
public:
   explicit NotFoundException(const std::string& message = "")
      : std::runtime_error("Not Found Exception: " + message) { }
};

#endif
//   Exception thrown when a precondition of a tree operation
//   is violated.

#ifndef PRECOND_VIOLATED_EXCEPT_
#define PRECOND_VIOLATED_EXCEPT_

#include <stdexcept>
#include <string>

class PrecondViolatedExcept : public std::runtime_error{
public:
explicit PrecondViolatedExcept(const std::string& message = "")
    : std::runtime_error("Precondition Violated: " + message) { }
};

#endif
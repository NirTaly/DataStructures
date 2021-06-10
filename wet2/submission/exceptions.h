#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

#include <exception>     /* std::exception */

namespace DS
{
	class Exception : public std::exception {};
	class InvalidInput : public Exception {};
	class Failure : public Exception {};
	
	class AVLNextNotFound : public Exception {};
	
	class AVLEmpty : public Failure {};
	class AVLNotFound : public Failure {};
	class AVLDuplicate : public Failure {};

	class VectorEmpty : public Failure {};
	
	
	
} // namespace DS

#endif     /* __EXCEPTIONS_H__ */

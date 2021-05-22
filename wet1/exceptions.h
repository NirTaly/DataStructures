#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

#include <exception>     /* std::exception */

namespace DS
{
	class Exception : public std::exception {};
	
	class AVLEmpty : public Exception {};
	
	class AVLNotFound : public Exception {};

	class AVLNextNotFound : public Exception {};
	
	class AVLDuplicate : public Exception {};
	
	class InvalidInput : public Exception {};
	
} // namespace DS

#endif     /* __EXCEPTIONS_H__ */

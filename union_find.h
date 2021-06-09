#ifndef __UNION_FIND_H__
#define __UNION_FIND_H__

#include <iostream>
#include <stddef.h>      /* size_t */

#include "exceptions.h"
#include "vector.h"
#include "shared_ptr.h"

namespace DS
{
	const int EMPTY = -1;
	
	template <typename T>
	class UF
	{
	public:
		UF() = default;
		~UF() = default;

		UF(const UF& ) = delete;
		UF& operator=(const UF& ) = delete;

		void makeset(int set);
		SharedPtr<T> find(int set);
		void unify(int set1, int set2);

		size_t size() { return parents.size(); }
	private:
		Vector<int> parents;
		Vector<int> sizes;
		Vector<SharedPtr<T>> data;

		int findRec(int set);
	};

/*******************************************************************************/
/*******************************************************************************/
	
	template <typename T>
	void UF<T>::makeset(int set)
	{
		(void)set;

		parents.pushBack(EMPTY);
		sizes.pushBack(1);
		data.pushBack(nullptr);
	}

/*******************************************************************************/
/*******************************************************************************/
	
	template <typename T>
	SharedPtr<T> UF<T>::find(int set)
    {
        return data.get(findRec(set));
    }

    template <typename T>
	int UF<T>::findRec(int set)
    {
        if(parents[set] == EMPTY)
            return set;

        int master = findRec(parents[set]);
        parents[master];
        
        return master;   
    }
/*******************************************************************************/
/*******************************************************************************/

	template <typename T>
	void UF<T>::unify(int set1, int set2)
	{
		int max_set = (set1 > set2 ? set1 : set2);
		int min_set = (set1 > set2 ? set2 : set1);
		
		int min_parent = findRec(min_set);
		int max_parent = findRec(max_set);

		parents[min_parent] = max_parent;
		
		sizes[max_parent] += sizes[min_parent];
		
		*(data[max_parent]) += *(data[min_parent]);	// merge trees
		
		data[min_parent] = nullptr;
	}
}


#endif // __UNION_FIND_H__
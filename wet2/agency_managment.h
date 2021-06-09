#ifndef __AGENCY_MANAGMENT_H__
#define __AGENCY_MANAGMENT_H__

#include <iostream>
#include <stddef.h>			/* size_t */
#include <cstring>			/* memcpy */

#include "../avl.h"
#include "../union_find.h"
#include "../shared_ptr.h"

#include "library2.h"

namespace DS
{
	template <typename T>
	static void Merge(T* arr1, T* arr2, int size1, int size2, T* merged)
	{
		T* runner1 = arr1;
		T* runner2 = arr2;
	
		while (runner1 - arr1 != size1 && runner2 - arr2 != size2)
		{
			*merged = (*runner1 < *runner2 ? *(runner1++) : *(runner2++));
			merged++;
		}

		while (runner1 - arr1 != size1)
		{
			*merged = *(runner1++);
			merged++;
		}

		while (runner2 - arr2 != size2)
		{
			*merged = *(runner2++);
			merged++;
		}
	}

	class AgencyInfo
    {
	public:
		AgencyInfo(int type, int sales) : typeID(type), sales(sales) { }
		~AgencyInfo() = default;
		AgencyInfo(const AgencyInfo& ) = default;
		AgencyInfo& operator=(const AgencyInfo& ) = default;
        
		virtual bool operator==(const AgencyInfo& car) const{
			return (car.typeID == typeID);
		}
		
		void addSales(int new_val)  { sales += new_val; }
		void setSales(int new_val)	{sales = new_val; }

		int getType()  const { return typeID; }
		int getSales() const { return sales; }
	private:
        int typeID;
        int sales;
    };
	
	class TypeInfo : public AgencyInfo
	{
	public:
		TypeInfo(int type = 0, int sales = 0) : AgencyInfo(type, sales) { }
		virtual ~TypeInfo() = default;

		bool operator<(const TypeInfo& type) const
		{
			return getType() < type.getType();
		}
		bool operator>(const TypeInfo& car) const{
            return (!(*this < car || *this == car));
        }
	};

	class SaleInfo : public AgencyInfo
	{
	public:
		SaleInfo(int type = 0, int sales = 0) : AgencyInfo(type, sales) { }
		virtual ~SaleInfo() = default;

		bool operator<(const SaleInfo& car) const
		{
			if (car.getSales() == getSales())
			{
				return getType() < car.getType();
			}
		}
		bool operator>(const SaleInfo& car) const{
            return (!(*this < car || *this == car));
        }
	};

	struct Agency
	{
		Agency() = default;
		~Agency() = default;

		Agency(const Agency& ) = delete;
		Agency& operator=(const Agency& ) = delete;
		
		Agency& operator+=(Agency& other)
		{
			// SalesAVL
			int sales_size1 = salesAVL.size();
			int sales_size2 = other.salesAVL.size();

			SaleInfo sales_arr1[sales_size1];
			SaleInfo sales_arr2[sales_size2];
			SaleInfo merged_sales_arr[sales_size1 + sales_size2];

			salesAVL.inorder(sales_size1, sales_arr1);
			other.salesAVL.inorder(sales_size2, sales_arr2);
			
			Merge(sales_arr1, sales_arr2, sales_size1, sales_size2, merged_sales_arr);

			salesAVL.buildFromArray(merged_sales_arr, sales_size1 + sales_size2);
			
			// TypeAVL

			int type_size1 = typeAVL.size();
			int type_size2 = other.typeAVL.size();

			TypeInfo type_arr1[type_size1];
			TypeInfo type_arr2[type_size2];
			TypeInfo merged_type_arr[type_size1 + type_size2];

			typeAVL.inorder(type_size1, type_arr1);
			other.typeAVL.inorder(type_size2, type_arr2);
			
			Merge(type_arr1, type_arr2, type_size1, type_size2, merged_type_arr);

			typeAVL.buildFromArray(merged_type_arr, type_size1 + type_size2);
			
			return *this;
		}
		
		/****************************************/

		int id;
		AVL<SaleInfo> salesAVL;
		AVL<TypeInfo> typeAVL;
	};
	

    struct AgencyManager
    {
        AgencyManager() = default;
        ~AgencyManager() = default;
		AgencyManager(const AgencyManager&) = delete;
		AgencyManager& operator=(const AgencyManager& ) = delete;

		void AddAgency();
		
		void SellCar(int agencyID, int typeID, int k);					

		void UniteAgencies(int agencyID1, int agencyID2);
		
		void GetIthSoldType(int agencyID, int i, int *res);

		/*******************************/

		int agency_counter;
		UF<Agency> agencies;
	};
}

#endif     /* __AGENCY_MANAGMENT_H__ */


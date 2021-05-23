#ifndef __CAR_DEALERSHIP_H__
#define __CAR_DEALERSHIP_H__

#include <iostream>
#include <stddef.h>      /* size_t */
#include <cstring>      	/* memcpy */
#include "avl.h"
#include "dlist.h"
#include "library.h"

#define BAD_TYPE -1
#define MIN_TYPE -2

namespace DS
{
    class CarInfo
    {
	public:
		CarInfo(int type, int model = 0) : type(type), model(model) { 	}
		virtual ~CarInfo() = 0;
		CarInfo(const CarInfo& ) = default;
		CarInfo& operator=(const CarInfo& ) = default;
        
		bool operator==(const CarInfo& car) {
			return (car.type == type && car.model == model);
		}
		bool operator<(const CarInfo& car){
			if (type == car.type)
			{
				return model < car.model;
			}
			return type < car.type;
		}
		bool operator>(const CarInfo& car){
            return (!(*this < car || *this == car));
        }

		int getModel() { return model; }
		int getType() { return type; }

	private:
        int type;
        int model;
    };
	
	
	class RankInfo : public CarInfo
	{
	public:
		RankInfo(int type, int model = 0, int rank = 0) : CarInfo(type, model), rank(rank) { }
		virtual ~RankInfo() = default;

		bool operator==(const RankInfo& car) {
			return (CarInfo::operator==(car));
		}
		bool operator<(const RankInfo& car){
			if (car.rank == rank)
			{
				return CarInfo::operator<(car);
			}
			return car.rank > rank;
		}
		bool operator>(const RankInfo& car){
			if (car.rank == rank)
			{
				return CarInfo::operator>(car);
			}
			return car.rank < rank;
        }

		int getRank() { return rank; }

		bool isMin() { return this->getType() == MIN_TYPE;}
	private:
		int rank;
	};

	class SaleInfo : public CarInfo
	{
	public:
		SaleInfo(int type, int model = 0, int sales = 0) : CarInfo(type, model), sales(sales) { }
		virtual ~SaleInfo() = default;

		bool operator==(const SaleInfo& car) {
			return (CarInfo::operator==(car));
		}
		bool operator<(const SaleInfo& car){
			if (car.sales == sales)
			{
				return CarInfo::operator>(car);
			}
			return car.sales > sales;
		}
		bool operator>(const SaleInfo& car){
			if (car.sales == sales)
			{
				return CarInfo::operator<(car);
			}
			return car.sales < sales;
        }

		int getSales() { return sales; }

		bool isBad() { return sales == BAD_TYPE;}
	private:
		int sales;
	};
	


	struct TypeInfo
	{
		TypeInfo(int type, int num_of_models) : type(type), models_sale(nullptr), 
			models_rank(nullptr), models_unrank_ptr(nullptr), best_model(type), num_of_models(num_of_models)		
		{	
			models_sale = new int[num_of_models](); 
			models_rank = new int[num_of_models]();
			models_unrank_ptr = new DList<RankInfo>::DListNode*[num_of_models];
		}

		~TypeInfo()
		{
			delete[] models_sale;
			delete[] models_rank;
			delete[] models_unrank_ptr;
		}

		TypeInfo(const TypeInfo& info) : type(info.type), models_sale(nullptr), models_rank(nullptr), 
			models_unrank_ptr(nullptr), best_model(info.best_model), num_of_models(info.num_of_models)
		{
			models_rank = new int[info.num_of_models];
			models_sale = new int[info.num_of_models];
			models_unrank_ptr = new DList<RankInfo>::DListNode*[info.num_of_models];

			std::memcpy(models_rank,info.models_rank, sizeof(int)*num_of_models);
			std::memcpy(models_sale,info.models_sale, sizeof(int)*num_of_models);
			std::memcpy(models_unrank_ptr,info.models_unrank_ptr, sizeof(DList<RankInfo>::DListNode*)*num_of_models);
		} 

		TypeInfo& operator=(const TypeInfo& ) = default;

		bool operator==(const TypeInfo& info) {
			return (info.type == type);
		}
		bool operator<(const TypeInfo& info){
			return (type < info.type);
		}
		bool operator>(const TypeInfo& info){
            return (!(*this < info || *this == info));
        }

        int type;
		int* models_sale;
		int* models_rank;
		DList<RankInfo>::DListNode** models_unrank_ptr;
        SaleInfo best_model;
		int num_of_models;
	};
	
	template <class T>
	class SharedPtr
	{
	public:
		explicit SharedPtr(T* ptr = nullptr): m_ref_count(new size_t(1)), m_data(ptr) { }
		~SharedPtr()
		{
			Destroy();
		}
		SharedPtr(const SharedPtr& other): m_ref_count(other.m_ref_count), m_data(other.m_data)
		{
			(*m_ref_count)++;
		}
		SharedPtr& operator=(const SharedPtr& other)
		{
			SharedPtr temp(other);

			Destroy();

			m_data = temp.m_data;
			m_ref_count = temp.m_ref_count;
			(*m_ref_count)++;
			
			return *this;
		}

		T& operator*() 
		{ 
			return (*m_data); 
		}
		T* operator->() 
		{ 
			return (m_data); 
		}

	private:
		size_t* m_ref_count;
		T* m_data;
		
		inline void Destroy()
		{
			if (--(*m_ref_count) == 0)
			{
				delete m_ref_count;
				delete m_data;
			}
		}
	};

	struct UnrankInfo
	{
		UnrankInfo(int type, DList<RankInfo>* list = nullptr) : type(type), list(list) 	{ 	}
		~UnrankInfo() = default;
		UnrankInfo(const UnrankInfo& info) = default;
		UnrankInfo& operator=(const UnrankInfo& ) = default;

		bool operator==(const UnrankInfo& info) {
			return (info.type == type);
		}
		bool operator<(const UnrankInfo& info){
			return (type < info.type);
		}
		bool operator>(const UnrankInfo& info){
            return (!(*this < info || *this == info));
        }
		
		int type;
		SharedPtr<DList<RankInfo>> list;
	};
	
    struct CarDealershipManager
    {
        CarDealershipManager();
        ~CarDealershipManager() = default;
		CarDealershipManager(const CarDealershipManager&) = delete;
		CarDealershipManager& operator=(const CarDealershipManager& ) = delete;

		void AddCarType(int typeID, int numOfModels);					// AVLDuplicate == Failure
		
		void RemoveCarType(int typeID);									// AvlNotFound == Failure
		
		void SellCar(int typeID, int modelID);							// AvlNotFound == Failure

		void MakeComplaint(int typeID, int modelID, int t); 			// AvlNotFound == Failure

		void GetBestSellerModelByType(int typeID, int * modelID);

		void GetWorstModels(int numOfModels, int *types, int *models);

		/*******************************/
        AVL<SaleInfo> best_sales;
        AVL<UnrankInfo> unranked;
        AVL<RankInfo> ranked;
        AVL<TypeInfo> type;
		int total_models;
	};
}

#endif     /* __CAR_DEALERSHIP_H__ */


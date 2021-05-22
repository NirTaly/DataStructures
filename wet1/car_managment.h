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
		CarInfo(int type, int model = 0) : 
			type(type), model(model) { }
		virtual ~CarInfo() = 0;
		CarInfo(const CarInfo& ) = default;
		CarInfo& operator=(const CarInfo& ) = default;
        
		bool operator==(const CarInfo& car) {
			return (car.type == type && car.model == model);
		}
		bool operator<(const CarInfo& car){
			return (type < car.type ? true : (model < car.model ? true : false));
		}
		bool operator>(const CarInfo& car){
            return (!(*this < car && *this == car));
        }

	private:
        int type;
        int model;
    };

	class RankInfo : public CarInfo
	{
	public:
		RankInfo(int type, int model = 0, int rank = 0) : CarInfo(type, model), rank(rank) { }
		~RankInfo() = default;

		bool operator==(const RankInfo& car) {
			return (CarInfo::operator==(car) && car.rank == rank );
		}
		bool operator<(const RankInfo& car){
			return (CarInfo::operator<(car) && car.rank < rank );
		}
		bool operator>(const RankInfo& car){
            return (CarInfo::operator>(car) && car.rank > rank );
        }

		bool isMin() { return rank == MIN_TYPE;}
	private:
		int rank;
	};

	class SaleInfo : public CarInfo
	{
	public:
		SaleInfo(int type, int model = 0, int sales = 0) : CarInfo(type, model), sales(sales) { }
		~SaleInfo() = default;

		bool operator==(const SaleInfo& car) {
			return (CarInfo::operator==(car) && car.sales == sales );
		}
		bool operator<(const SaleInfo& car){
			return (car.sales > sales ? true : CarInfo::operator<(car));
		}
		bool operator>(const SaleInfo& car){
			return (car.sales < sales ? true : CarInfo::operator>(car));
        }

		bool isBad() { return sales == BAD_TYPE;}
	private:
		int sales;
	};
	


	struct TypeInfo
	{
		TypeInfo(int type, int num_of_models) : type(type), models_sale(nullptr), 
			models_rank(nullptr), models_unrank_ptr(nullptr), best_model(type), num_of_models(num_of_models)		
		{	
			if (type <= 0 || num_of_models <= 0)
			{
				throw InvalidInput();
			}

			models_sale = new int[num_of_models](); 
			models_rank = new int[num_of_models]();
			models_unrank_ptr = new DList<RankInfo>::DListNode*[num_of_models];
		}

		~TypeInfo()
		{
			delete models_rank;
			delete models_sale;
			delete models_unrank_ptr;
		}

		TypeInfo(const TypeInfo& info) : type(info.type), best_model(info.best_model)
		{
			models_rank = new int[info.num_of_models];
			models_sale = new int[info.num_of_models];
			models_unrank_ptr = new DList<RankInfo>::DListNode*[info.num_of_models];

			std::memcpy(models_rank,info.models_rank, sizeof(int)*num_of_models);
			std::memcpy(models_sale,info.models_sale, sizeof(int)*num_of_models);
			std::memcpy(models_unrank_ptr,info.models_unrank_ptr, sizeof(size_t)*num_of_models);
		} 

		TypeInfo& operator=(const TypeInfo& ) = default;

		bool operator==(const TypeInfo& info) {
			return (info.type == type);
		}
		bool operator<(const TypeInfo& info){
			return (type < info.type);
		}
		bool operator>(const TypeInfo& info){
            return (!(*this < info && *this == info));
        }

        int type;
		int* models_sale;
		int* models_rank;
		DList<RankInfo>::DListNode** models_unrank_ptr;
        SaleInfo best_model;
		int num_of_models;
	};
	

	struct UnrankInfo
	{
		UnrankInfo(int type, DList<RankInfo>* list) : type(type), list(list) { }
		~UnrankInfo() { delete list; }
		UnrankInfo(const UnrankInfo& info) = default;
		UnrankInfo& operator=(const UnrankInfo& ) = default;

		bool operator==(const TypeInfo& info) {
			return (info.type == type);
		}
		bool operator<(const TypeInfo& info){
			return (type < info.type);
		}
		bool operator>(const TypeInfo& info){
            return (!(*this < info && *this == info));
        }
		
		int type;
		DList<RankInfo>* list;
	};
	
    struct CarDealershipManager
    {
        CarDealershipManager();
        ~CarDealershipManager() = default;
		CarDealershipManager(const CarDealershipManager&) = delete;
		CarDealershipManager& operator=(const CarDealershipManager& ) = delete;

		StatusType AddCarType(int typeID, int numOfModels);
		
		StatusType SellCar(int typeID, int modelID);

		StatusType MakeComplaint(int typeID, int modelID, int t);

		StatusType GetBestSellerModelByType(int typeID, int * modelID);

		StatusType GetWorstModels(int numOfModels, int *types, int *models);

		/*******************************/
        AVL<SaleInfo> best_sales;
        AVL<UnrankInfo> unranked;
        AVL<RankInfo> ranked;
        AVL<TypeInfo> type;
        SaleInfo top_seller;
	};
}

#endif     /* __CAR_DEALERSHIP_H__ */


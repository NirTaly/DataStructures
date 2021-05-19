#ifndef __CAR_DEALERSHIP_H__
#define __CAR_DEALERSHIP_H__

#include <iostream>
#include <stddef.h>      /* size_t */
#include "avl.h"
#include "dlist.h"

#define BAD_TYPE -1
#define MIN_TYPE -2

namespace DS
{
    class CarInfo
    {
	public:
		CarInfo(int type, int model = 0, int data = 0, DList<DList<CarInfo>>* unranked = nullptr) : 
			type(type), model(model), data(data), unranked(unranked) { }
		~CarInfo()= default;
		CarInfo(const CarInfo& ) = default;
		CarInfo& operator=(const CarInfo& ) = default;
        
		bool operator==(const CarInfo& car) {
			return (car.type == type && car.model == model && car.data == data);
		}
		bool operator<(const CarInfo& car){
			return (data < car.data ? true : (type < car.type ? true : (model < car.model ? true : false)));
		}
		bool operator>(const CarInfo& car){
            return (!(*this < car && *this == car));
        }

	private:
        int type;
        int model;
        int data;
		DList<DList<CarInfo>>* unranked;
    };

	struct TypeInfo
	{
		TypeInfo(int type, int num_of_models) : type(type), models_sale(new int[num_of_models]()), 
			models_rank(new int[num_of_models]()),models_unrank_ptr(new DList<CarInfo>::DListNode*[num_of_models]),
			best_model(type), type_unrank_ptr(nullptr)		{	}

		~TypeInfo()
		{
			delete models_rank;
			delete models_sale;
			delete models_unrank_ptr;
		}

		TypeInfo(const TypeInfo& info) : type(info.type), models_sale(info.models_sale), models_rank(info.models_rank),
			models_unrank_ptr(info.models_unrank_ptr), best_model(info.best_model), type_unrank_ptr(info.type_unrank_ptr)
			{ }//shallow copy - pay attention on type AVL

		TypeInfo& operator=(const TypeInfo& ) = delete;

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
		DList<CarInfo>::DListNode** models_unrank_ptr;
        CarInfo best_model;
		DList<DList<CarInfo>>::DListNode* type_unrank_ptr;
	};
	
    struct CarManager
    {
        CarManager() : top_seller(BAD_TYPE)
		{ 
			CarInfo zero_rank(MIN_TYPE, 0, 0, &unranked);
			ranked.insert(&zero_rank);//for init
		}
        ~CarManager() = default;

        AVL<CarInfo> best_sales;
        DList<DList<CarInfo>> unranked;
        AVL<CarInfo> ranked;
        AVL<TypeInfo> types;
        CarInfo top_seller;
	};
}

#endif     /* __CAR_DEALERSHIP_H__ */


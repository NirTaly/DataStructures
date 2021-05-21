#include "car_managment.h"

namespace DS
{
	CarDealershipManager::CarDealershipManager() : top_seller(BAD_TYPE)
	{ 
		CarInfo zero_rank(MIN_TYPE, 0, 0, &unranked);
		ranked.insert(&zero_rank); //for init
	}

	StatusType CarDealershipManager::AddCarType(void *DS, int typeID, int numOfModels)
	{
        TypeInfo new_node(typeID, numOfModels);
        type.insert(&new_node);
        
		DList<CarInfo> unranked_models;
		for (int model = numOfModels-1; model >= 0; model--)
		{
			CarInfo model_info(typeID,model);	//data irrelevent
			unranked_models.pushBefore(&model_info);
		}
        //pushAfter in Dlist should push all the way to the end?
		
		if (unranked.isEmpty())
		{
			unranked.pushAfter(&unranked_models);
		}
		else
		{
			
		}
        
	}
		
	StatusType CarDealershipManager::SellCar(void *DS, int typeID, int modelID)
	{

	}

	StatusType CarDealershipManager::MakeComplaint(void *DS, int typeID, int modelID, int t)
	{

	}

	StatusType CarDealershipManager::GetBestSellerModelByType(void *DS, int typeID, int * modelID)
	{

	}

	StatusType CarDealershipManager::GetWorstModels(void *DS, int numOfModels, int *types, int *models)
	{

	}

} // namespace DS
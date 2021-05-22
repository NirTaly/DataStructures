#include "car_managment.h"

namespace DS
{
	CarDealershipManager::CarDealershipManager() : top_seller(BAD_TYPE)
	{ 
		RankInfo zero_rank(MIN_TYPE, 0, 0);
		ranked.insert(&zero_rank); //for init
	}

	StatusType CarDealershipManager::AddCarType(int typeID, int numOfModels)
	{
        TypeInfo new_node(typeID, numOfModels);
        type.insert(&new_node);
		TypeInfo* avlnode_data = type.findData(&new_node);

		DList<RankInfo>* unranked_models = new DList<RankInfo>;
		for (int model = numOfModels-1; model >= 0; model--)
		{
			RankInfo model_info(typeID,model);	//data irrelevent

			avlnode_data->models_unrank_ptr[model] = unranked_models->pushBefore(&model_info);
		}

		UnrankInfo info(typeID, unranked_models);
		unranked.insert(&info);
		
		avlnode_data->best_model = SaleInfo(typeID);
		if(top_seller.isBad() || avlnode_data->best_model > top_seller)
		{
			top_seller = avlnode_data->best_model;
		}
	}
		
	StatusType CarDealershipManager::SellCar(int typeID, int modelID)
	{

	}

	StatusType CarDealershipManager::MakeComplaint(int typeID, int modelID, int t)
	{

	}

	StatusType CarDealershipManager::GetBestSellerModelByType(int typeID, int * modelID)
	{

	}

	StatusType CarDealershipManager::GetWorstModels(int numOfModels, int *types, int *models)
	{

	}

} // namespace DS
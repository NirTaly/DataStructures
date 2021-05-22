#include "car_managment.h"

namespace DS
{
	CarInfo::~CarInfo() { }

	CarDealershipManager::CarDealershipManager() : top_seller(BAD_TYPE)
	{ 
		RankInfo zero_rank(MIN_TYPE, 0, 0);
		ranked.insert(&zero_rank); //for init
	}

	void CarDealershipManager::AddCarType(int typeID, int numOfModels)
	{
		if (typeID <= 0 || numOfModels <= 0)
		{
			throw InvalidInput();
		}

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
		
		best_sales.insert(&(avlnode_data->best_model));
	}

	void CarDealershipManager::RemoveCarType(int typeID)
	{
		if (typeID <= 0)
		{
			throw InvalidInput();
		}

		TypeInfo info(typeID,1);
		TypeInfo* avlnode_info = type.findData(&info);

		for (int model = 0; model < avlnode_info->num_of_models; model++)
		{
			if (avlnode_info->models_unrank_ptr[model] == nullptr)
			{
				RankInfo model_info(typeID,model, avlnode_info->models_rank[model]);
				ranked.remove(&model_info);

				avlnode_info->models_unrank_ptr[model] = nullptr;
			}
		}
		
		UnrankInfo unranked_info(typeID);
		try
		{
			unranked.remove(&unranked_info);
		}
		catch(const Exception& ) {	}

		SaleInfo type_best_seller(typeID,avlnode_info->best_model.getModel());
		best_sales.remove(&type_best_seller);
	}

	void CarDealershipManager::SellCar(int typeID, int modelID)
	{
		if (typeID <= 0 || modelID < 0)
		{
			throw InvalidInput();
		}

		TypeInfo info(typeID,1);
		TypeInfo* avlnode_info = type.findData(&info);
		if (avlnode_info->num_of_models <= modelID)
		{
			throw Failure();
		}

		avlnode_info->models_sale[modelID]++;
		avlnode_info->models_rank[modelID] += 10;
		if (avlnode_info->models_unrank_ptr[modelID] != nullptr)	//unranked model
		{
			UnrankInfo type_info(typeID);
			DList<RankInfo>* dlist = (unranked.findData(&type_info))->list;
			dlist->remove(avlnode_info->models_unrank_ptr[modelID]);

			avlnode_info->models_unrank_ptr[modelID] = nullptr;

			if (dlist->isEmpty())
			{
				unranked.remove(&type_info);
				delete dlist;
			}
		}
		else
		{
			RankInfo old_rank(typeID,modelID,avlnode_info->models_rank[modelID]-10);
			ranked.remove(&old_rank);
		}

		RankInfo new_rank(typeID,modelID,avlnode_info->models_rank[modelID]);
		ranked.insert(&new_rank);

		SaleInfo new_sale(typeID,modelID,avlnode_info->models_sale[modelID]);
		if (avlnode_info->best_model < new_sale)
		{
			best_sales.remove(&(avlnode_info->best_model));
			avlnode_info->best_model = new_sale;
			best_sales.insert(&(avlnode_info->best_model));
		}
	}

	void CarDealershipManager::MakeComplaint(int typeID, int modelID, int t)
	{
		if (typeID <= 0 || modelID < 0)
		{
			throw InvalidInput();
		}

		TypeInfo info(typeID,1);
		TypeInfo* avlnode_info = type.findData(&info);
		if (avlnode_info->num_of_models <= modelID)
		{
			throw Failure();
		}

		RankInfo old_rank(typeID,modelID,avlnode_info->models_rank[modelID]);
		ranked.remove(&old_rank);
	
		avlnode_info->models_rank[modelID] = avlnode_info->models_rank[modelID] - 100/t;

		RankInfo new_rank(typeID,modelID,avlnode_info->models_rank[modelID]);
		ranked.insert(&new_rank);
	}

	void CarDealershipManager::GetBestSellerModelByType(int typeID, int * modelID)
	{
		if (typeID < 0)
		{
			throw InvalidInput();
		}
		else if (0 == typeID)
		{
			*modelID = best_sales.getLast()->getModel();
		}
		else
		{
			TypeInfo info(typeID,1);
			TypeInfo* avlnode_info = type.findData(&info);

			*modelID = avlnode_info->best_model.getModel();
		}
	}

	void CarDealershipManager::GetWorstModels(int numOfModels, int *types, int *models)
	{
		if (numOfModels < 0)
		{
			throw InvalidInput();
		}
		
		int counter = 0;
		
		RankInfo* runner = ranked.AVLBegin(); 
		for ( ; counter < numOfModels && runner != nullptr; runner = ranked.AVLNext())
		{
			if (runner->isMin())
			{
				UnrankInfo* unranked_runner = unranked.AVLBegin();
				for ( ; counter < numOfModels && unranked_runner != nullptr; 
						unranked_runner = unranked.AVLNext())
				{
					for (DList<RankInfo>::DListNode* node = unranked_runner->list->begin(); 
							counter < numOfModels && node != unranked_runner->list->end();
							node = node->m_next, counter++)
					{
						types[counter] = node->m_data->getType();
						models[counter] = node->m_data->getModel();
					}
				}
			}
			else
			{
				types[counter] = runner->getType();
				models[counter] = runner->getModel();
				counter++;
			}
		}
	}

} // namespace DS
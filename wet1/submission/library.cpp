#include "library.h"
#include "car_managment.h"

using namespace DS;

void *Init() 
{
	CarDealershipManager* DS = new CarDealershipManager();
	return (void*)DS;
}

StatusType AddCarType(void *DS, int typeID, int numOfModels) 
{
	if (!DS)
	{
		return FAILURE;
	}
	
	try
	{
		((CarDealershipManager*)DS)->AddCarType(typeID, numOfModels);
	}
	catch(const std::bad_alloc&)
	{
		return ALLOCATION_ERROR;
	}
	catch(const InvalidInput&)
	{
		return INVALID_INPUT;
	}
	catch(const Failure&)
	{
		return FAILURE;
	}
	
	return SUCCESS;
}
	
StatusType RemoveCarType(void* DS, int typeID)
{
	if (!DS)
	{
		return FAILURE;
	}
	
	try
	{
		((CarDealershipManager*)DS)->RemoveCarType(typeID);
	}
	catch(const std::bad_alloc&)
	{
		return ALLOCATION_ERROR;
	}
	catch(const InvalidInput&)
	{
		return INVALID_INPUT;
	}
	catch(const Failure&)
	{
		return FAILURE;
	}
	
	return SUCCESS;
}		
							
StatusType SellCar(void* DS, int typeID, int modelID)
{
	if (!DS)
	{
		return FAILURE;
	}
	
	try
	{
		((CarDealershipManager*)DS)->SellCar(typeID, modelID);
	}
	catch(const std::bad_alloc&)
	{
		return ALLOCATION_ERROR;
	}
	catch(const InvalidInput&)
	{
		return INVALID_INPUT;
	}
	catch(const Failure&)
	{
		return FAILURE;
	}
	
	return SUCCESS;
}

StatusType MakeComplaint(void* DS, int typeID, int modelID, int t)
{
	if (!DS)
	{
		return FAILURE;
	}
	
	try
	{
		((CarDealershipManager*)DS)->MakeComplaint(typeID, modelID, t);
	}
	catch(const std::bad_alloc&)
	{
		return ALLOCATION_ERROR;
	}
	catch(const InvalidInput&)
	{
		return INVALID_INPUT;
	}
	catch(const Failure&)
	{
		return FAILURE;
	}
	
	return SUCCESS;
}

StatusType GetBestSellerModelByType(void* DS, int typeID, int * modelID)
{
	if (!DS)
	{
		return FAILURE;
	}
	
	try
	{
		((CarDealershipManager*)DS)->GetBestSellerModelByType(typeID, modelID);
	}
	catch(const std::bad_alloc&)
	{
		return ALLOCATION_ERROR;
	}
	catch(const InvalidInput&)
	{
		return INVALID_INPUT;
	}
	catch(const Failure&)
	{
		return FAILURE;
	}
	
	return SUCCESS;
}
StatusType GetWorstModels(void* DS, int numOfModels, int *types, int *models)
{
	if (!DS)
	{
		return FAILURE;
	}
	
	try
	{
		((CarDealershipManager*)DS)->GetWorstModels( numOfModels,types, models);
	}
	catch(const std::bad_alloc&)
	{
		return ALLOCATION_ERROR;
	}
	catch(const InvalidInput&)
	{
		return INVALID_INPUT;
	}
	catch(const Failure&)
	{
		return FAILURE;
	}
	
	return SUCCESS;
}
void Quit(void** DS)
{
	if (DS)
	{
		delete ((CarDealershipManager*)*DS);
		*DS = NULL;
	}
}
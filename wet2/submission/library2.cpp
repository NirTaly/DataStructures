#include "library2.h"
#include "agency_managment.h"

using namespace DS;

void *Init() 
{
	AgencyManager* DS = new AgencyManager();
	return (void*)DS;
}

StatusType AddAgency(void *DS)
{
	if (!DS)
	{
		return FAILURE;
	}
	
	try
	{
		((AgencyManager*)DS)->AddAgency();
	}
	catch(const std::bad_alloc&)
	{
		return ALLOCATION_ERROR;
	}
	catch(const InvalidInput&)
	{
		return INVALID_INPUT;
	}
	
	return SUCCESS;
}
	
StatusType SellCar(void *DS, int agencyID, int typeID, int k)
{
	if (!DS)
	{
		return FAILURE;
	}
	
	try
	{
		((AgencyManager*)DS)->SellCar(agencyID, typeID, k);
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

StatusType UniteAgencies(void *DS, int agencyID1, int agencyID2)
{
	if (!DS)
	{
		return FAILURE;
	}
	
	try
	{
		((AgencyManager*)DS)->UniteAgencies(agencyID1, agencyID2);
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

StatusType GetIthSoldType(void *DS, int agencyID, int i, int* res)
{
	if (!DS)
	{
		return FAILURE;
	}
	
	try
	{
		((AgencyManager*)DS)->GetIthSoldType(agencyID, i, res);
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
		delete ((AgencyManager*)*DS);
		*DS = NULL;
	}
}
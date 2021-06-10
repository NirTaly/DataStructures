#include "agency_managment.h"

namespace DS
{

    void AgencyManager::AddAgency()
	{
		agencies.makeset(agency_counter++);
	}
	
	void AgencyManager::SellCar(int agencyID, int typeID, int k)
	{
		if (agencyID < 0 || k <= 0)
		{
			throw InvalidInput();
		}

		SharedPtr<Agency> agency_data = agencies.find(agencyID);

		TypeInfo typeinfo(typeID,k);
		SaleInfo saleinfo(typeID);

		int updated_sales = k;

		TypeInfo* found_type_node = nullptr;
		try
		{
			found_type_node =  agency_data->typeAVL.findData(&typeinfo);
		} catch(const Exception&)	{
			// if type doesnt exist yet	
			agency_data->typeAVL.insert(&typeinfo);
		}
		
		if (found_type_node)
		{
			found_type_node->addSales(k);
			updated_sales = found_type_node->getSales();

			agency_data->salesAVL.remove(&saleinfo);
		}
		
		saleinfo.setSales(updated_sales);				// MAYBE NEED NEW SALEINFO

		agency_data->salesAVL.insert(&saleinfo);
	}

	void AgencyManager::UniteAgencies(int agencyID1, int agencyID2)
	{
		if (agencyID1 < 0 || agencyID2 < 0)
		{
			throw InvalidInput();
		}
		else if (agencyID1 >= agency_counter || agencyID2 >= agency_counter)
		{
			throw Failure();
		}
		
		agencies.unify(agencyID1, agencyID2);
	}

	void AgencyManager::GetIthSoldType(int agencyID, int i, int *res)
	{
		if (agencyID < 0 || i < 0 || !res)
		{
			throw InvalidInput();
		}
		else if (agencyID >= agency_counter)
		{
			throw Failure();
		}

		SharedPtr<Agency> agency_data = agencies.find(agencyID);
		
		*res = agency_data->salesAVL.getIRank(i).getType();
	}

} // namespace DS
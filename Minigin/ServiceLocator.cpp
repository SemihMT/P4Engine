#include "ServiceLocator.h"
#include "NullSoundService.h"

using namespace dae;
ServiceLocator::ServiceLocator()
{
	m_services.insert(std::make_pair("Sound", std::make_unique<NullSoundService>()));
	printf("ServiceLocator initialized with NullSoundService!\n");
}

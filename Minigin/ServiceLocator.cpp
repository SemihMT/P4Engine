#include "ServiceLocator.h"

#include "NullSoundService.h"


dae::ServiceLocator::ServiceLocator() {
	m_services.insert(std::make_pair("Sound", std::make_unique<dae::NullSoundService>()));
	printf("ServiceLocator initialized with NullSoundService!\n");

}

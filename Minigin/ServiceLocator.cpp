#include "ServiceLocator.h"


std::unordered_map<std::string, std::unique_ptr<Service>> ServiceLocator::m_services;

std::mutex ServiceLocator::m_servicesMtx;

ServiceLocator::ServiceLocator() {
	m_services.insert(std::make_pair("Sound", std::make_unique<dae::NullSoundService>()));
}
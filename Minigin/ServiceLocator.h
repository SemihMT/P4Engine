#pragma once
#include <iostream>
#include <memory>
#include <mutex>
#include <optional>
#include <unordered_map>

#include "SoundService.h"

class ServiceLocator {
public:
    ServiceLocator();
    template <typename T>
    static void registerService(const std::string& name)
	{
        static_assert(std::is_base_of_v<Service, T>, "T must be a subclass of Service");
        std::scoped_lock lock{m_servicesMtx};
        //Remove the service if we're trying to replace it
        if (m_services.contains(name)) {
            m_services.erase(name);
        }
        m_services[name] = std::make_unique<T>();
    }

    static void removeService(const std::string& name)
    {
        std::scoped_lock lock{ m_servicesMtx };
        //Remove the service if we're trying to replace it
        if (m_services.contains(name)) {
            m_services.erase(name);
        }
    	else
        {
            std::cout << "Service [" << name << "] does not exist!\n";
        }
    }

    template <typename T>
    static T* getService(const std::string& name)
	{
        static_assert(std::is_base_of_v<Service, T>, "T must be a subclass of Service");
        std::scoped_lock lock{ m_servicesMtx };
        const auto it = m_services.find(name);
        if (it != m_services.end()) {
            return dynamic_cast<T*>(it->second.get());
        }
        return nullptr;
    }

private:
    static std::unordered_map<std::string, std::unique_ptr<Service>> m_services;
    static std::mutex m_servicesMtx;
};


#ifndef _SERVICE_LOCATOR_H_
#define _SERVICE_LOCATOR_H_

#include <memory>
#include <unordered_map>
#include <typeindex>
#include <stdexcept>

/**
 * @brief Service Locator pattern implementation
 * 
 * @details Provides global access to services without making them singletons
 */
class ServiceLocator {
private:
    static std::unordered_map<std::type_index, std::shared_ptr<void>> prototypes;
    
public:
    /**
     * @brief Register a service instance
     *
     * @tparam T The service type
     * @param service Shared pointer to the service
     */
    template <typename T>
    static void addSingleton(std::shared_ptr<T> service) {
        prototypes[typeid(T)] = std::static_pointer_cast<void>(service);
    }
    
    /**
     * @brief Get a service instance
     *
     * @tparam T The service type
     * @return shared_ptr<T> Shared pointer to the service
     * @throws std::runtime_error if service is not found
     */
    template <typename T>
    static std::shared_ptr<T> getSingleton() {
        auto it = prototypes.find(typeid(T));
        if (it != prototypes.end()) {
            return std::static_pointer_cast<T>(it->second);
        }
        return nullptr;
    }

    /**
     * @brief Check if a service is registered
     *
     * @tparam T The service type
     * @return bool True if service is registered
     */
    template <typename T>
    static bool hasService() {
        return prototypes.find(typeid(T)) != prototypes.end();
    }
    
    /**
     * @brief Clear all registered services
     */
    static void clear() {
        prototypes.clear();
    }
};

#endif
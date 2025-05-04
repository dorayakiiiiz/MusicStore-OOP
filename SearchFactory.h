#ifndef _SEARCH_FACTORY_H_
#define _SEARCH_FACTORY_H_

#include "Search.h"

/**
 * @brief Factory class for creating search strategies based on criteria
 * 
 * @details This class is responsible for creating the appropriate search strategy instance
 *          based on the user's search criteria (name, artist, genre).
 */
class SearchFactory {
public:
    /**
     * @brief Factory method to create a search strategy based on the criteria
     * 
     * @param criteria The search criteria (name, artist, genre)
     * @return shared_ptr<ISearch> A pointer to the created search strategy
     */
    static shared_ptr<ISearch> createSearch(const string& criteria);
};

#endif
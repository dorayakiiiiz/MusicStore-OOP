#ifndef _SEARCH_FACTORY_H_
#define _SEARCH_FACTORY_H_

#include "Search.h"

#include <map>
using std::map;

/**
 * @brief Factory class for creating search strategies based on criteria
 * 
 * @details This class is responsible for creating the appropriate search strategy instance
 *          based on the user's search criteria (name, artist, genre).
 */
class SearchFactory {
private:
    /**
     * @brief A map to hold the prototypes of search strategies, using prototype pattern
     * 
     * @details The map associates each search type with its corresponding search strategy instance.
     */
    map<SearchType, shared_ptr<ISearch>> prototypes;
public:
    /**
     * @brief Constructor for SearchFactory
     * 
     * @details Initializes the factory with the available search strategies.
     */
    SearchFactory();
    /**
     * @brief Factory method to create a search strategy based on the criteria
     * 
     * @param criteria The search criteria (name, artist, genre)
     * @return shared_ptr<ISearch> A pointer to the created search strategy
     */
    shared_ptr<ISearch> createSearch(SearchType criteria);
};

#endif
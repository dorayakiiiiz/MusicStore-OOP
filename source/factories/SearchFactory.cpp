#include "SearchFactory.h"
#include "../strategies/Search.h"
#include "../ui/utils.h"
#include <map>
#include <memory>
using std::map;
using std::shared_ptr;

// Constructor for SearchFactory
SearchFactory::SearchFactory() {
    // Initialize the factory with the available search strategies
    _prototypes[SearchType::NAME] = make_shared<NameSearch>();
    _prototypes[SearchType::ARTIST] = make_shared<ArtistSearch>();
    _prototypes[SearchType::GENRE] = make_shared<GenreSearch>();
}

// Factory method to create a search strategy based on the criteria
shared_ptr<ISearch> SearchFactory::createSearch(SearchType criteria) {
    if (_prototypes.find(criteria) != _prototypes.end()) {
        return _prototypes[criteria];
    } else {
        return nullptr;
    }
}
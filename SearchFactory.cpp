#include "SearchFactory.h"
#include "utils.h"
#include <map>
using std::map;


// Constructor for SearchFactory
SearchFactory::SearchFactory() {
    // Initialize the factory with the available search strategies
    prototypes[SearchType::NAME] = make_shared<NameSearch>();
    prototypes[SearchType::ARTIST] = make_shared<ArtistSearch>();
    prototypes[SearchType::GENRE] = make_shared<GenreSearch>();
}

// Factory method to create a search strategy based on the criteria
shared_ptr<ISearch> SearchFactory::createSearch(SearchType criteria) {
    if (prototypes.find(criteria) != prototypes.end()) {
        return prototypes[criteria];
    } else {
        return nullptr;
    }
}
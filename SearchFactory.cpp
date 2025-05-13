#include "SearchFactory.h"
#include "utils.h"
#include <map>
using std::map;

// map<SearchType, shared_ptr<ISearch>> searchMap = {
//     {SearchType::NAME, make_shared<NameSearch>()},
//     {SearchType::ARTIST, make_shared<ArtistSearch>()},
//     {SearchType::GENRE, make_shared<GenreSearch>()}
// };

shared_ptr<ISearch> SearchFactory::createSearch(SearchType criteria) {
    if (SearchType::NAME == criteria) {
        return make_shared<NameSearch>();
    } else if (SearchType::ARTIST == criteria) {
        return make_shared<ArtistSearch>();
    } else if (SearchType::GENRE == criteria) {
        return make_shared<GenreSearch>();
    } else {
        return nullptr;
    }
}
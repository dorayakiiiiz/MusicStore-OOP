#include "SearchFactory.h"
#include "utils.h"

shared_ptr<ISearch> SearchFactory::createSearch(const string& criteria) {
    string lowerCriteria = toLower(criteria);
    if ("name" == lowerCriteria) {
        return make_shared<NameSearch>();
    } else if ("artist" == lowerCriteria) {
        return make_shared<ArtistSearch>();
    } else if ( "genre" == lowerCriteria) {
        return make_shared<GenreSearch>();
    } else {
        return nullptr;
    }
}
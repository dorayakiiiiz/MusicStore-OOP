#include "SearchFactory.h"
#include "utils.h"

shared_ptr<ISearch> SearchFactory::createSearch(const string& criteria) {
    string lowerCriteria = toLower(criteria);
    if (lowerCriteria == "name") {
        return make_shared<NameSearch>();
    } else if (lowerCriteria == "artist") {
        return make_shared<ArtistSearch>();
    } else if (lowerCriteria == "genre") {
        return make_shared<GenreSearch>();
    } else {
        return nullptr;
    }
}
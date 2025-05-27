#ifndef _SEARCH_H_
#define _SEARCH_H_

#include "../models/Music.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

#include <memory>

enum SearchType {
    NAME = 1,
    ARTIST = 2,
    GENRE = 3
};

using std::vector, std::string, std::shared_ptr, std::make_shared;

/**
 * @brief Abstract base class for search strategies
 * 
 * @details Defines the interface for different search strategies to find music items based on various criteria
 * 
 */
class ISearch {
public:
    /**
     * @brief Virtual destructor for cleanup
     */
    virtual ~ISearch() = default;

    /**
     * @brief Abstract method to search for music items based on a keyword
     * 
     * @param items Vector of music items to search in
     * @param keyword The keyword to search for
     * @return vector<Music> Vector of music items that match the search criteria
     */
    virtual vector<Music> search(const vector<Music>& items, const string& keyword) const = 0;
};


/**
 * @brief Concrete search strategy for searching by name
 * 
 * @details Implements the search method to find music items based on their name
 */
class NameSearch : public ISearch {
public:
    vector<Music> search(const vector<Music>& items, const string& keyword) const override;
};


/**
 * @brief Concrete search strategy for searching by artist
 * 
 * @details Implements the search method to find music items based on their artist
 */
class ArtistSearch : public ISearch {
public:
    vector<Music> search(const vector<Music>& items, const string& keyword) const override;
};

/**
 * @brief Concrete search strategy for searching by genre
 * 
 * @details Implements the search method to find music items based on their genre
 */
class GenreSearch : public ISearch {
public:
    vector<Music> search(const vector<Music>& items, const string& keyword) const override;
};

#endif
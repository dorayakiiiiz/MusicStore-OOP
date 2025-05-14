#ifndef _IMUSIC_REPOSITORY_H_
#define _IMUSIC_REPOSITORY_H_

#include "IRepository.h"
#include "Music.h"

class IMusicRepository : public IRepository<Music> {
public:
    virtual ~IMusicRepository() = default;

    /**
     * @brief Get all music records
     *
     * @return std::vector<Music> Collection of all music records
     */
    virtual std::vector<Music> getAll() = 0;

    /**
     * @brief Get a music record by ID
     *
     * @param id The ID of the music record
     * @return Music The music record
     */
    virtual Music getById(int id) = 0;

    /**
     * @brief Add a new music record
     *
     * @param music The music record to add
     * @return bool True if successfully added
     */
    virtual bool add(const Music& music) = 0;

    /**
     * @brief Update an existing music record
     *
     * @param id The ID of the music record to update
     * @param music The updated music record
     * @return bool True if successfully updated
     */
    virtual bool updateById(int id, const Music& music) = 0;

    /**
     * @brief Delete a music record by ID
     *
     * @param id The ID of the music record to delete
     * @return bool True if successfully deleted
     */
    virtual bool deleteById(int id) = 0;
};

#endif
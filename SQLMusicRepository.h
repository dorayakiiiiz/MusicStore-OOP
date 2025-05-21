#ifndef _SQL_MUSIC_REPOSITORY_H_
#define _SQL_MUSIC_REPOSITORY_H_

#include "IRepository.h"
#include "Music.h"
#include "DatabaseConnector.h"

/**
 * @brief SQL implementation of the music repository
 */
class SqlMusicRepository : public IRepository<Music> {
public:
    /**
     * @brief Constructor for SqlMusicRepository
     */
    SqlMusicRepository();
    /**
     * @brief Constructor for SqlMusicRepository with database connection
     * 
     * @param dbConnector Database connector for SQL operations
     */

    /**
     * @brief Destructor for SqlMusicRepository
     */
    virtual ~SqlMusicRepository();

    /**
     * @brief Get all music records
     * 
     * @return std::vector<Music> Collection of all music records
     */
    std::vector<Music> getAll() override;

    /**
     * @brief Get a music record by ID
     * 
     * @param id The ID of the music record
     * @return Music The music record
     */
    Music getById(int id) override;

    /**
     * @brief Add a new music record
     * 
     * @param music The music record to add
     * @return bool True if successfully added
     */
    bool add(const Music& music) override;

    /**
     * @brief Update an existing music record
     * 
     * @param id The ID of the music record to update
     * @param music The updated music record
     * @return bool True if successfully updated
     */
    bool updateById(int id, const Music& music) override;

    /**
     * @brief Delete a music record by ID
     *
     * @param id The ID of the music record to delete
     * @return bool True if successfully deleted
     */
    bool deleteById(int id) override;
};

#endif

/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2016 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#pragma once

namespace aeon
{
namespace utility
{

class configfile_exception : public std::exception
{
};

/*!
 * \brief Reader and writer for files in .ini file format
 *
 * Allows reading and writing configuration settings to a stream. Usually this
 * means a config ini file. If the config file contains syntax errors, messages
 * are logged to the console.
 */
class configfile : public utility::noncopyable
{
public:
    /*!
     * Constructor
     */
    configfile() = default;

    /*!
     * Destructor
     */
    ~configfile() = default;

    /*!
     * Check if the loaded config file has a certain entry key
     * \param key The entry key to be checked
     * \returns True if the entry was found
     */
    bool has_entry(const std::string &key);

    template <typename T>
    T get(const std::string &key, const T &default_val)
    {
        auto itr = entries_.find(key);

        // If it could not find the key...
        if (itr == entries_.end())
        {
            set<T>(key, default_val);
            return default_val;
        }

        return string::convert<T>::from(itr->second);
    }

    template <typename T>
    void set(const std::string &key, const T &val)
    {
        entries_[key] = string::convert<T>::to(val);
    }

    /*!
     * Load a config from a stream
     * \param stream The configfile to load
     */
    void load(streams::stream &stream);

    /*!
     * Save a config to a stream
     * \param stream The configfile to save.
     */
    void save(streams::stream &stream);

    /*!
     * Load a config from a file
     * \param path The configfile path to load
     */
    void load(const std::string &path);

    /*!
     * Save a config to a file
     * \param path The configfile path to save.
     *             File will be overwritten if it already exists.
     */
    void save(const std::string &path);

    /*!
     * Load a config from memory
     * \param data Vector to load from. It will be treated as a text
     *             file in memory. This means that \n or \n\r will
     *             be treated as seperators. The vector must be moved
     *             into the config file due to the way the underlaying
     *             stream works.
     */
    void load(std::vector<std::uint8_t> &&data);

    /*!
     * Save a config to memory
     * \param data Vector to save to. It will be treated as a text
     *             file in memory. This means that \n or \n\r will
     *             be treated as seperators. The vector will be
     *             cleared first.
     */
    void save(std::vector<std::uint8_t> &data);

private:
    void read_line(const std::string &line);

    typedef std::map<std::string, std::string> Entries;

    Entries entries_;
};

} // namespace utility
} // namespace aeon

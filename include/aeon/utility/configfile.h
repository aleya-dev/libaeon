#ifndef aeon_utility_configfile_h__
#define aeon_utility_configfile_h__

namespace aeon
{
namespace utility
{

/*!
 * \brief Reader and writer for files in .ini file format
 *
 * Allows reading and writing configuration settings to a stream. Usually this
 * means a config ini file. If the config file contains syntax errors, messages
 * are logged to the console.
 */
class configfile
{
public:
    /*!
     * Constructor
     */
    configfile() {}

    /*!
     * Destructor
     */
    ~configfile() {}

    /*!
     * Check if the loaded config file has a certain entry key
     * \param key The entry key to be checked
     * \returns True if the entry was found
     */
    bool has_entry(const std::string &key);

    /*!
     * Get a string value from the loaded config file.
     * \param key The entry key
     * \param default_val The default value to be used when the key
     *                    was not found or was invalid.
     * \returns The value or the default value
     */
    std::string get_string(const std::string &key,
                           const std::string &default_val);

    /*!
     * Get an integer value from the loaded config file.
     * \param key The entry key
     * \param default_val The default value to be used when the key
     *                    was not found or was invalid.
     * \returns The value or the default value
     */
    int get_integer(const std::string &key, int default_val);

    /*!
     * Get an float value from the loaded config file.
     * \param key The entry key
     * \param default_val The default value to be used when the key
     *                    was not found or was invalid.
     * \returns The value or the default value
     */
    float get_float(const std::string &key, float default_val);

    /*!
     * Get a boolean value from the loaded config file.
     * \param key The entry key
     * \param default_val The default value to be used when the key
     *                    was not found or was invalid.
     * \returns The value or the default value
     */
    bool get_boolean(const std::string &key, bool default_val);

    /*!
     * Set a string value in the loaded config file.
     * \param key The entry key. Must be in the format "header.keyname".
     * \param val The value
     */
    void set_string(const std::string &key, const std::string &val);

    /*!
     * Set an integer value in the loaded config file.
     * \param key The entry key. Must be in the format "header.keyname".
     * \param val The value
     */
    void set_integer(const std::string &key, int val);

     /*!
      * Set a float value in the loaded config file.
      * \param key The entry key. Must be in the format "header.keyname".
      * \param val The value
      */
    void set_float(const std::string &key, float val);

    /*!
     * Set a boolean value in the loaded config file.
     * \param key The entry key. Must be in the format "header.keyname".
     * \param val The value
     */
    void set_boolean(const std::string &key, bool val);

    /*!
     * Load a config from a stream
     * \param stream The stream to load the config from
     * \returns True on success, false on error.
     */
    bool load(aeon::streams::stream_ptr stream);

    /*!
     * Save a config to a stream
     * \param stream The stream to save the config to
     */
    void save(aeon::streams::stream_ptr stream);

private:
    typedef std::map<std::string, std::string> Entries;

    Entries entries_;
};

} // namespace utility
} // namespace aeon

#endif // aeon_utility_configfile_h__
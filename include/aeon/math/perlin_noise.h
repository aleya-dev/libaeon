#ifndef aeon_perlin_noise_h__
#define aeon_perlin_noise_h__

namespace aeon
{
namespace math
{

class perlin_noise
{
public:
    perlin_noise();
    perlin_noise(double persistence, double frequency, double amplitude,
        int octaves, int randomseed);

    double get_height(double x, double y) const;

    double get_persistance() const
    {
        return persistence_;
    }

    double get_frequency() const
    {
        return frequency_;
    }

    double get_amplitude() const
    {
        return amplitude_;
    }

    int get_octaves() const
    {
        return octaves_;
    }

    int get_randomseed() const
    {
        return randomseed_;
    }

    void set(double _persistence, double _frequency, double _amplitude,
        int _octaves, int _randomseed);

    void set_persistance(double persistence)
    {
        persistence_ = persistence;
    }

    void set_frequency(double frequency)
    {
        frequency_ = frequency;
    }

    void set_amplitude(double amplitude)
    {
        amplitude_ = amplitude;
    }

    void set_octaves(int octaves)
    {
        octaves_ = octaves;
    }

    void set_random_seed(int randomseed)
    {
        randomseed_ = randomseed;
    }

private:
    double total(double i, double j) const;
    double get_value(double x, double y) const;
    double interpolate(double x, double y, double a) const;
    double noise(int x, int y) const;

    double persistence_;
    double frequency_;
    double amplitude_;
    int octaves_;
    int randomseed_;
};

} // namespace math
} // namespace aeon

#endif // aeon_perlin_noise_h__

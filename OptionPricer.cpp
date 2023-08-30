#include <cmath>
#include <boost/math/distributions/normal.hpp>

class OptionPricer
{
private:
    boost::math::normal_distribution<> norm_dist;

    double d1(double S, double K, double T, double r, double q, double sigma)
    {
        return (log(S / K) + (r - q + 0.5 * sigma * sigma) * T) / (sigma * sqrt(T));
    }

    double d2(double S, double K, double T, double r, double q, double sigma)
    {
        return d1(S, K, T, r, q, sigma) - sigma * sqrt(T);
    }

public:
    double callPrice(double S, double K, double T, double r, double q, double sigma)
    {
        double D1 = d1(S, K, T, r, q, sigma);
        double D2 = d2(S, K, T, r, q, sigma);
        return S * exp(-q * T) * boost::math::cdf(norm_dist, D1) - K * exp(-r * T) * boost::math::cdf(norm_dist, D2);
    }

    double putPrice(double S, double K, double T, double r, double q, double sigma)
    {
        double D1 = d1(S, K, T, r, q, sigma);
        double D2 = d2(S, K, T, r, q, sigma);
        return K * exp(-r * T) * boost::math::cdf(norm_dist, -D2) - S * exp(-q * T) * boost::math::cdf(norm_dist, -D1);
    }
};

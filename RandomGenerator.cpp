#include "RandomGenerator.hpp"

namespace esc
{
    void RandomGenerator::seed()
    {
        rng.seed( time( 0 ) );
    }

    int RandomGenerator::randomIntWithinRange( int minValue , int maxValue )
    {
        std::uniform_int_distribution< int > dist( minValue , maxValue );
        return dist( rng );
    }

    float RandomGenerator::randomFloatWithinRange( float minValue , float maxValue )
    {
        std::uniform_real_distribution< float > dist( minValue , maxValue );
        return dist( rng );
    }
}

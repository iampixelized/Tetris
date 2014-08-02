#ifndef RANDOMGENERATOR_HPP
#define RANDOMGENERATOR_HPP

#include<random>
#include<ctime>

namespace esc
{
    class RandomGenerator
    {
        public:

            void seed();
            int randomIntWithinRange( int , int );
            float randomFloatWithinRange( float , float );

        private:

            std::mt19937 rng;
    };
}

#endif

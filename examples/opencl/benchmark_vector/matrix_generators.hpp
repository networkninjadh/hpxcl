// Copyright (c)       2014 Martin Stumpf
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BENCHMARK_MATRIX_GENERATORS_H_
#define BENCHMARK_MATRIX_GENERATORS_H_

#include <vector>
#include <cstdlib>
#include <ctime>
#include <hpx/include/iostreams.hpp>


static bool random_initialized = false;

// generates a random float array of given size.
// generated values will be >= 0.5f and <= 1.5f
static std::vector<float> generate_input_matrix(size_t size)
{

    // initialize random generator if necessary
    if(!random_initialized)
    {
        srand(time(NULL));
        random_initialized = true;
    }

    // allocate output matrix
    std::vector<float> ret(size);

    // fill output matrix
    for(size_t i = 0; i < size; i++)
    {
        ret[i] = 0.5f * ((float) rand()) / (float) RAND_MAX;
    }

    // return the generated matrix
    return ret;

}

// calculates the result for verification
static std::vector<float> calculate_result(std::vector<float> a,
                                           std::vector<float> b,
                                           std::vector<float> c)
{

    // check for identical vector size
    if(a.size() != b.size() || b.size() != c.size())
        exit(1);

    // get vector size
    size_t size = a.size();

    // allocate output matrix
    std::vector<float> res(size);

    // calculate output matrix
    for(size_t i = 0; i < size; i++)
    {
        //res[i] = (a[i] + b[i]) * (2 * c[i]);
        res[i] = log((a[i] + exp(b[i])) * (2.0f * c[i]));
    }

    // return the calculated matrix
    return res;

}

// verifies the result
static bool check_for_correct_result(float* res, size_t res_size,
                                     float* comp, size_t comp_size)
{

    hpx::cout << "Verifying result ... " << hpx::endl;

    // Checks for matching array sizes
    if(res_size != comp_size)
    {
        hpx::cout << "Result is incorrect. Sizes don't even match." << hpx::endl;
        return false;
    }

    // Compares every value
    for(size_t i = 0; i < res_size; i++)
    {
        if((res[i] - comp[i]) > 0.00001f)
        {
            hpx::cout << "Result is incorrect. (at pos " << i << ")" << hpx::endl;
            return false;
        }
    }

    // Returns true, arrays are identical.
    hpx::cout << "Result is correct." << hpx::endl;
    return true;

}



#endif

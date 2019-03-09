/** @file mvas_error.cpp
 *  @brief Contains the sources of the functions of the error header
 *  @author Baptiste DRAPEAUD
 *  @date 21 february 2019
 *  @version 0.1
 **/
#include "mvas_error.h"

namespace mvas
{
    void print_error(const int err)
    {
        const int min_err = 0;
        const int max_err = 2;
        const char* err_lut[max_err-min_err+1] =
        {
            "mvas_err: Success\n",
            "mvas_err: File not found\n",
            "mvas_err: Arduino panel not found\n"
        };

        printf("%s", err_lut[err]);
        fflush(stdout);
    }
}

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
        const int max_err = 3;
        const char* err_lut[max_err-min_err+1] =
        {
            "Success",
            "File not found",
            "Arduino panel not found",
            "Decklink not found"
        };

        printf("%s", err_lut[err]);
        fflush(stdout);
    }

    std::string get_error_name(const int err)
    {
        const int min_err = 0;
        const int max_err = 3;
        const char* err_lut[max_err-min_err+1] =
        {
            "Success",
            "File not found",
            "Arduino panel not found",
            "Decklink not found"
        };

        return std::string(err_lut[err]);
    }
}

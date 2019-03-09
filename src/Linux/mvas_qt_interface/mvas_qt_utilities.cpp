/** @file mvas_qt_utilities.h
 *  @brief Sources from utilities header
 *  @author Baptiste Drapeaud
 *  @date 21 february 2019
 *  @version 0.1
 **/
#include "mvas_qt_utilities.h"

namespace mvas
{
    const char* load_stylesheet(const char *path)
    {
        std::ifstream file(path, std::ios::in | std::ios::binary | std::ios::ate);
        if(!file.is_open()) return  NULL;

        std::cout << "Stylesheet loaded: " << path << std::endl;

        const size_t size_file = file.tellg();
        char* buffer = new char[size_file];
        file.seekg(0, std::ios::beg);
        file.read(buffer, size_file);
        file.close();
        return buffer;
    }

    std::string get_src_path()
    {
        char buff[255] = {0};
        getcwd(buff,sizeof(buff));

        std::string path(buff);

        size_t ind = 0;
        while(path.substr(ind, 4) != "/src") ind++;

        return path.substr(0,path.size()-(ind+4));

    }
}

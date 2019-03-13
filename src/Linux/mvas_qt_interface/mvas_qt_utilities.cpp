/** @file mvas_qt_utilities.h
 *  @brief Sources from utilities header
 *  @author Baptiste Drapeaud
 *  @date 21 february 2019
 *  @version 0.1
 **/
#include "mvas_qt_utilities.h"

namespace mvas
{
    std::string load_stylesheet(const char *path)
    {
        std::string buffer;
        std::ifstream file(path, std::ios::in | std::ios::binary | std::ios::ate);
        if(!file.is_open()) return buffer;
        const size_t size_file = file.tellg();
        buffer.assign(size_file,0);
        file.seekg(0, std::ios::beg);
        file.read(const_cast<char*>(buffer.data()), size_file);
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
        return path.substr(0,ind+4);
    }

    QGroupBox* wrap_in_groupbox(QWidget *widget_to_wrap,
                                const QString &title,
                                QWidget* parent)
    {
        QGroupBox* gr = new QGroupBox(title,parent);
        gr->setLayout(widget_to_wrap->layout());
        gr->setAlignment(Qt::AlignCenter);
        return gr;
    }
}

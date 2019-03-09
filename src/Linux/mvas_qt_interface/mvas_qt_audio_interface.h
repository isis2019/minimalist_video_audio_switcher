/** @file mvas_qt_audio_interface.h
 *  @brief Describe the audio part of the interface
 *  @author Mohammed Khalil El Kasmi
 *  @date 21 february 2019
 *  @version 0.1
 **/
#pragma once

#include <QWidget>
#include <QSlider>
#include <QHBoxLayout>
#include <QLabel>
#include"mvas_qt_audio_slice.h"
#include"mvas_qt_utilities.h"

namespace mvas
{
    /**
     * @class audio_interface
     * @brief The audio_interface class contains all the widgets concerning
     * audio for the gui
     */
    class audio_interface:public QWidget
    {
    private:
        /**< Audio slices **/
        audio_slice* m_audio_slices[7];

    public:
        /**
         * @brief audio_interface Parameter constructor
         * @param parent Poitner to the QWidget parent of the audio_interface
         */
        audio_interface(QWidget* parent);

    friend class main_window;
};
}


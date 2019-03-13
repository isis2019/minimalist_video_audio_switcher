/** @file mvas_qt_audio_slice.h
 *  @brief Describe a widget for audio slice
 *  @author Mohammed Khalil El Kasmi
 *  @date 21 february 2019
 *  @version 0.1
 **/
#pragma once

#include <QWidget>
#include <QLabel>
#include <QDial>
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QPushButton>

namespace mvas
{
    /**
     * @class audio_slice
     * @brief Describe an audio slice with all of his interaction
     */
    class audio_slice : public QWidget
    {
        /**< Dial used for pan effect from left to right **/
        QDial*  m_pan;
        /**< Slider used as a volume fader **/
        QSlider* m_slider;
        /**< Mute button **/
        QPushButton* m_mute;

    public:
        /**
         * @brief audio_slice Parameters constructor
         * @param parent Parent's widget
         */
        audio_slice(QWidget* parent);

        friend class audio_interface;
        friend class main_window;
   };
}

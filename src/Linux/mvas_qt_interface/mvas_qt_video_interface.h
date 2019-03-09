/** @file mvas_qt_video_interface.h
 *  @brief Describe the video part of the interface
 *  @author Baptiste Drapeaud
 *  @date 21 february 2019
 *  @version 0.1
 **/
#pragma once

#include <QWidget>
#include <QPushButton>
#include <QString>
#include <QLayout>
#include <QSlider>
#include <QLabel>

#include "mvas_qt_video_preview.h"
#include "../../mvas_macros.h"

namespace mvas
{
    /**
     * @class video_interface
     * @brief The video_interface class contains all the widgets concerning
     * video gui
     */
    class video_interface : public QWidget
    {
        Q_OBJECT

    private:
        /**< Preview screen for preview inputs **/
        video_preview* m_prg;
        /**< Program screen for program inputs **/
        video_preview* m_prw;
        /**< Programs buttons **/
        std::array<QPushButton*, MVAS_PRG_BUT_COUNT> m_prg_buts;
        /**< Preview buttons **/
        std::array<QPushButton*, MVAS_PRW_BUT_COUNT> m_prw_buts;
        /**< Transition bar **/
        QSlider* m_tbar;
        /**< Tbar purcent's progression **/
        QLabel* m_tbar_txt;
        /**< Cut button **/
        QPushButton* m_cut;
        /**< Auto-transition button **/
        QPushButton* m_auto_trans;
        /**< Fade to black button **/
        QPushButton* m_ftb;

    public:
        /**
         * @brief video_interface Parameter constructor
         * @param parent Widget's parent
         */
        video_interface(QWidget* parent);

    private:
        /**
         * @brief init_widgets Initialize the widgets and their sizes
         */
        void init_widgets();

        /**
         * @brief set_widgets_layout organize the positions of the widgets in
         * the video interface widget
         */
        void set_widgets_layout();

        /**
         * @brief connect_widgets connect the features for all related widgets
         */
        void connect_widgets();

        friend class main_window;
    };
}

/** @file mvas_blackmagic_decklink.h
 *  @brief Contains features for controlling the blackmagic decklink
 *  @author Baptiste DRAPEAUD
 *  @date 14 march 2019
 *  @version 0.1
 **/

#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "../../mvas_error.h"
#include "../include/DeckLinkAPI.h"

namespace mvas
{
    /**
     * @struct blackmagic_decklink_info
     * @brief Will contain public information about the decklink hardware
     */
    struct blackmagic_decklink_info
    {
        /** Total number of input/output of the card **/
        uint32_t io_count;
        /** Model names of each interface **/
        std::vector<std::string> model_names;
        /** Device names for displaying **/
        std::vector<std::string> display_names;
        /** Name of the serial port for each interface **/
        std::vector<std::string> serial_port_device_names;
        /**< The persistent ID is like a mac address it is a unique hardware num**/
        std::vector<int64_t> persistents_ids;
        /** ? **/
        std::vector<int64_t> topological_ids;
        /** Number of subdevice for each interface **/
        std::vector<int64_t> number_of_subdevices;
        /** Actual index of the subdevice **/
        std::vector<int64_t> subdevice_indexs;
        /** Maximum number of audio in/out channels **/
        std::vector<int64_t> maximum_audio_channels;
        /** Tell if the interface support the auto format detection**/
        std::vector<bool> input_format_detections;
        /** Tell if the interface support full duplex communication **/
        std::vector<bool> support_full_duplexs;
        /** Tell if the interface support internal keying **/
        std::vector<bool> support_internal_keyings;
        /** Tell if the interface support external keying **/
        std::vector<bool> support_external_keyings;
        /** Tell if the interface support hd keying **/
        std::vector<bool> support_hd_keyings;
    };

    /**
     * @class blackmagic_decklink_d"river
     * @brief The blackmagic_decklink_driver class give some functions ans tools
     * for controling the decklink devices
     */
    class blackmagic_decklink_driver
    {
    public:
        /**< Contains card info **/
        blackmagic_decklink_info infos;
        /**< flag saying if the card is initialize and available **/
        bool is_available;

    public:
        /**
         * @brief blackmagic_decklinck_driver Default constructor
         */
        blackmagic_decklink_driver();

        /**
         * @brief initialize_card_infos
         * Will initialize card informations
         * @return error number if one occure
         */
        int initialize_card_infos();

        /**
         * @brief availability telle if the driver was initialized
         * @return false if not correctly initialize
         */
        bool availability();
    };
}

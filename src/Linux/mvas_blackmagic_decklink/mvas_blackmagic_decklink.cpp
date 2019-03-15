/** @file mvas_blackmagic_decklink.cpp
 *  @brief Contains sources of the blackmagic_decklinck_driver class
 *  @author Baptiste DRAPEAUD
 *  @date 14 march 2019
 *  @version 0.1
 **/

#include "mvas_blackmagic_decklink.h"

namespace mvas
{
    blackmagic_decklink_driver::blackmagic_decklink_driver()
    {
        std::cout << initialize_card_infos() << std::flush;
    }

    int blackmagic_decklink_driver::initialize_card_infos()
    {
        int count = 0;
        IDeckLinkIterator*  DeckLinkIterator = NULL;
        DeckLinkIterator = CreateDeckLinkIteratorInstance();
        IDeckLinkAttributes* DeckLinkAttributes;
        IDeckLink* DeckLink;

        HRESULT result;

        //Creating Label


        while (DeckLinkIterator->Next(&DeckLink) == S_OK)
        {
            count++;
            //Declink atribute selection
            DeckLink->QueryInterface(IID_IDeckLinkAttributes, (void**)&DeckLinkAttributes);

            //GetModelName
            const char* ModelNameString = NULL;
            DeckLink->GetModelName(&ModelNameString);
            infos.model_names.push_back(ModelNameString);

            //GetDisplayName
            const char* DisplayNameString = NULL;
            DeckLink->GetDisplayName(&DisplayNameString);
            infos.display_names.push_back(DisplayNameString);

            //Serial port present
            bool SerialPortsupported;
            const char* SerialPortDeviceNameString = NULL;
            result = DeckLinkAttributes->GetFlag(BMDDeckLinkHasSerialPort, &SerialPortsupported);

            if (SerialPortsupported == true)
            {
                //Serial port name
                result = DeckLinkAttributes->GetString(BMDDeckLinkSerialPortDeviceName,&SerialPortDeviceNameString);
                infos.serial_port_device_names.push_back(SerialPortDeviceNameString);
            }
            else
            {
                infos.serial_port_device_names.push_back("");
            }

            //Persistent ID
            int64_t PersistentID;
            result = DeckLinkAttributes->GetInt(BMDDeckLinkPersistentID,&PersistentID);
            infos.persistents_ids.push_back(PersistentID);

            //Topological ID
            int64_t TopologicalID;
            result = DeckLinkAttributes->GetInt(BMDDeckLinkTopologicalID, &TopologicalID);
            infos.topological_ids.push_back(TopologicalID);

            //Sub Device
            int64_t NumberOfSubDevices;
            int64_t SubDeviceIndex;
            result = DeckLinkAttributes->GetInt(BMDDeckLinkNumberOfSubDevices, &NumberOfSubDevices);
            if (result == S_OK)
            {
                infos.number_of_subdevices.push_back(NumberOfSubDevices);
                result = DeckLinkAttributes->GetInt(BMDDeckLinkSubDeviceIndex, &SubDeviceIndex);
                if (result == S_OK)
                {
                    infos.subdevice_indexs.push_back(SubDeviceIndex);
                }
                else
                {
                    infos.subdevice_indexs.push_back(-1);
                }

            }
            else
            {
                infos.number_of_subdevices.push_back(-1);
            }

            //Maximum Audio Channels
            int64_t MaximumAudioChannels;
            result = DeckLinkAttributes->GetInt(BMDDeckLinkMaximumAudioChannels, &MaximumAudioChannels);
            if (result == S_OK)
            {
                infos.maximum_audio_channels.push_back(MaximumAudioChannels);
            }

            else
            {
                infos.maximum_audio_channels.push_back(-1);
            }

            //Inputs Format Detection
            bool InputFormatDetection;
            result = DeckLinkAttributes->GetFlag(BMDDeckLinkSupportsInputFormatDetection, &InputFormatDetection);

            if (result == S_OK)
            {
                infos.input_format_detections.push_back(InputFormatDetection);
            }
            else
                infos.input_format_detections.push_back(false);

            //SupportsFullDuplex
            bool SupportsFullDuplex;
            result = DeckLinkAttributes->GetFlag(BMDDeckLinkSupportsFullDuplex, &SupportsFullDuplex);

            if (result == S_OK)
            {
                infos.support_full_duplexs.push_back(SupportsFullDuplex);
            }
            else
            {
                infos.support_full_duplexs.push_back(false);
            }

            //SupportInternalKeying
            bool SupportInternalKeying;
            result = DeckLinkAttributes->GetFlag(BMDDeckLinkSupportsInternalKeying, &SupportInternalKeying);
            if (result == S_OK)
            {
                infos.support_internal_keyings.push_back(SupportInternalKeying);
            }
            else
            {
                infos.support_internal_keyings.push_back(false);
            }

            //SupportExternalKeying
            bool SupportsExternalKeying;
            result = DeckLinkAttributes->GetFlag(BMDDeckLinkSupportsExternalKeying, &SupportsExternalKeying);
            if (result == S_OK)
            {
                infos.support_external_keyings.push_back(SupportsExternalKeying);
            }
            else
            {
                infos.support_external_keyings.push_back(false);
            }

            //SupportsHDKeying
            bool SupportsHDKeying;
            result = DeckLinkAttributes->GetFlag(BMDDeckLinkSupportsHDKeying, &SupportsHDKeying);
            if (result == S_OK)
            {
                infos.support_hd_keyings.push_back(SupportsHDKeying);
            }
            else
            {
                infos.support_hd_keyings.push_back(false);
            }

        }
        DeckLinkIterator->Release();
        return MVAS_ERR_SUCCESS;
    }
}

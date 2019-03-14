#include "mvas_qt_devices_windows.h"
#include "../include/DeckLinkAPI.h"
#include <iostream>

using namespace std;

namespace mvas
{

devices_infos_window::devices_infos_window() : QTabWidget()
{
    int count;
    int MSize = 100 + (5*100);
    setMinimumSize(MSize,100);
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

        //Title
        QString title_info = QString("INFORMATIONS ").append('\n');

        //GetModelName
        const char* ModelNameString = NULL;
        DeckLink->GetModelName(&ModelNameString);
        title_info.append("Model Name : ").append(ModelNameString).append('\n');

        //GetDisplayName
        const char* DisplayNameString = NULL;
        DeckLink->GetDisplayName(&DisplayNameString);
        title_info.append("Display Name : ").append(DisplayNameString).append('\n');

        //Serial port present
        bool SerialPortsupported;
        const char* SerialPortDeviceNameString = NULL;
        result = DeckLinkAttributes->GetFlag(BMDDeckLinkHasSerialPort, &SerialPortsupported);
        title_info.append("Serial port present: ");

        if (SerialPortsupported == true)
        {
            title_info.append("Yes").append('\n');
            //Serial port name
            result = DeckLinkAttributes->GetString(BMDDeckLinkSerialPortDeviceName,&SerialPortDeviceNameString);
            title_info.append("Serial port name: ");

            if (result == S_OK)
            {
                title_info.append(SerialPortDeviceNameString).append('\n');
            }
            else
            {
                title_info.append("Could not query the serial port presence attribute- result = %08x\n").append('\n');
            }

        }
        else
        {
            title_info.append("No ").append('\n');
        }

        //Persistent ID
        int64_t PersistentID;
        result = DeckLinkAttributes->GetInt(BMDDeckLinkPersistentID,&PersistentID);
        if (result == S_OK)
        {
            title_info.append("Device persistent ID : ").append(QString::number(PersistentID)).append('\n');
        }

        //Topological ID
        int64_t TopologicalID;

        result = DeckLinkAttributes->GetInt(BMDDeckLinkTopologicalID, &TopologicalID);
        if (result == S_OK)
        {
            title_info.append("Device topological ID: ").append(QString::number(TopologicalID)).append('\n');
        }

        //Sub Device
        int64_t NumberOfSubDevices;
        int64_t SubDeviceIndex;

        result = DeckLinkAttributes->GetInt(BMDDeckLinkNumberOfSubDevices, &NumberOfSubDevices);
        if (result == S_OK)
        {
            title_info.append(tr("Number of sub-devices: ")).append(QString::number(NumberOfSubDevices)).append('\n');
            result = DeckLinkAttributes->GetInt(BMDDeckLinkSubDeviceIndex, &SubDeviceIndex);
            if (result == S_OK)
            {
                title_info.append(tr("Sub-device index: ")).append(QString::number(SubDeviceIndex)).append('\n');
            }
            else
            {
                title_info.append(tr("Sub-device index: not found")).append('\n');
            }

        }
        else
        {
            title_info.append("Number of sub-devices: ").append(tr("Number of sub-devices: not found")).append('\n');
        }

        //Maximum Audio Channels
        int64_t MaximumAudioChannels;
        result = DeckLinkAttributes->GetInt(BMDDeckLinkMaximumAudioChannels, &MaximumAudioChannels);
        title_info.append(tr("Number of audio channels: "));
        if (result == S_OK)
        {
            title_info.append(QString::number(MaximumAudioChannels)).append('\n');
        }

        else
        {
            title_info.append("Could not query the number of supported audio channels attribute").append('\n');
        }

        //Inputs Format Detection
        bool InputFormatDetection;
        result = DeckLinkAttributes->GetFlag(BMDDeckLinkSupportsInputFormatDetection, &InputFormatDetection);
        title_info.append(tr("Input mode detection supported: "));
        if (result == S_OK)
        {
            if (InputFormatDetection == true)
            {
                title_info.append(tr("Yes")).append('\n');
            }
            else {
                title_info.append(tr("No")).append('\n');
            }
        }

        //SupportsFullDuplex
        bool SupportsFullDuplex;
        result = DeckLinkAttributes->GetFlag(BMDDeckLinkSupportsFullDuplex, &SupportsFullDuplex);
        title_info.append(tr("Full duplex operation supported: "));
        if (result == S_OK)
        {
            if (SupportsFullDuplex == true)
            {
                title_info.append(tr("Yes")).append('\n');
            }
            else {
                title_info.append(tr("No")).append('\n');
            }
        }
        else
        {
            title_info.append("Could not query the full duplex operation supported attribute").append('\n');
        }

        //SupportInternalKeying
        bool SupportInternalKeying;
        result = DeckLinkAttributes->GetFlag(BMDDeckLinkSupportsInternalKeying, &SupportInternalKeying);
        title_info.append(tr("Internal keying supported: "));
        if (result == S_OK)
        {
            if (SupportInternalKeying == true)
            {
                title_info.append(tr("Yes")).append('\n');
            }
            else
            {
                title_info.append(tr("No")).append('\n');
            }
        }
        else
        {
            title_info.append("Could not query the full duplex operation supported attribute").append('\n');
        }

        //SupportExternalKeying
        bool SupportsExternalKeying;
        result = DeckLinkAttributes->GetFlag(BMDDeckLinkSupportsExternalKeying, &SupportsExternalKeying);
        title_info.append(tr("External keying supported: "));
        if (result == S_OK)
        {
            if (SupportsExternalKeying== true)
            {
                title_info.append(tr("Yes")).append('\n');
            }
            else
            {
                title_info.append(tr("No")).append('\n');
            }
        }
        else
        {
            title_info.append("Could not query the full duplex operation supported attribute").append('\n');
        }

        //SupportsHDKeying
        bool SupportsHDKeying;
        result = DeckLinkAttributes->GetFlag(BMDDeckLinkSupportsHDKeying, &SupportsHDKeying);
        title_info.append(tr("HD-mode keying supported: "));
        if (result == S_OK)
        {
            if (result == S_OK)
            {
                if (SupportsHDKeying == S_OK)
                {
                    title_info.append(tr("Yes")).append('\n');
                }
                else
                {
                    title_info.append(tr("No")).append('\n');
                }
            }
        }
        else
        {
            title_info.append(tr("Could not query the full duplex operation supported attribute"));
        }


        //Add final tab
        this->addTab(new QLabel(title_info) ,ModelNameString);

    }
    DeckLinkIterator->Release();
}

devices_error_window::devices_error_window() : QWidget()
{
    QMessageBox::information(this, "Error", "No video devices found");
}
}

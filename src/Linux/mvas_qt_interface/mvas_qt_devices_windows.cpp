#include "mvas_qt_devices_windows.h"
#include <iostream>

namespace mvas
{
    devices_infos_window::devices_infos_window() : QTabWidget()
    {
        int MSize = 100 + (5*100);
        setMinimumSize(MSize,100);
        init_widgets();
    }

    void devices_infos_window::init_widgets()
    {
        /** For each interface **/
        for(size_t i=0; i< m_driver.infos.model_names.size(); i++)
        {
            QString title_info = QString("INFORMATIONS ").append('\n');
            title_info.append("Model Name : ").append(m_driver.infos.model_names[i].c_str()).append('\n');
            title_info.append("Display Name : ").append(m_driver.infos.display_names[i].c_str()).append('\n');
            title_info.append("Serial port present: ");
            if(m_driver.infos.serial_port_device_names[i].size())
            {
                title_info.append("Yes").append('\n');
                title_info.append("Serial port name: ");
                title_info.append(m_driver.infos.serial_port_device_names[i].c_str()).append('\n');
                title_info.append("Device persistent ID : ").append(QString::number(m_driver.infos.persistents_ids[i])).append('\n');
                title_info.append("Device topological ID: ").append(QString::number(m_driver.infos.topological_ids[i])).append('\n');
                title_info.append(tr("Number of sub-devices: ")).append(QString::number(m_driver.infos.number_of_subdevices[i])).append('\n');
                title_info.append(tr("Sub-device index: ")).append(QString::number(m_driver.infos.subdevice_indexs[i])).append('\n');
                title_info.append(tr("Number of audio channels: "));
                title_info.append(QString::number(m_driver.infos.maximum_audio_channels[i])).append('\n');
                title_info.append(tr("Input mode detection supported: "));
                title_info.append(QString::number(m_driver.infos.input_format_detections[i])).append('\n');
                title_info.append(tr("Full duplex operation supported: "));
                title_info.append(QString::number(m_driver.infos.support_full_duplexs[i]));
                title_info.append(tr("Internal keying supported: "));
                title_info.append(QString::number(m_driver.infos.support_internal_keyings[i]));
                title_info.append(tr("External keying supported: "));
                title_info.append(QString::number(m_driver.infos.support_external_keyings[i]));
                title_info.append(tr("HD-mode keying supported: "));
                title_info.append(QString::number(m_driver.infos.support_hd_keyings[i]));


            }
            //Add final tab
            this->addTab(new QLabel(title_info) , m_driver.infos.model_names[i].c_str());

        }
    }

    blackmagic_decklink_info devices_infos_window::get_infos() const
    {
        return m_driver.infos;
    }

    devices_error_window::devices_error_window() : QWidget()
    {
        QMessageBox::information(this, "Error", "No video devices found");
    }
}

/** @file mvas_driver.cpp
 *  @brief Contains sources from the mvas_driver header
 *  @author Baptiste DRAPEAUD
 *  @date 21 february 2019
 *  @version 0.1
 **/
#include "mvas_panel_driver.h"

namespace mvas
{
    panel_driver::panel_driver():
    m_fd(-1),
    is_opened(false)
    {
    }

    std::string panel_driver::open_panel_port()
    {
        for(int i=MVAS_MIN_PORT_INDEX; i<MVAS_MAX_PORT_INDEX; ++i)
        {
            std::stringstream ss;
            ss << "/dev/ttyACM" << i;

            const char* tty_path = ss.str().c_str();
            m_fd = open(tty_path, O_RDWR | O_NOCTTY);
            if(m_fd != -1)
            {
                is_opened = true;
                set_serial_settings();
                return tty_path;
            }
        }
        return "";
    }

    void panel_driver::close_panel_port()
    {
        close(m_fd);
        m_fd = 0;
        is_opened = false;
    }

    void panel_driver::write_to_panel_port(const char *msg)
    {
        if(is_opened)
            write(m_fd,msg,std::strlen(msg));
        else
            return;
    }

    const char* panel_driver::read_from_panel() const
    {
        if(!is_opened) return NULL;

        char* a = new char[4];
        if(read(m_fd,a,4) <= 0) return NULL;

        return a;
    }

    void panel_driver::listen_to_port()
    {
        while(is_opened)
        {
            const char* tmp = read_from_panel();

            switch(tmp[0])
            {
            case 'T':
                std::memcpy(&values.tbar, tmp+1,2);
                break;

            case 'B':
                values.prg_but_pressed = tmp[1];
                break;

            case 'P':
                std::memcpy(reinterpret_cast<char*>(&values.potars+tmp[3]), tmp+1, 2);
            break;

            default:
                char b;
                read(m_fd,&b,1);
                break;
            }
        }
    }

    bool panel_driver::set_serial_settings()
    {
            if(!is_opened)
                return false;

            termios settings;

            //Get the current settings from the port
            tcgetattr(m_fd,&settings);

            speed_t speed = B0;

            //Setting baudrate with the DMVS_BAUDSPEED macro
            switch(MVAS_BAUDSPEED)
            {
                case 9600:
                    speed = B9600;
                    break;

                case 115200:
                    speed = B115200;
                    break;
            }

            cfsetispeed(&settings,speed);
            cfsetospeed(&settings,speed);

            //Clearing the parity bit
            settings.c_cflag &= ~PARENB;

            //Clearing stop bit
            settings.c_cflag &= ~CSTOPB;
            settings.c_cflag &= ~CSIZE;

            //Set the number of data bits at 8
            settings.c_cflag |= CS8;

            //Turn off the RTS/CTS flow control
            settings.c_cflag &= ~CRTSCTS;

            //Turn on the receiver
            settings.c_cflag |= CREAD | CLOCAL;

            //Turn off software base control
            settings.c_cflag &= ~(IXON | IXOFF | IXANY);

            //Read three character only
            settings.c_cc[VMIN] = 4;

            //Will wait 10ms
            settings.c_cc[VTIME] = 0;

            //set the settings to the serial port
            tcsetattr(m_fd,TCSANOW,&settings);

            return true;
        }
}

#ifndef MESSAGE_H
#define MESSAGE_H

#include <QSharedPointer>

#define MESSAGE_BUFFER_LENGTH 1024

namespace usb {

    class Message
    {
        uint16_t length = MESSAGE_BUFFER_LENGTH;
        uint8_t buffer[MESSAGE_BUFFER_LENGTH];

    public:
        void setCommand(uint8_t command);
        uint8_t getCommand();

        void setReply(uint8_t reply);
        uint8_t getReply();

        void setHeader(uint16_t header);
        uint16_t getHeader();

        void setHeader0(uint8_t header0);
        uint8_t getHeader0();

        void setHeader1(uint8_t header1);
        uint8_t getHeader1();

        void setPayloadLength(uint16_t length);
        uint16_t getPayloadLength();

        uint8_t *getPayload();

        void setPacketLength(uint16_t length);
        uint16_t getPacketLength();
        uint8_t *getPacketBuffer();
    };

    typedef QSharedPointer<Message> pMessage;
}

Q_DECLARE_METATYPE(usb::pMessage)

#endif // MESSAGE_H

/// Copyright (c) 2023 Noé Perard-Gayot (MadMcCrow), François Zajéga (frankiezafe) & Michal Seta (djiamnot)
/// This work is licensed under the terms of the MIT license. For a copy see <https://opensource.org/licenses/MIT>

#ifndef OSCSENDER_H
#define OSCSENDER_H


#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/node.hpp>

#include "osc_msg.h"

using namespace godot;

namespace osc {

    class OSCSender : public Node {
        GDCLASS(OSCSender, Node);

    public:

        static void _bind_methods();

        OSCSender();

        virtual ~OSCSender();

        bool setup(godot::String ip, unsigned int port);

        bool start();

        void stop();

        void msg( String address );

        void add( Variant var );

        void send();

    protected:

        std::string _ip;
        int _port;
        std::size_t _buffer_size;
        String _endpoint;
        bool _is_ready;
        bool _running;

        UdpTransmitSocket* _socket;

        char* _buffer;
        osc::OutboundPacketStream* _packet;
        bool _packet_closed;

        void reset_message();

    };
};

#endif /* OSCSENDER_H */

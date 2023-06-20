/// Copyright (c) 2023 Noé Perard-Gayot (MadMcCrow), François Zajéga (frankiezafe) & Michal Seta (djiamnot)
/// This work is licensed under the terms of the MIT license. For a copy see <https://opensource.org/licenses/MIT>

#include "osc_sender.h"
#include <godot_cpp/variant/utility_functions.hpp>

using namespace osc;

void OSCSender::_bind_methods() {
    ClassDB::bind_method(D_METHOD("setup", "ip", "port"), &OSCSender::setup);
    ClassDB::bind_method(D_METHOD("start"), &OSCSender::start);
    ClassDB::bind_method(D_METHOD("stop"),  &OSCSender::stop);
    ClassDB::bind_method(D_METHOD("msg", "address"),  &OSCSender::msg);
    ClassDB::bind_method(D_METHOD("add", "var"),  &OSCSender::add);
    ClassDB::bind_method(D_METHOD("send"),  &OSCSender::send);
}

OSCSender::OSCSender() :
_port(0), _buffer_size(1024),
_is_ready(false), _running(false),
_socket(0), _buffer(0), _packet(0), _packet_closed(false) {
}

OSCSender::~OSCSender() {

    reset_message();
    stop();

}

bool OSCSender::setup(godot::String ip, unsigned int port) {

    std::string s(ip.utf8().get_data());
    unsigned int p = port;

    if (s.empty()) {
        WARN_PRINT_ED("Invalid osc::OSCSender setup: invalid ip");
        return false;
    }
    if (p <= 0) {
        WARN_PRINT_ED("Invalid osc::OSCSender setup: invalid port");
        return false;
    }

    bool autorestart = false;
    if (_running) {
        stop();
        autorestart = true;
    }

    _ip = s;
    _port = p;
    _endpoint = ip + ":" + godot::String::num(_port);

    _is_ready = true;

    if (autorestart) {
        return start();
    }

    return true;

}

bool OSCSender::start() {

    if (!_is_ready) {
        WARN_PRINT_ED("OSCSender::start, failed to start");
        return false;

    }

    stop();

    try {

        IpEndpointName _message_target = IpEndpointName(_ip.c_str(), _port);
        _socket = new UdpTransmitSocket(_message_target);
        WARN_PRINT_ED("OSCSender::start, started successfully on " + _endpoint);

    } catch (std::exception& e) {

        WARN_PRINT_ED("OSCSender::start, failed to start on " + _endpoint);
        //        std::cout << "scsender::stafailed to startrt, failed to starty" << e.what() << std::endl;

    }




    _running = true;
    return true;

}

void OSCSender::stop() {

    if (_socket) {
        delete _socket;
        _socket = 0;
        UtilityFunctions::print("OSCSender::stop, socket closed on " + _endpoint);
    }
    _running = false;

}

void OSCSender::reset_message() {

    if (_packet) {
        delete _packet;
        _packet = 0;
        _packet_closed = false;
    }
    if (_buffer) {
        delete[] _buffer;
        _buffer = 0;
    }

}

void OSCSender::msg(godot::String address) {

    reset_message();
    std::string std_address(address.utf8().get_data());

    _buffer = new char[_buffer_size];
    _packet = new osc::OutboundPacketStream(_buffer, _buffer_size);
    (*_packet) << osc::BeginBundleImmediate
            << osc::BeginMessage(std_address.c_str());

}

void OSCSender::add(godot::Variant var) {

    if (!_packet) {
        WARN_PRINT_ED("OSCSender::add, message is not ready! "
                "call 'start_message' first!");
        return;
    }

    switch (var.get_type()) {
        case godot::Variant::Type::BOOL:
        {
            bool b = var;
            (*_packet) << b;
        }
            break;
        case godot::Variant::Type::STRING:
        case godot::Variant::Type::NODE_PATH:
        case godot::Variant::Type::RID:
        case godot::Variant::Type::OBJECT:
        {
            godot::String s = var;
            //godot::CharString u = s.utf8();
            //(*_packet) << u.get_data();
        }
            break;
        case godot::Variant::Type::INT:
        {
            int i = var;
            (*_packet) << i;
        }
            break;
        case godot::Variant::Type::FLOAT:
        {
            float f = var;
            (*_packet) << f;
        }
            break;
        case godot::Variant::Type::VECTOR2:
        {
            godot::Vector2 v = var;
            (*_packet) << float( v.x);
            (*_packet) << float( v.y);
        }
            break;
        case godot::Variant::Type::VECTOR3:
        {
            godot::Vector3 v = var;
            (*_packet) << float( v.x);
            (*_packet) << float( v.y);
            (*_packet) << float( v.z);
        }
            break;
        case godot::Variant::Type::QUATERNION:
        {
            godot::Quaternion q = var;
            (*_packet) << float( q.x);
            (*_packet) << float( q.y);
            (*_packet) << float( q.z);
            (*_packet) << float( q.w);
        }
            break;
        case godot::Variant::Type::COLOR:
        {
            godot::Color c = var;
            (*_packet) << float( c.r );
            (*_packet) << float( c.g );
            (*_packet) << float( c.b );
            (*_packet) << float( c.a );
        }
            break;
        default:
            WARN_PRINT_ED("OSCSender::add, unable to add "
                    "this kind of data!");
            break;

    }

}

void OSCSender::send() {

    if (!_packet) {
        WARN_PRINT_ED("OSCSender::send, message is not ready! "
                "call 'start_message' first!");
        return;
    }

    if (!_packet_closed) {
        (*_packet) << osc::EndMessage << osc::EndBundle;
        _packet_closed = true;
    }
    _socket->Send(_packet->Data(), _packet->Size());
}

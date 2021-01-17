
#include "static_helper.h"
#include "core/object/object.h"
#include "core/string/print_string.h"

void Armory::print_msg(Object *obj, const char *txt)
{
    if (obj)
    {
        auto class_name = String("[") + obj->get_class() + String("]");
        auto objet_string = String("[") + obj->to_string() + String("]");
        auto str = class_name + objet_string + String(": ") + txt;
        print_verbose(str);
        return;
    }
    print_verbose(txt);
}

void Armory::print_msg(Object *obj, const String &txt)
{
    if (obj)
    {
        auto class_name = String("[") + obj->get_class() + String("]");
        auto objet_string = String("[") + obj->to_string() + String("]");
        auto str = class_name + objet_string + String(": ") + txt;
        print_verbose(str);
        return;
    }
    print_verbose(txt);
}

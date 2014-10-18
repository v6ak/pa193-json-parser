#include <sstream>
#include <iomanip>
#include "json.h"
using std::endl;

void writeIndentation(std::ostream &out, int indent) {
    for(int i=0; i<indent; i++){
        out << "\t";
    }
}


std::ostream &::Json::operator<<(std::ostream &os, Json::Value const &value) {
    value.dumpTo(os, 0);
    return os;
}

void Json::Number::dumpTo(std::ostream &out, int indent) const{
    out << value;
}

void Json::String::dumpTo(std::ostream &out, int indent) const {
    out << "\"";
    for(char c: value){
        switch (c){
            case '\"':
                out << "\\\"";
                break;
            case '\\':
                out << "\\\\";
                break;
            case '/':
                out << "/";
                break;
            case '\b':
                out << "\\b";
                break;
            case '\f':
                out << "\\f";
                break;
            case '\n':
                out << "\\n";
                break;
            case '\r':
                out << "\\r";
                break;
            case '\t':
                out << "\\t";
                break;
            default:
                if(isprint(c)){
                    out << c;
                }else{
                    std::stringstream ss;
                    ss << std::hex << std::setw(4) << (int)c;
                    out << "\\u" << ss;
                }
        }
    }
    out << "\"";
}

void Json::Null::dumpTo(std::ostream &out, int indent) const {
    out << "null";
}

void Json::Boolean::dumpTo(std::ostream &out, int indent) const {
    out << (value ? "true" : "false");
}

void Json::Array::dumpTo(std::ostream &out, int indent) const {
    out << "[" << endl;
    bool first = true;
    for(Value *v: values){
        if(!first){
            out << "," << endl;
        }
        writeIndentation(out, indent+1);
        out << *v;
        first = false;
    }
    out << endl;
    writeIndentation(out, indent);
    out << "]";
}

void Json::Object::dumpTo(std::ostream &out, int indent) const {
    out << "{" << endl;
    bool first = true;
    for(std::pair<std::string, Value *> const & kv: values){
        if(!first){
            out << "," << endl;
        }
        writeIndentation(out, indent+1);
        out << Json::String(kv.first);
        out << ":";
        kv.second->dumpTo(out, indent+1);
        first = false;
    }
    out << endl;
    writeIndentation(out, indent);
    out << "}";
}

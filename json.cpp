#include <sstream>
#include <iomanip>
#include "json.h"
#include <cctype>
#include <locale>
#include <iconv.h>
#include <iostream>


#define LENGTH(a) (sizeof(a)/sizeof((a)[0]))

using std::endl;
using std::pair;
using std::hex;
using std::setw;
using std::make_shared;
using std::stringstream;
using std::shared_ptr;


void writeIndentation(ostream &out, int indent) {
    for(int i=0; i<indent; i++){
        out << "\t";
    }
}


ostream &::Json::operator<<(ostream &os, Json::Value const &value) {
    value.dumpTo(os, 0);
    return os;
}

void Json::Number::dumpTo(ostream &out, int indent) const{
    out << value;
}

void Json::String::dumpTo(ostream &out, int indent) const {
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
                    stringstream ss;
                    ss << hex << setw(4) << (int)c;
                    out << "\\u" << ss;
                }
        }
    }
    out << "\"";
}

void Json::Null::dumpTo(ostream &out, int indent) const {
    out << "null";
}

void Json::Boolean::dumpTo(ostream &out, int indent) const {
    out << (value ? "true" : "false");
}

void Json::Array::dumpTo(ostream &out, int indent) const {
    out << "[" << endl;
    bool first = true;
    for(shared_ptr<Value> v: values){
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

void Json::Object::dumpTo(ostream &out, int indent) const {
    out << "{" << endl;
    bool first = true;
    for(pair<string, shared_ptr<Value>> const & kv: values){
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

void consumeWhitespace(istream &in) {
    while(iswspace(in.peek())){
        char whitespace;
        in.read(&whitespace, 1);
    }
}

void checkNotEof(istream &in) {
	if(in.eof()){
		throw std::string("Unexpected EOF.");
	}
}


inline void consumeExpectedCharacter(istream &in, char expectedCharacter) {
	char quote;
	in.read(&quote, 1);
	checkNotEof(in);
	if(quote != expectedCharacter){
		throw std::string("Unexpected character: ")+quote;
	}

}

inline void consumeQuote(istream &in){
	consumeExpectedCharacter(in, '\"');
}

shared_ptr<Json::Number> Json::Number::readNumberFrom(istream &in) {
    // TODO: proccess errors
	// TODO: locale
    double x;
    consumeWhitespace(in);
    in >> x;
    return make_shared<Json::Number>(x);
}

void x() {
	size_t inSize = 2;
	//char src[1];
	int n1 = 65;
	int n2 = 66;
	char* src = new char[2]; //(char*)malloc(2*sizeof(char));	// TODO: static allocation;
	src[0] = (char) n1;
	src[1] = (char) n2;
	std::cout << "src[1] = " << src[1] << endl;
	//std::cout << "src[2] = " << src[2] << endl;
	for(int i=0; i<inSize; i++){
		std::cout << "src[";
		std::cout << i;
		std::cout << "] = ";
		std::cout << src[i];
		std::cout << "endl\n";

		/*std::cout << "pSrc[";
		std::cout << i;
		std::cout << "] = ";
		std::cout << " = ";
		std::cout << pSrc[i];
		std::cout << ";";
		std::cout << "endl\n";*/
	}

}


shared_ptr<Json::String> Json::String::readStringFrom(istream &in) {
    consumeWhitespace(in);
	consumeQuote(in);
	stringstream ss;
    char c;
	while(!in.read(&c, 1).eof()){
		//std::cout << "Read char: " << c << std::endl;
		switch (c){
			case '"':
				return make_shared<Json::String>(ss.str());
			case '\\':
				char c2;
				in.read(&c2, 1);
				checkNotEof(in);
				switch (c2){
					case '"':
					case '\\':
					case '/':
						ss << c2;
						break;
					case 'b':
						ss << '\b';
						break;
					case 'f':
						ss << '\f';
						break;
					case 'n':
						ss << '\n';
						break;
					case 'r':
						ss << '\r';
						break;
					case 't':
						ss << '\t';
						break;
					case 'u': {
						char hexa[4];
						in.read(hexa, sizeof(hexa) / sizeof(hexa[0]));
						stringstream hexass;
						for (int i = 0; i < sizeof(hexa) / sizeof(hexa[0]); i++) {
							hexass << hexa[i];
						}
						//long n;
						int n1, n2;
						hexass >> std::hex >> setw(2) >> n1 >> n2;
						checkNotEof(in);
						size_t inSize = 2;
						//char src[1];
						x();
						{
							// just clone of problematic part of code, it does not raise any warning
							size_t inSize1 = 2;
							//char src[1];
							int n11 = 65;
							int n21 = 66;
							char* src = new char[2]; //(char*)malloc(2*sizeof(char));	// TODO: static allocation;
							src[0] = (char) n11;
							src[1] = (char) n21;
							std::cout << "src[1] = " << src[1] << endl;
							//std::cout << "src[2] = " << src[2] << endl;
							for(int i=0; i< inSize1; i++){
								std::cout << "src[";
								std::cout << i;
								std::cout << "] = ";
								std::cout << src[i];
								std::cout << "endl\n";

								/*std::cout << "pSrc[";
								std::cout << i;
								std::cout << "] = ";
								std::cout << " = ";
								std::cout << pSrc[i];
								std::cout << ";";
								std::cout << "endl\n";*/
							}
						}
						char* src = new char[20]; //(char*)malloc(2*sizeof(char));	// TODO: static allocation;
						src[0] = (char) n1;
						src[1] = (char) n2;
						for(int i=2; i<20; i++){src[i] = 'X';};
						std::cout << "src[1] = " << src[1] << endl;
						for(int i=0; i<inSize; i++){
							std::cout << "src[";
							std::cout << i;
							std::cout << "] = ";
							std::cout << src[i];
							std::cout << "endl\n";

							/*std::cout << "pSrc[";
							std::cout << i;
							std::cout << "] = ";
							std::cout << " = ";
							std::cout << pSrc[i];
							std::cout << ";";
							std::cout << "endl\n";*/
						}
						iconv_t ic = iconv_open(""/*"UTF-8"*/, "UCS-2"); // TODO: autoclose
						if (ic == (iconv_t)(-1)){
							throw std::string("Can't convert characters");
						}

						char* pSrc = src;
						while(inSize > 0){
							size_t outSize = 1;
							char out[outSize];
							char* pOut = out;
							std::cout << "iconv()" << inSize << std::endl;
							size_t res = iconv(ic, &pSrc, &inSize, &pOut, &outSize);
							if(res == (size_t)-1){
								switch (errno){
									case E2BIG:
										// continue
										break;
									case EILSEQ:
										throw std::string("Unexpected rejected characters - EILSEQ");
									case EINVAL:
										throw std::string("Unexpected rejected characters - EINVAL");
									default:
										throw std::string("Unknown conversion errno.");
								}
							}else{
								size_t copySize = LENGTH(out) - outSize;
								for(int i=0; i<copySize; i++){
									ss << out[i];
									std::cout << "copy: " << (int)out[i] << " " << out[i] << std::endl;
								}
								std::cout << "res = " << (int)res << std::endl;
							};
						}
						iconv_close(ic);
						/*
						wchar_t cn = (wchar_t)n;
						wchar_t cns[2];
						cns[0] = cn;
						cns[1] = '\0';
						std::wstringstream wss;
						wss << cn;
						//std::locale loc (std::locale(), );

						ss.imbue(loc);
						//iconv_t ic = iconv_open("UTF-8", "UCS-2");
						if (ic == (iconv_t)(-1)){
							throw std::string("Can't convert characters");
						}
						ss << wss.str();
						ss << "(|" << cn << "|)";
						ss << "u(" << n << ")";
						ss << cn;
						*/

						// TODO: check error
						//throw std::string("TODO: implement: \\u")+n; // TODO
						break;
					}
					default:
						throw std::string("Unexpected character: ")+c2;

				}
				break;

				// TODO
			default:
				ss << c;
		}
	}

}

shared_ptr<Json::Value> tryOrFail(istream &in, const string expect, shared_ptr<Json::Value> value) {
	for(char e: expect){
		char a;
		in >> a;
		checkNotEof(in);
		if(e != a){
			throw std::string("Error when expecting token '")+expect+"'. Expected char: '"+e+"'. Actual char: '"+a+"'.";
		}
	}
	return value;
}

shared_ptr<Json::Value> Json::Value::readFrom(istream &in) {
    consumeWhitespace(in);
    char c = in.peek();
	checkNotEof(in);
    switch(c){
        case '\"':
            return String::readStringFrom(in);
        case '[':
            //return Array::readArrayFrom(in);
        case '{':
            //return Object::readObjectFrom(in);
        case 't':
            return tryOrFail(in, "true", make_shared<Json::Boolean>(true));
        case 'f':
            return tryOrFail(in, "false", make_shared<Json::Boolean>(false));
        case 'n':
            return tryOrFail(in, "null", Json::null);
        default:
            if(isdigit(c) || (c == '-')){
                return Number::readNumberFrom(in);
            }
            throw std::string("Unexpected character: ")+c;
    }
}

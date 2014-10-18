#include <iostream>
#include "json.h"

using namespace std;

int main() {
    Json::Number num(3.14159265358972);
    Json::String s("5.\" ' \1 0");
    Json::Boolean t(true);
    Json::Boolean f(false);
    Json::Array a = {{&s, &t, &f, &num}};
    Json::Object o  = {{{"num", &num}, {"t", &t}, {"a", &a}}};
    cout << num << endl << s << endl << endl;
    cout << Json::null << " " << t << " " << f << endl;
    cout << "a: " << a << endl;
    cout << "o: " << o << endl;

    return 0;
}
#include <iostream>
#include "json.h"

using std::shared_ptr;
using std::cout;
using std::endl;
using std::make_shared;
namespace J = Json;

int main() {
    auto num = make_shared<J::Number>(3.14159265358972);
    auto s = make_shared<J::String>("5.\" ' \1 0");
    auto t = make_shared<J::Boolean>(true);
    auto f = make_shared<J::Boolean>(false);
    auto a = make_shared<J::Array>(J::Array({s, t, f, num}));
    auto o = make_shared<J::Object>(J::Object({{"num", num}, {"t", t}, {"a", a}}));
    cout << *num << endl << *s << endl << endl;
    cout << J::null << " " << *t << " " << *f << endl;
    cout << "a: " << *a << endl;
    cout << "o: " << *o << endl;

    return 0;
}

#include <ostream>
#include <vector>
#include <map>
#include <memory>

using std::shared_ptr;
using std::ostream;
using std::string;
using std::vector;
using std::initializer_list;
using std::map;

namespace Json {


    class Value{
    public:
        virtual void dumpTo(ostream &out, int indent) const = 0;
    };


    class Number : public Value{
    // TODO: precision etc.
    private:
        double value;
    public:
        Number(double value): value(value) {}
        virtual void dumpTo(ostream &out, int indent) const;
    };


    class String : public Value{
    // TODO: look at unicode
    // FIXME: Unprintable characters
    private:
        string value;
    public:
        String(string value): value(value) {}
        virtual void dumpTo(ostream &out, int indent) const;
    };

    class Null: public Value{
    public:
        Null(){}
        static const Null value;
        virtual void dumpTo(ostream &out, int indent) const;
    };
    const Null null;

    class Boolean: public Value{
    private:
        bool value;
    public:
        Boolean(bool value): value(value) {};
        virtual void dumpTo(ostream &out, int indent) const;
    };

    class Array: public Value{
    // TODO: safety
    private:
        vector<shared_ptr<Value>> values;
    public:
        Array(initializer_list<shared_ptr<Value>> values): values(values) {};

        virtual void dumpTo(ostream &out, int indent) const;
    };

    class Object: public Value{
    // TODO: safety
    private:
        map<string, shared_ptr<Value>> values;
    public:
        Object(map<string, shared_ptr<Value>> values): values(values) {};
        virtual void dumpTo(ostream &out, int indent) const;
    };


    ostream& operator<<(ostream& os, const Value& value);

}
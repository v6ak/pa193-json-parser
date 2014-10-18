
#include <ostream>
#include <vector>
#include <map>

namespace Json {


    class Value{
    public:
        virtual void dumpTo(std::ostream &out, int indent) const = 0;
    };


    class Number : public Value{
    // TODO: precision etc.
    private:
        double value;
    public:
        Number(double value): value(value) {}
        virtual void dumpTo(std::ostream &out, int indent) const;
    };


    class String : public Value{
    // TODO: look at unicode
    // FIXME: Unprintable characters
    private:
        std::string value;
    public:
        String(std::string value): value(value) {}
        virtual void dumpTo(std::ostream &out, int indent) const;
    };

    class Null: public Value{
    public:
        Null(){}
        static const Null value;
        virtual void dumpTo(std::ostream &out, int indent) const;
    };
    const Null null;

    class Boolean: public Value{
    private:
        bool value;
    public:
        Boolean(bool value): value(value) {};
        virtual void dumpTo(std::ostream &out, int indent) const;
    };

    class Array: public Value{
    // TODO: deallocation
    // TODO: safety
    private:
        std::vector<Value*> values;
    public:
        Array(std::initializer_list<Value*> values): values(values) {};

        virtual void dumpTo(std::ostream &out, int indent) const;
    };

    class Object: public Value{
    // TODO: deallocation
    // TODO: safety
    private:
        std::map<std::string, Value*> values;
    public:
        Object(std::map<std::string, Value*> values): values(values) {};
        virtual void dumpTo(std::ostream &out, int indent) const;
    };


    std::ostream& operator<<(std::ostream& os, const Value& value);

}
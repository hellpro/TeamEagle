#ifndef INVALIDBOOLEXCEPTION_H
#define INVALIDBOOLEXCEPTION_H

#include <string>

using namespace std;

class InvalidBoolException {
    public:
        InvalidBoolException();
        InvalidBoolException(string input);
        int get_exception();

    private:
        int exception_type;
};

#endif // INVALIDBOOLEXCEPTION_H

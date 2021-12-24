//
// Created by jmuppave on 9/15/2021.
//

#ifndef UDEMY_I_PRINTABLE_H
#define UDEMY_I_PRINTABLE_H
class I_Printable
{
    friend std::ostream &operator<<(std::ostream &os, const I_Printable &obj);
public:
    virtual void print(std::ostream &os) const = 0;
    virtual ~I_Printable() = default;
};

//std::ostream &operator<<(std::ostream &os, const I_Printable &obj) {
//    obj.print(os);
//    return os;
//}

#endif //UDEMY_I_PRINTABLE_H

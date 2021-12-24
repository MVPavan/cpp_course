//
// Created by jmuppave on 9/16/2021.
//

#ifndef UDEMY_INSUFFICIENTFUNDSEXCEPTION_H
#define UDEMY_INSUFFICIENTFUNDSEXCEPTION_H

class InsufficientFundsException: std::exception
{
public:
    InsufficientFundsException() noexcept = default;
    ~InsufficientFundsException() override = default;
    const char* what() const noexcept override{
        return "Insufficient funds exception";
    }
};
#endif //UDEMY_INSUFFICIENTFUNDSEXCEPTION_H

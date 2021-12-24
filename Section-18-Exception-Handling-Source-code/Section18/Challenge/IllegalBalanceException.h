#ifndef __ILLEGAL_BALANCE_EXCEPTION_H__
#define __ILLEGAL_BALANCE_EXCEPTION_H__

class IllegalBalanceException:std::exception
{
public:
    IllegalBalanceException() noexcept = default;
    ~IllegalBalanceException() override = default;
    const char* what() const noexcept override{
        return "Illegal balance exception";
    }
};

#endif // __ILLEGAL_BALANCE_EXCEPTION_H__

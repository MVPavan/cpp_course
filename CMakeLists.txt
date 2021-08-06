cmake_minimum_required(VERSION 3.19)
project(udemy)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        udemy
        Section-15-Inheritance-Source-code/Section15/Challenge/main.cpp
        Section-15-Inheritance-Source-code/Section15/Challenge/Account.cpp
        Section-15-Inheritance-Source-code/Section15/Challenge/SavingsAccount.cpp
        Section-15-Inheritance-Source-code/Section15/Challenge/Account_Util.cpp
        Section-15-Inheritance-Source-code/Section15/Challenge/CheckingAccount.cpp
        Section-15-Inheritance-Source-code/Section15/Challenge/TrustAccount.cpp
)
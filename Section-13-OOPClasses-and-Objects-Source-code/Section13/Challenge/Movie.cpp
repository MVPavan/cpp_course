#include <iostream>
#include "Movie.h"

bool Movie::valid_rating(const std::string& rating) {
    if(rating == "G" || rating == "PG" || rating == "PG-13" || rating == "R")
        return true;
    return false;
}

Movie::Movie(const std::string& name, const std::string& rating, int watched)
    : name{name}, rating{rating}, watched{watched}{
    if(!valid_rating(rating)){
        std::cout << "Provided rating " << rating << "for movie " << name << " is not valid !" << std::endl;
    }
}

void Movie::display() const{
    std::cout << name << ", " << rating <<  ", " << watched  <<   std::endl;
}
#ifndef _MOVIES_H_
#define _MOVIES_H_

#include <string>
#include <vector>
#include "Movie.h"

class Movies{
private:
    std::vector<Movie> movies{};
public:
    Movies()=default;
    ~Movies()=default;

    bool add_movie(const std::string& name, const std::string& rating, int watched);

    bool increment_watched(const std::string& name);

    void display() const;

};

#endif
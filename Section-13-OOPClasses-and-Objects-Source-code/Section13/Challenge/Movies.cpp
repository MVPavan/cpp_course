
#include <string>
#include <iostream>
#include "Movies.h"


bool Movies::add_movie(const std::string& name, const std::string& rating, int watched){
    for(const Movie& movie:movies){
        if (movie.get_name()==name){
            std::cout << "Movie with "<< name <<" already exists!" <<std::endl;
            return false;
        }
    }
    Movie temp {name,rating,watched};
    movies.push_back(temp);
    return true;
}

bool Movies::increment_watched(const std::string& name) {
    for (Movie &movie:movies) {
        if (movie.get_name() == name) {
            movie.increment_watched();
            std::cout << name << " watch incremented" << std::endl;
            return true;
        }
    }
    std::cout << name << " not found" << std::endl;
    return false;
}

void Movies::display() const {
    if (movies.empty()) {
        std::cout << "Sorry, no movies to display\n" << std::endl;
    } else {
        std::cout << "\n===================================" << std::endl;
        for(const Movie& movie:movies)
            movie.display();
        std::cout << "\n===================================" << std::endl;
    }
}
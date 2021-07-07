#ifndef _MOVIE_H_
#define _MOVIE_H_

#include <string>
#include <utility>

class  Movie{
private:
    std::string name{};
    std::string rating{};
    int watched {0};
public:
    Movie(const std::string& name, const std::string& rating, int watched);
    ~Movie() = default;

    std::string get_name() const{return name;}
    std::string get_rating() const{return rating;}
    int get_watched() const {return watched;}

    void set_name(std::string name){this->name = std::move(name);}
    void set_rating(std::string rating){this->rating = std::move(rating);}
    void set_watched(int watched){this->watched = watched;}

    void increment_watched() {watched++;}

    void display() const;

    static bool valid_rating(const std::string&);

};

#endif
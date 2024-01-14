#ifndef RECORD_HH
#define RECORD_HH

#include <string>
#include <string.h>

class record{

    int _minute;
    int _wheelbarrow_number;
    int _stone_weight;
    int _number_of_stones;

    std::string _stone_name;

    public:

    record (    int minute, int wheelbarrow_number, int stone_weight, 
                char *stone_name, int number_of_stones );

    int get_minute () { return _minute; }

    int get_wheelbarrow_number () { return _wheelbarrow_number; }

    int get_stone_weight () { return _stone_weight; }

    int get_number_of_stones () { return _number_of_stones; }

    std::string get_stone_name () { return _stone_name; }
    
};

#endif
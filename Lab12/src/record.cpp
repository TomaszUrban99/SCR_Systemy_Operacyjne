#include "record.hh"

record::record ( int minute, int wheelbarrow_number, int stone_weight, 
                char *stone_name, int number_of_stones ){

                    _minute = minute;
                    _wheelbarrow_number = wheelbarrow_number;
                    _stone_weight = stone_weight;
                    _number_of_stones = number_of_stones;

                    _stone_name.assign(stone_name,stone_name + strlen(stone_name));

            }
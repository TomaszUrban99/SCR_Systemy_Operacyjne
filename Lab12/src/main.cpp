#include <iostream>
#include <stdio.h>
#include <string>

#include "log.hh"
#include "record.hh"

int main(int argc, char **argv){

    record new_record ( 1, 2, 3, "tusk", 4);

    std::cout << new_record.get_minute() << " " << new_record.get_number_of_stones() 
    << " " << new_record.get_stone_name() << " " << new_record.get_stone_weight() << std::endl;

    return 0;
}
#include "record.hh"

record::record ( int wheelbarrow_number, int stone_weight, 
                char *stone_name, int number_of_stones ){

                    _wheelbarrow_number = wheelbarrow_number;
                    _stone_weight = stone_weight;
                    _number_of_stones = number_of_stones;

                    strcpy(_stone_name, stone_name);

            }

std::istream &operator>>(std::istream &input, record &new_record){

    int temp_variable;

    /* ----------- Read wheelbarrow number ----------------- */

    input >> temp_variable;

    if ( input.fail() ){    return input;   }

    new_record.set_wheelbarrow_number(temp_variable);

    /* -------------- Read stone name --------------------- */
    
    /*std::string temp_string;
    input >> temp_string;

    if ( input.fail() ){    return input;   }

    new_record.set_stone_name(temp_string);*/

    /* ------------- Read stone weight --------------------- */

    input >> temp_variable;

    if ( input.fail() ){    return input;   }

    new_record.set_stone_weight(temp_variable);

    /* ----------- Read number of stones ------------------- */

    input >> temp_variable;

    if ( input.fail() ){    return input;   }

    new_record.set_number_of_stones(temp_variable);

    return input;
}

std::ostream& operator<<(std::ostream& output, record& record_to_print){

    output  << record_to_print.get_minute() << " " << record_to_print.get_wheelbarrow_number() << " " 
            << record_to_print.get_stone_name() << " " << record_to_print.get_stone_weight() << " " 
            << record_to_print.get_number_of_stones() << std::endl;

    return output;
}
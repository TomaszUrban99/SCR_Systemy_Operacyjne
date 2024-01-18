#include "log.hh"

int log::read_log( char *filename ){

    FILE *file_stream;
    file_stream = fopen (filename, "r");
    char get_char;

    int minute;

    while (  fscanf(file_stream, "%d", &minute)!= EOF ){

        get_char = getc(file_stream);

        record new_record;
    
        while ( get_char != '\n'){

            /* Implement list */
            fscanf(file_stream, "%d%s%d%d", 
                &new_record.get_wheelbarrow_number(), new_record.get_stone_name(),
                &new_record.get_stone_weight(), &new_record.get_number_of_stones());

            /* Set minute in record */
            new_record.set_minute(minute);

            /* Push record to the end of list */
            list_of_rec.push_back(new_record);
        
            get_char = getc(file_stream);

            /* Increment number of records in a log */
            number_of_records++;
        }
    }

    return 0;
}

void log::print_log(){
}


std::istream& operator>>(std::istream &input, log &new_log ){
    return input;
}

std::ostream& operator<<(std::ostream &output, log &log_to_print){

    std::list<record>::iterator pointer;

    for ( pointer = log_to_print.get_list_of_rec().begin(); 
            pointer != log_to_print.get_list_of_rec().end(); ++pointer  ){
                output << *pointer;
            }

    return output;
}
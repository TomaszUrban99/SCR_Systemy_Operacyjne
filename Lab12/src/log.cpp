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
                &list_of_records[number_of_records].get_wheelbarrow_number(), 
                list_of_records[number_of_records].get_stone_name(),
                &list_of_records[number_of_records].get_stone_weight(), 
                &list_of_records[number_of_records].get_number_of_stones());

            /* Set minute in record */
            list_of_records[number_of_records].set_minute(minute);
        
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
    
    int size_of_log = log_to_print.get_number_of_records();

    for ( int i = 0; i < size_of_log; ++i ){
        output << log_to_print[i];
    }

    return output;
}
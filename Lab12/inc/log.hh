#ifndef LOG_HH
#define LOG_HH

#include <iostream>
#include <fstream>
#include <cstdio>
#include <list>

#include "record.hh"

#define SIZE_OF_LOG 100

class log {

    int number_of_records = 0;

    record list_of_records[SIZE_OF_LOG];

    std::list<record> list_of_rec;

    public:

    int get_number_of_records () { return number_of_records; }

    /*!
        \brief Overload of [] operator
        \par int index
    */
    record& operator[] ( int index ) { return list_of_records[index]; }

    /*!
        \brief Read log with records
        \par char **filename - name of file to read
    */
    int read_log ( char *filename );

    /*!
        \brief Print log with records
    */
    void print_log ();

    /*!
        \brief Return reference to list
    */
    std::list<record> &get_list_of_rec () { return list_of_rec; }

};

std::istream& operator>>(std::istream &input, log &new_log );

std::ostream& operator<<(std::ostream &output, log &log_to_print);

#endif
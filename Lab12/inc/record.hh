#ifndef RECORD_HH
#define RECORD_HH

#include <iostream>
#include <string>
#include <string.h>

#define STONE_NAME_LENGTH 10

class record{

    int _minute;
    int _wheelbarrow_number;
    int _stone_weight;
    int _number_of_stones;

    char _stone_name[STONE_NAME_LENGTH];

    public:

    /* --------------- CONSTRUCTORS AND DESTRUCTORS ------------------ */

    record () {}

    record (    int wheelbarrow_number, int stone_weight, 
                char *stone_name, int number_of_stones );

    /* ------------------------ INTERFACE ---------------------------- */

    /*! \brief Return value of _minute attribute */
    int &get_minute () { return _minute; }

    /*! \brief Set value of _minute to minute */
    void set_minute ( int minute ) { _minute = minute; }

    /* --------------------- _WHEELBARROW_NUMBER --------------------- */
    
    int &get_wheelbarrow_number () { return _wheelbarrow_number; }

    void set_wheelbarrow_number ( int wheelbarrow_number ) { 
        _wheelbarrow_number = wheelbarrow_number; }

    /* ---------------------- _STONE_WEIGHT --------------------------- */

    int &get_stone_weight () { return _stone_weight; }

    void set_stone_weight ( int stone_weight ) { _stone_weight = stone_weight; }

    /* ------------------- _NUMBER_OF_STONES -------------------------- */

    int &get_number_of_stones () { return _number_of_stones; }

    void set_number_of_stones ( int number_of_stones ) { _number_of_stones = number_of_stones; }

    /* -------------------------- _STONE_NAME ------------------------- */

    char *get_stone_name () { return _stone_name; }

    void set_stone_name ( char *stone_name ) { strcpy(_stone_name,stone_name); }

};

/*!
    \brief Input operator
*/
std::istream &operator>>(std::istream &input, record &new_record );

/*!
    \brief Output operator
*/
std::ostream &operator<<(std::ostream &output, record &new_record );

#endif
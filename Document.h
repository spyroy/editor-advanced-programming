#pragma once

#include <iostream>
#include <string>
#include <vector>

class Document{
    private:
        std::vector<std::string> doc;
        int rows;
        int row_pointer;
        std::string file_name;
    
    public:
        // constructors
        Document();
        Document(std::string file);
        
        // destructor
        ~Document();

        // functions
        bool move_pointer_to(int to);
        bool add_to_pointer(int add);
        bool subtruct_from_pointer(int sub);
        bool go_to_last();
        bool add_row_after(std::string row);
        bool add_row_befor(std::string row);
        bool after_i();
        bool change_current_row(std::string row);
        bool delete_current_row();
        bool search_for_text(std::string text);
        bool swap_text(std::string old_t, std::string new_t);
        bool join();
        bool write_to_file(std::string file);
        bool quit();

        // getters
        unsigned int get_rows(){return rows;}
        const char* get_file_name(){return file_name.c_str();}

};
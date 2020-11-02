#include "Document.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>

/* constructor */
Document::Document() {
    rows = 0;
    row_pointer = 0;
}

/* constructor */
Document::Document(std::string filename)
{
    rows = 0;
    row_pointer = 0;
    std::ifstream inFile;
    inFile.open(filename);
    if (inFile.fail()) {
        std::cerr << "Error opeing a file" << std::endl;
        inFile.close();
        exit(1);
    }
    std::string line;
    while (getline(inFile, line))
    {
        doc.push_back(line);
        rows++;
    }
    inFile.close();
}

/* destructor */
Document::~Document() {
    doc.clear();
    doc.shrink_to_fit();
    rows = 0;
    row_pointer = 1;
}

/* number case */
bool Document::move_pointer_to(int to){
    if(to > rows || to < 1){
        std::cout << "incorrect input" << std::endl;
        return false;
    }
    row_pointer = to;
    std::cout << "row_pointer: " << row_pointer << " rows: " << rows << std::endl;
    for (auto line = doc.begin(); line != doc.end(); ++line){
        std::cout << *line << std::endl;
    } 
    return true;
}

/* '+' case */
bool Document::add_to_pointer(int add){
    if(row_pointer + add > rows){
        std::cout << "incorrect input" << std::endl;
        return false;
    }
    row_pointer += add;
    std::cout << "row_pointer: " << row_pointer << " rows: " << rows << std::endl;
    for (auto line = doc.begin(); line != doc.end(); ++line){
        std::cout << *line << std::endl;
    } 
    return true;
}

/* '-' case */
bool Document::subtruct_from_pointer(int sub){
    if(row_pointer - sub < 1){
        std::cout << "incorrect input" << std::endl;
        return false;
    }
    row_pointer -= sub;
    std::cout << "row_pointer: " << row_pointer << " rows: " << rows << std::endl;
    for (auto line = doc.begin(); line != doc.end(); ++line){
        std::cout << *line << std::endl;
    } 
    return true;
}

/* '$' case */
bool Document::go_to_last(){
    row_pointer = rows;
    std::cout << "row_pointer: " << row_pointer << " rows: " << rows << std::endl;
    for (auto line = doc.begin(); line != doc.end(); ++line){
        std::cout << *line << std::endl;
    } 
    return true;
}

/* 'a' case */
bool Document::add_row_after(std::string row){
    if(row.size() == 0){
        return true;
    }
    if(row == "."){
        return false;
    }
    std::vector<std::string>::iterator it;
    it = doc.begin();
    doc.insert(it+row_pointer,row);
    row_pointer++;
    rows++;
    return true;
}

/* 'i' case */
bool Document::add_row_befor(std::string row){
    if(rows == 0){
        std::cout << "incorrect input" << std::endl;
        return false;
    }
    if(row.size() == 0){
        return true;
    }
    if(row == "."){
        return false;
    }
    int tmp = row_pointer;
    std::vector<std::string>::iterator it;
    it = doc.begin();
    doc.insert(it+row_pointer-1,row);
    rows++;
    row_pointer++;
    return true;
}

/* correcting row_pointer */
bool Document::after_i(){
    row_pointer--;
    return true;
}

/* 'c' case */
bool Document::change_current_row(std::string row){
    if(rows == 0){
        std::cout << "nothing to change" << std::endl;
        return false;
    }
    if(row.size() == 0){
        return true;
    }
    if(row == "."){
        return false;
    }
    add_row_after(row);
    return true;
}

bool Document::after_c(int i){
    std::cout << "i is " << i << std::endl;
    row_pointer -= i;
    delete_current_row();
    row_pointer += i-1;
    return true;
}

/* 'd' case */
bool Document::delete_current_row(){
    if(rows == 0){
        std::cout << "nothing to delete" << std::endl;
        return false;
    }
    std::vector<std::string>::iterator it;
    it = doc.begin();
    doc.erase(it+row_pointer-1);
    if(rows == 1)
        row_pointer--;
    rows--;
    std::cout << "row_pointer: " << row_pointer << " rows: " << rows << std::endl;
    for (auto line = doc.begin(); line != doc.end(); ++line){
        std::cout << *line << std::endl;
    } 
    return true;
}

/* '/.../' case */
bool Document::search_for_text(std::string text){
    if(rows == 0){
        std::cout << "nothing to search" << std::endl;
        return false;
    }
    std::vector<std::string>::iterator it;
    it = doc.begin()+row_pointer;
    int tmp = row_pointer;
    bool found = false;

    /* first search from current row */
    for (int i = row_pointer-1; i < rows; ++i){
        if (doc.at(i).find(text) != std::string::npos){
            std::string temp = "";
            int index = doc.at(i).find(text);
            found = true;
            break;   
        }
        row_pointer++;
    }

    /* starting the search from the beggining */
    if(found == false){
        row_pointer = 1;
        for (int i = 0; i < rows; ++i){
            if (doc.at(i).find(text) != std::string::npos){
                std::string temp = "";
                int index = doc.at(i).find(text);
                found = true;
                break;           
            }
            row_pointer++;
        }
    }

    /* the word was not found */
    if(found == false){
        row_pointer = tmp;
        std::cout << "could not find the word: " << text << std::endl;
        return false;
    }

    std::cout << "row_pointer: " << row_pointer << " rows: " << rows << std::endl;
    for (auto line = doc.begin(); line != doc.end(); ++line){
        std::cout << *line << std::endl;
    } 

    return true;
}

/* 's/.../.../' case */
bool Document::swap_text(std::string old_t, std::string new_t){
    bool flag = search_for_text(old_t);
    if(flag == false){
        return false;
    }
    int index;
    if(doc.at(row_pointer-1).find(old_t) != std::string::npos){
        index = doc.at(row_pointer-1).find(old_t);
    }
    else
    {
        std::cout << "could not find the word: " << old_t << std::endl;
        return false;
    }
    doc.at(row_pointer-1).replace(index,old_t.size(),new_t);
    std::cout << "row_pointer: " << row_pointer << " rows: " << rows << std::endl;
    for (auto line = doc.begin(); line != doc.end(); ++line){
        std::cout << *line << std::endl;
    } 
    return true;
}

/* 'j' case */
bool Document::join(){
    if(rows == 1 || row_pointer == rows){
        std::cout << "nothing to join" << std::endl;
        return false;
    }
    doc.at(row_pointer-1) += " ";
    doc.at(row_pointer-1) += doc.at(row_pointer);
    std::vector<std::string>::iterator it;
    it = doc.begin()+row_pointer;
    doc.erase(it);
    rows--;
    std::cout << "row_pointer: " << row_pointer << " rows: " << rows << std::endl;
    for (auto line = doc.begin(); line != doc.end(); ++line){
        std::cout << *line << std::endl;
    } 
    return true;
}

/* 'w' case */
bool Document::write_to_file(std::string file){
    std::vector<std::string> tmp;
    copy(doc.begin(), doc.end(), back_inserter(tmp));
    std::fstream inFile;
    inFile.open(file);
    if (inFile.fail()) {
        std::ofstream outfile (file);
        while(!tmp.empty()){
            outfile << tmp.front() << std::endl;
            tmp.erase(tmp.begin());
        }
    }
    else
    {
        while(!tmp.empty()){
            inFile << tmp.front() << std::endl;
            tmp.erase(tmp.begin());
        }
    }
    inFile.close();

    return true;
}

#include "Editor.h"
#include "Document.h"
#include <sstream>

void Editor::loop(){
    std::string input;

    while(true){
        getline(std::cin,input);
        std::string c = input.substr(0,1);
        char command = c[0];
        int number;

        /* in case a number was entered */
        if(isdigit(command)){
            number = atoi(input.c_str());
            doc.move_pointer_to(number);
            std::cin.clear();
            continue;
        }

        switch(command){
            
            /* add to pointer */
            case '+':
                input = input.substr(1,input.size()-1);
                number = atoi(input.c_str());
                doc.add_to_pointer(number);
                std::cin.clear();
                break;
            
            /* subtruct from pointe */
            case '-':
                input = input.substr(1,input.size()-1);
                number = atoi(input.c_str());
                doc.subtruct_from_pointer(number);
                std::cin.clear();
                break;
            
            /* go to last line */
            case '$':
                doc.go_to_last();
                std::cin.clear();
                break;
            
            /* add row after current row */
            case 'a':{
                bool flag = false;
                std::string txt;
                while(true){
                    std::getline(std::cin,txt);
                    flag = doc.add_row_after(txt);
                    if(flag == false){
                        break;
                    }
                }
                std::cin.clear();
                break;
            }

            /* add row before current row */
            case 'i':{
                bool flag = false;
                std::string txt;
                while(doc.get_rows() != 0){
                    std::cout << "im here" << std::endl;
                    std::getline(std::cin,txt);
                    flag = doc.add_row_befor(txt);
                    if(flag == false){
                        break;
                    }
                }
                if(doc.get_rows() != 0)
                    doc.after_i();
                std::cin.clear();
                break;
            }
            
            /* change current row */
            case 'c':{
                bool flag = false;
                std::string txt;
                int i = 0;
                while(true){
                    std::getline(std::cin,txt);
                    flag = doc.change_current_row(txt);
                    i++;
                    if(flag == false){
                        break;
                    }
                }
                doc.after_c(i);
                std::cin.clear();
                break;
            }

            /* delete current row */
            case 'd':
                doc.delete_current_row();
                std::cin.clear();
                break;

            /* go to <txt> row */
            case '/':
                input = input.substr(1,input.size()-2);
                doc.search_for_text(input);
                std::cin.clear();
                break;

            /* swap text */
            case 's':{
                std::string old_s = input.substr(2,input.size()-3);
                int index = 0;
                for(int i = 0; i < old_s.size(); i++){
                    if(old_s[i] == '/'){
                        break;
                    }
                    index++;
                }
                std::string tmp = old_s;
                old_s = old_s.substr(0,index);
                std::string new_s = tmp.substr(index+1,tmp.size()-old_s.size()-1);
                doc.swap_text(old_s,new_s);
                std::cin.clear();
                break;
            }

            /* join current row with the one after it */
            case 'j':
                doc.join();
                std::cin.clear();
                break;

            /* write to file */
            case 'w':{
                input = input.substr(1,input.size()-1);
                doc.write_to_file(input);
                std::cin.clear();
                break;
            }

            /* quit program */
            case 'q':
                exit(0);

            default:
                std::cin.clear();
                std::cout << "?" << std::endl;
                break;
        }
    }
}
#include <iostream>

int main(){
    while(true){
        std::string txt;
        std::cin >> txt;
        if(txt == "."){
            break;
        }
        else{
            std::cout << txt << std::endl;
        }
    }
    return 0;
}
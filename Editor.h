#pragma once

#include <iostream>
#include <string>
#include "Document.h"

class Editor{
    private: 
        Document doc;

    public:
        Editor(){;}
        Editor(char* filename):doc(filename){};
        ~Editor(){;}
        void loop();
};

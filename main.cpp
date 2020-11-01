#include "Editor.h"

int main(int argc, char** argv){
    
    switch (argc)
    {
        /* no file input */
        case 1:{
            Editor editor;
            editor.loop();
            break;
        }

        /* with file input */
        case 2:{
            Editor editor(argv[1]);
            editor.loop();
            break;
        }

        default:
            break;
    }

    return 0;
}
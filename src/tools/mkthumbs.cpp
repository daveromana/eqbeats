#include <text/text.h>
#include <track/art.h>
#include <iostream>
#include <wand/magick_wand.h>

int main(int argc, char **argv){
    if(argc != 2){
        std::cerr << "Usage: mkthumbs ID" << std::endl;
        return 1;
    }
    MagickWandGenesis();
    int tid = number(argv[1]);
    if(!tid) return 1;
    Art art(tid);
    if(!art) return 1;
    art.makeThumbs();
    MagickWandTerminus();
    return 0;
}

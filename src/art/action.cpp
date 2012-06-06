#include "actions.h"
#include "../art.h"
#include "../session.h"
#include "../track.h"
#include "../user.h"
#include <text/text.h>
#include "../path.h"
#include "../cgi.h"

void Action::uploadArt(int tid){
    cgicc::file_iterator file = cgi.getFile("file");
    if(Track(tid).artist() == Session::user() && file != cgi.getFiles().end()){
        std::string filename = eqbeatsDir() + "/art/" + number(tid);
        std::ofstream out(filename.c_str(), std::ios_base::binary);
        file->writeToStream(out);
        out.close();
        Art art(tid);
        art.makeThumbs();
    }
    //redirect(Track::url(tid));
}

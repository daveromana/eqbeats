#include "pages.h"
#include "../audio.h"
#include "../extended.h"
#include <core/cgi.h>
#include <text/text.h>
#include <unistd.h>
#include <render/file.h>
#include <stat/stat.h>

void Pages::trackMisc(Document *doc){

    std::string sub;
    int tid = route("track", path, sub);
    if(!tid) return;

    if(sub == "embed"){
        Track t(tid);
        if(t){
            t.fill(doc->dict());
            t.player(doc->dict(), true);
        }
        doc->setTemplate("html/player-embed.tpl", "text/html", t ? 200 : 404);
        doc->dict()->ShowSection(t ? "FOUND" : "NOT_FOUND");
        return;
    }

    else if(sub == "json"){
        ExtendedTrack t(tid);
        if(!t) return;
        doc->setJson("json/track.tpl");

        doc->dict()->ShowSection("HAS_AVATAR");

#ifdef HAVE_LIBHIREDIS
        doc->dict()->ShowSection("HAS_STATS");
        Dict *stats = doc->dict()->AddIncludeDictionary("STATS");
        stats->SetFilename("json/stats.tpl");

        Stat::fillMeasurement(stats, "trackView", t.artist.id, tid, false, false);
        Stat::fillMeasurement(stats, "trackPlay", t.artist.id, tid, false, false);
        Stat::fillMeasurement(stats, "trackDownload", t.artist.id, tid, false, false);

        stats->ShowSection("HAS_UNIQUE");
        Stat::fillMeasurement(stats, "trackView", t.artist.id, tid, true, false);
        Stat::fillMeasurement(stats, "trackPlay", t.artist.id, tid, true, false);
        Stat::fillMeasurement(stats, "trackDownload", t.artist.id, tid, true, false);
#endif

        t.fill(doc->dict());
    }

    // Download

    else if(sub == "original" || sub == "vorbis" || sub == "mp3"
            || sub == "aac" || sub == "opus"){
        Track t(tid);
        if(!t)
            return;
        else if(sub == "original")
            doc->download(Audio(&t).original(), true);
        else if(sub == "vorbis")
            doc->download(Audio(&t).vorbis(), true);
        else if(sub == "aac")
            doc->download(Audio(&t).aac(), true);
        else if(sub == "opus")
            doc->download(Audio(&t).opus(), true);
        else
            doc->download(Audio(&t).mp3(), true);
    }

}

#include <stdio.h>
#include "actions.h"
#include "../html/html.h"
#include "../session.h"
#include "../utils.h"

using namespace std;
using namespace Html;

std::string Action::trackVisibility(int tid, cgicc::Cgicc &cgi){
    User u = Session::user();
    Track t(tid);
    if(u.id() != t.artistId() || !u || 
       ( cgi("visible") != "t" && cgi("visible") != "f" ) ||
       cgi.getEnvironment().getRequestMethod() != "POST")
        return redirect("/");
    t.setVisible(cgi("visible")=="t");
    return redirect(t.url());
}

std::string Action::updateNotes(int tid, cgicc::Cgicc &cgi){
    User u = Session::user();
    Track t(tid);
    if(u.id()==t.artistId() && u &&
       cgi.getEnvironment().getRequestMethod() == "POST" )
        t.setNotes(cgi("notes"));
    return redirect(t.url());
}

std::string Action::renameTrack(int tid, cgicc::Cgicc &cgi){
    User u = Session::user();
    Track t(tid);
    if(u.id()==t.artistId() && u && !cgi("title").empty() &&
       cgi.getEnvironment().getRequestMethod() == "POST" )
        t.setTitle(cgi("title"));
    return redirect(t.url());
}

std::string deletionForm(const Track &t){
    return header("Track deletion") +
        "<form method=\"post\">"
            "Do you really want to delete <b>" + escape(t.title()) + "</b> ? "
            "<input type=\"submit\" value=\"Delete\" name=\"confirm\" />"
        "</form>"
        "<a class=\"danger\" href=\"" + t.url() + "\">Cancel</a>"
        + footer();
}

std::string Action::deleteTrack(int tid, cgicc::Cgicc &cgi){
    User u = Session::user();
    Track t(tid);
    if(u.id()!=t.artistId() || !u)
        return redirect(t.url());
    if(cgi.getEnvironment().getRequestMethod()!="POST" || cgi("confirm")!="Delete")
        return deletionForm(t);
    t.remove();
    return redirect(u.url());
}

std::string Action::updateCategories(int tid, cgicc::Cgicc &cgi){
    User u = Session::user();
    Track t(tid);
    if(u.id()!=t.artistId() || !u || cgi.getEnvironment().getRequestMethod()!="POST")
        return redirect(t.url());
    
    if(!cgi("rmcats").empty()){
        vector<Category> cats = t.getCategories();
        vector<int> ids;
        for(vector<Category>::iterator i = cats.begin(); i != cats.end(); i++)
            if(!cgi(number(i->id())).empty())
                ids.push_back(i->id());
        if(!ids.empty())
            t.removeCategories(ids);
    }
    else if(!cgi("cat").empty())
        t.addCategory(number(cgi("cat")));
    return redirect(t.url());
}
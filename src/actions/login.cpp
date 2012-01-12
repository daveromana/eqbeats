#include "actions.h"
#include "../session.h"
#include "../html/html.h"

std::string loginForm(const cgicc::Cgicc &cgi, const std::string &error=std::string()){
    return Html::header("Login") + "<h2>Login</h2>" +
        (error.empty() ? "" : "<div class=\"error\">" + error + "</div>") +
        "<form action=\"/login\" method=\"post\">"
            "<table>"
                "<tr>"
                    "<td><label for=\"r_email\">Email:</label></td>"
                    "<td><input id=\"r_email\" name=\"email\" "
                    "value=\""+cgi("email")+"\"/></td>"
                "</tr>"
                "<tr>"
                    "<td><label for=\"r_pw\">Password:</label></td>"
                    "<td><input id=\"r_pw\" name=\"pw\" type=\"password\" /></td>"
                "</tr>"
            "</table>"
            "<input type=\"submit\" value=\"Login\" />"
            "<input type=\"hidden\" name=\"redirect\" value=\""+cgi("redirect")+"\" />"
        "</form>"
        "<a href=\"/register\">Register</a>"
        + Html::footer();
}

std::string Action::login(cgicc::Cgicc &cgi){
    if(Session::user()) return Html::redirect(cgi("redirect").empty()? Session::user().url() : cgi("redirect"));

    if(cgi.getEnvironment().getRequestMethod() != "POST")
        return loginForm(cgi);

    if(cgi("email").empty())
        return loginForm(cgi, "Please specify an Email address.");

    if(cgi("pw").empty())
        return loginForm(cgi, "Please specify a password.");

    std::string sid = Session::login(cgi("email"), cgi("pw"), cgi.getEnvironment().getRemoteAddr());
    if(sid.empty())
        return loginForm(cgi, "Sorry, wrong credentials.");

    return "Set-Cookie: sid=" + sid + ";Max-Age=2592000\n" // 30 days
    + Html::redirect(cgi("redirect").empty()? Session::user().url() : cgi("redirect")) +
        "Logged in, redirecting...";
}

std::string Action::logout(cgicc::Cgicc &cgi){
    Session::logout();
    return "Set-Cookie: sid=\n" + Html::redirect(cgi("redirect").empty()?"/":cgi("redirect")) +
        "Logged out, redirecting...";
}
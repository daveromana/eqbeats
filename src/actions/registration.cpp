#include "actions.h"
#include "../render/html/page.h"
#include "../render/http.h"
#include "../account.h"
#include "../session.h"
#include "../log.h"
#include "../number.h"
#include "../render/render.h"
#include "../cgi.h"

using namespace Render;

void registrationForm(const std::string &error=std::string()){
    Html::header("Register");
    o << "<h2>Register</h2>"
      << (error.empty() ? "" : "<div class=\"error\">" + error + "</div>")
      << "<form action=\"/register\" method=\"post\">"
            "<table>"
                "<tr>"
                    "<td><label for=\"r_name\">Display name:</label></td>"
                    "<td><input id=\"r_name\" name=\"name\" /></td>"
                "</tr>"
                "<tr>"
                    "<td><label for=\"r_email\">Email:</label></td>"
                    "<td><input id=\"r_email\" name=\"email\" /></td>"
                "</tr>"
                "<tr>"
                    "<td><label for=\"r_pw\">Password:</label></td>"
                    "<td><input type=\"password\" id=\"r_pw\" name=\"pw\" /></td>"
                "</tr>"
                "<tr>"
                    "<td><label for=\"r_pwconf\">Confirm password:</label></td>"
                    "<td><input type=\"password\" id=\"r_pwconf\" name=\"pwconf\" /></td>"
                "</tr>"
            "</table>"
            "<input type=\"submit\" value=\"Register\" />"
        "</form>";
    Html::footer();
}

void Action::registration(){
    if(Session::user()) return Http::redirect("/");
    if(cgi.getEnvironment().getRequestMethod() != "POST")
        return registrationForm();
    if(cgi("name").empty())
        return registrationForm("Please specify a display name.");
    if(cgi("email").empty())
        return registrationForm("Please specify an email address.");
    if(!Account::validEmail(cgi("email")))
        return registrationForm("Invalid email address.");
    if(cgi("pw").empty())
        registrationForm("Please specify a password.");
    if(cgi("pw")!=cgi("pwconf"))
        return registrationForm("Passwords mismatch.");
    Account account = Account::create(cgi("name"), cgi("pw"), cgi("email"));
    if(!account)
        return registrationForm("Sorry, name or email already in use.");

    log("New user: " + account.name() + " (" + number(account.id()) + ")");

    o << "Set-Cookie: sid="
      << Session::login(account.id(), cgi.getEnvironment().getRemoteAddr())
      << ";Max-Age=2592000\n"; // 30 days
    Http::redirect("/quickstart");
    o << "Account created, redirecting...";
}

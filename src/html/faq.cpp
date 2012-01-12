#include "html.h"

std::string Html::faq(){
    return header("FAQ") + "<h2>Frequently Asked Questions</h2><div class=\"faq\">"

        "<div><h4>What is this?</h4>"
        "<p>A place for artists to publish their MLP-related music, and get in touch with their audience.</p></div>"

        "<div><h4>Why?</h4>"
        "<p>Because there is no other central repository for MLP music.</p></div>"

        "<div><h4>Why not [INSERT SITE HERE]?</h4>"
        "<p>Because we try to make the publishing and listening process as smooth as can be. No ads, no limits, no downsides.</p></div>"

        "<div><h4>I've got a question/problem/idea!</h4>"
        "<p>What are you waiting for? Drop us a line at contact@eqbeats.org.</p></div>"

        "</div>" + footer();
}
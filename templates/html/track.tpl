{{%AUTOESCAPE context="HTML"}}
<div class="track">
    <h2>{{TITLE}}
        <span class="buttons">
            {{#NOT_FAVORITE}}
            <a href="{{#LOGGED_OUT}}/login?redirect={{/LOGGED_OUT}}/track/{{TLINK}}/favorite"
            title="Add to favorites">
                <img src="/static/icons/star-empty.png" alt="Add to favorites" /></a>
            {{/NOT_FAVORITE}}
            {{#IS_FAVORITE}}
            <a href="{{#LOGGED_OUT}}/login?redirect={{/LOGGED_OUT}}/track/{{TLINK}}/unfavorite"
            title="Remove from favorites">
                <img src="/static/icons/star.png" alt="Remove from favorites" /></a>
            {{/IS_FAVORITE}}
            {{#IS_VISIBLE}}{{#HAS_PLAYLISTS}}
            <span id="addplaylist">
                <img src="/static/icons/playlist-add.png" alt="Playlists">
                <form action="/track/{{TLINK}}/playlist" method="post" title="Add to playlist">
                    <select name="playlist">
                        {{#PLAYLIST}}<option value="{{PLAYLIST_ID}}">{{PLAYLIST_NAME}}</option>{{/PLAYLIST}}
                    </select><input type="submit" value="Add to this playlist"/>
                </form>
            </span>
            {{/HAS_PLAYLISTS}}{{/IS_VISIBLE}}
        </span>
    </h2>
    <h4>by <a href="/user/{{ULINK}}">{{USERNAME}}</a> <span class="date">on {{DAY}}</span></h4>

    {{#HAS_ART}}<img class="art" alt="" src="/track/{{TLINK}}/art/medium" />{{/HAS_ART}}

    {{#READY}}{{>PLAYER}}{{/READY}}
    {{#HAS_STATUS}}<div class="status">Status: {{STATUS}}</div>{{/HAS_STATUS}}

    <div class="toolbar">
        {{#READY}}
        <span><img alt="" src="/static/icons/drive-download.png" /> Download :
            <a href="/track/{{TLINK}}/vorbis">OGG Vorbis</a>
            {{#MP3_SOURCE}}<a href="/track/{{TLINK}}/mp3">Original MP3</a>{{/MP3_SOURCE}}
            {{#OTHER_SOURCE}}
            <a href="/track/{{TLINK}}/mp3">MP3</a>
            <a href="/track/{{TLINK}}/original">Original ({{EXTENSION}})</a>
            {{/OTHER_SOURCE}}
            <a href="/track/{{TLINK}}/art" target="_blank">Art</a>
        </span>
        {{/READY}}
        <span><img alt="" src="/static/icons/balloon-white-left.png" /> Share : <a href="#embedcode" onclick="document.getElementById('embedcode').style.display='block';return false;">Embed</a></span>

        {{#IS_SELF}}
        {{#HAS_HITS}}<span><img alt="" src="/static/icons/edit-number.png" /> Hits : {{HIT_COUNT}}</span>{{/HAS_HITS}}
        {{/IS_SELF}}
        {{#NOT_SELF}}
        <form action="/track/{{TLINK}}/report" method="post">
            <button type="submit" class="report"><img alt="" src="/static/icons/flag.png" /> <span>Report</span></button>
        </form>
        {{/NOT_SELF}}
    </div>
    <textarea id="embedcode" style="display:none;">{{>EMBED_CODE:html_escape}}</textarea>

    {{#IS_SELF}}
    <div class="toolbar tags"><img alt="" src="/static/icons/tag.png" /> Tags:
        <form action="/track/{{TLINK}}/tags" method="post">
            <input name="tags" value="{{#TAG}}{{TAG}}{{#TAG_separator}}, {{/TAG_separator}}{{/TAG}}" />
            <input type="submit" value="Update" />
            <span class="legend">(comma-separated, e.g. instrumental, electronic)</span>
        </form>
    </div>
    {{/IS_SELF}}
    {{#NOT_SELF}}{{#HAS_TAGS}}
    <div class="toolbar tags"><img alt="" src="/static/icons/tag.png" /> Tags:
        {{#TAG}}<a href="/tracks/tag/{{TAG}}">{{TAG}}</a>{{/TAG}}
    </div>
    {{/HAS_TAGS}}{{/NOT_SELF}}

    <div class="license">
        {{#COPYRIGHT}} Copyright &copy; {{USERNAME}} {{/COPYRIGHT}}
        {{#OTHER_LICENSE}} License: {{LICENSE}} {{/OTHER_LICENSE}}
        {{#IS_SELF}}<a href="/track/{{TLINK}}/license">(change)</a>{{/IS_SELF}}
    </div>

    {{#HAS_NOTES}}<div class="notes">{{NOTES:x-format}}</div>{{/HAS_NOTES}}

    {{>EVENTS}}
    <form class="postcomment" action="/track/{{TLINK}}/comment" method="post">
        {{#LOGGED_OUT}}Name : <input type="text" name="name" /><br />{{/LOGGED_OUT}}
        <input class="honeypot" type="text" name="url" placeholder="If you can see this, don't fill it in." />
        <textarea name="msg"></textarea><br />
        <input type="submit" value="Post a comment" onclick="this.form.submit();this.disabled=true;return false;" />
    </form>

    {{#IS_SELF}}
    <div class="edit">
        <h3><img src="/static/icons/pencil.png" alt="" /> Edit</h3>
        {{#IS_HIDDEN}}
        <form class="publish" action="/track/{{TLINK}}/publish" method="post">
            <img src="/static/icons/disc-arrow.png" alt="" />
            This track is not yet published.
            <input type="submit" value="Publish"/>
            <input type="hidden" name="tid" value="{{TLINK}}"/>
        </form>
        {{/IS_HIDDEN}}

        <div class="rename">
            <h4><img alt="" src="/static/icons/rename.png" /> Rename</h4>
            <form method="post" action="/track/{{TLINK}}/rename">
                <b>{{USERNAME}}</b> -
                <input type="text" name="title" value="{{TITLE}}" />
                <input type="submit" value="Rename" />
            </form>
        </div>


        <div class="column">

            <h4><img src="/static/icons/drive-upload.png" alt="" /> Re-upload</h4>
            {{>UPLOADER}}

            <h4><img src="/static/icons/picture.png" alt="" /> Art</h4>
            <form action="/track/{{TLINK}}/art/upload" method="post" enctype="multipart/form-data">
                <input type="file" name="file" />
                <input type="submit" value="Upload a picture" />
            </form>

            <h4><img src="/static/icons/balloon-sound.png"> Broadcast</h4>
            <form action="/track/{{TLINK}}/flags" method="post">
                <input type="checkbox" name="airable" {{#IS_AIRABLE}}checked="checked"{{/IS_AIRABLE}} />
                Celestia Radio<br />
                <input type="submit" value="Update" />
            </form>
            <h4><img src="/static/icons/youtube-up.png" alt=""> Youtube</h4>
            {{#HAS_YOUTUBE}}
            <form action="/track/{{TLINK}}/youtube_upload">
                <input type="submit" value="Upload this to YouTube"/>
                <a class="huh" href="/faq#youtube">Huh?</a>
            </form>
            {{/HAS_YOUTUBE}}
            {{#NO_YOUTUBE}}
            <form action="https://accounts.google.com/o/oauth2/auth">
                Your YouTube account is not linked.
                <a class="huh" href="/faq#youtube">Huh?</a>
                </br>
                <input type="submit" value="Link your YouTube account"/>
                <input type="hidden" name="response_type" value="code"/>
                <input type="hidden" name="client_id" value="767490682254.apps.googleusercontent.com"/>
                <input type="hidden" name="scope" value="https://uploads.gdata.youtube.com/feeds/api/users/default/uploads"/>
                <input type="hidden" name="access_type" value="offline"/>
                <input type="hidden" name="redirect_uri" value="http://eqbeats.org/oauth/yt"/>
                <input type="hidden" name="approval_prompt" value="force"/>
            </form>
            {{/NO_YOUTUBE}}
        </div>

        <div class="column">
            <h4><img src="/static/icons/card-pencil.png" /> Notes</h4>
            <form action="/track/{{TLINK}}/notes" method="post">
                <textarea name="notes">{{#HAS_NOTES}}{{NOTES:pre_escape}}{{/HAS_NOTES}}</textarea><br />
                <div class="legend">(tags: [b]old, [u]nderline, [i]talic)</div>
                <input type="submit" value="Update description" />
            </form>
        </div>
        <a class="delete" href="/track/{{TLINK}}/delete">Delete track</a>
        <div style="clear:both;"></div>
    </div>
    {{/IS_SELF}}

</div>


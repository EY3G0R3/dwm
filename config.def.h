/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 4;        /* border pixel of windows */
static const unsigned int gappx     = 6;        /* gap pixel between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const Bool viewontag         = True;     /* Switch view on tag switch */

static const char *fonts[]          = { "monospace:pixelsize=13" };
static const char dmenufont[]       = "monospace:pixelsize=13";

static char normbordercolor[]  = "#928374";
static char normbgcolor[]      = "#282828";  // gruvbox dark bg
static char normfgcolor[]      = "#eeeeee";  // lightgray
static char selbordercolor[]   = "#005577";  // cyan
static char selbgcolor[]       = "#005577";  // cyan
static char selfgcolor[]       = "#eeeeee";  // lightgray
static char titlebordercolor[] = "#282828";  // gruvbox dark bg
static char titlebgcolor[]     = "#282828";  // gruvbox dark bg
static char titlefgcolor[]     = "#eeeeee";  // lightgray


static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*                      fg            bg               border   */
	[SchemeNorm]   = { normfgcolor  , normbgcolor   , normbordercolor  },
	[SchemeSel]    = { selfgcolor   , selbgcolor    , selbordercolor   },
	[SchemeTitle]  = { titlefgcolor , titlebgcolor  , titlebordercolor },
};

static const char *xres = "/home/igorg/.Xresources";

/* tagging */
static const char *tags[] = { "~", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0" };

static const Rule rules[] = {
	// xprop(1):
	//      WM_CLASS(STRING) = instance, class
	//      WM_NAME(STRING) = title
	/* class           instance                                       title       tags mask     isfloating   monitor */
	{ "Google-chrome", "www.wunderlist.com"                         , NULL,       1 << 1,       0,           -1 },
	{ "Firefox"      , NULL                                         , NULL,       1 << 2,       0,           -1 },
	{ "Google-chrome", "outlook.office365.com__owa"                 , NULL,       1 << 3,       0,           -1 },
	{ "Google-chrome", "outlook.office.com__calendar_view_workweek" , NULL,       1 << 4,       0,           -1 },
	{ "Google-chrome", "our.intern.facebook.com__intern_calendar"   , NULL,       1 << 4,       0,           -1 },
	{ "Google-chrome", "fb.workplace.com__chat"                     , NULL,       1 << 5,       0,           -1 },
	{ "Google-chrome", "www.messenger.com"                          , NULL,       1 << 6,       0,           -1 },
	{ "Nautilus"     , "nautilus"                                   , NULL,       1 << 7,       0,           -1 },
	{ "Steam"        , NULL                                         , NULL,       1 << 9,       0,           -1,},
// igorg: Spotify detection doesn't seem to work
	{ "Spotify"      , NULL                                         , NULL,       1 << 10,      0,           -1,},
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
// igorg: custom characters for layouts
// igorg: some more: ╠ ├ ┣ ▞ ꖸ 𐌎
// TODO: pick more representative symbols now that I realized that symbols need to be 3 characters long
//       to avoid jerking while switching layouts
	/* symbol     arrange function */
	{ "tile"  , tile },    /* first entry is default */
	{ "float" , NULL },    /* no layout function means floating behavior */
	{ "[M]"   , monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };



// igorg: audio keys not defined, so define them
// igorg: from https://shanetully.com/2012/07/simulating-mediakey-presses-in-x11/
#define XF86AudioPlay 0x1008ff14
#define XF86AudioNext 0x1008ff17
#define XF86AudioPrev 0x1008ff16
#define XF86AudioStop 0x1008ff15


static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_a,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },

// igorg: lock/suspend/kill client/exit:
	{ Mod1Mask|ControlMask,         XK_l,      spawn,          SHCMD("~/rc/bin/i3exit.sh lock") },
	{ Mod1Mask|ControlMask,         XK_s,      spawn,          SHCMD("~/rc/bin/i3exit.sh suspend") },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_r,      quit,           {1} },

// igorg: automatically pick the best resolution/configuration, for solo/multi displays
	{ MODKEY,                       XK_p,      spawn,          SHCMD("~/rc/bin/igorandr") },

// igorg: show pavucontrol for audio profile selection
	{ MODKEY,                       XK_bracketleft, spawn,     SHCMD("pavucontrol -t 5") },

// igorg: screenshots
	{ 0,                            XK_Print,  spawn,          SHCMD("maim --select ~/db/Screenshots/$(date +%Y-%m-%d---%H-%M-%S).png") },
	{ Mod1Mask,                     XK_Print,  spawn,          SHCMD("maim -i $(xdotool getactivewindow) ~/db/Screenshots/$(date +%Y-%m-%d---%H-%M-%S).png") },
	{ ControlMask,                  XK_Print,  spawn,          SHCMD("maim ~/db/Screenshots/$(date +%Y-%m-%d---%H-%M-%S).png") },

// igorg: keyboard layout switching
	{ MODKEY,                       XK_e,      spawn,          SHCMD("xkblayout-state set 0") },
	{ MODKEY,                       XK_r,      spawn,          SHCMD("xkblayout-state set 1") },
	{ MODKEY,                       XK_u,      spawn,          SHCMD("xkblayout-state set 2") },

// igorg: disable touchpad
	{ MODKEY|ShiftMask,             XK_t,      spawn,          SHCMD("~/rc/bin/toggle-touchpad.sh") },

	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },

// igorg: option 1, default: use dwm's navigation
        //{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
        //{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
        //{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
        //{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
// igorg: option 2: use dwm's navigation but with inverted j and k (j goes down k goes up)
        //{ MODKEY,                       XK_j,      focusstack,     {.i = -1 } },
        //{ MODKEY,                       XK_k,      focusstack,     {.i = +1 } },
        //{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
        //{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
// igorg: option 3: use vim navigation (hjkl) and left-right arrows to move screen divider:
        { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
        { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
        { MODKEY,                       XK_h,      focusstack,     {.i = -1 } },
        { MODKEY,                       XK_l,      focusstack,     {.i = +1 } },

// igorg: arrow keys: up/down/left/right navigate the stack; shift+left/right moves screen delimiter
        { MODKEY,                       XK_Left,   focusstack,     {.i = -1 } },
        { MODKEY,                       XK_Right,  focusstack,     {.i = +1 } },
        { MODKEY,                       XK_Up,     focusstack,     {.i = -1 } },
        { MODKEY,                       XK_Down,   focusstack,     {.i = +1 } },
        { MODKEY|ShiftMask,             XK_Left,   setmfact,       {.f = -0.05} },
        { MODKEY|ShiftMask,             XK_Right,  setmfact,       {.f = +0.05} },

// make the selected window "in spotlight", bumping it to order 0
	{ MODKEY,                       XK_Return, zoom,           {0} },

// layout switching (tile, floating, monocle)
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },

// igorg: Mod+Tab option 1: show previous tag. Not that useful
	//{ MODKEY,                       XK_Tab,    view,           {0} },
// igorg: Mod+Tab option 2: switch to tile layout
	{ MODKEY,                       XK_Tab,    setlayout,      {.v = &layouts[0]} },

// igorg: Mod+Space option 1: switch between two last layouts. Can be extremely confusing.
        //{ MODKEY,                       XK_space,  setlayout,      {0} },
// igorg: Mod+Space option 2: switch to monocle layout
	{ MODKEY,                       XK_space,  setlayout,      {.v = &layouts[2]} },
// igorg: Mod+Space option 3: ideal behavior: switch between tile and monocle layouts
        // TODO: implement and see

// toggle floating
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },

// navigating between multiple monitors
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

// dwm-xrdb patch: reload ~/.Xresources
	{ MODKEY,                       XK_F5,     xrdb,           {.v = NULL } },

// tags
        TAGKEYS(                        XK_grave,                  0)
        TAGKEYS(                        XK_1,                      1)
        TAGKEYS(                        XK_2,                      2)
        TAGKEYS(                        XK_3,                      3)
        TAGKEYS(                        XK_4,                      4)
        TAGKEYS(                        XK_5,                      5)
        TAGKEYS(                        XK_6,                      6)
        TAGKEYS(                        XK_7,                      7)
        TAGKEYS(                        XK_8,                      8)
        TAGKEYS(                        XK_9,                      9)

// igorg: option 1, default: use to summon all windows together
        { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
        { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
// igorg: option 2, added: use for one extra tag ("0"), currently using spotify there
        //TAGKEYS(                        XK_0,                      10)

// igorg: Weirdly, xev doesn't generate XK_KP_x events when pressed together with windows key
// Thus, the below declarations don't work:
        TAGKEYS(                        XK_KP_1,                   1)
        TAGKEYS(                        XK_KP_2,                   2)
        TAGKEYS(                        XK_KP_3,                   3)
        TAGKEYS(                        XK_KP_4,                   4)
        TAGKEYS(                        XK_KP_5,                   5)
        TAGKEYS(                        XK_KP_6,                   6)
        TAGKEYS(                        XK_KP_7,                   7)
        TAGKEYS(                        XK_KP_8,                   8)
        TAGKEYS(                        XK_KP_9,                   9)
        TAGKEYS(                        XK_KP_0,                   10)


// igorg: audio controls for spotify
	{ 0,                            XF86AudioPlay,  spawn,     SHCMD("dbus-send --print-reply --dest=org.mpris.MediaPlayer2.spotify /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.PlayPause") },
	{ 0,                            XF86AudioStop,  spawn,     SHCMD("dbus-send --print-reply --dest=org.mpris.MediaPlayer2.spotify /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.Stop") },
	{ 0,                            XF86AudioPrev,  spawn,     SHCMD("dbus-send --print-reply --dest=org.mpris.MediaPlayer2.spotify /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.Previous") },
	{ 0,                            XF86AudioNext,  spawn,     SHCMD("dbus-send --print-reply --dest=org.mpris.MediaPlayer2.spotify /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.Next") },

// igorg: program launchers
	{ MODKEY,                       XK_q,           spawn,     SHCMD("~/rc/bin/quip") },
	{ MODKEY,                       XK_n,           spawn,     SHCMD("google-chrome") },

// TODO: migrate keybindings for commonly used apps
// TODO: invoke them from their ~/rc/bin/ launchers
        // igorg: # Mail
        //bindsym $mod+m  exec google-chrome --app=https://outlook.office365.com/owa/
        // igorg: # Outlook Calendar
        //#bindsym $mod+c  exec google-chrome --app=https://outlook.office365.com/owa/?path=/calendar/view/WorkWeek
        // igorg: # FB calendar
        //bindsym $mod+c  exec google-chrome --app=https://our.intern.facebook.com/intern/calendar

// TODO: migrate screen brightness
        //bindsym XF86MonBrightnessUp exec "xbacklight +10"
        //bindsym XF86MonBrightnessDown exec "xbacklight -10"

//# TODO: migrate volume control. Not urgent because pa-applet currently handles this
//# igorg: TODO: fix unmute: https://askubuntu.com/questions/65764/how-do-i-toggle-sound-with-amixer
        //bindsym XF86AudioMute exec amixer -D default sset Master toggle && pkill -RTMIN+10 i3blocks
        //bindsym XF86AudioRaiseVolume exec amixer -D default sset Master 5%+ && pkill -RTMIN+10 i3blocks
        //bindsym XF86AudioLowerVolume exec amixer -D default sset Master 5%- && pkill -RTMIN+10 i3blocks
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


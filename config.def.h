/* See LICENSE file for copyright and license details. */

/* igorg: needed for media keys */
#include "X11/XF86keysym.h"

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int taglinepx = 1;        /* height of tag underline */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const unsigned int gappih    = 0;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 0;       /* vert inner gap between windows */
static const unsigned int gappoh    = 0;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 0;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const Bool viewontag         = True;     /* Switch view on tag switch */

static const char *fonts[]          = { "monospace:pixelsize=10" };

/* gruvbox color scheme */
#define COL_GRUVBOX_BG        "#282828"
#define COL_GRUVBOX_BG0       "#282828"
#define COL_GRUVBOX_BG0_H     "#1d2021"
#define COL_GRUVBOX_BG0_S     "#32302f"
#define COL_GRUVBOX_BG1       "#3c3836"
#define COL_GRUVBOX_BG2       "#504945"
#define COL_GRUVBOX_BG3       "#665c54"
#define COL_GRUVBOX_BG4       "#7c6f64"

#define COL_GRUVBOX_FG        "#ebdbb2"
#define COL_GRUVBOX_FG0       "#fbf1c7"
#define COL_GRUVBOX_FG1       "#ebdbb2"
#define COL_GRUVBOX_FG2       "#d5c4a1"
#define COL_GRUVBOX_FG3       "#bdae93"
#define COL_GRUVBOX_FG4       "#a89984"

#define COL_GRUVBOX_GRAY1     "#a89984"
#define COL_GRUVBOX_GRAY2     "#928374"
#define COL_GRUVBOX_GRAY3     "#928374"

#define COL_GRUVBOX_RED_HI    "#cc241d"
#define COL_GRUVBOX_RED_LO    "#fb4934"
#define COL_GRUVBOX_GREEN_HI  "#98971a"
#define COL_GRUVBOX_GREEN_LO  "#b8bb26"
#define COL_GRUVBOX_YELLOW_HI "#d79921"
#define COL_GRUVBOX_YELLOW_LO "#fabd2f"
#define COL_GRUVBOX_BLUE_HI   "#458588"
#define COL_GRUVBOX_BLUE_LO   "#83a598"
#define COL_GRUVBOX_PURPLE_HI "#b16286"
#define COL_GRUVBOX_PURPLE_LO "#d3869b"
#define COL_GRUVBOX_AQUA_HI   "#689d6a"
#define COL_GRUVBOX_AQUA_LO   "#8ec07c"
#define COL_GRUVBOX_ORANGE_HI "#d65d0e"
#define COL_GRUVBOX_ORANGE_LO "#fe8019"

/* some schemes don't use border/fg/bg colors */
#define COL_UNUSED            "#ff0000"

static char normbordercolor[]   = COL_GRUVBOX_BG;
static char normbgcolor[]       = COL_GRUVBOX_BG;
static char normfgcolor[]       = COL_GRUVBOX_GRAY2;
static char selbordercolor[]    = COL_GRUVBOX_YELLOW_LO;
static char selbgcolor[]        = COL_GRUVBOX_BG;
static char selfgcolor[]        = COL_GRUVBOX_GRAY2;
// option 1: title is present
//static char titlebordercolor[] = COL_UNUSED;
//static char titlebgcolor[]     = COL_GRUVBOX_BG;
//static char titlefgcolor[]     = COL_GRUVBOX_FG1;
// option 2: title is disabled (fg=bg) because it introduces more noise than value
static char titlebordercolor[]  = COL_UNUSED;
static char titlebgcolor[]      = COL_GRUVBOX_BG;
static char titlefgcolor[]      = COL_GRUVBOX_BG;
static char urgentbordercolor[] = COL_GRUVBOX_RED_LO;
static char urgentbgcolor[]     = COL_GRUVBOX_BG;
static char urgentfgcolor[]     = COL_GRUVBOX_GREEN_LO;
static char emptybordercolor[]  = COL_UNUSED;
static char emptybgcolor[]      = COL_GRUVBOX_BG;
static char emptyfgcolor[]      = COL_GRUVBOX_BG1;


static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*                      fg            bg               border   */
	[SchemeNorm]     = { normfgcolor    , normbgcolor    , normbordercolor     },
	[SchemeSel]      = { selfgcolor     , selbgcolor     , selbordercolor      },
	[SchemeTitle]    = { titlefgcolor   , titlebgcolor   , titlebordercolor    },
	[SchemeUrgent]   = { urgentfgcolor  , urgentbgcolor  , urgentbordercolor   },
	[SchemeEmpty]    = { emptyfgcolor   , emptybgcolor   , emptybordercolor    },
};

static const char *xres = "/home/igorg/.Xresources";



/* tagging */
// First tag has to be on line 110.
// Then tags number can be figured out by subtracting 110 from the line number
// TODO: tidy some code and move it to line 100 instead
// Convention: first letter of the word is the shortcut
static const char *tags[] = {
	"~", 		// ~: terminal
	"quip",		// q: quip
	"web", 	 	// w: web 		e: english layout 	a: launch apps
	"slack", 	// s: slack (WorkChat)
	"dm",		// d: dm (Messenger) 				z:zoom
	"xmail", 	// x: mail
	"calendar",     // c: calendar
	"files",        // f: files
	"1",  		// 1: wunderlist
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"0",
};
static const char *defaultapps[] = { // has to contain the same number of entries as tags[]
	"dwm-sensible-terminal", 	// ~: terminal
	"quip",		// q: quip
	"google-chrome",// w: web 		e: english layout 	a: launch apps
	"WorkChat", 	// s: slack (WorkChat)
	"Messenger",    // d: dm (Messenger) 				z:zoom
	"Mail", 	// x: mail
	"Calendar",     // c: calendar
	"nautilus",     // f: files
	"Wunderlist",  	// 1: wunderlist
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	"steam",
	"spotify",
};

static const Rule rules[] = {
	// xprop(1):
	//      WM_CLASS(STRING) = instance, class
	//      WM_NAME(STRING) = title
        /* class                   instance                                       title       tags mask     isfloating   monitor */
// use left-hand-only shortcuts to switch between tags
	// terminal
	// q: quip
        { "Google-chrome"        , "fb.quip.com__browse"                        , NULL,       1 << 1,       0,           -1 },
	// s: slack (WorkChat)
        { "Google-chrome"        , "fb.workplace.com__chat"                     , NULL,       1 << 3,       0,           -1 },
	// x: email
        { "Google-chrome"        , "outlook.office365.com__owa"                 , NULL,       1 << 5,       0,           -1 },
	// w: web
        { "Firefox"              , NULL                                         , NULL,       1 << 2,       0,           -1 },
	// d: dm (Messenger)
        { "Google-chrome"        , "www.messenger.com"                          , NULL,       1 << 4,       0,           -1 },
	// c: calendar
        { "Google-chrome"        , "outlook.office.com__calendar_view_workweek" , NULL,       1 << 6,       0,           -1 },
        { "Google-chrome"        , "our.intern.facebook.com__intern_calendar"   , NULL,       1 << 6,       0,           -1 },
	// f: files
        { "Nautilus"             , "nautilus"                                   , NULL,       1 << 7,       0,           -1 },
        { "Org.gnome.Nautilus"   , "org.gnome.Nautilus"                         , NULL,       1 << 7,       0,           -1 },
	// 1: Wunderlist
        { "Google-chrome"        , "www.wunderlist.com"                         , NULL,       1 << 8,       0,           -1 },
	// 3: Terraforming Mars
        { "steam_app_800270"     , "terraformingmars.exe"                       , NULL,       1 << 10,      0,           -1 },
	// 9: steam
        { "Steam"                , NULL                                         , NULL,       1 << 16,      0,           -1,},
	// 0: Spotify (detection doesn't seem to work well)
        { "Spotify"              , NULL                                         , NULL,       1 << 17,      0,           -1,},
};

/* layout(s) */
static const float mfact     = 0.5;  /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "layouts.c"
static const Layout layouts[] = {
// igorg: custom characters for layouts
// igorg: some more: ╠ ├ ┣ ▞ ꖸ 𐌎
// TODO: pick more representative symbols now that I realized that symbols need to be 3 characters long
//       to avoid jerking while switching layouts
//       Currently keeping all symbols 5 characters long
	/* symbol     arrange function */
	{ "tile " , tile    },    /* first entry is default */
	{ "float" , NULL    },    /* no layout function means floating behavior */
	{ "     " , monocle },    /* monocle layout will have special symbol handling in drawbar() */
	{ "grid " , grid    },
	// TODO: if modified, remember to update all references to &layouts[0] etc
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      vieworlaunch,   {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, NULL };
static const char *termcmd[]  = { "dwm-sensible-terminal", NULL };
static const char scratchpadname[] = "scratchpad";
//static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };
//static const char *scratchpadcmd[] = { "kitty", "-T", scratchpadname, NULL };
static const char *todocmd[]  = { "et", NULL, NULL, NULL, "TODO" };

static Key keys[] = {
	/* modifier                     key                             function        argument */
// igorg: dmenu-powered launchers/searches:
	{ MODKEY,                       XK_a,                           spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_a,                           spawn,          SHCMD("~/bin/dwm-dmenu-desktop") },
	// igorg: websearch
	{ MODKEY,                       XK_y,                           spawn,          SHCMD("~/bin/dmenu_websearch.sh YouTube: https://youtube.com/?q=") },
	{ MODKEY,                       XK_b,                           spawn,          SHCMD("~/bin/dmenu_websearch.sh Bunny:   https://bunnylol.facebook.net/?") },
	//{ MODKEY,                       XK_s,                           spawn,          SHCMD("~/bin/dmenu_websearch.sh Google:  https://google.com/?q=") },
	// igorg: open chrome bookmark
	{ MODKEY,                       XK_apostrophe,                  spawn,          SHCMD("~/src/chrome-dmenu/chrome-dmenu.sh") },

// igorg: program launchers
	{ MODKEY|ShiftMask,             XK_Return,                      spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_n,                           spawn,          SHCMD("google-chrome") },
	{ MODKEY|ShiftMask,             XK_n,                           spawn,          SHCMD("google-chrome --incognito") },
	{ MODKEY,                       XK_v,                           runorraise,     {.v = todocmd } },

// igorg: scratchpad is unnecessary, just use regular '~' tag
	//{ MODKEY,                       XK_grave,                       togglescratch,  {.v = scratchpadcmd } },

// igorg: session control: lock/suspend/kill client/exit:
	{ Mod1Mask|ControlMask,         XK_l,                           spawn,          SHCMD("~/bin/i3exit.sh lock") },
	{ Mod1Mask|ControlMask,         XK_s,                           spawn,          SHCMD("~/bin/i3exit.sh suspend") },
	// igorg: Temporarily use XK_r to quit dwm (since XK_q is used by a tag)
	{ MODKEY|ShiftMask,             XK_r,                           quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_r,                           quit,           {1} },
	// TODO: find appropriate shortcuts for these key which are currently used by tags:
	//{ MODKEY|ShiftMask,             XK_c,                           killclient,     {0} },
	//{ MODKEY|ShiftMask,             XK_q,                           quit,           {0} },
	// igorg: dwm-xrdb patch: reload ~/.Xresources
	{ MODKEY|ShiftMask,             XK_F5,                          xrdb,           {0} },
	// igorg: show/hide bar
	{ MODKEY|ShiftMask,             XK_b,                           togglebar,      {0} },
	// igorg: disable touchpad
	{ MODKEY|ShiftMask,             XK_t,                           spawn,          SHCMD("~/bin/toggle-touchpad.sh") },
	//igorg: automatically pick the best resolution/configuration, for solo/multi displays
	{ MODKEY,                       XK_p,                           spawn,          SHCMD("~/bin/igorandr dwm") },

// igorg: option 1: show pavucontrol for audio profile selection
	//{ MODKEY,                       XK_bracketleft,         spawn,          SHCMD("pavucontrol -t 5") },
// igorg: option 2: route audio between hdmi/internal directly by hotkeys
	{ MODKEY,                       XK_bracketleft,                 spawn,          SHCMD("~/bin/route-audio-to-audio-jack.sh") },
	{ MODKEY,                       XK_bracketright,                spawn,          SHCMD("~/bin/route-audio-to-hdmi.sh") },
	{ MODKEY,                       XK_backslash,                   spawn,          SHCMD("pavucontrol -t 5") },

// igorg: screenshots
	{ 0,                            XK_Print,                       spawn,          SHCMD("~/bin/take-screenshot.sh --select") },
	{ Mod1Mask,                     XK_Print,                       spawn,          SHCMD("~/bin/take-screenshot.sh --window") },
	{ ControlMask,                  XK_Print,                       spawn,          SHCMD("~/bin/take-screenshot.sh") },

// igorg: keyboard layout switching
	{ MODKEY,                       XK_e,                           spawn,          SHCMD("xkblayout-state set 0") },
	{ MODKEY,                       XK_r,                           spawn,          SHCMD("xkblayout-state set 1") },
	{ MODKEY,                       XK_u,                           spawn,          SHCMD("xkblayout-state set 2") },

// igorg: disable increment/decrement number of clients in master/stack area.
//	rationale:
//		1. mod+d after several mod+i doesn't restore the previous layout
//		2. misclicking one of these buttons result in a few seconds of confusion
//		   with no intuitive "undo" action
	//{ MODKEY,                       XK_i,                           incnmaster,     {.i = +1 } },
	//{ MODKEY,                       XK_d,                           incnmaster,     {.i = -1 } },

// igorg: option 1, default: use dwm's navigation
        //{ MODKEY,                       XK_j,                           focusstack,     {.i = +1 } },
	//{ MODKEY,                       XK_k,                           focusstack,     {.i = -1 } },
	//{ MODKEY,                       XK_h,                           setmfact,       {.f = -0.05} },
	//{ MODKEY,                       XK_l,                           setmfact,       {.f = +0.05} },
// igorg: option 2: use dwm's navigation but with inverted j and k (j goes down k goes up)
	//{ MODKEY,                       XK_j,                           focusstack,     {.i = -1 } },
	//{ MODKEY,                       XK_k,                           focusstack,     {.i = +1 } },
	//{ MODKEY,                       XK_h,                           setmfact,       {.f = -0.05} },
	//{ MODKEY,                       XK_l,                           setmfact,       {.f = +0.05} },
// igorg: option 3: use vim navigation (hjkl) and left-right arrows to move screen divider:
	{ MODKEY,                       XK_j,                           focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,                           focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,                           focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_l,                           focusstack,     {.i = +1 } },

// igorg: arrow keys: up/down/left/right navigate the stack; shift+left/right moves screen delimiter
	{ MODKEY,                       XK_Left,                        focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_Right,                       focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Up,                          focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_Down,                        focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Left,                        setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_Right,                       setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Up,                          incrovgaps,     {.i = -5 } },
	{ MODKEY|ShiftMask,             XK_Down,                        incrovgaps,     {.i = +5 } },
// make the selected window "in spotlight", bumping it to order 0
	{ MODKEY,                       XK_Return,                      zoom,           {0} },

// layout switching (tile, floating, monocle)
	{ MODKEY,                       XK_t,                           setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_g,                           setlayout,      {.v = &layouts[3]} },
// igorg: use XK_f and XK_m for tags
	//{ MODKEY,                       XK_f,                           setlayout,      {.v = &layouts[1]} },
	//{ MODKEY,                       XK_m,                           setlayout,      {.v = &layouts[2]} }
// igorg: switch between tile and monocle layouts
	{ MODKEY,                       XK_z,                           swaplayouts,    {0} },

// igorg: Mod+Space option 1: switch between two last layouts. Can be extremely confusing.
	//{ MODKEY,                       XK_space,               setlayout,      {0} },
// igorg: Mod+Space option 2: switch to monocle layout
	//{ MODKEY,                       XK_space,               setlayout,      {.v = &layouts[2]} },
// igorg: Mod+Space option 3: superior to option 1 and 2: switch between tile and monocle layouts
	//{ MODKEY,                       XK_space,               swaplayouts,    {0} },
// igorg: Mod+Space option 4: disable and use Mod+Z because it works better with mouse
	//{ MODKEY,                       XK_space,               swaplayouts,    {0} },

	{ MODKEY|ShiftMask,             XK_space,                       togglefloating, {0} },
	{ MODKEY,                       XK_Tab,                         toggleoverview, {0} },

// navigating between multiple monitors
	{ MODKEY,                       XK_comma,                       focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,                      focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                       tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,                      tagmon,         {.i = +1 } },

// tags
	TAGKEYS(                        XK_grave,                       0)   // console
	TAGKEYS(                        XK_q,                           1)   // quip
	TAGKEYS(                        XK_w,                           2)   // web
	//TAGKEYS(                        XK_e,                           )  // reserved for switching to english layout
	//TAGKEYS(                        XK_a,                           )  // reserved for launching apps
	TAGKEYS(                        XK_s,                           3)   // slack
	TAGKEYS(                        XK_d,                           4)   // dm
	//TAGKEYS(                        XK_z,                           )  // reserved for 'zoom': switch between tile/mono
	TAGKEYS(                        XK_x,                           5)   // xmail
	TAGKEYS(                        XK_c,                           6)   // calendar
	TAGKEYS(                        XK_f,                           7)   // files
	TAGKEYS(                        XK_1,                           8)   // wunderlist
	TAGKEYS(                        XK_2,                           9)
	TAGKEYS(                        XK_3,                           10)
	TAGKEYS(                        XK_4,                           11)
	TAGKEYS(                        XK_5,                           12)
	TAGKEYS(                        XK_6,                           13)
	TAGKEYS(                        XK_7,                           14)
	TAGKEYS(                        XK_8,                           15)
	TAGKEYS(                        XK_9,                           16)
	TAGKEYS(                        XK_0,                           17)

// igorg: Weirdly, xev doesn't generate XK_KP_x events when pressed together with windows key
// igorg: Thus, the below declarations don't work:
	TAGKEYS(                        XK_KP_1,                        8)
	TAGKEYS(                        XK_KP_2,                        9)
	TAGKEYS(                        XK_KP_3,                        10)
	TAGKEYS(                        XK_KP_4,                        11)
	TAGKEYS(                        XK_KP_5,                        12)
	TAGKEYS(                        XK_KP_6,                        13)
	TAGKEYS(                        XK_KP_7,                        14)
	TAGKEYS(                        XK_KP_8,                        15)
	TAGKEYS(                        XK_KP_9,                        16)
	TAGKEYS(                        XK_KP_0,                        17)

// igorg: audio controls for Spotify
	{ 0,                            XF86XK_AudioPlay,               spawn,          SHCMD("dbus-send --print-reply --dest=org.mpris.MediaPlayer2.spotify /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.PlayPause") },
	{ 0,                            XF86XK_AudioStop,               spawn,          SHCMD("dbus-send --print-reply --dest=org.mpris.MediaPlayer2.spotify /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.Stop") },
	{ 0,                            XF86XK_AudioPrev,               spawn,          SHCMD("dbus-send --print-reply --dest=org.mpris.MediaPlayer2.spotify /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.Previous") },
	{ 0,                            XF86XK_AudioNext,               spawn,          SHCMD("dbus-send --print-reply --dest=org.mpris.MediaPlayer2.spotify /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.Next") },

// igorg: screen brightness
// TODO: change this to a script which will also show the current brightness from notify-send
	{ 0,                            XF86XK_MonBrightnessUp,         spawn,          SHCMD("xbacklight +10") },
	{ 0,                            XF86XK_MonBrightnessDown,       spawn,          SHCMD("xbacklight -10") },

//# TODO: migrate volume control. Not urgent because pa-applet currently handles this
//# igorg: TODO: fix unmute: https://askubuntu.com/questions/65764/how-do-i-toggle-sound-with-amixer
	//bindsym XF86XK_AudioMute        exec amixer -D default sset Master toggle && pkill -RTMIN+10 i3blocks
	//bindsym XF86XK_AudioRaiseVolume exec amixer -D default sset Master 5%+ && pkill -RTMIN+10 i3blocks
	//bindsym XF86XK_AudioLowerVolume exec amixer -D default sset Master 5%- && pkill -RTMIN+10 i3blocks
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
	{ ClkTagBar,            0,              Button1,        vieworlaunch,   {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


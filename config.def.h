/* See LICENSE file for copyright and license details. */

// disable autoformatting by clang for now
// clang-format off

/* igorg: needed for media keys */
#include "X11/XF86keysym.h"

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 1;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int taglinepx = 1;        /* height of tag underline */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 0;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const unsigned int gappih    = 5;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 5;       /* vert inner gap between windows */
static const unsigned int gappoh    = 5;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 5;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const Bool viewontag         = True;     /* Switch view on tag switch */

// NOTE: for Nerd Fonts, prefer "Propo" variants because they contain large-sized icons
// static const char *fonts[]          = { "monofur for Powerline:size=15" };
// static const char *fonts[]          = { "HeavyData Nerd Font:size=14" };
// static const char *fonts[]          = { "ProFont for Powerline:size=14" };
// static const char *fonts[]          = { "ProggyClean Nerd Font Mono:size=16" };
// static const char *fonts[]          = { "CaskaydiaCove NFM:size=14" };
// static const char *fonts[]          = { "IosevkaTermSlab Nerd Font Propo:size=14" };
// static const char *fonts[]          = { "Terminess Nerd Font Propo:size=12" };
// static const char *fonts[]          = { "FantasqueSansM Nerd Font Propo:size=14" };
static const char *fonts[]          = { "RecMonoCasual Nerd Font Propo:size=14" };


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

static const char *colors[][3]      = {
	/*                      fg            bg               border   */
	[SchemeNorm]     = { normfgcolor    , normbgcolor    , normbordercolor     },
	[SchemeSel]      = { selfgcolor     , selbgcolor     , selbordercolor      },
	[SchemeTitle]    = { titlefgcolor   , titlebgcolor   , titlebordercolor    },
	[SchemeUrgent]   = { urgentfgcolor  , urgentbgcolor  , urgentbordercolor   },
	[SchemeEmpty]    = { emptyfgcolor   , emptybgcolor   , emptybordercolor    },
};

static const char *xres = "/home/igorg/.Xresources";

// First tag has to be on line 100.
// Then tags number can be figured out by subtracting 100 from the line number
// Convention: first letter of the word is the shortcut
static const char *tags[] = {
	"", // q: quick terminal. More icons:          
	"", // w: web    󰖟                e: english layout
	"", // a: asana    
	"󰒱", // s: slack (WorkChat 󰒱 )
	"󰍡", // d: dm (Messenger 󰍥 󰍡 󰍧 )     f: toggle fullscreen
	"", // z: files
	"", // x: mail
	"", // c: calendar
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

static const Rule rules[] = {
	// xprop(1):
	//      WM_CLASS(STRING) = instance, class
	//      WM_NAME(STRING) = title
        /* class                   instance                                       title       tags mask     isfloating   isfakefullscreen    monitor       float x,y,w,h         floatborderpx*/
	// use left-hand-only shortcuts to switch between tags
	// terminal
	// q: code. Keep quip here as well in the meantime
        { "Google-chrome"        , "fb.quip.com__browse"                        , NULL,       1 << 0,       0,           0,                  -1 },
	// w: web
        { "Firefox"              , NULL                                         , NULL,       1 << 1,       0,           0,                  -1 },
	// a: asana
        { "Google-chrome"        , "app.asana.com"                              , NULL,       1 << 2,       0,           0,                  -1 },
	// s: slack (WorkChat)
        { "Google-chrome"        , "fb.workplace.com__chat"                     , NULL,       1 << 3,       0,           0,                  -1 },
        { "Slack"                , "slack"                                      , NULL,       1 << 3,       0,           0,                  -1 },
	// d: dm (Messenger)
        { "Google-chrome"        , "www.messenger.com"                          , NULL,       1 << 4,       0,           0,                  -1 },
        { "Surf"                 , "https://www.messenger.com/"                 , NULL,       1 << 4,       0,           0,                  -1 },
	// z: filez
        { "Nautilus"             , "nautilus"                                   , NULL,       1 << 5,       0,           0,                  -1 },
        { "Org.gnome.Nautilus"   , "org.gnome.Nautilus"                         , NULL,       1 << 5,       0,           0,                  -1 },
	// x: email
        { "Google-chrome"        , "outlook.office365.com__owa"                 , NULL,       1 << 6,       0,           0,                  -1 },
        { "Google-chrome"        , "mail.google.com__mail_u_0"                  , NULL,       1 << 6,       0,           0,                  -1 },
	// c: calendar
        { "Google-chrome"        , "outlook.office.com__calendar_view_workweek" , NULL,       1 << 7,       0,           0,                  -1 },
        { "Google-chrome"        , "our.intern.facebook.com__intern_calendar"   , NULL,       1 << 7,       0,           0,                  -1 },
        { "Google-chrome"        , "calendar.google.com__calendar"              , NULL,       1 << 7,       0,           0,                  -1 },
	// 1: Todo
        // { "Google-chrome"        , "www.wunderlist.com"                         , NULL,       1 << 7,       0,           0,                  -1 },
        // { "Google-chrome"        , "to-do.office.com"                           , NULL,       1 << 7,       0,           0,                  -1 },
	// 3: Games: Terraforming Mars
        { "steam_app_800270"     , "terraformingmars.exe"                       , NULL,       1 << 9,       0,           1,                  -1 },
        { "CS.x86_64"            , "CS.x86_64"          /* Cultist Simulator */ , NULL,       1 << 9,       0,           0,                  -1 },
	// 9: steam
        { "Steam"                , NULL                                         , NULL,       1 << 15,      0,           0,                  -1 },
        { "steam"                , "steamwebhelper"                             , NULL,       1 << 15,      0,           0,                  -1 },
	// 0: Spotify (detection doesn't seem to work well)
        { "Spotify"              , NULL                                         , NULL,       1 << 16,      0,           0,                  -1 },

	// Scratchpad: terminal
        { "scratchpad_terminal"  , "scratchpad_terminal"                        , NULL,       SPTAG(0),     1,           0,                  -1 ,         200, 100, 1400, 880,  0 },
	// Scratchpad: todo (todoist)
        { "Google-chrome"        , "todoist.com__app"                           , NULL,       SPTAG(1),     1,           0,                  -1 ,         200, 50, 2000, 1280,  0 },
        { "Google-chrome"        , "todoist.com__app_project_2247069292"        , NULL,       SPTAG(1),     1,           0,                  -1 ,         200, 50, 2000, 1280,  0 },
	// Scratchpad: todo (ticktick)
        { "Google-chrome"        , "ticktick.com__webapp"                       , NULL,       SPTAG(1),     1,           0,                  -1 ,         200, 50, 2000, 1280,  0 },
        { "Surf"                 , "https://ticktick.com/webapp/"               , NULL,       SPTAG(1),     1,           0,                  -1 ,         200, 50, 2000, 1280,  0 },
        { "ticktick"             , "ticktick"                                   , NULL,       SPTAG(1),     1,           0,                  -1 ,         200, 50, 2000, 1280,  0 },
        // { "Nozbe"             , "nozbe"                                      , NULL,       SPTAG(1),     1,           0,                  -1 ,         200, 100, 1400, 880,  0 },
	// Scratchpad: vim
	// note: gvim window resizes itself, so setting geometry here isn't doing any good. However, setting it to float is
        { "scratchpad_vim"       , "scratchpad_vim"                             , NULL,       SPTAG(2),     1,           0,                  -1 ,         200, 100, 1400, 880,  0 },
	// Scratchpad: top
        { "scratchpad_top"       , "scratchpad_top"                             , NULL,       SPTAG(3),     1,           0,                  -1 ,         2000, 100, 1000, 1000,  0 },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;

const char *spcmd_terminal[] = {"scratchpad_terminal", NULL };
const char *spcmd_todo[] = {"Todo", NULL };
const char *spcmd_vim[] = {"scratchpad_vim", NULL };
const char *spcmd_top[] = {"scratchpad_top", NULL };

static Sp scratchpads[] = {
	/* name          cmd  */
	{"scratchpad_terminal", spcmd_terminal},
	{"todo",                spcmd_todo},
	{"scratchpad_vim",      spcmd_vim},
	{"scratchpad_top",      spcmd_top},
};

/* layout(s) */
static const float mfact     = 0.5;  /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "layouts.c"

const enum {
  LayoutCentered,
  LayoutFloat,
  LayoutMonocle,
  LayoutGrid,
  LayoutTile
} LayoutDefault = LayoutTile;

// igorg: custom characters for layouts
// igorg: some more: ╠ ├ ┣ ▞ ꖸ 𐌎
// TODO: pick more representative symbols now that I realized that symbols need to be 3 characters long
//       to avoid jerking while switching layouts
//       Currently keeping all symbols 5 characters long
static const Layout layouts[] = {
                      /* symbol     arrange function */
	[LayoutCentered] = { "centered" , tcl_always }, /* first entry is default */
	[LayoutFloat]    = { "float"    , NULL       }, /* no layout function means floating behavior */
	[LayoutMonocle]  = { "     "    , monocle    }, /* monocle layout will have special symbol handling in drawbar() */
	[LayoutGrid]     = { "grid "    , grid       },
	[LayoutTile]     = { "tile "    , tile       },
};


/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      vieworlaunch,   {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

static Key keys[] = {
	/* modifier                     key                             function        argument */
	{ MODKEY|ShiftMask,             XK_BackSpace,                   quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_r,                           quit,           {1} },

	// igorg: dwm-xrdb patch: reload ~/.Xresources
	{ MODKEY|ShiftMask,             XK_F5,                          xrdb,           {0} },

	// igorg: show/hide bar
	{ MODKEY|ShiftMask,             XK_b,                           togglebar,      {0} },

	// igorg: scratchpads
	{ MODKEY,                       XK_grave,                       togglescratch,  {.ui = 0 } },
	{ MODKEY,                       XK_1,                           togglescratch,  {.ui = 1 } },
	{ MODKEY,                       XK_semicolon,                   togglescratch,  {.ui = 2 } },
	{ MODKEY,                       XK_Escape,                      togglescratch,  {.ui = 3 } },

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
	{ MODKEY,                       XK_j,                           focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_k,                           focusstack,     {.i = +1 } },
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
	// currently used by terminal
	// { MODKEY,                       XK_Return,                      zoom,           {0} },
	{ MODKEY,                       XK_v,                           zoom,           {0} },

// layout switching (tile, floating, monocle)
	{ MODKEY,                       XK_t,                           setlayout,      {.v = &layouts[LayoutTile]} },
	{ MODKEY|ShiftMask,             XK_g,                           setlayout,      {.v = &layouts[LayoutGrid]} },
	{ MODKEY,                       XK_p,                           setlayout,      {.v = &layouts[LayoutCentered]} },
// igorg: use XK_f and XK_m for tags
	//{ MODKEY,                       XK_f,                           setlayout,      {.v = &layouts[LayoutFloat]} },
	//{ MODKEY,                       XK_m,                           setlayout,      {.v = &layouts[LayoutMonocle]} }
// igorg: switch between tile and monocle layouts
	{ MODKEY,                       XK_f,                           swaplayouts,    {0} },

// igorg: Mod+Space option 1: switch between two last layouts. Can be extremely confusing.
	//{ MODKEY,                       XK_space,               setlayout,      {0} },
// igorg: Mod+Space option 2: switch to monocle layout
	//{ MODKEY,                       XK_space,               setlayout,      {.v = &layouts[LayoutMonocle]} },
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
	// TAGKEYS(                        XK_grave,                       0)   // scratchpad: console
	TAGKEYS(                        XK_q,                           0)   // qcode
	TAGKEYS(                        XK_w,                           1)   // web
	// TAGKEYS(                        XK_e,                            )  // reserved for switching to english layout
	TAGKEYS(                        XK_a,                           2)   // asana
	TAGKEYS(                        XK_s,                           3)   // slack
	TAGKEYS(                        XK_d,                           4)   // dm
	TAGKEYS(                        XK_z,                           5)   // filez
	TAGKEYS(                        XK_x,                           6)   // xmail
	TAGKEYS(                        XK_c,                           7)   // calendar
	// TAGKEYS(                        XK_1,                           8)   // scratchpad: todo
	TAGKEYS(                        XK_2,                           8)
	TAGKEYS(                        XK_3,                           9)
	TAGKEYS(                        XK_4,                           10)
	TAGKEYS(                        XK_5,                           11)
	TAGKEYS(                        XK_6,                           12)
	TAGKEYS(                        XK_7,                           13)
	TAGKEYS(                        XK_8,                           14)
	TAGKEYS(                        XK_9,                           15)
	TAGKEYS(                        XK_0,                           16)

// igorg: Weirdly, xev doesn't generate XK_KP_x events when pressed together with windows key
// igorg: Thus, the below declarations don't work:
	TAGKEYS(                        XK_KP_1,                        9)
	TAGKEYS(                        XK_KP_2,                        10)
	TAGKEYS(                        XK_KP_3,                        11)
	TAGKEYS(                        XK_KP_4,                        12)
	TAGKEYS(                        XK_KP_5,                        13)
	TAGKEYS(                        XK_KP_6,                        14)
	TAGKEYS(                        XK_KP_7,                        15)
	TAGKEYS(                        XK_KP_8,                        16)
	TAGKEYS(                        XK_KP_9,                        17)
	TAGKEYS(                        XK_KP_0,                        18)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[LayoutMonocle]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        vieworlaunch,   {0} },
	{ ClkTagBar,            0,              Button2,        killall,        {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

void
setlayoutex(const Arg *arg)
{
	setlayout(&((Arg) { .v = &layouts[arg->i] }));
}

void
viewex(const Arg *arg)
{
	view(&((Arg) { .ui = 1 << arg->ui }));
}

void
viewall(const Arg *arg)
{
	view(&((Arg){.ui = ~0}));
}

void
toggleviewex(const Arg *arg)
{
	toggleview(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagex(const Arg *arg)
{
	tag(&((Arg) { .ui = 1 << arg->ui }));
}

void
toggletagex(const Arg *arg)
{
	toggletag(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagall(const Arg *arg)
{
	tag(&((Arg){.ui = ~0}));
}

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
static Signal signals[] = {
	/* signum           function */
	{ "focusstack",     focusstack },
	{ "setmfact",       setmfact },
	{ "togglebar",      togglebar },
	{ "incnmaster",     incnmaster },
	{ "togglefloating", togglefloating },
	{ "focusmon",       focusmon },
	{ "tagmon",         tagmon },
	{ "zoom",           zoom },
	{ "view",           view },
	{ "viewall",        viewall },
	{ "viewex",         viewex },
	{ "toggleview",     view },
	{ "toggleviewex",   toggleviewex },
	{ "tag",            tag },
	{ "tagall",         tagall },
	{ "tagex",          tagex },
	{ "toggletag",      tag },
	{ "toggletagex",    toggletagex },
	{ "killclient",     killclient },
	{ "quit",           quit },
	{ "setlayout",      setlayout },
	{ "setlayoutex",    setlayoutex },
};

/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMonoNerdFont:size=10" };
static const char dmenufont[]       = "JetBrainsMonoNerdFont:size=10";
static const char col_cakepop_sorbet[] = "#fbc850";
static const char col_coco_black[]     = "#1c1c1c";
static const char col_dark_charcoal[]  = "#333333";
static const char col_mossy[]          = "#836f3f";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_mossy, col_coco_black, col_dark_charcoal },
	[SchemeSel]  = { col_cakepop_sorbet, col_dark_charcoal,  col_mossy  },
};

/* tagging */
static const char *tags[][2] = {
    {"󰎦", "󰎤"},
    {"󰎩", "󰎧"},
    {"󰎬", "󰎪"},
    {"󰎮", "󰎭"},
    {"󰎰", "󰎱"},
    {"󰎵", "󰎳"},
    {"󰎸", "󰎶"},
    {"󰎻", "󰎹"},
    {"󰎾", "󰎼"}
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ "float",    NULL,       NULL,       511,          1,           -1 },
};

/* layout(s) */
static const float mfact        = 0.75; /* factor of master area size [0.05..0.95] */
static const int nmaster        = 1;    /* number of clients in master area */
static const int resizehints    = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1;    /* 1 will force focus on the fullscreen window */
static const int refreshrate    = 120;  /* refresh rate (per second) for client move/resize */
static const int mainmon        = 0;    /* xsetroot will only change the bar on this monitor */

static const Layout layouts[] = {
	/* symbol   arrange function */
	{ "",      tileright },
    { "",      tileleft },
	{ "",      bstack },
	{ "󰗉",      bstackhoriz },
	{ "",      monocle },
	{ "",      NULL },
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
static char dmenumon[2]            = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]      = { "dmenu_run", "-p", " Launch:", "-m", dmenumon, "-fn", dmenufont, "-nb", col_coco_black, "-nf", col_mossy, "-sb", col_dark_charcoal, "-sf", col_cakepop_sorbet, NULL };
static const char *tool_menu[]     = { "./.bin/tools", "-m", dmenumon, "-fn", dmenufont, "-nb", col_coco_black, "-nf", col_mossy, "-sb", col_dark_charcoal, "-sf", col_cakepop_sorbet, NULL };
static const char *termcmd[]       = { "st", NULL };
static const char *incvol[]        = {"./.bin/set-audio", "Master", "1%+", NULL};
static const char *decvol[]        = {"./.bin/set-audio", "Master", "1%-", NULL};
static const char *mutevol[]       = {"./.bin/set-audio", "Master", "toggle", NULL};
static const char *incmic[]        = {"./.bin/set-audio", "Capture", "1%+", NULL};
static const char *decmic[]        = {"./.bin/set-audio", "Capture", "1%-", NULL};
static const char *mutemic[]       = {"./.bin/set-audio", "Capture", "toggle", NULL};
static const char *incbacklight[]  = { "nenobacklight", "set", "intel_backlight", "5%+", NULL };
static const char *decbacklight[]  = { "nenobacklight", "set", "intel_backlight", "5%-", NULL };
static const char *fullbacklight[] = { "nenobacklight", "set", "intel_backlight", "100%", NULL };
static const char *halfbacklight[] = { "nenobacklight", "set", "intel_backlight", "50%", NULL };
static const char *media_info[]    = { "./.bin/notify-current-media" , NULL };
static const char *media_pause[]   = { "/usr/bin/playerctl", "play-pause" , NULL };
static const char *media_prev[]    = { "/usr/bin/playerctl", "previous" , NULL };
static const char *media_next[]    = { "/usr/bin/playerctl", "next" , NULL };
static const char *browser[]       = { "/usr/bin/firefox", "next" , NULL };
static const char *sshot[]         = { "./.bin/tool/tool-screenshot", NULL };
static const char *scapfull[]      = { "./.bin/tool/tool-screencap", "fullscreen", NULL };
static const char *scap[]          = { "./.bin/tool/tool-screencap", "window", NULL };
static const char *notes[]         = { "./.bin/tool/tool-notes", NULL };
static const char *clipboard[]     = { "./.bin/tool/tool-clipboard_history", NULL };
static const char *todos[]         = { "./.bin/tool/tool-todo", "-m", dmenumon, "-fn", dmenufont, "-nb", col_coco_black, "-nf", col_mossy, "-sb", col_dark_charcoal, "-sf", col_cakepop_sorbet, NULL };
static const char *mathtool[]      = { "./.bin/tool/tool-math", "-m", dmenumon, "-fn", dmenufont, "-nb", col_coco_black, "-nf", col_mossy, "-sb", col_dark_charcoal, "-sf", col_cakepop_sorbet, NULL };
static const char *notify[]        = { "dunstctl", "history-pop", NULL };
static const char *hwstats[]       = { "./.bin/tool/tool-hwstat", NULL };
static const char *ip_addr[]       = { "./.bin/tool/tool-ip_info", NULL };
static const char *bluetooth[]       = { "./.bin/tool/tool-bluetooth", NULL };
static const char *session[]       = { "./.bin/tool/tool-session", "-m", dmenumon, "-fn", dmenufont, "-nb", col_coco_black, "-nf", col_mossy, "-sb", col_dark_charcoal, "-sf", col_cakepop_sorbet, NULL };
static const char *lock[]          = { "slock", NULL };

/* Targets */
static const Target targets[] = {
	/* label      Hostname */
	{ "[Local]", NULL      }, // Default
    { "[Patsy]", "patsy"   },
};

static const Key keys[] = {
	/* modifier         key                        function          argument */

    // Media Keys
	{ 0,			    XF86XK_AudioLowerVolume,   spawn,            {.v = decvol        } },
	{ 0,			    XF86XK_AudioRaiseVolume,   spawn,            {.v = incvol        } },
    { 0,                XF86XK_AudioMute,          spawn,            {.v = mutevol       } },
	{ ShiftMask,        XF86XK_AudioLowerVolume,   spawn,            {.v = decmic        } },
	{ ShiftMask,	    XF86XK_AudioRaiseVolume,   spawn,            {.v = incmic        } },
    { 0,                XF86XK_AudioMicMute,       spawn,            {.v = mutemic       } },
	{ 0,			    XF86XK_MonBrightnessUp,    spawn,            {.v = incbacklight  } },
	{ 0,			    XF86XK_MonBrightnessDown,  spawn,            {.v = decbacklight  } },
	{ ShiftMask,        XF86XK_MonBrightnessUp,    spawn,            {.v = fullbacklight } },
	{ ShiftMask,        XF86XK_MonBrightnessDown,  spawn,            {.v = halfbacklight } },
	{ 0,                XF86XK_Favorites,          spawn,            {.v = browser       } },


	{ MODKEY,           XK_Up,                     spawn,            {.v = media_info} },
	{ 0,                XF86XK_AudioPlay,          spawn,            {.v = media_pause} },
	{ 0,                XF86XK_AudioPrev,          spawn,            {.v = media_prev} },
	{ 0,                XF86XK_AudioNext,          spawn,            {.v = media_next} },

    // Launchers
	{ MODKEY,           XK_p,                      spawn,            {.v = dmenucmd } },
    { MODKEY|ShiftMask, XK_p,                      spawn,            {.v = tool_menu} },
	{ MODKEY,           XK_o,                      spawn,            {.v = lock     } },
	{ MODKEY|ShiftMask, XK_o,                      spawn,            {.v = session  } },
	{ MODKEY,           XK_c,                      spawn,            {.v = sshot    } },
	{ MODKEY|ShiftMask, XK_c,                      spawn,            {.v = clipboard} },
	{ MODKEY,           XK_s,                      spawn,            {.v = scapfull } },
	{ MODKEY|ShiftMask, XK_s,                      spawn,            {.v = scap     } },
	{ MODKEY,           XK_a,                      spawn,            {.v = notes    } },
	{ MODKEY|ShiftMask, XK_a,                      spawn,            {.v = todos    } },
	{ MODKEY,           XK_n,                      spawn,            {.v = notify   } },
	{ MODKEY,           XK_m,                      spawn,            {.v = mathtool } },
	{ MODKEY,           XK_z,                      spawn,            {.v = hwstats  } },
	{ MODKEY|ShiftMask, XK_z,                      spawn,            {.v = ip_addr  } },
    { MODKEY|ShiftMask, XK_b,                      spawn,            {.v = bluetooth} },
	{ MODKEY|ShiftMask, XK_Return,                 spawn,            {.v = termcmd  } },

    // Window Management
	{ MODKEY,           XK_Return,                 zoom,             {0} },

	{ MODKEY,           XK_d,                      incnmaster,       {.i = -1 } },
	{ MODKEY,           XK_i,                      incnmaster,       {.i = +1 } },

	{ MODKEY,           XK_h,                      setmfact,         {.f = -0.05} },
	{ MODKEY,           XK_l,                      setmfact,         {.f = +0.05} },

	{ MODKEY|ShiftMask, XK_k,                      inplacerotate,    {.i = -1} },
	{ MODKEY|ShiftMask, XK_j,                      inplacerotate,    {.i = +1} },

	{ MODKEY,           XK_k,                      focusstack,       {.i = -1 } },
	{ MODKEY,           XK_j,                      focusstack,       {.i = +1 } },

	{ MODKEY|ShiftMask, XK_l,                      inplacerotate,    {.i = -2} },
	{ MODKEY|ShiftMask, XK_h,                      inplacerotate,    {.i = +2} },

	{ MODKEY,           XK_r,                      runrulesfocused,  {0} },
	{ MODKEY|ShiftMask, XK_r,                      runrulesall,      {0} },

	{ MODKEY,           XK_u,                      focusurgent,      {0} },
	{ MODKEY,           XK_b,                      togglebar,        {0} },

	{ MODKEY,           XK_q,                      killclient,       {0} },
	{ MODKEY|ShiftMask, XK_q,                      quit,             { 0 }            },

    // Layouts
	{ MODKEY,           XK_t,                      setlayout,        {.v = &layouts[0]} },
	{ MODKEY|ShiftMask, XK_t,                      setlayout,        {.v = &layouts[1]} },
	{ MODKEY,           XK_e,                      setlayout,        {.v = &layouts[2]} },
	{ MODKEY|ShiftMask, XK_e,                      setlayout,        {.v = &layouts[3]} },
	{ MODKEY,           XK_f,                      setlayout,        {.v = &layouts[4]} },
	{ MODKEY|ShiftMask, XK_f,                      setlayout,        {.v = &layouts[5]} },
	{ MODKEY,           XK_space,                  setlayout,        {0} },
	{ MODKEY|ShiftMask, XK_space,                  togglefloating,   {0} },

    // Monitors
	{ MODKEY,           XK_comma,                  focusmon,         {.i = -1 } },
	{ MODKEY,           XK_period,                 focusmon,         {.i = +1 } },
	{ MODKEY|ShiftMask, XK_comma,                  tagmon,           {.i = -1 } },
	{ MODKEY|ShiftMask, XK_period,                 tagmon,           {.i = +1 } },
	{ MODKEY,           XK_apostrophe,             swapmon,          {0} },

    // Targets
	{ MODKEY|ShiftMask, XK_Up,                     settarget,        {.i = 1} },
	{ MODKEY|ShiftMask, XK_Down,                   settarget,        {.i = -1} },

    // Tagging
	{ MODKEY,           XK_Tab,                    view,             {0} },
	{ MODKEY,           XK_0,                      view,             {.ui = ~0 } },
	{ MODKEY|ShiftMask, XK_0,                      tag,              {.ui = ~0 } },
	TAGKEYS(XK_1, 0)
	TAGKEYS(XK_2, 1)
	TAGKEYS(XK_3, 2)
	TAGKEYS(XK_4, 3)
	TAGKEYS(XK_5, 4)
	TAGKEYS(XK_6, 5)
	TAGKEYS(XK_7, 6)
	TAGKEYS(XK_8, 7)
	TAGKEYS(XK_9, 8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[3]} },
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


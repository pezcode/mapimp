/*

  .....____    ...::$$$$=$=$=$  ...____
_____/    /__        $$     $$___/    /___
\           //\\____$$   __$$\__         /
 \__     __//        /  / $$__  /    ___/
   /    /___\   \.   ) / $$  / /    /___
  /        /    /   / / $$  __/        /
  \_______....  ___/ / $$_   \\_______/
          /    /$$=$=$=$/ \   \
      ...(____/           /   /
                 .......:::./

	mapimp plugin version 0.9
	coded by takerZ
	tPORt, 2009-2010

YOU CAN USE THE SOURCE ANY WAY YOU LIKE WITHOUT
RESTRICTIONS, BUT STILL REMEMBER THAT THIS SOFTWARE
IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE BLAH BLAH BLAH
*/
#ifndef __MAPIMP_H__
#define __MAPIMP_H__

/* Target specific stuff */
#ifdef OLLYDBG

//#pragma comment(lib, "__odbg\\ollydbgvc7.lib")

#else
#ifdef IMMDBG

#pragma comment(lib, "__immdbg\\immunitydebugger.lib")

#endif
#endif

#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "psapi.lib")
#pragma comment(lib, "pcre.lib")

/* Shut uninteresting warnings the hell up */
#pragma warning(disable: 4996)

typedef struct
{
	size_t count;
	LPVOID first;
	LPVOID last;
} list_t;

typedef struct
{
	BOOL comments;
	BOOL labels;
	BOOL collisionchecks;
	ULONG aimport;
	BOOL applytodebuggee;
	BOOL demangle;
	BOOL usemasks;
	list_t* masks;
} config_t;

typedef struct
{
	LPVOID next;
	CHAR* buffer;
	CHAR* repl;
	size_t repl_s;
	int insert;
	int type;	
	int errcode;
	CHAR* errptr;
	int erroffset;
	pcre* regex;
	pcre_extra* extra;
} mask_t;

#define OVECTOR_COMP_COUNT 3

typedef struct
{
	int rm_so;
	int rm_eo;
	int reserved;
} match_t;

typedef struct
{
	ULONG base;
	WCHAR* name;
	PULONG segments;
	size_t nseg;
} module_t;

typedef struct
{
	LPVOID next;
	WCHAR* buffer;
	size_t size;
	ULONG offset;
	ULONG segment;
} name_t;

/* Plugin action identifiers */
typedef enum
{
	ACTION_IMPORT,
	ACTION_OPTIONS,
	ACTION_ABOUT = 3
} __action;

/* Autoimport option definitions */
typedef enum
{
	AUTOIMPORT_DISABLED,
	AUTOIMPORT_ASK,
	AUTOIMPORT_ALWAYS
} __autoimport;

/* mask_compile output definitions */
typedef enum
{
	FILTER_NOERROR = 0,
	/*
		The last pcre_compile2() error code is 67
		as defined in PCRE documentation
	*/
	FILTER_INVALID_MASK = 68,
	FILTER_INVALID_KEY,
	FILTER_INVALID_REPLACEMENT
} __filter_error;

/* mask_filter output definitions */
typedef enum
{
	FILTER_NOTHING,
	FILTER_SKIP,
	FILTER_CUT,
	FILTER_REPLACE = 4
} __mask_type;

/* module_info error codes */
typedef enum
{
	MODULE_SUCCESS,
	MODULE_BASE_NOT_FOUND,
	MODULE_OUT_OF_RANGE,
	MODULE_FILE_MAPPING_FAILURE,
	MODULE_FILE_SHARING_VIOLATION
} __module_error;

typedef enum
{
	ID_ADD = 2000,
	ID_APPLY,
	ID_APPLYTO,
	ID_ASKTOIMPORT,
	ID_AUTOIMPORT,
	ID_CANCEL,
	ID_COLLISIONS,
	ID_COMMENTS,
	ID_DEBUGGEE,
	ID_DECREASE,
	ID_DELETE,
	ID_DEMANGLE,
	ID_DONOTHING,
	ID_EDIT,
	ID_FILTER,
	ID_IMPORT,
	ID_IMPORTALWAYS,
	ID_INCREASE,
	ID_INSERT,
	ID_LABELS,
	ID_LOAD,
	ID_MASKS,
	ID_MAXINCREASE,
	ID_MAXDECREASE,
	ID_MODULE,
	ID_OVERWRITE,
	ID_SAVE,
	ID_SKIP,
	ID_USEMASKS
} __wnd_id;

/* .UDD tag */
#define TAG_MAPIMP			  0x504D694D

#define MAPBUFLEN             1024
#define ERRBUFLEN             2 * TEXTLEN

/* Configuration file parameters */
#define CONFIG_STR_COMMENTS   "comments"
#define CONFIG_STR_LABELS     "labels"
#define CONFIG_STR_COLLISIONS "collisionchecks"
#define CONFIG_STR_APPLYTO    "applytodebuggee"
#define CONFIG_STR_AUTOIMPORT "autoimport"
#define CONFIG_STR_DEMANGLE   "demangle"
#define CONFIG_STR_USEMASKS   "usemasks"
#define CONFIG_STR_MASKS      "customfilter"
#define CONFIG_STR_MAXSIZE    sizeof(CONFIG_STR_COLLISIONS)

/* Option window definitions */
#define OPTWND_CLASS_NAME     L"mapimp_wnd"
#define OPTWND_WINDOW_NAME    L"Options"
#define OPTWND_FONT_NAME      L"Verdana"
#define OPTWND_ICON_NAME      L"ICO_OPTIONS"
#define OPTWND_WINDOW_WIDTH   354
#define OPTWND_WINDOW_HEIGHT  312

#define INPUTWND_TYPE         196

#endif
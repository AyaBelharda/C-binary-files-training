#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <windows.h>
#define VMax 15
#define DMax 11
#define MMax 3
#ifndef _CONIO2_H_
#define _CONIO2_H_

#include <conio.h>
#ifdef UNICODE
#include <windows.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif
#endif /* _CONIO2_H_ */
/**
 * Colors which you can use in your application.
 */
typedef enum
{
    BLACK,          /**< black color */
    BLUE,           /**< blue color */
    GREEN,          /**< green color */
    CYAN,           /**< cyan color */
    RED,            /**< red color */
    MAGENTA,        /**< magenta color */
    BROWN,          /**< brown color */
    LIGHTGRAY,      /**< light gray color */
    DARKGRAY,       /**< dark gray color */
    LIGHTBLUE,      /**< light blue color */
    LIGHTGREEN,     /**< light green color */
    LIGHTCYAN,      /**< light cyan color */
    LIGHTRED,       /**< light red color */
    LIGHTMAGENTA,   /**< light magenta color */
    YELLOW,         /**< yellow color */
    WHITE           /**< white color */
} COLORS;


/**
 * This defines enables you to use all MinGW conio.h functions without
 * underscore.
 */
#define cgets   _cgets
#define cprintf _cprintf
#define cputs   _cputs
#define cscanf  _cscanf

#ifdef UNICODE
    #define cgetws   _cgetws
    #define getwch   _getwch
    #define getwche  _getwche
    #define putwch   _putwch
    #define ungetwch _ungetwch
    #define cputws   _cputws
    #define cwprintf _cwprintf
    #define cwscanf  _cwscanf
#endif
/*@}*/


#ifndef _CONIO_NO_GETTEXT_
  #define gettext _conio_gettext
#endif

#define ScreenClear clrscr

/**
 * @anchor cursortypes
 * @name Cursor types
 * Predefined cursor types. */
/*@{*/
#define _NOCURSOR 0         /**< no cursor */
#define _SOLIDCURSOR 100    /**< cursor filling whole cell */
#define _NORMALCURSOR 20    /**< cursor filling 20 percent of cell height */
/*@}*/

/**
 * Structure holding information about screen.
 * @see gettextinfo
 * @see inittextinfo
 */
struct text_info {
    unsigned char curx;          /**< cursor coordinate x */
    unsigned char cury;          /**< cursor coordinate y */
    unsigned short attribute;    /**< current text attribute */
    unsigned short normattr;     /**< original value of text attribute after
                                      start of the application. If you don't
                                      called the <TT>inittextinfo</TT> on the
                                      beginning of the application, this always
                                      will be black background and light gray
                                      foreground */
    unsigned char screenwidth;   /**< screen width */
    unsigned char screenheight;  /**< screen height */
};

/**
 * Structure used by gettext/puttext.
 * @see _conio_gettext
 * @see puttext
 */
struct char_info {
#ifdef UNICODE
    wchar_t letter;        /**< character value */
#else
    char letter;           /**< character value */
#endif
    unsigned short attr;   /**< attribute value */
};

/**
 * Returns information of the screen.
 * @see text_info
 */
void gettextinfo (struct text_info * info);

/**
 * Call this if you need real value of normattr attribute in the text_info
 * structure.
 * @see text_info
 */
void inittextinfo (void);

/**
 * Clears rest of the line from cursor position to the end of line without
 * moving the cursor.
 */
void clreol (void);

/**
 * Clears whole screen.
 */
void clrscr (void);

/**
 * Delete the current line (line on which is cursor) and then moves all lines
 * below one line up. Lines below the line are moved one line up.
 */
void delline (void);

/**
 * Insert blank line at the cursor position.
 * Original content of the line and content of lines below moves one line down.
 * The last line is deleted.
 */
void insline (void);

/**
 * Gets text from the screen. If you haven't defined <TT>_CONIO_NO_GETTEXT_</TT>
 * prior to including <TT>conio2.h</TT> you can use this function also under
 * the <TT>gettext</TT> name.
 * @see char_info
 * @see puttext
 * @param left Left coordinate of the rectangle, inclusive, starting from 1.
 * @param top Top coordinate of the rectangle, inclusive, starting from 1.
 * @param right Right coordinate of the rectangle, inclusive, starting from 1.
 * @param bottom Bottom coordinate of the rectangle, inclusive, starting from 1.
 * @param buf You have to pass buffer of size
 * <TT>(right - left + 1) * (bottom - top + 1) * sizeof(char_info)</TT>.
 */
void _conio_gettext (int left, int top, int right, int bottom,
                     struct char_info * buf);

/**
 * Puts text back to the screen.
 * @see char_info
 * @see _conio_gettext
 * @param left Left coordinate of the rectangle, inclusive, starting from 1.
 * @param top Top coordinate of the rectangle, inclusive, starting from 1.
 * @param right Right coordinate of the rectangle, inclusive, starting from 1.
 * @param bottom Bottom coordinate of the rectangle, inclusive, starting from 1.
 * @param buf You have to pass buffer of size
 * <TT>(right - left + 1) * (bottom - top + 1) * sizeof(char_info)</TT>.
 */
void puttext (int left, int top, int right, int bottom, struct char_info * buf);

/**
 * Copies text.
 * @param left Left coordinate of the rectangle, inclusive, starting from 1.
 * @param top Top coordinate of the rectangle, inclusive, starting from 1.
 * @param right Right coordinate of the rectangle, inclusive, starting from 1.
 * @param bottom Bottom coordinate of the rectangle, inclusive, starting from 1.
 * @param destleft Left coordinate of the destination rectangle.
 * @param desttop Top coordinate of the destination rectangle.
 */
void movetext (int left, int top, int right, int bottom, int destleft,
              int desttop);

/**
 * Moves cursor to the specified position.
 * @param x horizontal position
 * @param y vertical position
 */
void gotoxy(int x, int y);

/**
 * Puts string at the specified position.
 * @param x horizontal position
 * @param y vertical position
 * @param str string
 */
void cputsxy (int x, int y, char * str);

/**
 * Puts char at the specified position.
 * @param x horizontal position
 * @param y vertical position
 * @param ch char
 */
void putchxy (int x, int y, char ch);

/**
 * Sets the cursor type.
 * @see @ref cursortypes
 * @param type cursor type, under Win32 it is height of the cursor in percents
 */
void _setcursortype (int type);

/**
 * Sets attribute of text.
 * @param _attr new text attribute
 */
void textattr (int _attr);

/**
 * Sets text attribute back to value it had after program start.
 * It uses text_info's normattr value.
 * @see text_info
 */
void normvideo (void);

/**
 * Sets text background color.
 * @see COLORS
 * @param color new background color
 */
void textbackground (int color);

/**
 * Sets text foreground color.
 * @see COLORS
 * @param color new foreground color
 */
void textcolor (int color);

/**
 * Reads the cursor X position.
 * @returns cursor X position
 */
int wherex (void);

/**
 * Reads the cursor Y position.
 * @returns cursor Y position
 */
int wherey (void);

/**
 * Reads password. This function behaves like cgets.
 *
 * @see cgets
 * @param prompt prompt which will be displayed to user
 * @param str string for the password. <TT>str[0]</TT> have to contain
 * length of the <TT>str</TT> - 3
 * @returns <TT>&str[2]</TT>, the password will be stored in <TT>str</TT>
 * beginning at <TT>str[2]</TT>, in <TT>str[1]</TT> will be length of the
 * string without <TT>\\0</TT>, at <TT>str[2 + str[1]]</TT> will be \\0.
 */
char * getpass (const char * prompt, char * str);

/**
 * Makes foreground colors light.
 * If the current foreground color is less than <TT>DARKGRAY</TT> adds
 * 8 to the its value making dark colors light.
 * @see COLORS
 * @see lowvideo
 */
void highvideo (void);

/**
 * Makes foreground colors dark.
 * If the current foreground color is higher than <TT>LIGHTGRAY</TT> substracts
 * 8 from its value making light colors dark.
 * @see COLORS
 * @see highvideo
 */
void lowvideo (void);

/*@{*/
/*
 * You may need to link with libmsvcr70.a or libmsvcr70d.a or libmsvcr71.a
 *  or libmsvcr71d.a if you want any of these functions.
 */
#ifdef UNICODE
_CRTIMP wchar_t * __cdecl         _cgetws(wchar_t *);
_CRTIMP unsigned short __cdecl    _getwch(void);
_CRTIMP unsigned short __cdecl    _getwche(void);
_CRTIMP unsigned short __cdecl    _putwch(wchar_t);
_CRTIMP unsigned short __cdecl    _ungetwch(unsigned short);
_CRTIMP int __cdecl               _cputws(const wchar_t *);
_CRTIMP int __cdecl               _cwprintf(const wchar_t *, ...);
_CRTIMP int __cdecl               _cwscanf(const wchar_t *, ...);
#endif
/*@}*/

/**
 * Pauses program execution for a given time.
 * @see switchbackground
 * @param ms miliseconds
 */
void delay (int ms);

/**
 * Replaces background color in the whole window. The text however
 * is left intact. Does not modify textbackground().
 * @see flashbackground
 * @param color background color
 */
void switchbackground (int color);

/**
 * Changes background color for a given time and then it restores it back.
 * You can use it for visual bell. Does not modify textbackground().
 * @see switchbackground
 * @see delay
 * @param color background color
 * @param ms miliseconds
 */
void flashbackground (int color, int ms);

/**
 * Clears the keyboard buffer.
 * To see it in effect run <TT>conio_test</TT> and try to press a key during
 * the 'Flashing...' phase.
 */
void clearkeybuf (void);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#endif

static int __BACKGROUND = BLACK;
static int __FOREGROUND = LIGHTGRAY;
static struct text_info __text_info = {
    1, 1,
    LIGHTGRAY + (BLACK << 4),
    LIGHTGRAY + (BLACK << 4),
    80, 25
};
static int __CONIO_TOP = 0;
static int __CONIO_LEFT = 0;

static void
__fill_text_info (void)
{
    CONSOLE_SCREEN_BUFFER_INFO info;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    __CONIO_LEFT = info.srWindow.Left;
    __CONIO_TOP = info.srWindow.Top;
    __text_info.curx = info.dwCursorPosition.X - __CONIO_LEFT + 1;
    __text_info.cury = info.dwCursorPosition.Y - __CONIO_TOP  + 1;
    __text_info.attribute = info.wAttributes;
    __text_info.screenwidth  = info.srWindow.Right - info.srWindow.Left + 1;
    __text_info.screenheight = info.srWindow.Bottom - info.srWindow.Top + 1;
}

void
gettextinfo (struct text_info * info)
{
    __fill_text_info();
    *info = __text_info;
}

void
inittextinfo (void)
{
    CONSOLE_SCREEN_BUFFER_INFO info;

    GetConsoleScreenBufferInfo (GetStdHandle(STD_OUTPUT_HANDLE), &info);
    __text_info.normattr = info.wAttributes;
}

void
clrscr (void)
{
    DWORD written;
    int i;

    __fill_text_info();
    for (i = __CONIO_TOP; i < __CONIO_TOP + __text_info.screenheight; i++) {
      FillConsoleOutputAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
        __FOREGROUND + (__BACKGROUND << 4), __text_info.screenwidth,
        (COORD) {__CONIO_LEFT, i},
        &written);
      FillConsoleOutputCharacter (GetStdHandle(STD_OUTPUT_HANDLE), ' ',
        __text_info.screenwidth,
        (COORD) {__CONIO_LEFT, i},
        &written);
    }
    gotoxy (1, 1);
}


void
clreol (void)
{
    COORD coord;
    DWORD written;

    __fill_text_info();
    coord.X = __CONIO_LEFT + __text_info.curx - 1;
    coord.Y = __CONIO_TOP  + __text_info.cury - 1;

    FillConsoleOutputAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
      __FOREGROUND + (__BACKGROUND << 4),
      __text_info.screenwidth - __text_info.curx + 1, coord, &written);
    FillConsoleOutputCharacter (GetStdHandle (STD_OUTPUT_HANDLE),
      ' ', __text_info.screenwidth - __text_info.curx + 1, coord, &written);
    gotoxy (__text_info.curx, __text_info.cury);
}


void
delline (void)
{
    COORD coord;
    SMALL_RECT rect;
    CHAR_INFO fillchar;

    __fill_text_info();
    coord.X = __CONIO_LEFT;
    coord.Y = __CONIO_TOP + __text_info.cury - 1;
    rect.Left = __CONIO_LEFT;
    rect.Top = __CONIO_TOP + __text_info.cury;
    rect.Right = __CONIO_LEFT + __text_info.screenwidth - 1;
    rect.Bottom = __CONIO_TOP + __text_info.screenheight - 1;
    fillchar.Attributes = __FOREGROUND + (__BACKGROUND << 4);
#ifdef UNICODE
    fillchar.Char.UnicodeChar = L' ';
    ScrollConsoleScreenBufferW (GetStdHandle (STD_OUTPUT_HANDLE),
      &rect, NULL, coord, &fillchar);
#else
    fillchar.Char.AsciiChar = ' ';
    ScrollConsoleScreenBufferA (GetStdHandle (STD_OUTPUT_HANDLE),
      &rect, NULL, coord, &fillchar);
#endif


    gotoxy (__text_info.curx, __text_info.cury);
}

void
insline (void)
{
    COORD coord;
    SMALL_RECT rect;
    CHAR_INFO fillchar;

    __fill_text_info();
    coord.X = __CONIO_LEFT;
    coord.Y = __CONIO_TOP + __text_info.cury;
    rect.Left = __CONIO_LEFT;
    rect.Top = __CONIO_TOP + __text_info.cury - 1;
    rect.Right = __CONIO_LEFT + __text_info.screenwidth - 1;
    rect.Bottom = __CONIO_TOP + __text_info.screenheight - 2;
    fillchar.Attributes = __FOREGROUND + (__BACKGROUND << 4);
#ifdef UNICODE
    fillchar.Char.UnicodeChar = L' ';
    ScrollConsoleScreenBufferW (GetStdHandle (STD_OUTPUT_HANDLE),
      &rect, NULL, coord, &fillchar);
#else
    fillchar.Char.AsciiChar = ' ';
    ScrollConsoleScreenBufferA (GetStdHandle (STD_OUTPUT_HANDLE),
      &rect, NULL, coord, &fillchar);
#endif

    gotoxy (__text_info.curx, __text_info.cury);
}

void
movetext (int left, int top, int right, int bottom, int destleft, int desttop)
{
    struct char_info * buffer;

    buffer = malloc ((right - left + 1) * (bottom - top + 1) * sizeof(struct char_info));
    gettext (left, top, right, bottom, buffer);
    puttext (destleft, desttop, destleft + right - left, desttop + bottom - top, buffer);
    free(buffer);
}

void
_conio_gettext (int left, int top, int right, int bottom,
  struct char_info * buf)
{
    int i;
    SMALL_RECT r;
    CHAR_INFO* buffer;
    COORD size;

    __fill_text_info();
    r = (SMALL_RECT) {__CONIO_LEFT + left - 1, __CONIO_TOP + top - 1,
      __CONIO_LEFT + right - 1, __CONIO_TOP + bottom - 1};
    size.X = right - left + 1;
    size.Y = bottom - top + 1;
    buffer = malloc (size.X * size.Y * sizeof(CHAR_INFO));

    ReadConsoleOutput (GetStdHandle (STD_OUTPUT_HANDLE),
      (PCHAR_INFO) buffer, size, (COORD) {0, 0}, &r);

    for (i = 0; i < size.X * size.Y; i++)
    {
#ifdef UNICODE
        buf[i].letter = buffer[i].Char.UnicodeChar;
#else
        buf[i].letter = buffer[i].Char.AsciiChar;
#endif
        buf[i].attr = buffer[i].Attributes;
    }
    free (buffer);
}

void
puttext (int left, int top, int right, int bottom, struct char_info * buf)
{
    int i;
    SMALL_RECT r;
    CHAR_INFO* buffer;
    COORD size;

    __fill_text_info();
    r = (SMALL_RECT) {__CONIO_LEFT + left - 1, __CONIO_TOP + top - 1,
      __CONIO_LEFT + right - 1, __CONIO_TOP + bottom - 1};
    size.X = right - left + 1;
    size.Y = bottom - top + 1;
    buffer = malloc (size.X * size.Y * sizeof(CHAR_INFO));

    for (i = 0; i < size.X * size.Y; i++)
    {
#ifdef UNICODE
        buffer[i].Char.UnicodeChar = buf[i].letter;
#else
        buffer[i].Char.AsciiChar = buf[i].letter;
#endif
        buffer[i].Attributes = buf[i].attr;
    }

    WriteConsoleOutput (GetStdHandle (STD_OUTPUT_HANDLE),
      buffer, size, (COORD) {0, 0}, &r);
    free (buffer);
}

void
gotoxy(int x, int y)
{
  COORD c;

  c.X = __CONIO_LEFT + x - 1;
  c.Y = __CONIO_TOP  + y - 1;
  SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void
cputsxy (int x, int y, char * str)
{
    gotoxy (x, y);
    cputs (str);
}

void
putchxy (int x, int y, char ch)
{
    gotoxy (x, y);
    putch (ch);
}

void
_setcursortype (int type)
{
    CONSOLE_CURSOR_INFO Info;

    if (type == 0) {
        Info.bVisible = FALSE;
    } else {
      Info.dwSize = type;
      Info.bVisible = TRUE;
    }
    SetConsoleCursorInfo (GetStdHandle (STD_OUTPUT_HANDLE),
      &Info);
}


void
textattr (int _attr)
{
    __FOREGROUND = _attr & 0xF;
    __BACKGROUND = _attr >> 4;
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), _attr);
}

void
normvideo (void)
{
    textattr (__text_info.normattr);
}

void
textbackground (int color)
{
    __BACKGROUND = color;
    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
      __FOREGROUND + (color << 4));
}


void
textcolor (int color)
{
    __FOREGROUND = color;
    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
      color + (__BACKGROUND << 4));
}


int
wherex (void)
{
    __fill_text_info();
    return __text_info.curx;
}


int
wherey (void)
{
    __fill_text_info();
    return __text_info.cury;
}

char *
getpass (const char * prompt, char * str)
{
    int maxlength = str[0];
    int length = 0;
    int ch = 0;
    int x, y;

    cputs(prompt);
    __fill_text_info();
    x = __text_info.curx;
    y = __text_info.cury;

    while (ch != '\r') {
        ch = getch();
        switch (ch) {
            case '\r' : /* enter */
                break;
            case '\b' : /* backspace */
                if (length > 0) putchxy (x + --length, y, ' ');
                gotoxy (x + length, y);
                break;
            default:
                if (length < maxlength) {
                    putchxy (x + length, y, '*');
                    str[2 + length++] = ch;
                }
        }
    }

    str[1] = length;
    str[2 + length] = '\0';
    return &str[2];
}

void
highvideo (void)
{
    if (__FOREGROUND < DARKGRAY) textcolor(__FOREGROUND + 8);
}

void
lowvideo (void)
{
    if (__FOREGROUND > LIGHTGRAY) textcolor(__FOREGROUND - 8);
}

void
delay (int ms)
{
    Sleep(ms);
}

void
switchbackground (int color)
{
    struct char_info* buffer;
    int i;

    buffer = malloc(__text_info.screenwidth * __text_info.screenheight *
      sizeof(struct char_info));
    _conio_gettext(1, 1, __text_info.screenwidth, __text_info.screenheight,
      buffer);
    for (i = 0; i < __text_info.screenwidth * __text_info.screenheight; i++) {
        unsigned short attr = buffer[i].attr & 0xF;
        buffer[i].attr = (color << 4) | attr;
    }
    puttext(1, 1, __text_info.screenwidth, __text_info.screenheight, buffer);
    free(buffer);
}

void
flashbackground (int color, int ms)
{
    struct char_info* buffer;

    buffer = malloc(__text_info.screenwidth * __text_info.screenheight *
      sizeof(struct char_info));
    _conio_gettext(1, 1, __text_info.screenwidth, __text_info.screenheight,
      buffer);
    switchbackground(color);
    delay(ms);
    puttext(1, 1, __text_info.screenwidth, __text_info.screenheight, buffer);
    free(buffer);
}

void
clearkeybuf (void)
{
    while (kbhit()) {
        getch();
    }
}

#ifdef __cplusplus
}
#endif

void Speak(char *discours) { //procédure qui auditionne une chaine de caractères
    char chaine[256];
    sprintf(chaine, "echo m=\"%s\" > file.vbs", discours);
    system(chaine);
    sprintf(chaine, "echo CreateObject(\"SAPI.SpVoice\").Speak m >> file.vbs");
    system(chaine);
    sprintf(chaine, "file.vbs");
    system(chaine);
    remove("file.vbs");
}

//Declaration de la structure temperature qui contient le nom de la Wilaya, la date et la température ainsi qu'un champ de suppression logique
typedef struct Temperature
{
    char Wilaya[VMax];
    char Date[DMax];
    float temp;
    bool effa;

}Temp;
/*******************************************************************************/

Temp Nouvel_Eregistrement()
/**< Lecture d'un nouveau eregistrement */
{
    float Temperature;
    Temp Nouv_Temperature; //Déclaration d'un nouveau enregistement.
    printf("\tVeuillez entrer le nom de la Wilaya: ");
    scanf("%s",Nouv_Temperature.Wilaya);
    printf("\tVeuillez entrer la date: ");
    scanf("%s",Nouv_Temperature.Date);
    printf("\tVeuillez entrer la temperature correspondante: ");
    scanf("%f",&Temperature);
    //Affectation des information dans leurs champs
    Nouv_Temperature.temp = Temperature;
    Nouv_Temperature.effa = false;
    return Nouv_Temperature;
}
/*******************************************************************************/
FILE *Crea_FB(char *Nom_Fich)
/**< Création du fichier */
{   FILE *fb;
    Temp T;
    int Arret=0;
    int rep;
    if (access(Nom_Fich,F_OK)==0) //Cas où le fichier existe déja.
    {   printf("\tFichier existe deja, il a ete ouvert\n");
        fb=fopen(Nom_Fich,"rb+");
        return fb;
    }
    else //Cas où le fichier n'existe pas.
    {
      fb=fopen(Nom_Fich,"wb+");
      printf("\tLe fichier a ete cree,Veuillez proceder à le remplir\n");
     while (Arret==0)
      { int NbInfo = 0;
        fseek(fb,0,SEEK_SET);
        fread(&NbInfo, sizeof(int),1,fb);//Lire le nombre d'enregistrements.
        NbInfo++;
        fseek(fb,0,SEEK_SET);//se positioner en début du fichier
        fwrite(&NbInfo,sizeof(int),1,fb); //mise à jours du nombre d'enregistrements.
        T=Nouvel_Eregistrement();
        fseek(fb,0,SEEK_END);//Aller vers la fin du fichier.
        fwrite(&T, sizeof(T),1,fb);//Ecriture du nouvel enregistrement.
        printf("\tSi vous voulez quitter entrer 1 sinon entrer 0\n");
        scanf("%d",&rep);
        if(rep==1)
        {
            Arret=1;
            textcolor(5);
            printf("\nles informations ont ete bien enregistrees, merci pour votre contribution\n");
        }
        else
        {
            Arret=0;
        }
      }
      return fb;
    }

}
/*******************************************************************************/
void Ajout_N(FILE *fb)
/**< L'Ajout d'une nouvelle Wilaya dans le fichier */
{  Temp T;
   T=Nouvel_Eregistrement();
   fseek(fb,0,SEEK_SET);
   int NbInfo;
   fread(&NbInfo, sizeof(int),1,fb);//Lire le nombre d'enregistrements.
   NbInfo++;
   fseek(fb,0,SEEK_SET);
   fwrite(&NbInfo,sizeof(int),1,fb);//mise à jours du nombre d'enregistrements.
   fseek(fb,0,SEEK_END);//Aller vers la fin du fichier.
   fwrite(&T,sizeof(T),1,fb); //Ecriture de l'enregistrement dans le fichier
}
/*******************************************************************************/
void Modif_Wilaya(FILE *fb)
/**< Modification des information de la Wilaya */
{   Temp T_Modif;
    char Wilaya[VMax],date[11];
    float tempN;
    int i=0, Arret=0;
    printf("\tVeuillez donner le nom de la Wilaya et la date(Sauter la ligne entre les 2 donnees)\n");
    scanf("%s",&Wilaya);
    scanf("%s",&date);
    int NbInfo;
    fseek(fb,0,SEEK_SET);
    fread(&NbInfo, sizeof(int),1,fb);//Lire le nombre d'enregistrements.
    fseek(fb, sizeof(int),SEEK_SET);//Se positionner après la première donnée.
    for (int i = 0;i<NbInfo && Arret==0;i++)
    {
      fread(&T_Modif,sizeof(T_Modif),1,fb);
      if (strcmp(T_Modif.Wilaya,Wilaya)==0 && strcmp(T_Modif.Date,date)==0)
      { //Comparaison des informations.
          printf("\tVeuillez donner la nouvelle temperature\n");
          scanf("%f",&tempN);
          T_Modif.temp = tempN;
          fseek(fb,sizeof(int)+sizeof(T_Modif)*i,SEEK_SET);
          //Mise à jours du fichier.
          fwrite(&T_Modif,sizeof(T_Modif),1,fb);
          printf("\tModification effectue avec succes\n");
          Arret=1;
      }
    }
}
/*******************************************************************************/
void INFO_Wilaya(FILE *fb)
/**< Affichage de la temperature Min,Max,Moy d'une Wilaya */
{   char Wilaya[VMax];
    int Nb_Occ=0;
    Temp T;
    printf("\tDonner une Wilaya: ");
    scanf("%s",&Wilaya);
    int NbInfo;
    fseek(fb,0,SEEK_SET);
    fread(&NbInfo,sizeof(int),1,fb);//Lire le nb d'enregistrements.
    fseek(fb, sizeof(int),SEEK_SET);
    //Initialisation des infos.
    float min= 100;
    float max = -100;
    float somTemp=0;
    for (int i = 0;i<NbInfo;i++)
    {
        fread(&T,sizeof(T),1,fb);
        if(strcmp(T.Wilaya,Wilaya)==0 && !T.effa)
        {
            Nb_Occ++; //Incrémentation du nombre d'occurence de la Wilaya
            somTemp=somTemp+T.temp;
            if (T.temp>=max)
            {
                max=T.temp; //Mise à jour de la temperature maximale
            }
            if(T.temp <= min)
            {
                min=T.temp; //Mise à jour de la temperature minimale
            }
        }
    }
    if (Nb_Occ>0 )
    { //Affichage
        printf("\tWilaya : %s\n", Wilaya);
        printf("\tTemperature Minimale  : %.2f\n", min);
        printf("\tTemperature Maximale : %.2f\n", max);
        printf("\tTemperature Moyenne: %.2f\n", (somTemp/Nb_Occ));

    }
    else
    {
        printf("La Wilaya n'existe pas\n");
    }

}
/*******************************************************************************/
void Supp_enreg(FILE *fb)
/**< Suppression de tous les enregistrements relatifs à une Wilaya */
{   Temp T;
    char Wilaya[VMax];
    printf("\tDonner une Wilaya\n");
    scanf("%s",&Wilaya);
    int NbInfo;
    fseek(fb,0,SEEK_SET);//se positionner en début de fichier
    fread(&NbInfo, sizeof(int),1,fb);//Lire le nombre de données
    fseek(fb, sizeof(int),SEEK_SET);
    int i=0;
     for (int i = 0;i<NbInfo;i++)
    {
        fread(&T,sizeof(Temp),1,fb);
        if(strcmp(T.Wilaya,Wilaya)==0 && ! T.effa)
        {    T.effa=true; //Mise à jour du champ effacé.
             fseek(fb,sizeof(int) + sizeof(Temp)*i,SEEK_SET); //Se positionner où l faut écrire le nouvel enregistrement.
             fwrite(&T,sizeof(Temp),1,fb);//Mise à jours du fichier.
             printf("\tSuppression effectuee avec succes\n");
        }

    }

}
/*******************************************************************************/
void afficher_fichier(FILE * f)
/**< Afficher le contenu du fichier */
{
    Temp Aff;
    int NbInfo;
    fseek(f,0,SEEK_SET);
    fread(&NbInfo, sizeof(int),1,f);
    if(NbInfo==0){
        printf("\tLe fichier est vide\n");
        return;
    }
    fseek(f, sizeof(int),SEEK_SET);
     for (int i = 0;i<NbInfo;i++){
         fread(&Aff, sizeof(Temp),1,f);//Lire l'enregistrement.
         if(!Aff.effa){
             printf("\tLes informations sur cette Wilaya sont:\n");
             printf("\tWilaya : %s\n", Aff.Wilaya);
             printf("\tDate : %s\n", Aff.Date);
             printf("\tTemperature : %.2f\n", Aff.temp);
         }
     }
 }
/*******************************************************************************/

bool verification(char nom_wilaya){
FILE *f = NULL;
f=fopen("wilaya.txt","r+");
if (f==NULL)
    printf("erreur lors de l'ouverture du fichier");
else{
    char ligne[256];
    bool trouv=false;
    while ((!feof(f)) && (fgets(ligne, sizeof(ligne), f)) && (!trouv) ){
     if (strcmp(ligne,nom_wilaya) ==0)
                trouv=true;
                return trouv;}
 fclose(f);
}
}
/*******************************************************************************/
void codage(unsigned char ligne[], unsigned char mot[]);
 /* cryptage d'une ligne par un mot-cle */

void codage_fichier()
 {
 FILE *f = NULL, *g = NULL;
 char nomf1[20], nomf2[20];
 char ligne[256];
 char mot[20];

 printf("Nom du fichier texte en entree : ");
 scanf(" %s", nomf1);
 printf("Nom du fichier texte en sortie : ");
 scanf(" %s", nomf2);
 printf("Le mot cle (<20 car) : ");
 scanf(" %s", mot);
 f = fopen(nomf1,"rb");
 if (f == NULL) return 1;
 g = fopen(nomf2,"wb");
 if (g == NULL) return 1;
 /*if ( fgets(ligne, sizeof(ligne), f) ) {
         codage(ligne,mot);
       fprintf(g, "%s", ligne);
    }*/
 while ( !feof(f) )
 if ( fgets(ligne, sizeof(ligne), f) ) {
 codage(ligne,mot);
 fprintf(g, "%s", ligne);
 }
 fclose(f);
 fclose(g);
 return 0;
 }


 void codage( unsigned char ligne[], unsigned char mot[])
 {
 // signed char -128 -> +127
 // unsigned char 0 -> +255
 int i = 0, j = 0;
 while ( ligne[i] != '\0' ) //Tant que ce n'est pas la fin de la chaine de caractères
 if (ligne[i] >= 32 && ligne[i] < 127) {
 ligne[i] = ligne[i] + mot[j];
 while ( ligne[i] > 126 )
 ligne[i] = ligne[i] - 127 + 32;
 // pour que le code obtenu reste un caractere affichable
 // les caract affichables ont un code ascii entre 32 et 126
 i++;
 j++;
 if (mot[j] == '\0') j = 0; // si c'est la fin de la chaine de caractère du mot ou de la clé
 }
 else
 i++;
 }


/*****************************************************************************************/


void bienvenu()
    {
     srand(time(0));
     int *nbPic = 1;
     textcolor(5);
     printf("\n\n\n\n");
     printf("\t\t\t\t |||||||||||     |||||||))                                     \n");
    printf("\t\t\t\t     |||         |||     ))                                   \n");
    printf("\t\t\t\t     |||         |||     ))                                    \n");
    printf("\t\t\t\t     |||         |||))))))                                           \n");
    printf("\t\t\t\t     |||         |||                                           \n");
    printf("\t\t\t\t     |||         |||                                               \n");
    printf("\t\t\t\t     |||         |||                                                   \n");
    printf("\t\t\t\t     |||         |||                                                \n\n");

     textcolor(7);
     printf("\n\n\n\tESSAI EXO6 TD1\n");
     printf("\n\tANNEE SCOLAIRE:   ");
     textcolor(5);
     printf("2022 / 2023\n");
     textcolor(5);
     printf("\n\t\t\t\t\t\tREALISE PAR:\n");
     textcolor(7);
     printf("\n\t\t\t\t\t\tBELHARDA AYA    G02/A\n");

     printf("\n\t\t\t\t\t\tTOUTOU SALSABILA   G02/A\n");

      srand(time(0));

    Speak("BIENVENU CHER UTILISATEUR");
   sleep (3);
     system("cls");

    }

int main() {
    FILE * f;
    char tab[58];
    char Nom_Fich[255];
    bool isOn = true;
    int choix;
    bienvenu();
    while (isOn)
    {

        textcolor(5);
        printf("\tBienvenue cher utilisateur\n");
        textcolor(5);
        printf("\n\t1- ");
        textcolor(7);
        printf("Operations sur le fichier\n");
        textcolor(5);
        printf("\t2- ");
        textcolor(7);
        printf("Quitter\n");
        printf("\n\tVeuilliez entrer votre choix: ");

        scanf("%d",&choix);
        if(choix==1){
            printf("\n\tEntrer un nom pour le fichier: ");
            scanf("%s",&Nom_Fich);
            f=Crea_FB(Nom_Fich);
            while (f!=NULL){
                textcolor(5);
                printf("\n\t0-");
                textcolor(7);
                printf(" Voir les infos sur une Wilaya (max,min,moy)\n");
                textcolor(5);
                printf("\t1-");
                textcolor(7);
                printf(" Ajouter une Wilaya\n");
                textcolor(5);
                printf("\t2-");
                textcolor(7);
                printf(" Modifier une Wilaya\n");
                textcolor(5);
                printf("\t3-");
                textcolor(7);
                printf(" Effacer une Wilaya\n");
                textcolor(5);
                printf("\t4-");
                textcolor(7);
                printf(" Afficher tout le fichier\n");
                textcolor(5);
                printf("\t5-");
                textcolor(7);
                printf(" Coder le fichier\n");
                textcolor(5);
                printf("\t6-");
                textcolor(7);
                printf(" Decoder le fichier\n");
                textcolor(5);
                printf("\t7-");
                textcolor(7);
                printf(" Fermer le fichier\n");
                printf("\n\tVeuilliez entrer votre choix: ");
                scanf("%d",&choix);
                switch (choix) {
                    case 0:
                        {
                           INFO_Wilaya(f);
                        }
                        break;
                    case 1:
                        {
                             Ajout_N(f);
                        }
                        break;
                    case 2:
                        {

                           Modif_Wilaya(f);
                        }
                        break;
                    case 3:
                        {
                           Supp_enreg(f);

                        }
                        break;
                    case 4:
                         {
                            afficher_fichier(f);

                         }
                        break;
                    case 5:
                         {
                            codage_fichier();

                         }
                        break;
                    case 6:
                         {
                            decodage_fichier(Nom_Fich);

                         }
                        break;
                    case 7:
                        {
                            fclose(f);
                            f = NULL;
                        }
                        break;
                    default:
                        printf("Veuillez entrer un choix valide\n");
                        break;
                }
            }
        }else if (choix ==2){
            isOn=false;
        }else{
            printf("Veuillez entrer un choix valide\n");
        }
    }

    return 0;
}

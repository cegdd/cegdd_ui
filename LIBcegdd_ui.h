#ifndef CEGDD_UI
#define CEGDD_UI

#include <stdbool.h>

#include <GL/gl.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

struct pict
{
    SDL_Rect pos;
    GLuint texture;

    int x;
    int y;
};

struct TEXTE
{
    struct pict img;
	int lenght;
	int high;
};

struct hookpict
{
    struct pict pict;
    SDL_Point translation;
    SDL_Rect Originpos;
};

struct moving_pict
{
    struct pict pict;
    GLuint texture[16];
    int frame;
    int current;
    int delay;
    int time;
};

struct BOUTON
{
	GLuint texture;
	SDL_Rect pos;
	int etat;
	int flag;
};


struct BOUTON_TEXTE
{
	struct TEXTE texte;
	struct BOUTON bouton;
};


enum{B_NORMAL, B_SURVOLER, B_CLIQUER, B_IMPOSSIBLE, B_INUSE};/*bouton*/
enum{B_detail, B_liste, B_none};//a suppr
enum{SLIDE_CLOSE, SLIDE_ESPECE, SLIDE_DETAIL};//a suppr

bool CEGDD_UI_colisionbox(SDL_Rect *A, SDL_Rect *B, bool pointeur);
bool CEGDD_UI_isInTheGoodPanel(struct BOUTON *liste_bouton, int slidestate, int index);

int CEGDD_UI_BT_up(struct SDL_Rect pointeur, struct BOUTON *liste_bouton, int *Qtt_bouton, bool *asked);

void CEGDD_UI_setPos4(SDL_Rect *pos, int x, int y, int w, int h);
void CEGDD_UI_setPos2(SDL_Point *point, int x, int y);
void CEGDD_UI_setPos2rect(SDL_Rect *point, int x, int y);
void CEGDD_UI_copypos(SDL_Rect *source, SDL_Rect *target);
void CEGDD_UI_draw_pict(struct pict *image);
void CEGDD_UI_setColor(SDL_Color *couleur, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void CEGDD_UI_draw_hookpict(struct hookpict *image, SDL_Rect *support);
void CEGDD_UI_draw(GLuint texture, SDL_Rect *pos);
void CEGDD_UI_Turn_And_Draw (struct pict *img, float angle);
void CEGDD_UI_turn_draw_hookpict(int angle, struct hookpict *image, SDL_Rect *support);
void CEGDD_UI_Sync_Moving_Pict(int time, struct moving_pict *m_pict);
void CEGDD_UI_draw_button(struct BOUTON *bouton);
void CEGDD_UI_draw_color_black(SDL_Rect *pos);
void CEGDD_UI_creerbouton(char *path, int x, int y, int w, int h, int state, int flag, struct BOUTON *liste_bouton, int *Qtt_bouton);
void CEGDD_UI_creerboutontexte(char *path, int x, int y, int state, int flag, struct BOUTON *liste_bouton, int *Qtt_bouton, SDL_Color *couleur, TTF_Font *police);
void CEGDD_UI_creertexte(char *path, int x, int y, struct TEXTE *liste_texte, int *Qtt_texte, SDL_Color *couleur, TTF_Font *police);
void CEGDD_UI_setboutontexte(char *path, int index, struct BOUTON *liste_bouton, SDL_Color *couleur, TTF_Font *police);
void CEGDD_UI_setboutonnombre(int nombre, int index, struct BOUTON *liste_bouton, SDL_Color *couleur, TTF_Font *police);
void CEGDD_UI_BT_pointeur(struct SDL_Rect pointeur, struct BOUTON *liste_bouton, int *Qtt_bouton, int slidestate);
void CEGDD_UI_BT_down(struct BOUTON *liste_bouton, int *Qtt_bouton);

Uint8 CEGDD_UI_obtenirPixel(SDL_Surface *surface, SDL_Point *pix);
Uint8 CEGDD_UI_obtenirPixel_hook(SDL_Surface *surface, SDL_Point *pix);

GLuint CEGDD_UI_loadTexture(const char * filename);
GLuint CEGDD_UI_loadTextureandsize(const char * filename, struct SDL_Rect *pos);
GLuint CEGDD_UI_convertTexture(SDL_Surface *surface);
GLuint CEGDD_UI_imprime (char s[], int len, SDL_Color *couleur, TTF_Font *police, int *LenghtReturn, int *HighReturn);

SDL_Surface * CEGDD_UI_flipSurface(SDL_Surface * surface);

#endif

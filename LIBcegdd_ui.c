#include "LIBcegdd_ui.h"

void CEGDD_UI_setPos4(SDL_Rect *pos, int x, int y, int w, int h)
{
    pos->x = x;
    pos->y = y;
    pos->w = w;
    pos->h = h;
}

void CEGDD_UI_setPos2(SDL_Point *point, int x, int y)
{
    point->x = x;
    point->y = y;
}

void CEGDD_UI_setPos2rect(SDL_Rect *point, int x, int y)
{
    point->x = x;
    point->y = y;
}

void CEGDD_UI_copypos(SDL_Rect *source, SDL_Rect *target)
{
    target->x = source->x;
    target->y = source->y;
    target->w = source->w;
    target->h = source->h;
}

Uint8 CEGDD_UI_obtenirPixel(SDL_Surface *surface, SDL_Point *pix)
{
    Uint8 *p = (Uint8 *)surface->pixels + pix->y * surface->pitch + pix->x * 4;
    /* HAVE TO BE 32 BIT PNG */
    return *p;
}

Uint8 CEGDD_UI_obtenirPixel_hook(SDL_Surface *surface, SDL_Point *pix)
{
    Uint8 *p = (Uint8 *)surface->pixels + (surface->h-pix->y) * surface->pitch + pix->x * 4;
    /* HAVE TO BE 32 BIT PNG */
    return *p;
}


GLuint CEGDD_UI_loadTextureandsize(const char * filename, struct SDL_Rect *pos)
{
    GLuint glID;
    SDL_Surface * picture_surface = NULL;
    SDL_Surface *gl_surface = NULL;
    SDL_Surface * gl_fliped_surface = NULL;
    Uint32 rmask, gmask, bmask, amask;
    SDL_PixelFormat format;

    picture_surface = IMG_Load(filename);
    if (picture_surface == NULL)
        {   printf ("surface %s not correctly loaded \n", filename);
            return 0;}//0 is an error for opengl

    pos->w = picture_surface->w;
    pos->h = picture_surface->h;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN

    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else

    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    format = *(picture_surface->format);
    format.BitsPerPixel = 32;
    format.BytesPerPixel = 4;
    format.Rmask = rmask;
    format.Gmask = gmask;
    format.Bmask = bmask;
    format.Amask = amask;

    gl_surface = SDL_ConvertSurface(picture_surface,&format,SDL_SWSURFACE);

    gl_fliped_surface = CEGDD_UI_flipSurface(gl_surface);

    glGenTextures(1, &glID);

    glBindTexture(GL_TEXTURE_2D, glID);


    glTexImage2D(GL_TEXTURE_2D, 0, 4, gl_fliped_surface->w,
                 gl_fliped_surface->h, 0, GL_RGBA,GL_UNSIGNED_BYTE,
                 gl_fliped_surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);


    SDL_FreeSurface(gl_fliped_surface);
    SDL_FreeSurface(gl_surface);
    SDL_FreeSurface(picture_surface);

    return glID;
}

GLuint CEGDD_UI_loadTexture(const char * filename)
{
    GLuint glID;
    SDL_Surface * picture_surface = NULL;
    SDL_Surface *gl_surface = NULL;
    SDL_Surface * gl_fliped_surface = NULL;
    Uint32 rmask, gmask, bmask, amask;
    SDL_PixelFormat format;

    picture_surface = IMG_Load(filename);

    if (picture_surface == NULL)
        {return 0;}

#if SDL_BYTEORDER == SDL_BIG_ENDIAN

    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else

    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    format = *(picture_surface->format);
    format.BitsPerPixel = 32;
    format.BytesPerPixel = 4;
    format.Rmask = rmask;
    format.Gmask = gmask;
    format.Bmask = bmask;
    format.Amask = amask;

    gl_surface = SDL_ConvertSurface(picture_surface,&format,SDL_SWSURFACE);

    gl_fliped_surface = CEGDD_UI_flipSurface(gl_surface);

    glGenTextures(1, &glID);

    glBindTexture(GL_TEXTURE_2D, glID);


    glTexImage2D(GL_TEXTURE_2D, 0, 4, gl_fliped_surface->w,
                 gl_fliped_surface->h, 0, GL_RGBA,GL_UNSIGNED_BYTE,
                 gl_fliped_surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);


    SDL_FreeSurface(gl_fliped_surface);
    SDL_FreeSurface(gl_surface);
    SDL_FreeSurface(picture_surface);

    return glID;
}

GLuint CEGDD_UI_convertTexture(SDL_Surface *surface)
{
    GLuint glID;
    SDL_Surface *gl_surface = NULL;
    SDL_Surface * gl_fliped_surface = NULL;
    Uint32 rmask, gmask, bmask, amask;
    SDL_PixelFormat format;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN

    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else

    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    format = *(surface->format);
    format.BitsPerPixel = 32;
    format.BytesPerPixel = 4;
    format.Rmask = rmask;
    format.Gmask = gmask;
    format.Bmask = bmask;
    format.Amask = amask;

    gl_surface = SDL_ConvertSurface(surface,&format,SDL_SWSURFACE);

    gl_fliped_surface = CEGDD_UI_flipSurface(gl_surface);

    glGenTextures(1, &glID);

    glBindTexture(GL_TEXTURE_2D, glID);


    glTexImage2D(GL_TEXTURE_2D, 0, 4, gl_fliped_surface->w,
                 gl_fliped_surface->h, 0, GL_RGBA,GL_UNSIGNED_BYTE,
                 gl_fliped_surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    return glID;
}

SDL_Surface * CEGDD_UI_flipSurface(SDL_Surface * surface)
{
    int current_line,pitch;
    SDL_Surface * fliped_surface = SDL_CreateRGBSurface(SDL_SWSURFACE,
                                   surface->w,surface->h,
                                   surface->format->BitsPerPixel,
                                   surface->format->Rmask,
                                   surface->format->Gmask,
                                   surface->format->Bmask,
                                   surface->format->Amask);



    SDL_LockSurface(surface);
    SDL_LockSurface(fliped_surface);

    pitch = surface->pitch;
    for (current_line = 0; current_line < surface->h; current_line ++)
    {
        memcpy(&((unsigned char* )fliped_surface->pixels)[current_line*pitch],
               &((unsigned char* )surface->pixels)[(surface->h - 1  -
                                                    current_line)*pitch],
               pitch);
    }

    SDL_UnlockSurface(fliped_surface);
    SDL_UnlockSurface(surface);
    return fliped_surface;
}

void CEGDD_UI_draw_pict(struct pict *image)
{
    glBindTexture(GL_TEXTURE_2D, image->texture);
    glBegin(GL_QUADS);
        glTexCoord2d(0,0);          glVertex2d(image->pos.x,image->pos.y);
        glTexCoord2d(0,1);          glVertex2d(image->pos.x,image->pos.y+image->pos.h);
        glTexCoord2d(1,1);          glVertex2d(image->pos.x+image->pos.w,image->pos.y+image->pos.h);
        glTexCoord2d(1,0);          glVertex2d(image->pos.x+image->pos.w,image->pos.y);
    glEnd();
}

GLuint CEGDD_UI_imprime (char s[], int len, SDL_Color *couleur, TTF_Font *police, int *LenghtReturn, int *HighReturn)
{
    if(s[0] == '\0')
	{
		printf ("try to print an empty string\n");
		return -1;
	}
	else if(police == NULL)
	{
		printf ("try to print with an unloaded font\n");
		return -1;
	}
	else if(couleur == NULL)
	{
		printf ("try to print without any color\n");
		return -1;
	}
	else
    {
		SDL_Surface *SurfTemp = NULL;

		SurfTemp = TTF_RenderText_Blended_Wrapped(police, (const char *)s, *couleur, len);

		if (LenghtReturn != NULL)
		{
			*LenghtReturn = SurfTemp->w;
		}
		if (HighReturn != NULL)
		{
			*HighReturn = SurfTemp->h;
		}
		return CEGDD_UI_convertTexture(SurfTemp);
    }
}

void CEGDD_UI_setColor(SDL_Color *couleur, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	couleur->r = r;
	couleur->g = g;
	couleur->b = b;
	couleur->a = a;
}

void CEGDD_UI_draw_hookpict(struct hookpict *image, SDL_Rect *support)
{
    image->pict.pos.x = support->x + image->translation.x;
    image->pict.pos.y = support->y + image->translation.y;

    glBindTexture(GL_TEXTURE_2D, image->pict.texture);
    glBegin(GL_QUADS);
        glTexCoord2d(0,0);          glVertex2d(image->pict.pos.x,image->pict.pos.y);
        glTexCoord2d(0,1);          glVertex2d(image->pict.pos.x,image->pict.pos.y+image->pict.pos.h);
        glTexCoord2d(1,1);          glVertex2d(image->pict.pos.x+image->pict.pos.w,image->pict.pos.y+image->pict.pos.h);
        glTexCoord2d(1,0);          glVertex2d(image->pict.pos.x+image->pict.pos.w,image->pict.pos.y);
    glEnd();
}

void CEGDD_UI_draw(GLuint texture, SDL_Rect *pos)
{
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);
        glTexCoord2d(0,0);          glVertex2d(pos->x,pos->y);
        glTexCoord2d(0,1);          glVertex2d(pos->x,pos->y+pos->h);
        glTexCoord2d(1,1);          glVertex2d(pos->x+pos->w,pos->y+pos->h);
        glTexCoord2d(1,0);          glVertex2d(pos->x+pos->w,pos->y);
    glEnd();
}

void CEGDD_UI_Turn_And_Draw (struct pict *img, float angle)
{
    SDL_Point temp;
    temp.x = img->pos.x;
    temp.y = img->pos.y;

    img->pos.x = 0 - (img->pos.w/2);
    img->pos.y = 0 - (img->pos.h/2);

	glTranslatef(temp.x+(img->pos.w/2), temp.y+(img->pos.h/2), 0);
	glRotatef(angle, 0, 0 ,1);

	CEGDD_UI_draw_pict(img);

	img->pos.x = temp.x;
	img->pos.y = temp.y;

    glLoadIdentity();
}

void CEGDD_UI_turn_draw_hookpict(int angle, struct hookpict *image, SDL_Rect *support)
{
    glPushMatrix();

    image->pict.pos.x = support->x + image->translation.x;
    image->pict.pos.y = support->y + image->translation.y;

    CEGDD_UI_Turn_And_Draw(&image->pict, angle);

    glPopMatrix();
}

void CEGDD_UI_Sync_Moving_Pict(int time, struct moving_pict *m_pict)
{
    if (time - m_pict->time >= m_pict->delay)
    {
        m_pict->time = time;
        m_pict->current++;
        if(m_pict->current >= m_pict->frame)
        {
            m_pict->current = 0;
        }
        m_pict->pict.texture = m_pict->texture[m_pict->current];
    }
}

void CEGDD_UI_draw_button(struct BOUTON *bouton)
{
    glBindTexture(GL_TEXTURE_2D, bouton->texture);
    switch(bouton->etat)
    {
        case B_IMPOSSIBLE:
            glColor3ub(255, 0, 0);
            break;
        case B_SURVOLER:
            glColor3ub(150, 150, 255);
            break;
        case B_INUSE:
        case B_CLIQUER:
            glColor3ub(0, 0, 255);
            break;
        default:
            glColor3ub(255, 255, 255);
            break;
    }
    glBegin(GL_QUADS);
        glTexCoord2d(0,0);          glVertex2d(bouton->pos.x,bouton->pos.y);
        glTexCoord2d(0,1);          glVertex2d(bouton->pos.x,bouton->pos.y+bouton->pos.h);
        glTexCoord2d(1,1);          glVertex2d(bouton->pos.x+bouton->pos.w,bouton->pos.y+bouton->pos.h);
        glTexCoord2d(1,0);          glVertex2d(bouton->pos.x+bouton->pos.w,bouton->pos.y);
    glEnd();

    glColor3ub(255, 255, 255);
}

void CEGDD_UI_draw_color_black(SDL_Rect *pos)
{
    glColor3ub(0, 0, 0);
        glBegin(GL_QUADS);
            glVertex2d(pos->x,pos->y);
            glVertex2d(pos->x,pos->y+pos->h);
            glVertex2d(pos->x+pos->w,pos->y+pos->h);
            glVertex2d(pos->x+pos->w,pos->y);
        glEnd();
    glColor3ub(255, 255, 255);
}

void CEGDD_UI_creerbouton(char *path, int x, int y, int w, int h, int state, int flag, struct BOUTON *liste_bouton, int *Qtt_bouton)
{
    liste_bouton[*Qtt_bouton].etat = state;
    liste_bouton[*Qtt_bouton].flag = flag;
    CEGDD_UI_setPos4(&liste_bouton[*Qtt_bouton].pos, x, y, w, h);
    liste_bouton[*Qtt_bouton].texture = CEGDD_UI_loadTexture (path);
    if (glIsTexture(liste_bouton[*Qtt_bouton].texture) == GL_FALSE)
    {
        printf("texture not loaded\n");
    }

    *Qtt_bouton += 1;
}

void CEGDD_UI_creerboutontexte(char *path, int x, int y, int state, int flag, struct BOUTON *liste_bouton, int *Qtt_bouton, SDL_Color *couleur, TTF_Font *police)
{
    liste_bouton[*Qtt_bouton].etat = state;
    liste_bouton[*Qtt_bouton].flag = flag;
    liste_bouton[*Qtt_bouton].texture = CEGDD_UI_imprime(path, 9999, couleur, police, &liste_bouton[*Qtt_bouton].pos.w, &liste_bouton[*Qtt_bouton].pos.h);//9999 len max

    CEGDD_UI_setPos2rect(&liste_bouton[*Qtt_bouton].pos, x, y);

    if (glIsTexture(liste_bouton[*Qtt_bouton].texture) == GL_FALSE)
    {
        printf("texture not loaded\n");
    }

    *Qtt_bouton += 1;
}

void CEGDD_UI_creertexte(char *path, int x, int y, struct TEXTE *liste_texte, int *Qtt_texte, SDL_Color *couleur, TTF_Font *police)
{
    liste_texte[*Qtt_texte].img.texture = CEGDD_UI_imprime(path, 9999, couleur, police, &liste_texte[*Qtt_texte].img.pos.w, &liste_texte[*Qtt_texte].img.pos.h);

    CEGDD_UI_setPos2rect(&liste_texte[*Qtt_texte].img.pos, x, y);

    if (glIsTexture(liste_texte[*Qtt_texte].img.texture) == GL_FALSE)
    {
        printf("texture of texte n: %d not loaded\n", *Qtt_texte);
    }

    *Qtt_texte +=1;
}


void CEGDD_UI_setboutontexte(char *buffer, int index, struct BOUTON *liste_bouton, SDL_Color *couleur, TTF_Font *police)
{
    liste_bouton[index].texture = CEGDD_UI_imprime(buffer, 9999, couleur, police, &liste_bouton[index].pos.w, &liste_bouton[index].pos.h);

}

void CEGDD_UI_setboutonnombre(int nombre, int index, struct BOUTON *liste_bouton, SDL_Color *couleur, TTF_Font *police)
{
    char buffer[32];
    sprintf(buffer, "%d", nombre);
    liste_bouton[index].texture = CEGDD_UI_imprime(buffer, 9999, couleur, police, &liste_bouton[index].pos.w, &liste_bouton[index].pos.h);

}

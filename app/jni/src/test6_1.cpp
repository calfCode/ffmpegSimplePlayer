//
// Created by Lenovo on 2024/7/15.
//
# include "SDL.h"
#include <string>
#include <unistd.h>
#include "SDL_ttf.h"
#include "../util/alog.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class LTexture
{
public:
    //Initializes variables
    LTexture();

    //Deallocates memory
    ~LTexture();

    //Loads image at specified path
    bool loadFromFile( std::string path );

    //Deallocates texture
    void free();

    //Set color modulation
    void setColor( Uint8 red, Uint8 green, Uint8 blue );

    //Set blending
    void setBlendMode( SDL_BlendMode blending );

    //Set alpha modulation
    void setAlpha( Uint8 alpha );

    //Renders texture at given point
    void render( int x, int y, SDL_Rect* clip = NULL );

    //Gets image dimensions
    int getWidth();
    int getHeight();

private:
    //The actual hardware texture
    SDL_Texture* mTexture;

    //Image dimensions
    int mWidth;
    int mHeight;
};
LTexture::LTexture()
{
    //Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    //Deallocate
    free();
}
void LTexture::free()
{
    //Free texture if it exists
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
    //Modulate texture rgb
    SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
    //Set blending function
    SDL_SetTextureBlendMode( mTexture, blending );
}

void LTexture::setAlpha( Uint8 alpha )
{
    //Modulate texture alpha
    SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip )
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };

    //Set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    // 渲染纹理到渲染器
//    SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}
typedef struct {
    int type ;
    int status ;
    SDL_Rect rect ;
    LTexture ltexture ;
} UIButton ;
int main ( int argc , char * argv [])
{
    SDL_Window * window ;
    SDL_Renderer * renderer ;
// Initialize SDL .
    if ( SDL_Init ( SDL_INIT_VIDEO ) < 0)
        return 1;

    if(TTF_Init()<0){
        LOGD("TTF_Init fail:%s ",TTF_GetError());
    }
    TTF_Font *font;
    font = TTF_OpenFont("/data/user/0/org.libsdl.app/app_picture/simhei.ttf",28);
    if (font){
        LOGD("TTF_OpenFont ok");
    } else{
        LOGD("TTF_OpenFont fail:%s ",TTF_GetError());
    }
// Create the window where we will draw .
    window = SDL_CreateWindow (" SDL_RenderClear ",
                               SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED ,
                               512 , 512 , 0) ;
// must call SDL_CreateRenderer for draw calls to affect this window .
            renderer = SDL_CreateRenderer ( window , -1 , 0) ;
// Select the color for drawing . It is set to red here .
            SDL_SetRenderDrawColor ( renderer , 255 , 255 , 255 , 255) ;
// Clear the entire screen to our selected color .
    SDL_RenderClear ( renderer ) ;
     // 添 加 绘 制 点 、 直 线 、 矩 形 的 绘 制 代 码


     // 绘制矩形
    SDL_Rect fillRect = { SCREEN_WIDTH *3/4 , SCREEN_HEIGHT /
                                              4, SCREEN_WIDTH / 8 , SCREEN_HEIGHT / 8 };
    SDL_Rect outlineRect = { SCREEN_WIDTH *3/4 ,
                             SCREEN_HEIGHT / 4 , SCREEN_WIDTH /8 , SCREEN_HEIGHT /8
    };
// 绘 制 红 色 填 充 区 域
    SDL_SetRenderDrawColor ( renderer , 0xFF , 0x00 , 0x00 , 0x00 ) ;
    SDL_RenderFillRect ( renderer , & fillRect );

    SDL_SetRenderDrawColor ( renderer , 0x00 , 0xFF , 0x00 , 0xFF ) ;
    int a = fillRect .x+ fillRect .w/2;
    int b = fillRect .y+ fillRect .h +50;
    // 绘制点组成虚线
    for (int i = fillRect .y -50; i < b; i += 4 )
    {
        SDL_RenderDrawPoint ( renderer , a, i );
    }
    // 绘制短线组成虚线
    SDL_SetRenderDrawColor ( renderer , 0x00 , 0x00 , 0xFF , 0xFF ) ;
    for (int  i = fillRect .y -50; i < b; i += 10 )
    {
        SDL_RenderDrawLine ( renderer , a, i, a, i+5) ;
    }



// Up until now everything was drawn behind the scenes .
   SDL_RenderPresent ( renderer );
// Give us time to see the window .
    SDL_Delay (5000) ;
// Always be sure to clean up
    SDL_Quit () ;
    return 0;
}
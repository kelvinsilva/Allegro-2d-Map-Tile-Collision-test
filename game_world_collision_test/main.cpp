//Kelvin Silva
#include <allegro.h>
#include <winalleg.h>

#define WHITE makecol(255,255,255)
#define RED makecol(255, 50, 50)

#define WIDTH 1100
#define HEIGHT 550


bool rectinrect(RECT rectangle1, RECT rectangle2){

    POINT rectangle_top_left{ rectangle1.left, rectangle1.top };
    POINT rectangle_top_right{ rectangle1.right, rectangle1.top };
    POINT rectangle_bot_left{ rectangle1.left, rectangle1.bottom };
    POINT rectangle_bot_right{ rectangle1.right, rectangle1.bottom };

    if(PtInRect(&rectangle2 , rectangle_top_left)){
        return true;
    }else if(PtInRect(&rectangle2, rectangle_top_right)){
        return true;
    }else if(PtInRect(&rectangle2, rectangle_bot_left)){
        return true;
    }else if(PtInRect(&rectangle2, rectangle_bot_right)){
        return true;
    }else return false;


}


int main(){


    allegro_init();
    install_keyboard();
    if(install_sound(DIGI_AUTODETECT, MIDI_NONE, "") != 0){

        allegro_message("error initializing the sound system");
    }


    set_color_depth(16);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1100, 550, 0, 0);



    BITMAP *buffer = create_bitmap(WIDTH, HEIGHT);

    RECT rectangle1{0, 20, 50, 70};
    RECT rectangle2{0, 20, 50, 70};

    while(!key[KEY_ESC]){

        if (key[KEY_UP]){

            rectangle1.top--;
            rectangle1.bottom--;
        }
        if (key[KEY_DOWN]){

            rectangle1.top++;
            rectangle1.bottom++;
        }
        if(key[KEY_LEFT]){

            rectangle1.left--;
            rectangle1.right--;
        }
        if(key[KEY_RIGHT]){

            rectangle1.left++;
            rectangle1.right++;
        }
        if(key[KEY_W]){

            rectangle2.top--;
            rectangle2.bottom--;
        }
        if(key[KEY_S]){

            rectangle2.top++;
            rectangle2.bottom++;
        }
        if(key[KEY_A]){

            rectangle2.left--;
            rectangle2.right--;
        }
        if(key[KEY_D]){

            rectangle2.left++;
            rectangle2.right++;
        }


        if (rectinrect(rectangle1, rectangle2)){
            textprintf_ex(buffer, font, 0, 20, WHITE, 0, "Rectangles are touching");

        }else textprintf_ex(buffer, font, 0, 20, WHITE, 0, "Rectangles are not touching ");

        rect(buffer, rectangle1.left, rectangle1.top, rectangle1.right, rectangle1.bottom, WHITE);
        rect(buffer, rectangle2.left, rectangle2.top, rectangle2.right, rectangle2.bottom, WHITE);
        textprintf_ex(buffer, font, 0, 0, WHITE, 0, "Resolution = %ix%i ", SCREEN_W, SCREEN_H);

        blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);
        clear(buffer);

    }


        return 0;

}END_OF_MAIN()

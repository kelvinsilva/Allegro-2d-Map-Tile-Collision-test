//Actorclass .cpp
//Written by Kelvin Silva
#include "Actor_Class.h"
int if_neg_ret_zero(int num){

    //If num less than zero then zero else num
    return (num < 0) ? 0 : num;

}

BITMAP *grabframe(BITMAP *source, int width, int height, int startx, int starty, int columns, int frame){
//By Jonathan S Harbour
//Given BITMAP source, extract bitmap with width and height dimensions at frame frame.
    BITMAP *temp = create_bitmap(width, height);
    int x = startx + (frame % columns) * width;
    int y = starty + (frame / columns) * height;
    blit(source, temp, x, y, 0, 0, width, height);
    return temp;

}


void Actor::move_left(int pixels){

        horz_col_rect_mov_left(pixels);
        xpos -= pixels;

        if (xpos <= 0){
            xpos = 0;
        }

}

void Actor::move_right(int pixels){


        horz_col_rect_mov_right(pixels);
        xpos += pixels;


        if (xpos >= draw_surface->w){
            xpos = draw_surface->w;
        }

}

void Actor::move_up(int pixels){

        vert_col_rect_mov_up(pixels);
        ypos -= pixels;

        if (ypos <= 0){
            ypos = 0;
        }

}

void Actor::move_down(int pixels){


        vert_col_rect_mov_down(pixels);
        ypos += pixels;

        if (ypos >= draw_surface->h){
            ypos = draw_surface->h;
        }

}

void Actor::set_face(int face){

    facing = face;
}

void Actor::set_col_rect(int x1, int y1, int x2, int y2){
    colision_rect.left = x1;
    colision_rect.top = y1;
    colision_rect.right = x2;
    colision_rect.bottom = y2;
}

void Actor::vert_col_rect_mov_up(int units){

    if(!(ypos <= 0)){

        colision_rect.top -= units;
        colision_rect.bottom -= units;

        colision_rect.top = if_neg_ret_zero(colision_rect.top);
        colision_rect.bottom = if_neg_ret_zero(colision_rect.bottom);

    }

}

void Actor::vert_col_rect_mov_down(int units){

    if(!(ypos >= draw_surface->h)){
        colision_rect.top += units;
        colision_rect.bottom += units;

    }
}

void Actor::horz_col_rect_mov_left(int units){

    if(!(xpos <= 0)){
        colision_rect.right -= units;
        colision_rect.left -= units;

        colision_rect.right = if_neg_ret_zero(colision_rect.right);
        colision_rect.left = if_neg_ret_zero(colision_rect.left);
    }

}

void Actor::horz_col_rect_mov_right(int units){

    if(!(xpos >= draw_surface->w)){
        colision_rect.right += units;
        colision_rect.left += units;
    }

}


void Actor::display(int frame){

    BITMAP *drawsf= grabframe(actor_frames, frame_width, frame_height, 0, 0, columns, frame);
    if(facing == 0){
        draw_sprite(draw_surface, drawsf, xpos, ypos);
    }else draw_sprite_h_flip(draw_surface, drawsf, xpos, ypos);
}

int Actor::getxpos(){
    return xpos;
}

int Actor::getypos(){
    return ypos;
}

RECT Actor::getrect(){
    return colision_rect;
}

int Actor::getfacing(){
    return facing;
}

//Given position new x, new y, transform old x and old y values to match new x and new y values.
//From old x and old y values, we subtract the corresponding values new x and new y to obtain distance
//Then move left/up/down/right accordingly
//It is all relative from current position to new x and new y position.
void Actor::update_position(int x, int y){


    if(this->getxpos() >= x){
        int xxpos = this->getxpos() - x;
        this->move_left(xxpos);
    }
    if (this->getxpos() <= x){
        int xxpos =  x - this->getxpos();
        this->move_right(xxpos);

    }
    if(this->getypos() <= y){
        int yypos =  y - this->getypos();
        this->move_down(yypos);
    }
    if(this->getypos() >= y){
        int yypos = this->getypos() - y;
        this->move_up(yypos);

    }
}

//Actor::Actor(BITMAP *drawsurface, int xpos, int ypos, int facing, BITMAP *actorframes, int framewidth, int frameheight, int col)
//int col parameter  refers to the amount of columns in your spritesheet or if your bitmap has multiple frames in 1 bitmap

Actor::Actor(BITMAP *draw, int xpos, int ypos, int fac, BITMAP *actorfr, int frw, int frh, int col){

    draw_surface = draw;
    this->xpos = xpos;
    this->ypos = ypos;
    facing = fac;
    actor_frames = actorfr;
    frame_width = frw;
    frame_height = frh;
    columns = col;
    ZeroMemory(&colision_rect, sizeof(colision_rect));

    /*Example of Using Actor Class constructor....
    // __________________________________________________________________
    //|----->>>>Actor Class Constructor Description<<<<-----------------|
    //|1. Draw Destination  | 2. Start X Position                       |
    //|3. Start Y Position  | 4. Frame is flipped (facing)              |
    //|5. Ptr to bitmap art | 6. Width of each frame on sprite sheet    |
    //|7. H of frame sprite | 8. Total number of frames on sprite sheet |
    //|------------------------------------------------------------------
    //           1.      2.  3.  4.  5.  6. 7.  8.
    //           |       |   |   |   |   |  |   |
    //           V       V   V   V   V   V  V   V
    Actor thing(buffer, 50, 50, 0, guy, 50, 64, 8);
    */

}




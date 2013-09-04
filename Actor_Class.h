//Actor class
//Written By Kelvin Silva
//A simple class to define any actor on screen
//Do not instantiate this class with new

#ifndef ACTOR_CLASS_H_
#define ACTOR_CLASS_H_

#include <allegro.h>
#include <winalleg.h>


class Actor{

private:

    BITMAP *draw_surface; //Draw to screen or buffer? The destination of all drawing routines are this variable
    BITMAP *actor_frames; //Bitmap of actor. If the actor has multiple frames in 1 bitmap, check the grabframe function

    int xpos, ypos;
    RECT colision_rect;
    int facing;


    int frame_width, frame_height, columns; //If the actor has multiple frames defined in 1 bitmap, these parameters are required

    void vert_col_rect_mov_up(int); //Move the collision rectangles as the position is updated.
    void vert_col_rect_mov_down(int);
    void horz_col_rect_mov_left(int);
    void horz_col_rect_mov_right(int);

    friend int if_neg_ret_zero(int num); //Return zero if a number is negative.

    friend BITMAP *grabframe(BITMAP *source, int width, int height,     //Obtain a certain area of a bitmap function written By johnathan S. Harbour
                             int startx, int starty, int columns,
                             int frame);
public:

//Actor::Actor(BITMAP *drawsurface, int xpos, int ypos, int facing, BITMAP *actorframes, int framewidth, int frameheight, int col)
//int col parameter  refers to the amount of columns in your spritesheet or if your bitmap has multiple frames in 1 bitmap
    Actor(BITMAP*, int, int, int, BITMAP*, int, int, int);


//In actual game code, we will not directly use the move_ functions
//I included them for purposes of playing around/testing arrow keys
//Check update_position method for a better insight
    void move_left(int);
    void move_right(int);
    void move_up(int);
    void move_down(int);

//Flip the sprite
    void set_face(int);

    void set_col_rect(int, int, int, int);

    void display(int); //draw surface, which frame, xpos, ypos

    int getxpos(); //Useful note, xpos and ypos is top left corner of the sprite or rectangle
    int getypos();

    void update_position(int, int);


    RECT getrect(); //Return collision rectangle coordinates
    int getfacing(); //Return if it is "facing" or not. The usefulness of this function is questionable

};
#endif // ACTOR_CLASS_H_

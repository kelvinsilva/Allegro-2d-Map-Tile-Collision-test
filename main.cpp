//Kelvin Silva --> Sept 3 2013
//A simple testing sample for Actor class and how to implement such class in an allegro 2d environment.
//The collision detection isnt perfect and needs some tweaking but for the most part it works for small sized rectangles
#include "Actor_Class.h"
#include <mappyal.h>
#define WIDTH 1000
#define HEIGHT 350
#define MODE GFX_AUTODETECT_WINDOWED
#define WHITE makecol(255, 255, 255)


struct Colision_Result{

    bool left, right, top, bot;

    RECT rectangle_coords;

    int length_col_rect;
    int width_col_rect;

};

Colision_Result FG_COLISSION(RECT rcte, int xoff, int yoff, float yoffx){

/*This Function is to be used with the Collision_Results structure*/
/*Use this function only to check collision with mappy foreground tiles*/
/*A different function will be used for actual game environment object collision detection*/
/*Note that this only works for blocks of 24x24 pixels*/
/*Change '24' to the desired setting*/

/*NOTE! If you wish to use a big rectangle, implement a for loop to check a
collision rectangle that has bigger width or height than the height or width of each map tile

**** test_top = WIDTH_OR_HEIGH_OF_TILE / WIDTH_OR_HEIGHT_OF_COLLISION_RECTANGLE
Implement for loop yet to be added
*/

    RECT rct;

    BLKSTR *blockdata;  //Instantiate a mappy blkstructure pointer
    Colision_Result results{false, false, false, false, rct,0, 0};   //Set the collision results structure as if nothing has collided

/* *******************************************
Assign rectangle values + the offset of the map.
This is so we can get the real position of the
rectangle on the map instead of it merely on the viewing screen
*****************************************************/
    rct.top = rcte.top + yoff;
    rct.bottom = rcte.bottom + yoff;
    rct.left = rcte.left + xoff;
    rct.right = rcte.right + xoff;


    int width = rcte.right-rcte.left;
    int length = rcte.bottom - rcte.top;
    results.length_col_rect = length;
    results.width_col_rect = width;

/*The work flows as follows:
1. Obtain a certain tile from the map at X,Y coordinates
2. If a certain flag is checked along the X,Y coordinates of the rect structure passed, then we have a collision
3. Set the corresponding colision_results flags to true
*/

        //As the block approaches the top left from left side
        blockdata = MapGetBlockInPixels((int)rct.left+5, (int)rct.top);
        if(blockdata->bl || blockdata->br){
            results.top = true;
        }

        //As block approaches the top right from right side
        blockdata = MapGetBlockInPixels(rct.right-5, (int)rct.top);
        if(blockdata->bl || blockdata->br){
            results.top = true;

        }

        //As tile approaches bottom from left side going left
        blockdata = MapGetBlockInPixels((int)rct.right-5 , (int)rct.bottom) ;
        if(blockdata->tl || blockdata->tr){
                results.bot = true;
        }

        //As tile approache bottom from right going right
        blockdata = MapGetBlockInPixels((int)rct.left+5, (int)rct.bottom) ;
        if(blockdata->tl || blockdata->tr){
                results.bot = true;
        }

        //check bottom middle
        blockdata = MapGetBlockInPixels((int)rct.left+(width/2) , (int)rct.bottom) ;
        if(blockdata->tl || blockdata->tr){
                results.bot = true;
        }

        //As tile approaches left side going down
        blockdata = MapGetBlockInPixels((int)rct.left, (int)rct.top+10);
        if(blockdata->tl || blockdata->bl){
            results.left = true;
        }
        //As tile approaches left side going up
        blockdata = MapGetBlockInPixels((int)rct.left, rct.bottom-10) ;
        if(blockdata->tl || blockdata->bl){
                results.left = true;
        }
        //As tile approaches right side going up
        blockdata = MapGetBlockInPixels((int)rct.right, (int)rct.bottom-10) ;
        if(blockdata->tr || blockdata->br){
                results.right = true;
        }

        blockdata = MapGetBlockInPixels(rct.right, (int)rct.top+10);
        if(blockdata->tr || blockdata->br){
            results.right = true;
        }

    return results;
}
//int jump = 0;
int xoff = 0;
int yoff = 0;

int main(){

    allegro_init();
    install_timer();
    install_keyboard();
    set_color_depth(16);
    set_gfx_mode(MODE, WIDTH, HEIGHT, 0, 0);

    BITMAP *buffer = create_bitmap(WIDTH, HEIGHT);
    BITMAP *guy = load_bitmap("guy.bmp", NULL);


    //__________________________________________________________________
    //----->>>>Actor Class Constructor Description<<<<-----------------|
    //1. Draw Destination  | 2. Start X Position                       |
    //3. Start Y Position  | 4. Frame is flipped (facing)              |
    //5. Ptr to bitmap art | 6. Width of each frame on sprite sheet    |
    //7. H of frame sprite | 8. Total number of frames on sprite sheet |
    //------------------------------------------------------------------
    //           1.      2.  3.  4.  5.  6. 7.  8.
    //           |       |   |   |   |   |  |   |
    //           V       V   V   V   V   V  V   V
    Actor thing(buffer, 50, 50, 0, guy, 50, 64, 8);

    thing.set_col_rect(60, 59, 80, 100);

    //temp = load_bitmap("guy.bmp", NULL);
    MapLoad("map2.fmp");
    int framect = 0;

    RECT rectangle;
    float dx = 0 , dy = 0;
    int x = 50, y = 50; //Starting position of character

    bool jumpstate = false;
    int gravity = 3;
    int x_acceleration = 1;


    while(!key[KEY_ESC]){ //Quit if KEY_ESC == true


//The first step is to retrieve input from the user
        if(key[KEY_SPACE] && !jumpstate){
            dy = -35;  //If space is pressed, destination is to -35 pixels
            jumpstate = true;
        }
        if(key[KEY_LEFT]){
            dx -= x_acceleration;
            framect++; //As the user is pressing left or right keys we update the framecount for walking animation
        }
        if(key[KEY_RIGHT]){
            dx += x_acceleration;
            framect--;
        }

//Then we apply the input from user into the actor or thing we want to move
    dy*=.9; //As we multiply by .9 the number gets smaller and smaller hence simulating friction or gravity
    dx*=.9;
    x += dx; //Apply destination
    y += dy;

    //Insert data into the object
    thing.update_position(x, y);


    //Retrieve our collision rectangle
    rectangle = thing.getrect();
    //Obtain results
    //If the input from the user will be checked for collisions.
    Colision_Result results = FG_COLISSION(rectangle, xoff, yoff, 0);

    /*If the input from the user trips any of the flags then we must readjust
      the dx, dy, x, and y variables to satisfy game restrictions*/
    if(results.left){
        x += x_acceleration+1; //Add 1 so we actually dont permanently stick to the wall
    //cout << "\nresults: " << dx;
        dx = 0;
    }

    if(results.right){
        x -= x_acceleration;  //Add 1 so we actually dont permanently stick to the wall
        dx = 0;
    }

    if(results.top){

        dy = 0;
    }

    if(results.bot){ //If bottom collision happens

        if(!jumpstate){ //stop acceleration if you are not jumping
            y -= dy; //If you find that the collision rectangle goes inside map tile, uncomment this line.
            dy = 0;
        }else{
            y-= dy;
            dy = 0;
        }
        jumpstate = false;

    }else{          //Apply gravity
        dy+=gravity;
        dy*= .9;
    }

    //Once the game restrictions have been applied to user input, readjust the position of game actor.
    thing.update_position(x, y);
    rectangle = thing.getrect();

    //If the framecount counter exceeds or deceeds number of frames(going negative), keep it within bounds
    //Use for walking animations, etc....
        if (framect > 8)
            framect = 0;
        if (framect < 0)
            framect = 8;



    clear(screen);

    xoff =  thing.getxpos();
    yoff = thing.getypos();

    //The map scrolls as the character moves around.

    /*If the scrolling variable is bigger than the actual
    width of the map in pixels minus width of the screen, then we keep it within bounds.*/

    if(xoff >= (mapwidth*mapblockwidth-WIDTH)){
        xoff =  (mapwidth*mapblockwidth-WIDTH);
    }
    if(xoff < 0){
        xoff = 0;
    }

    if(yoff >= (mapheight*mapblockheight-HEIGHT)){
        yoff = mapheight*mapblockheight-HEIGHT;
    }
    if(yoff < 0){
        yoff = 0;
    }

           //Draw BG background and FG foreground
            MapDrawBG(buffer, xoff, yoff, 0, 0, WIDTH-1, HEIGHT-1);
            MapDrawFG(buffer, xoff, yoff, 0, 0, WIDTH-1, HEIGHT-1, 0);

            //Draw object and collision rectangle
            thing.display(framect);
            rect(buffer, rectangle.left, rectangle.top, rectangle.right, rectangle.bottom, WHITE);

            //Copy buffer to screen
            blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);

            //The rest was personal preference. I wanted to limit the framerate below my Monitor's refresh rate.
        rest(15);
        vsync();
    }

    return 0;
}
END_OF_MAIN()   //Allegro specific

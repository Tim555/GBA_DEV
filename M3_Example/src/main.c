#include "toolbox.h"
#include "render3d.h"

void vid_vsync()
{
    while(REG_VCOUNT >= 160);   // wait till VDraw
    while(REG_VCOUNT < 160);    // wait till VBlank
}

void draw_square(){
    struct point3d eye_point = create_point3d(-100, -20, -20);
    struct sqr s = create_sqr();
    struct sqr s_temp;
    float r, theta, phi;
    struct matrix m_rot, m_eye;
    int ii;

    to_polar(eye_point, &r, &phi, &theta);

    m_eye = create_eyepoint_matrix(phi, theta);
    m_rot = create_rotz_matrix(0.01);

    struct sqr_2d to_draw;

    s_temp = s;
    //eye point transformation
    transform(&s_temp, m_eye);
    translate(&s_temp, create_point3d(0, 0, -r));
    //project to 2d image
    to_draw = flatten(s_temp);
    center(&to_draw);
    for(ii=0; ii < 12; ++ii){
        m3_line(to_draw.lines[ii].from.x, to_draw.lines[ii].from.y, to_draw.lines[ii].to.x, to_draw.lines[ii].to.y, CLR_LIME);
    }

}

int main(){
    int ii, jj;
    REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;

    // Create objects.
    struct point3d eye_point = create_point3d(-100, -20, -20);
    struct sqr s = create_sqr();
    struct sqr s_temp;
    struct sqr_2d to_draw;
    float r, theta, phi;
    struct matrix m_rot, m_eye;

    // initialize rotation matrices.
    to_polar(eye_point, &r, &phi, &theta);
    m_eye = create_eyepoint_matrix(phi, theta);
    m_rot = create_rotz_matrix(0.1);

    float angle = 0;
    float angle_u = 0.1;

    m3_fill(CLR_BLACK);

    while(1){
        //m_rot = create_rotz_matrix(angle);
        //angle += angle_u;
        transform(&s, m_rot);


        m3_fill(CLR_BLACK);
        s_temp = s;
        //eye point transformation
        transform(&s_temp, m_eye);
        translate(&s_temp, create_point3d(0, 0, -r));
        //project to 2d image
        to_draw = flatten(s_temp);
        center(&to_draw);
        for(ii=0; ii < 12; ++ii){
            m3_line(to_draw.lines[ii].from.x, to_draw.lines[ii].from.y, to_draw.lines[ii].to.x, to_draw.lines[ii].to.y, CLR_LIME);
        }

        //vid_vsync();
    }
}


/*int main() {

    int ii, jj;
    REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;

    struct point3d eye_point = create_point3d(100, 0, 0);
    struct sqr s = create_sqr();
    struct sqr s_temp;
    float r, theta, phi;
    struct matrix m_rot, m_eye;

    to_polar(eye_point, &r, &phi, &theta);

    m_eye = create_eyepoint_matrix(phi, theta);
    m_rot = create_rotz_matrix(0.01);

    struct sqr_2d to_draw;


   // transform(&s, m);
   // translate(&s, create_point3d(0, 0, -r));

   // struct sqr_2d to_draw = flatten(s);
   // center(&to_draw);

    m3_fill(RGB15(12, 12 ,14));




    while(1){
        m3_fill(RGB15(12, 12 ,14));
        //transform original 3d object.
        transform(&s, m_rot);

        //copy square into working square.
        s_temp = s;
        //eye point transformation
        transform(&s_temp, m_eye);
        translate(&s_temp, create_point3d(0, 0, -r));
        //project to 2d image
        to_draw = flatten(s_temp);
        center(&to_draw);
        for(ii=0; ii < 12; ++ii){
            m3_line(to_draw.lines[ii].from.x, to_draw.lines[ii].from.y, to_draw.lines[ii].to.x, to_draw.lines[ii].to.y, CLR_RED);
        }

    }
    return 0;

}



/*
    m3_fill(RGB15(12, 12 ,14));

    m3_plot( 120, 80, RGB15(31, 0, 0) );    // or CLR_RED
    m3_plot( 136, 80, RGB15( 0,31, 0) );    // or CLR_LIME
    m3_plot( 120, 96, RGB15( 0, 0,31) );    // or CLR_BLUE

    // Fill screen with grey color
    m3_fill(RGB15(12, 12, 14));

    // Rectangles:
    m3_rect( 12,  8, 108,  72, CLR_RED);
    m3_rect(108, 72, 132,  88, CLR_LIME);
    m3_rect(132, 88, 228, 152, CLR_BLUE);

    // Rectangle frames
    m3_frame(132,  8, 228,  72, CLR_CYAN);
    m3_frame(109, 73, 131,  87, CLR_BLACK);
    m3_frame( 12, 88, 108, 152, CLR_YELLOW);

    // Lines in top right frame
    for(ii=0; ii<=8; ii++)
    {
        jj= 3*ii+7;
        m3_line(132+11*ii, 9, 226, 12+7*ii, RGB15(jj, 0, jj));
        m3_line(226-11*ii,70, 133, 69-7*ii, RGB15(jj, 0, jj));
    }

    // Lines in bottom left frame
    for(ii=0; ii<=8; ii++)
    {
        jj= 3*ii+7;
        m3_line(15+11*ii, 88, 104-11*ii, 150, RGB15(0, jj, jj));
    }


    while(1);

	return 0;
}
*/
#include <stdlib.h>
#include <GL/glut.h>
#include<time.h>
#include <math.h>
#include <GL/glut.h>
#include<stdio.h>

typedef struct 
{
    GLfloat TR_X ;
    GLfloat TR_Y ;
    GLfloat RT ;
}Transformacija;


/*struktura koja cuva transformacije koje su primenjene da bi se nacrtala slika*/
typedef struct
{
    GLfloat slika_TX;
    GLfloat slika_TY;
    GLfloat slika_R;
}Slika;


Transformacija *koordinate;
Slika *tacke;

/*parametri koji fiksiraju element kad je na dobrom mestu*/
static int na_dobrom_mestu_V1;
static int na_dobrom_mestu_V2;
static int na_dobrom_mestu_M1;
static int na_dobrom_mestu_M2;
static int na_dobrom_mestu_K;
static int na_dobrom_mestu_P;
static int na_dobrom_mestu_T;



static float rotation_parameter= 0;
static float translaton_parameter_X = 0;
static float translaton_parameter_Y = 0;

void draw_axes(float len) {
    glDisable(GL_LIGHTING);

    glBegin(GL_LINES);
        glColor3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(len,0,0);

        glColor3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,len,0);

        glColor3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,len);
    glEnd();

    glEnable(GL_LIGHTING);
}



   
void VELIKI_TROUGAO1()
{
	glPushMatrix();
            glColor3f(0, 0.2, 0);
            
            glBegin(GL_POLYGON);
                glVertex3f(0, 0, 0);
                glVertex3f(0.5, 0, 0);
                glVertex3f(0, 0.5, 0);
            glEnd();
    glPopMatrix();
    
}

void VELIKI_TROUGAO2()
{
	glPushMatrix();
            glColor3f(0.1, 0.1, 0.41);
            glBegin(GL_POLYGON);
                glVertex3f(0, 0, 0);
                glVertex3f(0.5, 0, 0);
                glVertex3f(0, 0.5, 0);
            glEnd();
    glPopMatrix();
}

void MALI_TROUGAO1()
{
	glPushMatrix();
            glColor3f(0.8, 0.2, 0.8);
            glBegin(GL_POLYGON);
                glVertex3f(0, 0, 0);
                glVertex3f(0, 0.25, 0);
                glVertex3f(0.25, 0, 0);
            glEnd();
    glPopMatrix();
}


void MALI_TROUGAO2()
{
	glPushMatrix();
            glColor3f(0, 0, 0.7);
            glBegin(GL_POLYGON);
                glVertex3f(0, 0, 0);
                glVertex3f(0, 0.25, 0);
                glVertex3f(0.25, 0, 0);
            glEnd();
    glPopMatrix();
}


void KVADRAT()
{
	glPushMatrix();
            glColor3f(0.25, 0.47, 0.8);
            glBegin(GL_POLYGON);
                glVertex3f(0, 0, 0);
                glVertex3f(0, 0.25, 0);
                glVertex3f(0.25,0.25,0);
                glVertex3f(0.25, 0, 0);
            glEnd();
    glPopMatrix();
}

void PARALELOGRA()
{
	glPushMatrix();
            glColor3f(0.8, 1, 0.8);
            glBegin(GL_POLYGON);
                glVertex3f(0.25, 0, 0);
                glVertex3f(0.5, 0, 0);
                glVertex3f(0.25, 0.25, 0);
                glVertex3f(0, 0.25, 0);
            glEnd();
    glPopMatrix();
}

void SREDNJI_TROUGAO()
{
	glPushMatrix();
            glColor3f(0, 0.25, 0.8);
            glBegin(GL_POLYGON);
                glVertex3f(0, 0, 0);
                glVertex3f(0.5, 0, 0);
                glVertex3f(0.25, 0.25, 0);
            glEnd();
    glPopMatrix();
}




#define TIMER_ID 1
#define TIMER_INTERVAL 20

float animation_parameter;
int animation_ongoing;
static int id;
static int ID;
/* Deklaracije callback funkcija. */
static void on_keyboard2(unsigned char key, int x, int y);
static void on_reshape2(int width, int height);
static void on_display2(void);
static void on_timer2(int id);

static void init_lights2();

/*/kako se krecu elementi od kojih se sastavlja*/
void kretanje()
{    
    glTranslatef(0+translaton_parameter_X,0+translaton_parameter_Y,0);
    glRotatef(-(0+rotation_parameter), 0, 0, 1);
}

void slika6()
{
    /*VELIKI TROUGAO 1*/ 
    
    glPushMatrix();
            glColor3f(1, 0, 0);
            
            glTranslatef(0.25,0.25,0);
            glRotatef(180,0,0,1);
            
            tacke[1].slika_TX = 0.25;
            tacke[1].slika_TY = 0.25;
            tacke[1].slika_R = 180;
            /*           
            glBegin(GL_POLYGON);
                glVertex3f(0, 0, 0);
                glVertex3f(0.5, 0, 0);
                glVertex3f(0, 0.5, 0);
            glEnd();
            */VELIKI_TROUGAO1();
    glPopMatrix();
    
    
    /*VELIKI TROUGAO 2*/
    glPushMatrix();
            
            glColor3f(1, 0, 0);
            
            glTranslatef(-0.25,-0.25,0);
            
            tacke[2].slika_TX =  -0.25;
            tacke[2].slika_TY = -0.25;
            tacke[2].slika_R = 0;
            
            
            /*
            glBegin(GL_POLYGON);
                glVertex3f(0, 0, 0);
                glVertex3f(0.5, 0, 0);
                glVertex3f(0, 0.5, 0);
            glEnd();*/
            VELIKI_TROUGAO2();
    glPopMatrix();
    
    
    /* MALI TROUGAO 1*/
    glPushMatrix();
            glColor3f(1, 0, 0);
            
            glTranslatef(0.25/2,-0.25,0);
            glRotatef(270,0,0,1);
            
            tacke[3].slika_TX = 0.25/2;
            tacke[3].slika_TY = -0.25;
            tacke[3].slika_R = 270;
            /*glBegin(GL_POLYGON);
                glVertex3f(0, 0, 0);
                glVertex3f(0, 0.25, 0);
                glVertex3f(0.25, 0, 0);
            glEnd();
            */
            MALI_TROUGAO1();
    glPopMatrix();
    
    
    /*MALI TROUGAO 2*/
    glPushMatrix();
            glColor3f(1, 0, 0);
            
            glTranslatef(-0.25/2,-0.25,0);
            glRotatef(180,0,0,1);
            
            tacke[4].slika_TX = -0.25/2;
            tacke[4].slika_TY = -0.25;
            tacke[4].slika_R = 180;
            
            /*
            glBegin(GL_POLYGON);
                glVertex3f(0, 0, 0);
                glVertex3f(0, 0.25, 0);
                glVertex3f(0.25, 0, 0);
            glEnd();
            */
            MALI_TROUGAO2();
    glPopMatrix();
    
    
    /*KVADRAT*/
    glPushMatrix();
            glColor3f(1,0,0);
            
            glTranslatef(-0.25/2,-0.5,0);
            tacke[5].slika_TX = -0.25/2;
            tacke[5].slika_TY = -0.5;
            tacke[5].slika_R = 0;
            /*
            glBegin(GL_POLYGON);
                glVertex3f(0, 0, 0);
                glVertex3f(0, 0.25, 0);
                glVertex3f(0.25,0.25,0);
                glVertex3f(0.25, 0, 0);
            glEnd();*/
            KVADRAT();
    glPopMatrix();
    
    
    /*PARALELOGRAM*/
    glPushMatrix();
            glColor3f(1,0,0);
            
            glTranslatef(0.25,0.6,0);
            glRotatef(135,0,0,1);
            
            tacke[6].slika_TX = 0.25;
            tacke[6].slika_TY = 0.6;
            tacke[6].slika_R = 135;
            
            /*
            glBegin(GL_POLYGON);
                glVertex3f(0.25, 0, 0);
                glVertex3f(0.5, 0, 0);
                glVertex3f(0.25, 0.25, 0);
                glVertex3f(0, 0.25, 0);
            glEnd();
            */
            PARALELOGRA();
    glPopMatrix();
    
    
    /*SEREDNJI TROUGAO*/
    glPushMatrix();
            glColor3f(1, 0, 0);
            
            glTranslatef(-0.25,0.25,0);
            
            tacke[7].slika_TX = -0.25;
            tacke[7].slika_TY = 0.25;
            tacke[7].slika_R = 0;
            
            /*glBegin(GL_POLYGON);
                glVertex3f(0, 0, 0);
                glVertex3f(0.5, 0, 0);
                glVertex3f(0.25, 0.25, 0);
            glEnd();*/
            SREDNJI_TROUGAO();
    glPopMatrix();
}
void slika5()
{
  /*  //VELIKI TROUGAO 1 
    */
    glPushMatrix();
            glColor3f(1, 0, 0);
            
            glTranslatef(0,0.25,0);
            glRotatef(180,0,0,1);
            
            tacke[1].slika_TX = 0;
            tacke[1].slika_TY = 0.25;
            tacke[1].slika_R = 180;
            /*glBegin(GL_POLYGON);
                glVertex3f(0, 0, 0);
                glVertex3f(0.5, 0, 0);
                glVertex3f(0, 0.5, 0);
            glEnd();*/
            VELIKI_TROUGAO1();
    glPopMatrix();
    
    
    /*VELIKI TROUGAO 2
 */   glPushMatrix();
            
            glColor3f(1, 0, 0);
            
            glTranslatef(-0.5,-0.25,0);
            
            tacke[2].slika_TX = -0.5;
            tacke[2].slika_TY = -0.25;
            tacke[2].slika_R = 0;
            
            /*
            glBegin(GL_POLYGON);
                glVertex3f(0, 0, 0);
                glVertex3f(0.5, 0, 0);
                glVertex3f(0, 0.5, 0);
            glEnd();
            */
            VELIKI_TROUGAO2();
    glPopMatrix();
    
    
    /* MALI TROUGAO 1*/
    glPushMatrix();
            glColor3f(1, 0, 0);
            
            glTranslatef(0,-0.25,0);
            
            tacke[3].slika_TX = 0;
            tacke[3].slika_TY = -0.25;
            tacke[3].slika_R = 0;
            /*
            glBegin(GL_POLYGON);
                glVertex3f(0, 0, 0);
                glVertex3f(0, 0.25, 0);
                glVertex3f(0.25, 0, 0);
            glEnd();
            */
            MALI_TROUGAO1();
    glPopMatrix();
    
    
    /*MALI TROUGAO 2*/
    glPushMatrix();
            glColor3f(1, 0, 0);
            
            glTranslatef(0.25,0,0);
            glRotatef(180,0,0,1);
            
            tacke[4].slika_TX = 0.25;
            tacke[4].slika_TY = 0;
            tacke[4].slika_R = 180;
           /* glBegin(GL_POLYGON);
                glVertex3f(0, 0, 0);
                glVertex3f(0, 0.25, 0);
                glVertex3f(0.25, 0, 0);
            glEnd();*/
           MALI_TROUGAO2();
    glPopMatrix();
    
    
    /*kvadrat*/
    glPushMatrix();
            glColor3f(1,0,0);
            tacke[5].slika_TX = 0;
            tacke[5].slika_TY = 0;
            tacke[5].slika_R = 0;
            
            /*
            glBegin(GL_POLYGON);
                glVertex3f(0, 0, 0);
                glVertex3f(0, 0.25, 0);
                glVertex3f(0.25,0.25,0);
                glVertex3f(0.25, 0, 0);
            glEnd();*/
            KVADRAT();
    glPopMatrix();
    
    
    /*PARALELOGRAM*/
    glPushMatrix();
            glColor3f(1, 0, 0);
            
            glTranslatef(-0.25,0.25,0);
            
            tacke[6].slika_TX = -0.25;
            tacke[6].slika_TY = 0.25;
            tacke[6].slika_R = 0;
                 /*      
            glBegin(GL_POLYGON);
                glVertex3f(0.25, 0, 0);
                glVertex3f(0.5, 0, 0);
                glVertex3f(0.25, 0.25, 0);
                glVertex3f(0, 0.25, 0);
            glEnd();*/
                 PARALELOGRA();
    glPopMatrix();
    
    
    /*SEREDNJI TROUGAO*/
    glPushMatrix();
            glColor3f(1, 0, 0);
            
            glTranslatef(-0.5,0.25,0);
            
            tacke[7].slika_TX = -0.5;
            tacke[7].slika_TY = 0.25;
            tacke[7].slika_R = 0;
            /*glBegin(GL_POLYGON);
                glVertex3f(0, 0, 0);
                glVertex3f(0.5, 0, 0);
                glVertex3f(0.25, 0.25, 0);
            glEnd();*/
            SREDNJI_TROUGAO();
    glPopMatrix();
}
void slika4()
{
    /*VELIKI TROUGAO 1*/ 
    
    glPushMatrix();
            glColor3f(1, 0, 0);
            
            glRotatef(90,0,0,1);
            
            tacke[1].slika_TX = 0;
            tacke[1].slika_TY = 0;
            tacke[1].slika_R = 90;
                   /*     
            glBegin(GL_POLYGON);
                glVertex3f(0, 0, 0);
                glVertex3f(0.5, 0, 0);
                glVertex3f(0, 0.5, 0);
            glEnd();*/
            VELIKI_TROUGAO1();
    glPopMatrix();
    
    
    /*VELIKI TROUGAO 2*/
    glPushMatrix();
            
            glColor3f(1, 0, 0);
            
            glRotatef(180,0,0,1);
            
            tacke[2].slika_TX = 0;
            tacke[2].slika_TY = 0;
            tacke[2].slika_R = 180;
            
            /*
            glBegin(GL_POLYGON);
                glVertex3f(0, 0, 0);
                glVertex3f(0.5, 0, 0);
                glVertex3f(0, 0.5, 0);
            glEnd();
            */
            VELIKI_TROUGAO2();
    glPopMatrix();
    
    
    /*// MALI TROUGAO 1*/
    glPushMatrix();
            glColor3f(1, 0, 0);
            
            glTranslatef(0,0.25/2,0);
            tacke[3].slika_TX = 0;
            tacke[3].slika_TY = 0.25;
            tacke[3].slika_R = 0;
            /*
            glBegin(GL_POLYGON);
                glVertex3f(0, 0, 0);
                glVertex3f(0, 0.25, 0);
                glVertex3f(0.25, 0, 0);
            glEnd();
            */
            MALI_TROUGAO1();
    glPopMatrix();
    
    
   /* //MALI TROUGAO 2
   */
   glPushMatrix();
            glColor3f(1, 0, 0);
            
            
            glTranslatef(0,-0.25/2,0);
            glRotatef(270,0,0,1);
            tacke[4].slika_TX = 0;
            tacke[4].slika_TY = -0.25/2;
            tacke[4].slika_R = 270;
            /*
            glBegin(GL_POLYGON);
                glVertex3f(0, 0, 0);
                glVertex3f(0, 0.25, 0);
                glVertex3f(0.25, 0, 0);
            glEnd();*/
            MALI_TROUGAO2();
    glPopMatrix();
    
    
    /*KVADRAT*/
    glPushMatrix();
            glColor3f(1,0,0);
            
            glTranslatef(0,-0.25/2,0);
            tacke[5].slika_TX = 0;
            tacke[5].slika_TY = -0.25/2;
            tacke[5].slika_R = 0;
            /*
            glBegin(GL_POLYGON);
                glVertex3f(0, 0, 0);
                glVertex3f(0, 0.25, 0);
                glVertex3f(0.25,0.25,0);
                glVertex3f(0.25, 0, 0);
            glEnd();*/
            KVADRAT();
    glPopMatrix();
    
    
    /*PARALELOGRAM*/
    glPushMatrix();
            glColor3f(1, 0, 0);
            
            glTranslatef(0.5,-0.25/2,0);
            glRotatef(90,0,0,1);
            
            tacke[6].slika_TX = 0.5;
            tacke[6].slika_TY = -0.25/2;
            tacke[6].slika_R = 90;
            
            
            /*
            glBegin(GL_POLYGON);
                glVertex3f(0.25, 0, 0);
                glVertex3f(0.5, 0, 0);
                glVertex3f(0.25, 0.25, 0);
                glVertex3f(0, 0.25, 0);
            glEnd();*/
            PARALELOGRA();
    glPopMatrix();
    
    
 /*   //SEREDNJI TROUGAO
*/    glPushMatrix();
            glColor3f(1, 0, 0);
            
            glTranslatef(0.5,-0.25-0.25/2,0);
            glRotatef(90,0,0,1);
            
            tacke[7].slika_TX = 0.5;
            tacke[7].slika_TY = -0.25-0.25/2;
            tacke[7].slika_R = 90;
            /*
            glBegin(GL_POLYGON);
                glVertex3f(0, 0, 0);
                glVertex3f(0.5, 0, 0);
                glVertex3f(0.25, 0.25, 0);
            glEnd();*/
            SREDNJI_TROUGAO();
    glPopMatrix();
}
void slika3()
{
  /*VELIKI TROUGAO 1*/ 
    
    glPushMatrix();
            glColor3f(1, 0, 0);
            
            glTranslatef(0,0.5,0);
            glRotatef(180,0,0,1);
            
            tacke[1].slika_TX = 0;
            tacke[1].slika_TY = 0.5;
            tacke[1].slika_R = 180;
                        
            /*glBegin(GL_POLYGON);
                glVertex3f(0, 0, 0);
                glVertex3f(0.5, 0, 0);
                glVertex3f(0, 0.5, 0);
            glEnd();*/
            VELIKI_TROUGAO1();
    glPopMatrix();
    
    
    /*VELIKI TROUGAO 2*/
    glPushMatrix();
            
            glColor3f(1, 0, 0);
            
            tacke[2].slika_TX = 0;
            tacke[2].slika_TY = 0;
            tacke[2].slika_R = 0;
            /*
             glBegin(GL_POLYGON);
                glVertex3f(0, 0, 0);
                glVertex3f(0.5, 0, 0);
                glVertex3f(0, 0.5, 0);
            glEnd();*/
            VELIKI_TROUGAO2();
    glPopMatrix();
    
    
    /* MALI TROUGAO 1*/
    glPushMatrix();
            glColor3f(1, 0, 0);
            
            glTranslatef(-0.5,0.25,0);
            
            tacke[3].slika_TX = -0.5;
            tacke[3].slika_TY = 0.25;
            tacke[3].slika_R = 0;
            /*
            glBegin(GL_POLYGON);
                glVertex3f(0, 0, 0);
                glVertex3f(0, 0.25, 0);
                glVertex3f(0.25, 0, 0);
            glEnd();*/
            MALI_TROUGAO1();
    glPopMatrix();
    
    
    /*/MALI TROUGAO 2*/
    glPushMatrix();
            glColor3f(1, 0, 0);
            
            glTranslatef(0.5,0.35,0);
            glRotatef(315,0,0,1);
            
            tacke[4].slika_TX = 0.5;
            tacke[4].slika_TY = 0.35;
            tacke[4].slika_R = 315;
            /*
            glBegin(GL_POLYGON);
                glVertex3f(0, 0, 0);
                glVertex3f(0, 0.25, 0);
                glVertex3f(0.25, 0, 0);
            glEnd();*/
            MALI_TROUGAO2();
    glPopMatrix();
    
    /*
    //KVADRAT*/
    glPushMatrix();
            glColor3f(1, 0, 0);
            
            glTranslatef(0.5,0,0);
            glRotatef(45,0,0,1);
            
            tacke[5].slika_TX = 0.5;
            tacke[5].slika_TY = 0;
            tacke[5].slika_R = 45;
            /*
            glBegin(GL_POLYGON);
                glVertex3f(0, 0, 0);
                glVertex3f(0, 0.25, 0);
                glVertex3f(0.25,0.25,0);
                glVertex3f(0.25, 0, 0);
            glEnd();*/
            KVADRAT();
    glPopMatrix();
    
    /*
    //PARALELOGRAM*/
    glPushMatrix();
            glColor3f(1, 0, 0);
            
            glTranslatef(-0.5,0,0);
            
            tacke[6].slika_TX = -0.5;
            tacke[6].slika_TY = 0;
            tacke[6].slika_R = 0;
            /*
            glBegin(GL_POLYGON);
                glVertex3f(0.25, 0, 0);
                glVertex3f(0.5, 0, 0);
                glVertex3f(0.25, 0.25, 0);
                glVertex3f(0, 0.25, 0);
            glEnd();*/
            PARALELOGRA();
    glPopMatrix();
    
    /*
    //SEREDNJI TROUGAO*/
    glPushMatrix();
            glColor3f(1, 0, 0);
                        
            glTranslatef(0.5+0.2,0.5+0.25/4-0.01,0);
            glRotatef(180,0,0,1);
            
            tacke[7].slika_TX = 0.5+0.2;
            tacke[7].slika_TY = 0.5+0.25/4-0.01;
            tacke[7].slika_R = 180;
            /*
            glBegin(GL_POLYGON);
                glVertex3f(0, 0, 0);
                glVertex3f(0.5, 0, 0);
                glVertex3f(0.25, 0.25, 0);
            glEnd();*/
            SREDNJI_TROUGAO();
    glPopMatrix();
}
void slika2()
{
  /*   //VELIKI TROUGAO 1 
    */
    glPushMatrix();
            glColor3f(1, 0, 1);
            
            glRotatef(270,0,0,1);
            tacke[1].slika_TX = 0;
            tacke[1].slika_TY = 0;
            tacke[1].slika_R = 270;
            
            /*
            glBegin(GL_POLYGON);
                glVertex3f(0, 0, 0);
                glVertex3f(0.5, 0, 0);
                glVertex3f(0, 0.5, 0);
            glEnd();*/
            VELIKI_TROUGAO1();
    glPopMatrix();
    
    /*
    //VELIKI TROUGAO 2
    */
    glPushMatrix();
            
            glColor3f(1, 0, 1);
            
            glTranslatef(0.5,-0.5,0);
            glRotatef(90,0,0,1);
            
            tacke[2].slika_TX = 0.5;
            tacke[2].slika_TY = -0.5;
            tacke[2].slika_R = 90;
                        
            /*glBegin(GL_POLYGON);
                glVertex3f(0, 0, 0);
                glVertex3f(0.5, 0, 0);
                glVertex3f(0, 0.5, 0);
            glEnd();*/
            VELIKI_TROUGAO2();
    glPopMatrix();
    
    /*
    // MALI TROUGAO 1
    */
    glPushMatrix();
            glColor3f(1, 0, 1);
            
            glTranslatef(0.25,0.25,0);
            glRotatef(180,0,0,1);
            
            tacke[3].slika_TX = 0.25;
            tacke[3].slika_TY = 0.25;
            tacke[3].slika_R = 180;
            /*
            glBegin(GL_POLYGON);
                glVertex3f(0, 0, 0);
                glVertex3f(0, 0.25, 0);
                glVertex3f(0.25, 0, 0);
            glEnd();*/
            MALI_TROUGAO1();
    glPopMatrix();
    
    /*
    //MALI TROUGAO 2
    */
    glPushMatrix();
            glColor3f(1, 0,1); 
            
            glTranslatef(0.25,0,0);
            tacke[4].slika_TX = 0.25;
            tacke[4].slika_TY = 0;
            tacke[4].slika_R = 0;
            
            /*
            glBegin(GL_POLYGON);
                glVertex3f(0, 0, 0);
                glVertex3f(0, 0.25, 0);
                glVertex3f(0.25, 0, 0);
            glEnd();*/
            MALI_TROUGAO2();
    glPopMatrix();
    
    /*
    //KVADRAT
    */
    glPushMatrix();
            glColor3f(1, 0, 1);
            
            glTranslatef(0.25/2,0.25,0);
            
            tacke[5].slika_TX = 0.25/2;
            tacke[5].slika_TY = 0.25;
            tacke[5].slika_R = 0;
            /*
            glBegin(GL_POLYGON);
                glVertex3f(0, 0, 0);
                glVertex3f(0, 0.25, 0);
                glVertex3f(0.25,0.25,0);
                glVertex3f(0.25, 0, 0);
            glEnd();*/
            KVADRAT();
    glPopMatrix();
    
    /*
    //PARALELOGRAM
    */
    glPushMatrix();
            glColor3f(1, 0, 1);
            
            glTranslatef(0.25,0,0);
            
            
            tacke[6].slika_TX = 0.25;
            tacke[6].slika_TY = 0;
            tacke[6].slika_R = 0;
            /*
            glBegin(GL_POLYGON);
                glVertex3f(0.25, 0, 0);
                glVertex3f(0.5, 0, 0);
                glVertex3f(0.25, 0.25, 0);
                glVertex3f(0, 0.25, 0);
            glEnd();*/
            PARALELOGRA();
    glPopMatrix();
    
    /*
    //SEREDNJI TROUGAO
    */
    glPushMatrix();
            glColor3f(1, 0, 1);
            
            glTranslatef(-0.25,0,0);
            tacke[7].slika_TX = -0.25;
            tacke[7].slika_TY = 0;
            tacke[7].slika_R = 0;
            
           /* glBegin(GL_POLYGON);
                glVertex3f(0, 0, 0);
                glVertex3f(0.5, 0, 0);
                glVertex3f(0.25, 0.25, 0);
            glEnd();*/
           SREDNJI_TROUGAO();
    glPopMatrix();
}
void slika1()
{
  /*  //VELIKI 1*/
    glPushMatrix();
            glColor3f(0, 0, 1);
            
            glTranslatef(0,-0.5,0);
            tacke[1].slika_TX = 0;
            tacke[1].slika_TY = -0.5;
            tacke[1].slika_R = 0;
            /*
            glBegin(GL_POLYGON);
                glVertex3f(0, 0, 0);
                glVertex3f(0.5, 0, 0);
                glVertex3f(0, 0.5, 0);
            glEnd();*/
            VELIKI_TROUGAO1();
    glPopMatrix();
    
    
    /*VELIKI 2*/
    glPushMatrix();
            glColor3f(0, 0, 1);
            
            glTranslatef(0.5,0,0);
            glRotatef(180,0,0,1);
            
            tacke[2].slika_TX = 0.5;
            tacke[2].slika_TY = 0;
            tacke[2].slika_R = 180;
            
            /*glBegin(GL_POLYGON);
                glVertex3f(0, 0, 0);
                glVertex3f(0.5, 0, 0);
                glVertex3f(0, 0.5, 0);
            glEnd();*/
            VELIKI_TROUGAO2();
    glPopMatrix();
    
    
    /*MALI 1*/
    glPushMatrix();
            glColor3f(0, 0, 1);
            
            glTranslatef(0.25,0.5,0);
            
            tacke[3].slika_TX = 0.25;
            tacke[3].slika_TY = 0.5;
            tacke[3].slika_R = 0;
            /*
            glBegin(GL_POLYGON);
                glVertex3f(0, 0, 0);
                glVertex3f(0, 0.25, 0);
                glVertex3f(0.25, 0, 0);
            glEnd();*/
            MALI_TROUGAO1();
    glPopMatrix();
    
    /*MALI 2*/
    glPushMatrix();
            glColor3f(0, 0, 1);
            
            glTranslatef(0.25,0.5,0);
            glRotatef(90,0,0,1);
            
            tacke[4].slika_TX = 0.25;
            tacke[4].slika_TY = 0.5;
            tacke[4].slika_R = 90;
            
           /* glBegin(GL_POLYGON);
                glVertex3f(0, 0, 0);
                glVertex3f(0, 0.25, 0);
                glVertex3f(0.25, 0, 0);
            glEnd();*/
           MALI_TROUGAO2();
    glPopMatrix();
    
    /*KVADRAT*/
    glPushMatrix();
            glColor3f(0, 0, 1);
            
            glTranslatef(0.25/2,0.25,0);
            
            tacke[5].slika_TX = 0.25/2;
            tacke[5].slika_TY = 0.25;
            tacke[5].slika_R = 0;

           /* glBegin(GL_POLYGON);
                glVertex3f(0, 0, 0);
                glVertex3f(0, 0.25, 0);
                glVertex3f(0.25,0.25,0);
                glVertex3f(0.25, 0, 0);
            glEnd();*/
           KVADRAT();
	
    glPopMatrix();
    
    
    /* PARALELOPIPED*/
    glPushMatrix();
            glColor3f(0, 0, 1);
            
            glTranslatef(0.25/2,0,0);
            
            tacke[6].slika_TX = 0.25/2;
            tacke[6].slika_TY = 0;
            tacke[6].slika_R = 0;
            
            /*
            glBegin(GL_POLYGON);
                glVertex3f(0.25, 0, 0);
                glVertex3f(0.5, 0, 0);
                glVertex3f(0.25, 0.25, 0);
                glVertex3f(0, 0.25, 0);
            glEnd();*/
            PARALELOGRA();
    glPopMatrix();
    
    /*SREDNJI TROUGAO*/
    glPushMatrix();
            glColor3f(0, 0, 1);
            
            glTranslatef(-0.25/2,0,0);
            
            tacke[7].slika_TX = -0.25/2;
            tacke[7].slika_TY = 0;
            tacke[7].slika_R = 0;
            /*
            glBegin(GL_POLYGON);
                glVertex3f(0, 0, 0);
                glVertex3f(0.5, 0, 0);
                glVertex3f(0.25, 0.25, 0);
            glEnd();*/
            SREDNJI_TROUGAO();
    glPopMatrix();
    
}
void linije(float x11, float y11, float x22, float y22)
{
    glBegin(GL_LINES);
        glColor3f(0.5, 0.5, 0.5);
        glVertex3f(x11, y11, 0);
        glVertex3f(x22, y22, 0);
    glEnd();
    
}
void mreza()
{
    static float x1,x2,y1,y2;

    for((x1=(-1)) && (x2=(-1)); (x1<=1) && (x2<=1);(x1= x1+0.1) && (x2 = x2+ 0.1))
    {
        y1=1;
        y2=-1;
         linije(x1,y1,x2,y2);
           
    }
     for((y1=(-1)) && (y2=(-1)); (y1<=1) && (y2<=1);(y1= y1+0.1) && (y2 = y2+ 0.1))
    {
        x1=1;
        x2=-1;
         linije(x1,y1,x2,y2);
           
    }
}



int main(int argc, char **argv)
{
    /* Inicijalizuje se GLUT. */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    /* Kreira se prozor. */
    glutInitWindowSize(1000,1000);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    /* Registruju se callback funkcije. */
    glutKeyboardFunc(on_keyboard2);
    glutReshapeFunc(on_reshape2);
    glutDisplayFunc(on_display2);

    /* Obavlja se OpenGL inicijalizacija. */
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);

    /* Ukjucujemo blending */
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /* Inicijalizujemo promenljive */
    animation_parameter = -1.5;
    animation_ongoing = 0;
    
    na_dobrom_mestu_V1 = 0;
    na_dobrom_mestu_V2 = 0;
    na_dobrom_mestu_M1 = 0;
    na_dobrom_mestu_M2 = 0;
    na_dobrom_mestu_K = 0;
    na_dobrom_mestu_P = 0;
    na_dobrom_mestu_T = 0;
    
    /*alocira se prostor za cuvanje koordinata komada kojima se trazi mesto*/
    koordinate = calloc(30, sizeof(Transformacija));
        if(koordinate == NULL)
            return -1;
    
    /*alocira se prostor za cuvanje pozicija slika koje treba da se sastave*/
    tacke = calloc(30, sizeof(Slika));
        if(tacke == NULL)
            return -1;
    
    srand(time(0)); /* random od ponudjenih 6 biramo onu koja treba da se slaze*/  
    id=rand()%6; /*id koja ce da se slaze...*/
    
    ID = 0;
    
    printf("%d", id);
    /* Program ulazi u glavnu petlju. */
    glutMainLoop();

    return 0;
}

static void on_timer2(int id)
{
    if (TIMER_ID != id)
        return;

    animation_parameter += 0.01;

    glutPostRedisplay();

    if (animation_ongoing) {
        glutTimerFunc(TIMER_INTERVAL, on_timer2, TIMER_ID);
    }
}

static void on_keyboard2(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        /* Zavrsava se program. */
        exit(0);
        break;

    case 'g':
    case 'G':
        /* Pokrecemo animaciju */
        if (!animation_ongoing) {
            animation_ongoing = 1;
            glutTimerFunc(TIMER_INTERVAL, on_timer2, TIMER_ID);
        }
        break;

    case 's':
    case 'S':
        animation_ongoing = 0;
        break;
   
        
        
    case 'a':
    case 'A':
            translaton_parameter_X -= 0.01; 
            glutTimerFunc(TIMER_INTERVAL, on_timer2, TIMER_ID);
            break;
    case 'D':
    case 'd':
            translaton_parameter_X += 0.01;
            glutTimerFunc(TIMER_INTERVAL, on_timer2, TIMER_ID);
            break;
    case 'W':
    case 'w':
            translaton_parameter_Y += 0.01;
            glutTimerFunc(TIMER_INTERVAL, on_timer2, TIMER_ID);
            break;
    case 'X':
    case 'x':
            translaton_parameter_Y -= 0.01;   
            glutTimerFunc(TIMER_INTERVAL, on_timer2, TIMER_ID);
            break;
    case 'L':
    case 'l':
            rotation_parameter += 1;
            glutTimerFunc(TIMER_INTERVAL, on_timer2, TIMER_ID);
            break;
    case 'J':
    case 'j':
            rotation_parameter -= 1;
            glutTimerFunc(TIMER_INTERVAL, on_timer2, TIMER_ID);
            break;    
    
    
    case '1':
            ID = 1;
                rotation_parameter= 0;
                translaton_parameter_X = 0;
                translaton_parameter_Y = 0;
            glutTimerFunc(TIMER_INTERVAL, on_timer2, TIMER_ID);
            break;
    case '2':
            ID = 2;
                rotation_parameter= 0;
                translaton_parameter_X = 0;
                translaton_parameter_Y = 0;
            glutTimerFunc(TIMER_INTERVAL, on_timer2, TIMER_ID);
            break;
    case '3':
            ID =3;
                rotation_parameter= 0;
                translaton_parameter_X = 0;
                translaton_parameter_Y = 0;
            glutTimerFunc(TIMER_INTERVAL, on_timer2, TIMER_ID);
            break;
    case '4':
            ID = 4;
                rotation_parameter= 0;
                translaton_parameter_X = 0;
                translaton_parameter_Y = 0;
            glutTimerFunc(TIMER_INTERVAL, on_timer2, TIMER_ID);
            break;
    case '5':
            ID = 5;
                rotation_parameter= 0;
                translaton_parameter_X = 0;
                translaton_parameter_Y = 0;
            glutTimerFunc(TIMER_INTERVAL, on_timer2, TIMER_ID);
            break;
    case '6':
            ID = 6;
                rotation_parameter= 0;
                translaton_parameter_X = 0;
                translaton_parameter_Y = 0;
            glutTimerFunc(TIMER_INTERVAL, on_timer2, TIMER_ID);
            break;
    case '7':
            ID = 7;
                rotation_parameter= 0;
                translaton_parameter_X = 0;
                translaton_parameter_Y = 0;
            glutTimerFunc(TIMER_INTERVAL, on_timer2, TIMER_ID);
            break;
            
    }
    
    
    
    
}

static void on_reshape2(int width, int height)
{
    /* Podesava se viewport. */
    glViewport(0, 0, width, height);

    /* Podesava se projekcija. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    /* glOrtho(-2.0, 2.0, -2.0, 2.0, 1, 10); */
    gluPerspective(30, (float) width / height, 1, 10);
}

static void init_lights2()
{
    /* Pozicija svetla (u pitanju je direkcionalno svetlo). */
    GLfloat light_position[] = { 3, -3, 7, 0 };

    /* Ambijentalna boja svetla. */
    GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1 };

    /* Difuzna boja svetla. */
    GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 1 };

    /* Spekularna boja svetla. */
    GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 };

    /* Ukljucuje se osvjetljenje i podesavaju parametri svetla. */
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
}

static void set_material2(int id)
{
    /* Koeficijenti ambijentalne refleksije materijala. */
    GLfloat ambient_coeffs[] = { 0.3, 0.3, 0.3, 1 };

    /* Koeficijenti difuzne refleksije materijala. */
    GLfloat diffuse_coeffs[] = { 0.4, 0.4, 0.4, 1 };

    /* Koeficijenti spekularne refleksije materijala. */
    GLfloat specular_coeffs[] = { 1, 1, 1, 1 };

    /* Koeficijent glatkosti materijala. */
    GLfloat shininess = 30;
    
      switch (id) {
        case 0:
            /* Difuzna komponenta se postavlja na crvenu */
            diffuse_coeffs[0] = 1.0;
            //diffuse_coeffs[3] = 0.7;
            break;
        case 1:
            /* Difuzna komponenta se postavlja na zelenu */
            diffuse_coeffs[1] = 1.0;
            break;
        case 2:
            /* Difuzna komponenta se postavlja na plavu */
            diffuse_coeffs[2] = 1.0;
            break;
    }

    /* Podesavaju se parametri materijala. */
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

}

static void on_display2(void)
{
    /* Brise se prethodni sadrzaj prozora. */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Podesava se vidna tacka. */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0, 0,6, 0, 0, 0, 0, 1, 0);

    init_lights2();
   

    glPushMatrix();
    /* Kreira se sfera. */
    set_material2(0);

   
    glPushMatrix();
    
            mreza();
  
    glPopMatrix();
    

{ /* slike koje treba sloziti*/
glPushMatrix();
   
    if(id == 1){
    /*slika id=1*/
    glPushMatrix();
        slika1();
    glPopMatrix();
    }
    else if(id == 2){
    /*slika id=2*/
     glPushMatrix();
    slika2();
    glPopMatrix();
    }
    else if(id == 3){
    /*slika id=3*/
     glPushMatrix();
    ;
    slika3();
    glPopMatrix();
    }
    else if(id == 4){
    /*slika id=4*/
     glPushMatrix();
   
    slika4();
    glPopMatrix();
    }
    else if(id == 5){
    /*slika id=5*/
     glPushMatrix();
    
    slika5();
    glPopMatrix();
    }
    else if(id == 0){
    /*slika id=6*/
     glPushMatrix();
    
    slika6();
    glPopMatrix();
    }
 
glPopMatrix();
}

glPushMatrix();
    
    set_material2(2);
    draw_axes(5.0); 
    glColor3f(1,0,1);
    
    glTranslatef(0,0,0.1);
 /* pocetne pozicije iz kojih se oni krecu */
    if(ID == 1 && na_dobrom_mestu_V1 == 0){
    glPushMatrix();
        glColor3f(0.1,0,1);
        
        if( (rotation_parameter == tacke[1].slika_R) &&
        (translaton_parameter_X == tacke[1].slika_TX) &&
        (translaton_parameter_Y == tacke[1].slika_TY)){
            
            na_dobrom_mestu_V1 = 1;
            glTranslatef(translaton_parameter_X, translaton_parameter_Y, 0);
            glRotatef(rotation_parameter, 0,0,1);
            VELIKI_TROUGAO1();
        
        }
        else{
        kretanje();
        
        VELIKI_TROUGAO1();
        }
    glPopMatrix();
    }
    if(ID == 2 && na_dobrom_mestu_V2 == 0){
    glPushMatrix();
        glColor3f(0.5,0,1);
        if( (rotation_parameter == tacke[2].slika_R) &&
        (translaton_parameter_X == tacke[2].slika_TX) &&
        (translaton_parameter_Y == tacke[2].slika_TY)){
            
            na_dobrom_mestu_V2 = 2;
            glTranslatef(translaton_parameter_X, translaton_parameter_Y, 0);
            glRotatef(rotation_parameter, 0,0,1);
            VELIKI_TROUGAO2();
        
        }else{
        kretanje();
        VELIKI_TROUGAO2();
        }
    glPopMatrix();
    }
    if(ID == 3 && na_dobrom_mestu_M1==0){
    glPushMatrix();
        glColor3f(1,0.5,1);
        if( (rotation_parameter == tacke[3].slika_R) &&
        (translaton_parameter_X == tacke[3].slika_TX) &&
        (translaton_parameter_Y == tacke[3].slika_TY)){
            
            na_dobrom_mestu_M1 = 1;
            glTranslatef(translaton_parameter_X, translaton_parameter_Y, 0);
            glRotatef(rotation_parameter, 0,0,1);
            MALI_TROUGAO1();
        
        }else{
        kretanje();
        MALI_TROUGAO1();
        }
    glPopMatrix();
    }
    if(ID == 4 && na_dobrom_mestu_M2==0){
    glPushMatrix();
        glColor3f(1,0,0.2);
        if( (rotation_parameter == tacke[4].slika_R) &&
        (translaton_parameter_X == tacke[4].slika_TX) &&
        (translaton_parameter_Y == tacke[4].slika_TY)){
            
            na_dobrom_mestu_M2 = 1;
            glTranslatef(translaton_parameter_X, translaton_parameter_Y, 0);
            glRotatef(rotation_parameter, 0,0,1);
            MALI_TROUGAO2();
        }else{
        kretanje();
        MALI_TROUGAO2();
        }
    glPopMatrix();
    }
    if(ID == 5 && na_dobrom_mestu_K == 0){
    glPushMatrix();
        glColor3f(0.2,0.2,1);
        if( (rotation_parameter == tacke[5].slika_R) &&
        (translaton_parameter_X == tacke[5].slika_TX) &&
        (translaton_parameter_Y == tacke[5].slika_TY)){
            
            na_dobrom_mestu_K = 1;
            glTranslatef(translaton_parameter_X, translaton_parameter_Y, 0);
            glRotatef(rotation_parameter, 0,0,1);
            KVADRAT();
        
        }
        kretanje();
        KVADRAT();
    glPopMatrix();
    }
    if(ID == 6 && na_dobrom_mestu_P == 0 ){
    glPushMatrix();
        glColor3f(1,0,0.3);
        if( (rotation_parameter == tacke[6].slika_R) &&
        (translaton_parameter_X == tacke[6].slika_TX) &&
        (translaton_parameter_Y == tacke[6].slika_TY)){
            
            na_dobrom_mestu_P = 1;
            glTranslatef(translaton_parameter_X, translaton_parameter_Y, 0);
            glRotatef(rotation_parameter, 0,0,1);
            PARALELOGRA();
            
        }else{
        kretanje();
        PARALELOGRA();
        }
    glPopMatrix();
    }
    if(ID == 7 && na_dobrom_mestu_T == 0){
    glPushMatrix();
        glColor3f(0.7,0.3,1);
        if( (rotation_parameter == tacke[7].slika_R) &&
        (translaton_parameter_X == tacke[7].slika_TX) &&
        (translaton_parameter_Y == tacke[7].slika_TY)){
            
            na_dobrom_mestu_T = 1;
            glTranslatef(translaton_parameter_X, translaton_parameter_Y, 0);
            glRotatef(rotation_parameter, 0,0,1);
            SREDNJI_TROUGAO();
        
        }
        else{
            kretanje();
            SREDNJI_TROUGAO();
        }
    glPopMatrix();
    }
 glPopMatrix();   
 
 /*stalne pozicije oko mreze elemenata*/   
glPushMatrix();
if(ID != 1 && na_dobrom_mestu_V1 != 1){
    glPushMatrix();
        glColor3f(0.1,0,1);
        glTranslatef(-1,1,0);
        VELIKI_TROUGAO1();
    glPopMatrix();
}
if(ID != 2 && na_dobrom_mestu_V2 != 1){
    glPushMatrix();
        glColor3f(0.5,0,1);
        glTranslatef(-1.5,0.5,0);
        VELIKI_TROUGAO2();
    glPopMatrix();
}
if(ID != 3 && na_dobrom_mestu_M1 != 1){
    glPushMatrix();
        glColor3f(1,0.5,1);
        glTranslatef(-1.25,0,0);
        MALI_TROUGAO1();
    glPopMatrix();
}
if(ID != 4 && na_dobrom_mestu_M2 != 1){
    glPushMatrix();
        glColor3f(1,0,0.2);
        glTranslatef(-0.4,1,0);
        MALI_TROUGAO2();
    glPopMatrix();
}
if(ID != 5 && na_dobrom_mestu_K != 1){
    glPushMatrix();
        glColor3f(0.2,0.2,1);
        glTranslatef(0,1,0);
        PARALELOGRA();
    glPopMatrix();
}
if(ID != 6 && na_dobrom_mestu_P != 1){
    glPushMatrix();
        glColor3f(1,0,0.3);
        glTranslatef(-1.5,-0.5,0);
        SREDNJI_TROUGAO();
    glPopMatrix();
}
if(ID != 7 && na_dobrom_mestu_T != 1){
    glPushMatrix();
        glColor3f(0.7,0.3,1);
        glTranslatef(-1.25,-1,0);
        KVADRAT();
    glPopMatrix(); 
}
glPopMatrix();
  










    glutSwapBuffers();
}

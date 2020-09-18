#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

/* Vreme proteklo od pocetka simulacije. */
static float animation_parameter;

/* Fleg koji odredjuje stanje tajmera. */
static int animation_active;


static int parametar_lopta;
static int parametar_pad;

static int rotiraj_se;
/* Deklaracije callback funkcija. */
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_timer(int value);
static void on_display(void);

static void set_material(int id);
static void init_lights();

static void lopta(void);
static void draw_kocka(void);


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





static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        /* Zavrsava se program. */
        exit(0);
        break;

    case 'g':
    case 'G':
        /* Pokrece se simulacija. */
        if (!animation_active) {
            glutTimerFunc(10, on_timer, 0);
            animation_active = 1;
            parametar_lopta = 0;
        }
        break;

    case 's':
    case 'S':
        /* Zaustavlja se simulacija. */
        if (animation_active) {
            glutTimerFunc(10, on_timer, 0);
            animation_active = 0;
            parametar_lopta = 1;
            parametar_pad = 1;
            animation_parameter = 0;
            
        }
        break;
    }
}

static void on_timer(int value)
{
    /* Proverava se da li callback dolazi od odgovarajuceg tajmera. */
    if (value != 0)
        return;

    /* Azurira se vreme simulacije. */
    animation_parameter++;

    /* Forsira se ponovno iscrtavanje prozora. */
    glutPostRedisplay();

    /* Po potrebi se ponovo postavlja tajmer. */
    if (animation_active)
        glutTimerFunc(10, on_timer, 0);
    if (animation_active == 0 && parametar_pad == 1)
        glutTimerFunc(10, on_timer, 0);
}

static void on_reshape(int width, int height)
{
    /* Postavlja se viewport. */
    glViewport(0, 0, width, height);

    /* Postavljaju se parametri projekcije. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) width / height, 1, 1500);
}

static void on_display(void)
{
    /* Postavlja se boja svih piksela na zadatu boju pozadine. */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Postavlja se vidna tacka. */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(8,8,13, 0, 0, 0, 0, 1, 0);  
    
    
    init_lights();

    if(parametar_pad == 0){ /* ono sto se pokrece kada se pritisne G*/
    /* Transliramo i rotiramo tako da kretanja ne budu u fazi */
    glPushMatrix();
        glTranslatef(
                sin(animation_parameter / 100.0f),
                sin(animation_parameter / 100.0f),
                sin(animation_parameter / 50.0f)
            );

        glRotatef(
            /* ugao */
                sin(animation_parameter / 50.0f) * 30.0f,
            /* vektor rotacije */
                0, 0, 1
            );

        draw_kocka();
    glPopMatrix();
    
    if(parametar_lopta == 0)
    { 
        lopta();
    }
    else{/* nestaje lopta*/
        
        double clip_plane[] = {-1,0,0,-5};

        glClipPlane(GL_CLIP_PLANE0, clip_plane);
        glEnable(GL_CLIP_PLANE0);

            lopta();
            
        glDisable(GL_CLIP_PLANE0);
    }
    }else{ /*kocka krece da pada */
        
        if( (-animation_parameter/20) > (-100/20)+0.52){
        
        glPushMatrix();
       
        glRotatef(
            /* ugao */
                90+animation_parameter,
            /* vektor rotacije */
                0, (-animation_parameter/20), (-animation_parameter/20)
            );
        glTranslatef(0, (-animation_parameter/20), (-animation_parameter/20));
        draw_kocka();
        glPopMatrix();
        }
        else{
        glPushMatrix();
        
        glTranslatef(0, (-100/20 + 0.53), (-100/20 + 0.53));
                
        draw_kocka();
        glPopMatrix();
        
    }}
    
   

    /*podloga*/
    glPushMatrix();
        glTranslatef(0, -100/20, -100/20);
        glScalef(10, 0.3,10);
        draw_kocka();
    glPopMatrix();
        
    draw_axes(5);


    /* Postavlja se nova slika u prozor. */
    glutSwapBuffers();
}

static void draw_kocka(void)
{
#define glutCube glutWireCube
    glPushMatrix();
    
    
 glPushMatrix();
        set_material(1);
        glTranslatef(0, 0, 0);
        glutSolidCube(1);
 glPopMatrix();
    

 
 
 
 
    glPopMatrix();
#undef glutCube
}


static void lopta(void){
    /*
      glRotatef(animation_parameter * 120, 
              animation_parameter, 
                animation_parameter,
              2+ animation_parameter/5);

      */
      
      set_material(0);
 glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glutSolidSphere(2.5, 64, 64);

    glCullFace(GL_BACK);
    glutSolidSphere(2.5, 64, 64);

glDisable(GL_CULL_FACE);
    
}



static void set_material(int id)
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
            diffuse_coeffs[3] = 0.7;
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


static void init_lights()
{
    /* Pozicija svetla (u pitanju je direkcionalno svetlo). */
    GLfloat light_position[] = { 1, 15, 5, 0 };

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


int main(int argc, char **argv)
{
    /* Inicijalizuje se GLUT. */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    /* Kreira se prozor. */
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    /* Registruju se funkcije za obradu dogadjaja. */
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);

    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    
    /* Inicijalizuju se globalne promenljive. */
    animation_parameter = 0;
    animation_active = 0;
    parametar_lopta = 0;
    parametar_pad = 0;
    rotiraj_se = 0;

    /* Obavlja se OpenGL inicijalizacija. */
    /*glClearColor(0, 0, 0, 0);*/
    glEnable(GL_DEPTH_TEST);
    glLineWidth(2);

    /* Ulazi se u glavnu petlju. */
    glutMainLoop();

    return 0;
}






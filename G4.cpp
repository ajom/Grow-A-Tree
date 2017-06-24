/*
   G4.cpp
   created by Katie Merin and Austin O'Malley on March 31, 2016
*/

#include <iostream>
#include <fstream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

int window_width = 1000;
int window_height = 750;
int xCamera = 0;
int yCamera = 0;
int zCamera = 350;

int growthIteration = 0;

bool chooseLocation = false;
int startLocationX = 0;
int startLocationY = -1000;

float zoomFactor = 0;
float xTranslate = 0;
float yTranslate = 0;
float yRotAngle = 0;

int CFGMode = 0;
char CFG[1000000];
int CFGSize = 0;
char newCFG[1000000];
int newCFGSize = 0;

float flowerColor[3], branchColor[3];
bool flowerB = false;

char* myArgv;

float angle, angle1, angle2, angle3;
int nRules, nRules1, nRules2, nRules3;
char var1, var2, var1_1, var2_1, var1_2, var2_2, var1_3, var2_3;
char rule1[50], rule2[50], rule1_1[50], rule2_1[50], rule1_2[50], rule2_2[50], rule1_3[50], rule2_3[50];
int lRule1, lRule2, lRule1_1, lRule2_1, lRule1_2, lRule2_2, lRule1_3, lRule2_3;
char start1[10], start2[10], start3[10], start[50];
int lBranch, lBranch1, lBranch2, lBranch3;


void makeButtons();
void drawLeaf();
void drawFlower();
void drawBranch();
void readInFile(char*);
void analyzeCFG1();
void drawCFG1();
void saveCFG(int);
void chooseCFG(int);
void writeDirections();
void writeError();
void clear();
void writeStrokeString(char mystring[], float, float, float, int);



// Drawing routine.
void drawScene() {
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(0.0, 0.0, 0.0);

   // Main Viewport
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glViewport(0, 0, 3*window_width/4, window_height);
   glFrustum(-250, 250, -250, 250, 175, 1300);
   gluLookAt(xCamera, yCamera, zCamera, 0, 0, 0, 0, 1, 0);

   glColor3f(0, 0, 0);

   glTranslatef(startLocationX + xTranslate, startLocationY + yTranslate, -500 + zoomFactor);
   glRotatef(yRotAngle, 0, 1, 0);


   if(CFGMode == 0){
      writeDirections();
   }

   if(growthIteration == 7){
      writeError();
   }

   drawCFG1();


   // Button Viewport
   glLoadIdentity();
   glViewport(3*window_width/4, 0, window_width/4, window_height);
   glOrtho(0, 250, 0, 750, -1.0, 1.0);

   glColor3f(.15, .15, .4);
   glRectf(0, 0, 250, 750);

   makeButtons();

   glFlush();
}


void clear() {
   int startLocationX = 0;
   int startLocationY = -1000;
   CFGMode = 0;
   chooseLocation = false;
   growthIteration = 0;
   xCamera = 0;
   yCamera = 0;
   zCamera = 350;
   zoomFactor = 0;
   yRotAngle = 0;
   xTranslate = 0;
   yTranslate = 0;

   if(growthIteration == 0){
      for (int i = 0; i < CFGSize; i++) {
         CFG[i] = '!';
      }
   }

   CFGSize = 0;
   angle = 0;
   lBranch = 0;
   var1 = 0;
   var2 = 0;

   lRule1 = 0; 
   lRule2 = 0;

   readInFile(myArgv);
   glutPostRedisplay();
}


void readInFile(char* argv) {
   // Open and read file
   myArgv = argv;

   ifstream myFile;
   myFile.open(argv);         // SET FILENAME HERE

   if (!myFile) {
      cerr << "Unable to open file!\n";
   }
   else {
      char a;

      myFile >> a >> a;
      myFile >> a >> a;

      for(int j = 0; j < 3; j++)
         myFile >> branchColor[j] >> a;

      myFile >> a >> a;
      myFile >> a >> a;

      for(int j = 0; j < 3; j++)
         myFile >> flowerColor[j] >> a;

      for(int j = 1; j < 4; j++){

         myFile >> a;
         myFile >> a;
         myFile >> angle;

         myFile >> a >> a;
         myFile >> a;
         myFile >> lBranch;

         // Starting varibles
         for (int i = 0; i < 10; i++) {
            myFile >> start[i];
            if(j == 1){
               CFG[i] = start[i];
               CFGSize++;
            }
            char c = myFile.peek();
            if (c == '\n') {
               break;
            }
         }

         // Rule 1
         myFile >> var1;
         myFile >> a;
         for (int i = 0; i < 50; i++) {
            myFile >> rule1[i];
            lRule1++;

            char c = myFile.peek();
            if (c == '\n') {
               break;
            }
         }

         // Rule 2
         myFile >> var2;
         myFile >> a;
         for (int i = 0; i < 50; i++) {
            myFile >> rule2[i];
            lRule2++;

            char c = myFile.peek();
            if (c == '\n') {
               break;
            }
         }      
         saveCFG(j);
      }

      myFile.close();
   }
}

void saveCFG(int n){
   if (n == 1){
      for (int i = 0; i < 10; i++)
            start1[i] = start[i];

      angle1 = angle;
      lBranch1 = lBranch;
      var1_1 = var1;
      var2_1 = var2;
      lRule1_1 = lRule1;
      lRule2_1 = lRule2;

      for(int i = 0; i < lRule1; i++){
         rule1_1[i] = rule1[i];
      }

      for(int i = 0; i < lRule2; i++){
         rule2_1[i] = rule2[i];
      }
   }else if(n == 2){
      for (int i = 0; i < 10; i++)
         start2[i] = start[i];
      angle2 = angle;
      lBranch2 = lBranch;
      var1_2 = var1;
      var2_2 = var2;
      lRule1_2 = lRule1;
      lRule2_2 = lRule2;

      for(int i = 0; i < lRule1; i++){
         rule1_2[i] = rule1[i];
      }

      for(int i = 0; i < lRule2; i++){
         rule2_2[i] = rule2[i];
      }

   }else if(n ==3){
      for (int i = 0; i < 10; i++)
         start3[i] = start[i];
      angle3 = angle;
      lBranch3 = lBranch;
      var1_3 = var1;
      var2_3 = var2;
      lRule1_3 = lRule1;
      lRule2_3 = lRule2;

      for(int i = 0; i < lRule1; i++){
         rule1_3[i] = rule1[i];
      }

      for(int i = 0; i < lRule2; i++){
         rule2_3[i] = rule2[i];
      }
      chooseCFG(1);
   }

   for(int i = 0; i < lRule1; i++){
      rule1[i] = '-';
   }

   for(int i = 0; i < lRule2; i++){
      rule2[i] = '-';
   }

   for (int i = 0; i < 10; i++)
      start[i] = '-';

   lRule1 = 0;
   lRule2 = 0;
   angle = 0;
   lBranch = 0;
   var1 = 0;
   var2 = 0;
}

void chooseCFG(int n){
   // Choose starting location
   chooseLocation = true;

   if (n == 1){
      if(growthIteration == 0){
         for (int i = 0; i < 10; i++) {
            CFG[i] = start1[i];
            CFGSize++;
         }
      }

      angle = angle1;
      lBranch = lBranch1;
      var1 = var1_1;
      var2 = var2_1;
      lRule1 = lRule1_1;
      lRule2 = lRule2_1;

      for(int i = 0; i < lRule1; i++){
         rule1[i] = rule1_1[i];
      }

      for(int i = 0; i < lRule2; i++){
         rule2[i] = rule2_1[i];
      }
   }else if(n == 2){
      if(growthIteration == 0){
         for (int i = 0; i < 10; i++) {
            CFG[i] = start1[i];
            CFGSize++;
         }
      }
      angle = angle2;
      lBranch = lBranch2;
      var1 = var1_2;
      var2 = var2_2;
      lRule1 = lRule1_2;
      lRule2 = lRule2_2;

      for(int i = 0; i < lRule1; i++){
         rule1[i] = rule1_2[i];
      }

      for(int i = 0; i < lRule2; i++){
         rule2[i] = rule2_2[i];
      }

   }else if(n ==3){
      if(growthIteration == 0){
         for (int i = 0; i < 10; i++) {
            CFG[i] = start1[i];
            CFGSize++;
         }
      }
      angle = angle3;
      lBranch = lBranch3;
      var1 = var1_3;
      var2 = var2_3;
      lRule1 = lRule1_3;
      lRule2 = lRule2_3;

      for(int i = 0; i < lRule1; i++){
         rule1[i] = rule1_3[i];
      }

      for(int i = 0; i < lRule2; i++){
         rule2[i] = rule2_3[i];
      }
   }
}

void analyzeCFG1() {
   // Determine and allocate new array with size = sum of all variables
   for (int i = 0; i < CFGSize; i++) {

      // If rule 1
      if (CFG[i] == var1) {
         for (int j = 0; j < lRule1; j++) {
            newCFG[j+newCFGSize] = rule1[j];
         }
         newCFGSize += lRule1;
      }

      // If rule 2
      else if (CFG[i] == var2) {
         for (int j = 0; j < lRule2; j++) {
            newCFG[j+newCFGSize] = rule2[j];
         }
         newCFGSize += lRule2;
      }

      // If anything else, 1
      else {
         newCFG[newCFGSize] = CFG[i];
         newCFGSize++;
      }
   
   }

   for (int i = 0; i < newCFGSize; i++) {
      CFG[i] = newCFG[i];
   }

   CFGSize = newCFGSize;
   newCFGSize = 0;
}

void drawCFG1() {
   glPushMatrix(); 

   for (int i = 0; i < CFGSize; i++) {
      if (CFG[i] == 'B') {
         drawBranch();
      }

      else if (CFG[i] == '[') { 
         glPushMatrix();
      }

      else if (CFG[i] == ']') {
         glPopMatrix();
      }

      else if (CFG[i] == '+') {
         glRotatef(angle1, 0, 0, 1);
      }

      else if (CFG[i] == '-') {
         glRotatef(-angle1, 0, 0, 1);
      }

      else if (CFG[i] == '&') {
         glRotatef(angle1, 1, 0, 0);
      }

      else if (CFG[i] == '^') {
         glRotatef(-angle1, 1, 0, 0);
      }

      else if (CFG[i] == '$') {
         glRotatef(angle1, 0, 1, 0);
      }

      else if (CFG[i] == '%') {
         glRotatef(-angle1, 0, 1, 0);
      }

      else if (CFG[i] == 'L') {
         drawLeaf();
      }

      else if (CFG[i] == 'F') {
         drawFlower();
      }
   }

   glPopMatrix();

}

void writeDirections(){
   char d1[] = "Welcome to Grow-A-Tree";
   char d2[] = "To begin please select a tree on the right";
   char d3[] = "Then click on this screen to select a starting location";
   char d4[] = "There is a default starting location in the bottom center";
   char d4_5[] = "Finally, click GROW to watch your tree get bigger";
   char d5[] = "To move the tree left press a and to move the tree right press d";
   char d6[] = "To move the tree up press w and to move the tree down press s";

   writeStrokeString(d1, -650, 2000, .75, 4);
   writeStrokeString(d2, -1000, 1800, .45, 3);
   writeStrokeString(d3, -1000, 1700, .45, 3);
   writeStrokeString(d4, -1000, 1600, .45, 3);
   writeStrokeString(d4_5, -1000, 1500, .45, 3);   
   writeStrokeString(d5, -1000, 1300, .45, 3);
   writeStrokeString(d6, -1000, 1200, .45, 3);
}

void writeError(){
   char e1[] = "This tree does not have enough nutrients to grow more!";
   char e2[] = "Please press CLEAR to start a new tree";

   writeStrokeString(e1, -1000, -50, .45, 3);
   writeStrokeString(e2, -1000, -150, .45, 3);
}

void makeButtons() {
   char grow[] = "Grow";
   char clear[] = "Clear";
   char tree[] = "TREE";
   char letter1[] = "1";
   char letter2[] = "2";
   char letter3[] = "3";

   glColor3f(.25, .25, 1);
   glRectf(50, 600, 200, 700);
   writeStrokeString(tree, 100, 680, .15, 4);
   writeStrokeString(letter1, 107, 610, .6, 4);
   glRectf(50, 450, 200, 550);
   writeStrokeString(tree, 100, 530, .15, 4);
   writeStrokeString(letter2, 107, 460, .6, 4);
   glRectf(50, 300, 200, 400);
   writeStrokeString(tree, 100, 380, .15, 4);
   writeStrokeString(letter3, 107, 310, .6, 4);

   glRectf(25, 175, 225, 250);   // Grow Button
   writeStrokeString(grow, 63, 190, .4, 4);

   glRectf(25, 75, 225, 150);    // Clear Button
   writeStrokeString(clear, 63, 90, .4, 4);

   glRectf(20, 20, 50, 50);   // rotate left button
   glRectf(70, 20, 100, 50);  // rotate right button
   glRectf(150, 20, 180, 50); // zoom in button
   glRectf(200, 20, 230, 50); // zoom out button

   glColor3f(.5, .5, .5);
   // rotate left
   glBegin(GL_QUAD_STRIP);
   glVertex2f(45, 25);
   glVertex2f(45, 32);
   glVertex2f(32, 28);
   glVertex2f(37, 33);
   glVertex2f(27, 40);
   glVertex2f(35, 40);
   glEnd();
   glBegin(GL_TRIANGLES);
   glVertex2f(23, 38);
   glVertex2f(40, 38);
   glVertex2f(31.5, 46);
   glEnd();
   
   // rotate right
   glBegin(GL_QUAD_STRIP);
   glVertex2f(75, 25);
   glVertex2f(75, 32);
   glVertex2f(88, 28);
   glVertex2f(83, 33);
   glVertex2f(93, 40);
   glVertex2f(85, 40);
   glEnd();
   glBegin(GL_TRIANGLES);
   glVertex2f(80, 38);
   glVertex2f(97, 38);
   glVertex2f(88.5, 46);
   glEnd();

   glRectf(155, 32, 175, 38); //plus sign
   glRectf(162, 25, 168, 45); //plus sign
   glRectf(205, 32, 225, 38); //minus sign
}


void writeStrokeString(char mystring[], float x1, float y1, float scale, int wLine){
   int i;

   glLineWidth(wLine);
   glPointSize(wLine - 2);

   glColor3f(.5, .5, .5);
   
   glPushMatrix();
   glTranslatef(x1, y1, 0.0);
   glScalef(scale, scale, scale);
   for (i = 0; mystring[i] != '\0'; i++) glutStrokeCharacter(GLUT_STROKE_ROMAN, mystring[i]);
   glPopMatrix();

   glColor3f(.25, .25, 1);   


   glLineWidth(1);
   glPointSize(1);
}


void drawLeaf() {
   int rotateAngle = rand() % 360;

   if (!flowerB){
      float altColor = (rand() % 40)*0.01 + 0.6;
      glColor3f(0, altColor, 0);
      glRotatef(rotateAngle, 0, 1, 0);
   }

   glPushMatrix();
   glScalef(.5, .5, 0);
   glRotatef(45, 0, 0, 1);

   glBegin(GL_POLYGON);
      glVertex3f(0, 0, 0);
      glVertex3f(10, 20, 0);
      glVertex3f(10, 40, 0);
      glVertex3f(0, 60, 0);
      glVertex3f(- 10, 40, 0);
      glVertex3f(- 10, 20, 0);
   glEnd();
   glPopMatrix();

   if (!flowerB)
      glRotatef(-rotateAngle, 0, 1, 0);
}


void drawFlower() {
   flowerB = true;
   glColor3f(flowerColor[0], flowerColor[1], flowerColor[2]);
   glPushMatrix();
   glScalef(.4, .4, 0);
   for (int i = 0; i < 10; i++) {
      glRotatef(18, 0 ,0, 1);
      glColor3f(1, .6, .7);
      drawLeaf();
      glRotatef(18, 0, 0, 1);
      glColor3f(1, .75, .8);
      drawLeaf();
   }
   glutSolidSphere(10, 40, 40);

   glPopMatrix();
   flowerB = false;

   glTranslatef(0, 2.5, 0);
}

void drawBranch() {
   glColor3f(branchColor[0], branchColor[1], branchColor[2]);

   glPushMatrix();
   glRotatef(-90, 1, 0, 0);
   GLUquadricObj *myobject;
   myobject = gluNewQuadric();
   gluCylinder(myobject, 2, 2, lBranch, 40, 40);
   glPopMatrix();

   glTranslatef(0, lBranch, 0);
}

// Initialization routine.
void setup() {
   glClearColor(1.0, 1.0, 1.0, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h) {
   glViewport(0, 0, (GLsizei)w, (GLsizei)h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glMatrixMode(GL_MODELVIEW);
}



void mouse(int button, int state, int x, int y) {
   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

      if (y > 50 && y < 450 && x > 800 && x < 950) {
         if (y > 50 && y < 150) {
            cout << "Drawing Tree 1" << endl;
            chooseCFG(1);
            CFGMode = 1;
         } else if (y > 200 && y < 300) {
            cout << "Drawing Tree 2" << endl;
            chooseCFG(2);
            CFGMode = 2;
         } else if (y > 350 && y < 450) {
            cout << "Drawing Tree 3" << endl;
            chooseCFG(3);
            CFGMode = 3;
         }
         // Choose starting location
         chooseLocation = true;
      }

      if (chooseLocation == true && x > 0 && x < 750) {
         startLocationX = 3.1579 * x - 1200;
         startLocationY = -3.1579 * y + 1200;
         chooseLocation = false;
      }

// glRectf(25, 175, 225, 250);
      else if (x > 775 && x < 975 && y > 500 && y < 575) {
         cout << "GROW" << endl;
         if(growthIteration < 7 && CFGMode > 0){
            analyzeCFG1();
            glutPostRedisplay();
            growthIteration++;
         }
      }

// glRectf(25, 75, 225, 150);
      else if (x > 775 && x < 975 && y > 600 && y < 675) {
         clear();
         glutPostRedisplay();
      }

      else if (y > 700 && y < 730) {
         if (x > 950 && x < 980) {
            zoomFactor = zoomFactor - 30;
            glutPostRedisplay();
         } else if (x > 900 && x < 930) {
            zoomFactor = zoomFactor + 30;
            glutPostRedisplay();
         } else if (x > 770 && x < 800) {
            yRotAngle = yRotAngle + 10;
            glutPostRedisplay();
         } else if (x > 820 && x < 850) {
            yRotAngle = yRotAngle - 10;
            glutPostRedisplay();
         }
      }
   }
}


// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y) {
   switch (key) {
      case 27:
         exit(0);
         break;
      case '7':
         xCamera = xCamera + 10;
         break;
      case '1':
         xCamera = xCamera - 10;
         break;
      case '8':
         yCamera = yCamera + 10;
         break;
      case '2':
         yCamera = yCamera - 10;
         break;
      case 'd':
         xTranslate = xTranslate + 30;
         break;
      case 'a':
         xTranslate = xTranslate - 30;
         break;
      case 'w':
         yTranslate = yTranslate + 30;
         break;
      case 's':
         yTranslate = yTranslate - 30;
         break;
      case 'q' :
         exit(1);
      default:
         break;
   }
   glutPostRedisplay();
}

// Main routine.
int main(int argc, char **argv) {
   glutInit(&argc, argv);

   char myA[] = "g4input.txt";
 

   if (argc > 1){
      readInFile(argv[1]);
   }
   else{
      readInFile(myA);
   }

   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize(window_width, window_height);
   glutInitWindowPosition(1000, 100);
   glutCreateWindow("Grow-A-Tree");
   setup(); 
   glutDisplayFunc(drawScene);
   glutReshapeFunc(resize);
   glutMouseFunc (mouse);
   glutKeyboardFunc(keyInput);
   glutMainLoop();

   return 0;  
}

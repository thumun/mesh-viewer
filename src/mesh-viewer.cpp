//--------------------------------------------------
// Author:
// Date:
// Description: Loads PLY files in ASCII format
//--------------------------------------------------

#include <cmath>
#include <string>
#include <vector>
#include "agl/window.h"
#include "plymesh.h"
#include "osutils.h"

using namespace std;
using namespace glm;
using namespace agl;

class MeshViewer : public Window {
public:
   MeshViewer() : Window() {
   }

   void setup() {


      // load all models at start of program 
      std::vector<std::string> dir = GetFilenamesInDir("../models", "ply"); 

      // int i = 0; 

      for (std::string file : dir){
         meshes.push_back(PLYMesh("../models/" + file));
         // cout << file << endl;
         // cout << "MIN: " << meshes[i].minBounds() << ", MAX: " << meshes[i].maxBounds() << endl;
         // i += 1; 
      }
      currentIndx = 0; 

      // below for testing: 

      mesh.load("../models/saratoga.ply");
      cout << "max: " << mesh.maxBounds() << ", min: " << mesh.minBounds() << endl; 

   }

   // maybe change floats to int in future
   void computeCamPos(int r, int a, int e){
      camPos.x = r*sin(a)*cos(e);
      camPos.y = r*sin(e);
      camPos.z = r*cos(a)*cos(e);
   }

   void mouseMotion(int x, int y, int dx, int dy) {

      // mapping not look good 
      // azimuth = acos(x/radius);
      // elevation = asin(y/radius);

      if(isMousePress){
         if (dx > 0){
         azimuth += 0.01;
            if (azimuth > 2*M_PI ){
               azimuth = 0; 
            }
         } else {
            azimuth -= 0.01f; 
            if (azimuth < 0 ){
               azimuth = 2*M_PI; 
            }
         }
         if (dy > 0){
            elevation += 0.5f;
            if (elevation > M_PI ){
               elevation = -1*M_PI; 
            }
         } else {
            elevation -= 0.5f; 
            if (elevation < -1*M_PI ){
               elevation = M_PI; 
            }
         }
      }

      // if (dx > 0){
      //    azimuth += 0.5f;
      //    if (azimuth > 2*M_PI ){
      //       azimuth = 0; 
      //    }
      // } else {
      //    azimuth -= 0.5f; 
      //    if (azimuth < 0 ){
      //       azimuth = 2*M_PI; 
      //    }
      // }

      // if (dy > 0){
      //    elevation += 0.5f;
      //    if (elevation > M_PI ){
      //       elevation = -1*M_PI; 
      //    }
      // } else {
      //    elevation -= 0.5f; 
      //    if (elevation < -1*M_PI ){
      //       elevation = M_PI; 
      //    }
      // }

   }

   void mouseDown(int button, int mods) {
      // moving camera backward - change r
      // radius -= 1;
      // computeCamPos(radius, azimuth, elevation);
      if (button == GLFW_MOUSE_BUTTON_LEFT){
         isMousePress = true; 
      }
   }

   void mouseUp(int button, int mods) {
      // moving camera forward - change r 
      // radius += 1;
      // computeCamPos(radius, azimuth, elevation);
      if (button == GLFW_MOUSE_BUTTON_LEFT){
         isMousePress = false; 
      }
   }

   void scroll(float dx, float dy) {
   }

   void keyUp(int key, int mods) {
      // will change to capital N 
      if (key == GLFW_KEY_N && mods == GLFW_MOD_SHIFT){

         // cout << " capital N pressed" << endl;

         if (currentIndx == meshes.size()-1){
            currentIndx = 0; // check if this wld fail 
         } else {
            currentIndx += 1;
         }
         // cout << currentIndx << endl; 


      } else if (key == GLFW_KEY_N){
         // cout << "n pressed" << endl;
         if (currentIndx == 0){
            currentIndx = meshes.size()-1; // check if this wld fail 
         } else {
            currentIndx -= 1;
         }
         // cout << currentIndx << endl; 
 
      } else if (key == GLFW_KEY_UP){
         // moving camera forward - change r
         radius += 0.5;

      } else if (key == GLFW_KEY_DOWN){
         // moving camera backward - change r
         radius -= 0.5;
      }
   }

   void draw() {
      float aspect = ((float)width()) / height();
      renderer.perspective(glm::radians(60.0f), aspect, 0.1f, 50.0f);
      // renderer.lookAt(eyePos, lookPos, up);

      computeCamPos(radius, azimuth, elevation);
      vec3 x = cross(up, camPos);
      vec3 y = cross(camPos, x);
      vec3 z = cross(x, y);

      renderer.lookAt(camPos, lookPos, z);

      // renderer.lookAt(camPos, lookPos, up);

      // renderer.rotate(vec3(0,0,0));
      // renderer.scale(vec3(1,1,1));
      // renderer.translate(vec3(0,0,0));

      renderer.rotate(vec3(0,0,0));
      // renderer.scale(vec3(mesh.getScaleRatio())); 
      // renderer.translate(mesh.getTranslateVal());
      // renderer.mesh(mesh);
      renderer.scale(vec3(meshes[currentIndx].getScaleRatio())); 
      renderer.translate(meshes[currentIndx].getTranslateVal());
      renderer.mesh(meshes[currentIndx]);
      // renderer.cube(); // for debugging!
   }

protected:
   PLYMesh mesh;
   std::vector<PLYMesh> meshes; 
   vec3 eyePos = vec3(10, 0, 0);
   vec3 lookPos = vec3(0, 0, 0);
   vec3 up = vec3(0, 1, 0);
   vec3 camPos = eyePos;
   float azimuth = 0; 
   float elevation = 0; 
   float radius = 10.0f; 
   bool isMousePress = false;

private:
   int currentIndx = 0; 
};

int main(int argc, char** argv)
{
   MeshViewer viewer;
   viewer.run();
   return 0;
}


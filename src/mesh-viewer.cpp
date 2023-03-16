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

      for (std::string file : dir){
         meshes.push_back(PLYMesh("../models/" + file));
      }
      
      shaders.push_back("normals");
      shaders.push_back("phong-vertex");
      shaders.push_back("phong-pixel");
      // add more shaders as make them 

      // loading the shaders at start of program 
      for (string s: shaders){
         renderer.loadShader(s, "../shaders/"+s+".vs", "../shaders/"+s+".fs");
      }

      meshIndx = 0; 
      shaderIndx = 0; 

   }

   // maybe change floats to int in future
   void computeCamPos(int r, int a, int e){
      camPos.x = r*cos(a)*cos(e);
      camPos.y = r*sin(e);
      camPos.z = r*sin(a)*cos(e);
   }

   void mouseMotion(int x, int y, int dx, int dy) {

      // mapping not look good 
      // azimuth = acos(x/radius);
      // elevation = asin(y/radius);

      if(isMousePress){

         azimuth += (float)dx*0.01f; 
         elevation += (float)dy*0.01f; 

         if (elevation > M_PI/2){
            elevation = -1*M_PI/2;

         } else if (elevation < -M_PI/2){
            elevation = M_PI/2;
         }
      }

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

         if (meshIndx == meshes.size()-1){
            meshIndx = 0; // check if this wld fail 
         } else {
            meshIndx += 1;
         }
         // cout << currentIndx << endl; 


      } else if (key == GLFW_KEY_N){
         // cout << "n pressed" << endl;
         if (meshIndx == 0){
            meshIndx = meshes.size()-1; // check if this wld fail 
         } else {
            meshIndx -= 1;
         }
         // cout << currentIndx << endl; 
 
      } else if (key == GLFW_KEY_UP){
         // moving camera forward - change r
         radius += 0.5;

      } else if (key == GLFW_KEY_DOWN){
         // moving camera backward - change r
         radius -= 0.5;
      } else if (key == GLFW_KEY_S){
         // cycling to next shader 
         if (shaderIndx == shaders.size()-1){
            shaderIndx = 0;
         } else { 
            shaderIndx +=1; 
         }
         
      } else if ((key == GLFW_KEY_S && mods == GLFW_MOD_SHIFT)){
         // going to previous shader 
         if (shaderIndx == 0){
            shaderIndx = shaders.size()-1;
         } else { 
            shaderIndx -=1; 
         }
      }
      cout << meshes[meshIndx]._filename << endl; 
      cout << "maxbounds: " << meshes[meshIndx].maxBounds() << endl; 
      cout << "minbounds: " << meshes[meshIndx].minBounds() << endl; 
   }

   void draw() {
      renderer.beginShader(shaders[shaderIndx]);
      float aspect = ((float)width()) / height();
      renderer.perspective(glm::radians(60.0f), aspect, 0.1f, 50.0f);

      computeCamPos(radius, azimuth, elevation);
      vec3 z = normalize(camPos-lookPos);
      vec3 x = cross(up, z);
      vec3 y = cross(z, x);

      renderer.lookAt(camPos, lookPos, y);

      // renderer.lookAt(eyePos, lookPos, up);

      renderer.rotate(vec3(0,0,0));
      renderer.scale(vec3(meshes[meshIndx].getScaleRatio())); 
      renderer.translate(meshes[meshIndx].getTranslateVal());
      renderer.mesh(meshes[meshIndx]);
      // renderer.cube(); // for debugging!
      renderer.endShader();
   }

protected:
   PLYMesh mesh;
   std::vector<PLYMesh> meshes; 
   std::vector<string> shaders; 
   vec3 eyePos = vec3(10, 0, 0);
   vec3 lookPos = vec3(0, 0, 0);
   vec3 up = vec3(0, 1, 0);
   vec3 camPos = eyePos;
   float azimuth = 0; 
   float elevation = 0; 
   float radius = 10.0f; 
   bool isMousePress = false;

private:
   int meshIndx; 
   int shaderIndx; 
};

int main(int argc, char** argv)
{
   MeshViewer viewer;
   viewer.run();
   return 0;
}


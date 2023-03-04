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

   void mouseMotion(int x, int y, int dx, int dy) {
   }

   void mouseDown(int button, int mods) {
   }

   void mouseUp(int button, int mods) {
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
 
      }
   }

   void draw() {
      float aspect = ((float)width()) / height();
      renderer.perspective(glm::radians(60.0f), aspect, 0.1f, 50.0f);
      renderer.lookAt(eyePos, lookPos, up);

      // renderer.rotate(vec3(0,0,0));
      // renderer.scale(vec3(1,1,1));
      // renderer.translate(vec3(0,0,0));

      // scale logic: -- pretty small but scaling

      float scaleRatio;

      vec3 magnitude; 
      magnitude.x = abs(mesh.maxBounds().x - mesh.minBounds().x);
      magnitude.y = abs(mesh.maxBounds().y - mesh.minBounds().y);
      magnitude.z = abs(mesh.maxBounds().z - mesh.minBounds().z);

      if (magnitude.x > 10 || magnitude.y > 10 || magnitude.z > 10){
         float scale = fmaxf(magnitude.x, magnitude.y); 
         scale = fmaxf(scale, magnitude.z);

         scaleRatio = 10 / scale; 

      } else {
         scaleRatio = 1.0f; 
      }

      // cout << "scale: " << scaleRatio << endl;

      // translate logic: 
      vec3 mediumPos; 
      mediumPos.x = (mesh.maxBounds().x-mesh.minBounds().x)/2;
      mediumPos.y = (mesh.maxBounds().y-mesh.minBounds().y)/2;
      mediumPos.z = (mesh.maxBounds().z-mesh.minBounds().z)/2;

      // float distToOrigin = sqrt(pow(mediumPos.x, 2) + pow(mediumPos.y, 2) + pow(mediumPos.z, 2));

      renderer.rotate(vec3(0,0,0));
      // renderer.scale(vec3(1,1,1));
      renderer.scale(vec3(scaleRatio,scaleRatio,scaleRatio)); 
      renderer.translate(vec3(mediumPos.x,mediumPos.y,mediumPos.z));
      renderer.mesh(mesh);
      // renderer.cube(); // for debugging!
   }

protected:
   PLYMesh mesh;
   std::vector<PLYMesh> meshes; 
   vec3 eyePos = vec3(10, 0, 0);
   vec3 lookPos = vec3(0, 0, 0);
   vec3 up = vec3(0, 1, 0);

private:
   int currentIndx = 0; 
};

int main(int argc, char** argv)
{
   MeshViewer viewer;
   viewer.run();
   return 0;
}


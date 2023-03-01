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
      mesh.load("../models/dolphins.ply");

      // if start is always cube
      // finding indx of cube in directory and storing as current indx 
      // src:https://stackoverflow.com/questions/15099707/how-to-get-position-of-a-certain-element-in-strings-vector-to-use-it-as-an-inde
      // auto temp = std::find(dir.begin(), dir.end(), "cube");
      // if (temp != dir.end()){
      //    int currentIndx = std::distance(dir.begin(), temp);
      // }

      // hard code for testing 
      currentIndx = 30; 

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
      if (key == GLFW_KEY_M){

         // cout << " capital N pressed" << endl;

         if (currentIndx == dir.size()-1){
            currentIndx = 0; // check if this wld fail 
         } else {
            currentIndx += 1;
         }
         // cout << currentIndx << endl; 

         // probly not my best idea 
         // mesh.~PLYMesh();
         // mesh.load(dir[currentIndx]);


      } else if (key == GLFW_KEY_N){
         // cout << "n pressed" << endl;
         if (currentIndx == 0){
            currentIndx = dir.size()-1; // check if this wld fail 
         } else {
            currentIndx -= 1;
         }
         // cout << currentIndx << endl; 
         // mesh.~PLYMesh();
         // mesh.load(dir[currentIndx]);
      }
   }

   void draw() {
      float aspect = ((float)width()) / height();
      renderer.perspective(glm::radians(60.0f), aspect, 0.1f, 50.0f);
      renderer.lookAt(eyePos, lookPos, up);

      // renderer.rotate(vec3(0,0,0));
      // renderer.scale(vec3(1,1,1));
      // renderer.translate(vec3(0,0,0));

      renderer.rotate(vec3(0,0,0));
      // renderer.scale(vec3(1,1,1));
      renderer.scale(vec3(1,1,1)); // but will this always work 
      renderer.translate(vec3(0,0,0));
      renderer.mesh(mesh);
      // renderer.cube(); // for debugging!
   }

protected:
   PLYMesh mesh;
   vec3 eyePos = vec3(10, 0, 0);
   vec3 lookPos = vec3(0, 0, 0);
   vec3 up = vec3(0, 1, 0);

private:
   // weird that this prints everything 
   std::vector<std::string> dir = GetFilenamesInDir("../models", "ply"); 
   int currentIndx = 0; 
};

int main(int argc, char** argv)
{
   MeshViewer viewer;
   viewer.run();
   return 0;
}


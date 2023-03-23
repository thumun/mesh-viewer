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

      // dir = GetFilenamesInDir("../shaders", "vs");
      // for (std::string file : dir){
      //    // cout << file.substr(0, file.length()-3) << endl; 
      //    shaders.push_back(file.substr(0, file.length()-3));
      // }
      
      shaders.push_back("normals");
      shaders.push_back("phong-vertex");
      shaders.push_back("phong-pixel");
      shaders.push_back("toon");

      // loading the shaders at start of program 
      for (string s: shaders){
         renderer.loadShader(s, "../shaders/"+s+".vs", "../shaders/"+s+".fs");
      }

      // source: https://pixabay.com/images/search/stars/
      
      textures.push_back("null");
      textures.push_back("stars");
      textures.push_back("bricks");

      // for (string t: textures){
      //    renderer.loadTexture(t, "../textures/"+t+".png", textureIndx);
      //    textureIndx+=1;
      // }

      if (textures.size() > 1){
         textureIndx = 0; 
         for (int i = 1; i < textures.size(); i++){
            renderer.loadTexture(textures[i], "../textures/"+textures[i]+".png", textureIndx+1);
            textureIndx+=1;
         }
      }

      meshIndx = 0; 
      shaderIndx = 0; 
      textureIndx = 0;

   }

   // maybe change floats to int in future
   void computeCamPos(float r, float a, float e){
      camPos.x = r*cos(a)*cos(e);
      camPos.y = r*sin(e);
      camPos.z = r*sin(a)*cos(e);
   }

   void mouseMotion(int x, int y, int dx, int dy) {

      // mapping not look good 
      // azimuth = acos(x/radius);
      // elevation = asin(y/radius);

      if(isMousePress){

         if (abs(dx) > abs(dy)){
            if (dx < 0){
               azimuth -= 0.1f; 
            } else { 
               azimuth += 0.1f; 
            }
            cout << "dx: " << dx << ", dy: " << dy << ", azimuth: " << azimuth << ", elevation: " << elevation << endl;
         } else { 
            if (dy < 0){
               elevation -= 0.05f; 
            } else { 
               elevation += 0.05f; 
            }
         }

         // azimuth += (float)dx*0.1f; 
         // elevation += (float)dy*0.02f; 

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
      } else if ((key == GLFW_KEY_S && mods == GLFW_MOD_SHIFT)){
         // going to previous shader 
         if (shaderIndx == 0){
            shaderIndx = shaders.size()-1;
         } else { 
            shaderIndx -=1; 
         }
      } else if (key == GLFW_KEY_S){
         // cycling to next shader 
         if (shaderIndx == shaders.size()-1){
            shaderIndx = 0;
         } else { 
            shaderIndx +=1; 
         }
         
      } else if ((key == GLFW_KEY_T && mods == GLFW_MOD_SHIFT)){
         // going to previous shader 
         if (textureIndx == 0){
            textureIndx = textures.size()-1;
         } else { 
            textureIndx -=1; 
            if (textureIndx == 0) {isTextured = false;};
         }
      } else if (key == GLFW_KEY_T){
         // cycling to next shader 
         if (textureIndx == textures.size()-1){
            isTextured = false;
            textureIndx = 0;
         } else { 
            textureIndx +=1; 
         }
         
      } 
      // cout << meshes[meshIndx]._filename << endl; 
      // cout << "maxbounds: " << meshes[meshIndx].maxBounds() << endl; 
      // cout << "minbounds: " << meshes[meshIndx].minBounds() << endl; 
   }

   void draw() {
      renderer.beginShader(shaders[shaderIndx]);

      // do make this better (?) - only initialize if 
      // shaders[shaderIndx].find("phong") == true 

      // for phong:

      isTextured = false; 

      if(textureIndx != 0){
         renderer.texture("diffuseTexture", textures[textureIndx]);
         isTextured = true; 
      }
      
      //http://learnwebgl.brown37.net/09_lights/lights_combined.html
      // used above to find numbers for lights 
      renderer.setUniform("Light.Position", 20, 20, 20, 1);
      renderer.setUniform("Light.La", 0.4, 0.2, 0.2);
      // hoping for a yellow color for light 
      renderer.setUniform("Light.Ld", 1.0, 1.0, 0.7);
      renderer.setUniform("Light.Ls", 1.0, 1.0, 0.7);

      //https://learnopengl.com/Lighting/Materials
      // http://devernay.free.fr/cours/opengl/materials.html
      // above link has table of materials -- used below (jade)
      renderer.setUniform("Material.Ka", 0.135, 0.2225, 0.1575);
      renderer.setUniform("Material.Kd", 0.54, 0.89, 0.63);
      renderer.setUniform("Material.Ks", 0.316228, 0.316228, 0.316228);
      renderer.setUniform("Material.Shininess", 0.1f);

      // for toon: 
      renderer.setUniform("LightPosition", 20, 20, 20);
      
      renderer.setUniform("isTexture", isTextured);

      float aspect = ((float)width()) / height();
      renderer.perspective(glm::radians(60.0f), aspect, 0.1f, 50.0f);

      computeCamPos(radius, azimuth, elevation);
      vec3 z = normalize(camPos-lookPos);
      vec3 x = cross(up, z);
      vec3 y = cross(z, x);

      renderer.lookAt(camPos, lookPos, vec3(0,1,0));

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
   std::vector<string> textures; 
   vec3 eyePos = vec3(10, 0, 0);
   vec3 lookPos = vec3(0, 0, 0);
   vec3 up = vec3(0, 1, 0);
   vec3 camPos = eyePos;
   float azimuth = 0; 
   float elevation = 0; 
   float radius = 10.0f; 
   bool isMousePress = false;
   bool isTextured;

private:
   int meshIndx; 
   int shaderIndx; 
   int textureIndx;
};

int main(int argc, char** argv)
{
   MeshViewer viewer;
   viewer.run();
   return 0;
}


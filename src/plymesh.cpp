//--------------------------------------------------
// Author:
// Date:
// Description: Loads PLY files in ASCII format
//--------------------------------------------------

#include "plymesh.h"
#include <limits>

using namespace std;
using namespace glm;

namespace agl {

   PLYMesh::PLYMesh(const std::string& filename) {
      load(filename);
      _minBounds = glm::vec3(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
      _maxBounds = glm::vec3(std::numeric_limits<float>::min(), std::numeric_limits<float>::min(), std::numeric_limits<float>::min());
   }

   PLYMesh::PLYMesh() {
   }

   void PLYMesh::init() {
      assert(_positions.size() != 0);
      initBuffers(&_faces, &_positions, &_normals);
   }

   PLYMesh::~PLYMesh() {
      _positions.clear();
      _normals.clear();
      _faces.clear();
   }

   bool PLYMesh::load(const std::string& filename) {
      if (_positions.size() != 0) {
         std::cout << "WARNING: Cannot load different files with the same PLY mesh\n";
         return false;
      }
      // reading file inputted 
      std::ifstream plyFile; 
      std::string line; 
      plyFile.open(filename);

      // check nullptr for plyfile? 
      // there's prbly a better way to read header 

      int lineCount = 0; 
      std::vector<string> lineItems;
      int verticiesNum = 0;
      int polygonNum = 0;

      // cout << "test" << endl;

      if (plyFile.is_open()) {

         getline(plyFile, line);
         // cout << line.find("ply") << endl;
         if (line.find("ply") == string::npos){
            // cout << "skipped:  " << line << endl;
            return false;
         }

         while(plyFile){
            getline(plyFile, line);
            if (line.find("element vertex") == string::npos){
               // cout << "skipped:  " << line << endl;
               continue;
            } else {
               lineItems = split(line, ' ');
               verticiesNum = stoi(lineItems[lineItems.size() - 1]);
               // cout << line << endl;
               // cout << "vertex: " << verticiesNum << endl;
               break; 
            }
         }

         while(plyFile){
            getline(plyFile, line);
            if (line.find("element face") == string::npos){
               // cout << "skipped:  " << line << endl;
               continue;
            } else {
               lineItems = split(line, ' ');
               polygonNum = stoi(lineItems[lineItems.size() - 1]);
               // cout << line << endl;
               // cout << "polygon: " << polygonNum << endl;
               break;
            }
         }

         while(plyFile){
            getline(plyFile, line);
            if (line.find("end_header") == string::npos){
               // cout << "skipped:  " << line << endl;
               continue;
            } else {
               // cout << "skipped:  " << line << endl;
               break;
            }
         }

         while(plyFile){
            // doing if statement here to differentiate vertex & polygon
            if (verticiesNum > 0){
               getline(plyFile, line);
               lineItems = split(line, ' ');
               _positions.push_back(std::stof(lineItems[0])); // x
               _positions.push_back(std::stof(lineItems[1])); // y
               _positions.push_back(std::stof(lineItems[2])); // z

               _normals.push_back(std::stof(lineItems[3])); // nx
               _normals.push_back(std::stof(lineItems[4])); // ny
               _normals.push_back(std::stof(lineItems[5])); // nz

               // cout << "vertex: " << lineItems[0] << ", " << lineItems[1] << ", " << lineItems[2] << endl; 

               verticiesNum -= 1; 
            } else if (polygonNum > 0){
               getline(plyFile, line);
               lineItems = split(line, ' ');
               _faces.push_back(std::stoi(lineItems[1]));
               _faces.push_back(std::stoi(lineItems[2]));
               _faces.push_back(std::stoi(lineItems[3]));

               // cout << "face: " << lineItems[1] << ", " << lineItems[2] << ", " << lineItems[3] << endl;
               polygonNum -= 1;  
            } else {
               break;
            }
         }
      }

      if (plyFile.is_open()){
         plyFile.close();
      }

      // calculating max & min bounds 
      for (int i = 0; i < _positions.size(); i++){
         _maxBounds.x = fmaxf(_maxBounds.x, _positions[i]);
         _maxBounds.y = fmaxf(_maxBounds.y, _positions[i+1]);
         _maxBounds.z = fmaxf(_maxBounds.z, _positions[i+2]);

         _minBounds.x = fminf(_minBounds.x, _positions[i]);
         _minBounds.y = fminf(_minBounds.y, _positions[i+1]);
         _minBounds.z = fminf(_minBounds.z, _positions[i+2]);
      }

      return true;
   }

   glm::vec3 PLYMesh::minBounds() const {
      return _minBounds;
   }

   glm::vec3 PLYMesh::maxBounds() const {
      return _maxBounds; 
   }

   // am i allowed to change this 
   int PLYMesh::numVertices() const {
      return _positions.size()/3;
   }

   // am i allowed to change this 
   int PLYMesh::numTriangles() const {
      return _faces.size()/3;
   }

   const std::vector<GLfloat>& PLYMesh::positions() const {
      return _positions;
   }

   const std::vector<GLfloat>& PLYMesh::normals() const {
      return _normals;
   }

   const std::vector<GLuint>& PLYMesh::indices() const {
      return _faces;
   }
   
   float PLYMesh::getScaleRatio() {
      float scaleRatio; 
      vec3 magnitude; 
      magnitude.x = abs(maxBounds().x - minBounds().x);
      magnitude.y = abs(maxBounds().y - minBounds().y);
      magnitude.z = abs(maxBounds().z - minBounds().z);

      if (magnitude.x > 10 || magnitude.y > 10 || magnitude.z > 10){
         float scale = fmaxf(magnitude.x, magnitude.y); 
         scale = fmaxf(scale, magnitude.z);

         scaleRatio = 10 / scale; 

      } else {
         scaleRatio = 1.0f; 
      }

      return scaleRatio;
   }

   glm::vec3 PLYMesh::getTranslateVal() {
      vec3 mediumPos; 

      float scaleRatio = getScaleRatio();
      mediumPos.x = scaleRatio*(maxBounds().x-minBounds().x)/2;
      mediumPos.y = scaleRatio*(maxBounds().y-minBounds().y)/2;
      mediumPos.z = scaleRatio*(maxBounds().z-minBounds().z)/2;

      return mediumPos;
   }

   // extension functions

   std::vector<std::string> PLYMesh::split(std::string str, char delimiter){
      std::stringstream ss;
      ss << str;
      vector<string> lineItems;
      string output;
      while (getline(ss, output, delimiter)) {
         lineItems.push_back(output);
      }
      return lineItems;
   }
}

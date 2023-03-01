//--------------------------------------------------
// Author:
// Date:
// Description: Loads PLY files in ASCII format
//--------------------------------------------------

#include "plymesh.h"

using namespace std;
using namespace glm;

namespace agl {

   PLYMesh::PLYMesh(const std::string& filename) {
      load(filename);
   }

   PLYMesh::PLYMesh() {
   }

   void PLYMesh::init() {
      assert(_positions.size() != 0);
      initBuffers(&_faces, &_positions, &_normals);
   }

   PLYMesh::~PLYMesh() {
   }

   bool PLYMesh::load(const std::string& filename) {
      if (_positions.size() != 0) {
         std::cout << "WARNING: Cannot load different files with the same PLY mesh\n";
         return false;
      }
      // todo: your code here

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
               _positions.push_back(std::stof(lineItems[1])); // z

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

      plyFile.close();

      return true;
   }

   glm::vec3 PLYMesh::minBounds() const {
      return glm::vec3(0);
   }

   glm::vec3 PLYMesh::maxBounds() const {
      return glm::vec3(0);
   }

   int PLYMesh::numVertices() const {
      return _positions.size();
   }

   int PLYMesh::numTriangles() const {
      return _faces.size();
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

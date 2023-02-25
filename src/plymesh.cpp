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
      return false;
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
}

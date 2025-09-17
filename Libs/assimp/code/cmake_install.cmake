# Install script for directory: H:/Desarrollo/ComputoGrafico2025/libs/assimp/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Assimp")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibassimp6.0.2-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "H:/Desarrollo/ComputoGrafico2025/libs/assimp/lib/Debug/assimp-vc143-mtd.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "H:/Desarrollo/ComputoGrafico2025/libs/assimp/lib/Release/assimp-vc143-mt.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "H:/Desarrollo/ComputoGrafico2025/libs/assimp/lib/MinSizeRel/assimp-vc143-mt.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "H:/Desarrollo/ComputoGrafico2025/libs/assimp/lib/RelWithDebInfo/assimp-vc143-mt.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibassimp6.0.2x" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "H:/Desarrollo/ComputoGrafico2025/libs/assimp/bin/Debug/assimp-vc143-mtd.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "H:/Desarrollo/ComputoGrafico2025/libs/assimp/bin/Release/assimp-vc143-mt.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "H:/Desarrollo/ComputoGrafico2025/libs/assimp/bin/MinSizeRel/assimp-vc143-mt.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "H:/Desarrollo/ComputoGrafico2025/libs/assimp/bin/RelWithDebInfo/assimp-vc143-mt.dll")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/anim.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/aabb.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/ai_assert.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/camera.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/color4.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/color4.inl"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/config.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/ColladaMetaData.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/commonMetaData.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/defs.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/cfileio.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/light.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/material.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/material.inl"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/matrix3x3.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/matrix3x3.inl"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/matrix4x4.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/matrix4x4.inl"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/mesh.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/ObjMaterial.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/pbrmaterial.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/GltfMaterial.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/postprocess.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/quaternion.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/quaternion.inl"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/scene.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/metadata.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/texture.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/types.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/vector2.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/vector2.inl"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/vector3.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/vector3.inl"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/version.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/cimport.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/AssertHandler.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/importerdesc.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/Importer.hpp"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/DefaultLogger.hpp"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/ProgressHandler.hpp"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/IOStream.hpp"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/IOSystem.hpp"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/Logger.hpp"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/LogStream.hpp"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/NullLogger.hpp"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/cexport.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/Exporter.hpp"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/DefaultIOStream.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/DefaultIOSystem.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/ZipArchiveIOSystem.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/SceneCombiner.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/fast_atof.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/qnan.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/BaseImporter.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/Hash.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/MemoryIOWrapper.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/ParsingUtils.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/StreamReader.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/StreamWriter.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/StringComparison.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/StringUtils.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/SGSpatialSort.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/GenericProperty.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/SpatialSort.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/SkeletonMeshBuilder.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/SmallVector.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/SmoothingGroups.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/SmoothingGroups.inl"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/StandardShapes.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/RemoveComments.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/Subdivision.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/Vertex.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/LineSplitter.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/TinyFormatter.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/Profiler.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/LogAux.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/Bitmap.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/XMLTools.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/IOStreamBuffer.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/CreateAnimMesh.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/XmlParser.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/BlobIOSystem.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/MathFunctions.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/Exceptional.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/ByteSwapper.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/Base64.hpp"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/Compiler/pushpack1.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/Compiler/poppack1.h"
    "H:/Desarrollo/ComputoGrafico2025/libs/assimp/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "H:/Desarrollo/ComputoGrafico2025/libs/assimp/bin/Debug/assimp-vc143-mtd.pdb")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "H:/Desarrollo/ComputoGrafico2025/libs/assimp/bin/Release/assimp-vc143-mt.pdb")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "H:/Desarrollo/ComputoGrafico2025/libs/assimp/bin/MinSizeRel/assimp-vc143-mt.pdb")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "H:/Desarrollo/ComputoGrafico2025/libs/assimp/bin/RelWithDebInfo/assimp-vc143-mt.pdb")
  endif()
endif()


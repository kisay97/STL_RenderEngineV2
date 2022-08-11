#pragma once

#include <Core/Core.h>

#include <Math/Vector2f.h>
#include <Math/Vector3f.h>
#include <Renderer/VertexDeclaration.h>
#include <Renderer/StaticMesh.h>

#include <Importer.hpp>
#include <cimport.h>
#include <postprocess.h>
#include <scene.h>

namespace STL
{
	class ENGINE_API ModelLoader
	{
	public:
		static void LoadModel(ID3D11Device* device, const std::string& filename, StaticMesh* outMesh);
		
	private:
		static const aiScene* ImportMesh(const std::string& filename);
		static void ProcessNode(ID3D11Device* device, aiNode* node, const aiScene* scene, StaticMesh* outMesh);
		static void ProcessMesh(ID3D11Device* device, const aiMesh* mesh, const aiScene* scene, StaticMesh* outMesh);
	};
}
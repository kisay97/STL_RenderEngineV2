#include "Core.h"
#include "ModelLoader.h"
#include <Utility/STLException.h>
#include <Material/TransformMaterial.h>

namespace STL
{
	void ModelLoader::LoadModel(ID3D11Device* device, const std::string& filename, StaticMesh* outMesh)
	{
		//auto search = meshMap.find(filename);
		//if (search != meshMap.end())
		//{
		//	outMesh = search->second;
		//	return;
		//}

		std::unique_ptr<const aiScene> scene(ImportMesh(filename));

		if (scene == nullptr)
		{
			throw std::exception("failed to load modeling.");
		}

		ProcessNode(device, scene->mRootNode, scene.get(), outMesh);
	}

	const aiScene* ModelLoader::ImportMesh(const std::string& filename)
	{
		auto finalPath = std::filesystem::current_path().parent_path();
		finalPath /= "Content\\Models";
		finalPath /= filename;

		static const uint32 flags =
			aiProcess_JoinIdenticalVertices |
			aiProcess_ValidateDataStructure |
			aiProcess_ImproveCacheLocality |
			aiProcess_RemoveRedundantMaterials |
			aiProcess_GenUVCoords |
			aiProcess_CalcTangentSpace |
			aiProcess_TransformUVCoords |
			aiProcess_FindInstances |
			aiProcess_LimitBoneWeights |
			aiProcess_OptimizeMeshes |
			aiProcess_GenSmoothNormals |
			aiProcess_SplitLargeMeshes |
			aiProcess_Triangulate |
			aiProcess_ConvertToLeftHanded |
			aiProcess_SortByPType;

		return aiImportFile(finalPath.string().c_str(), flags);
	}

	void ModelLoader::ProcessNode(ID3D11Device* device, aiNode* node, const aiScene* scene, StaticMesh* outMesh)
	{
		for (uint32 ix = 0; ix < node->mNumMeshes; ++ix)
		{
			const aiMesh* mesh = scene->mMeshes[node->mMeshes[ix]];
			ProcessMesh(device, mesh, scene, outMesh);
		}

		for (uint32 ix = 0; ix < node->mNumChildren; ++ix)
		{
			ProcessNode(device, node->mChildren[ix], scene, outMesh);
		}
	}

	void LoadPosition(const aiMesh* mesh, uint32 index, Vector3f& outPosition)
	{
		outPosition.x = mesh->mVertices[index].x;
		outPosition.y = mesh->mVertices[index].y;
		outPosition.z = mesh->mVertices[index].z;
	}

	void LoadUV(const aiMesh* mesh, uint32 index, Vector2f& outUV)
	{
		if (mesh->HasTextureCoords(0) == true)
		{
			outUV.x = mesh->mTextureCoords[0][index].x;
			outUV.y = mesh->mTextureCoords[0][index].y;
		}
	}

	void LoadNormal(const aiMesh* mesh, uint32 index, Vector3f& outNormal)
	{
		if (mesh->HasNormals() == true)
		{
			outNormal.x = mesh->mNormals[index].x;
			outNormal.y = mesh->mNormals[index].y;
			outNormal.z = mesh->mNormals[index].z;
		}
	}

	void LoadTangentAndBiNormal(const aiMesh* mesh, uint32 index, Vector3f& outTangent, Vector3f& outBinormal)
	{
		if (mesh->HasTangentsAndBitangents() == true)
		{
			outTangent.x = mesh->mTangents[index].x;
			outTangent.y = mesh->mTangents[index].y;
			outTangent.z = mesh->mTangents[index].z;

			outBinormal.x = mesh->mBitangents[index].x;
			outBinormal.y = mesh->mBitangents[index].y;
			outBinormal.z = mesh->mBitangents[index].z;
		}
	}

	std::wstring GetFileNameOnly(aiString& path)
	{
		std::string pathString = path.C_Str();
		std::filesystem::path filePath(pathString);
		std::string filename = filePath.filename().string();
		std::wstring wfilename;
		wfilename.assign(filename.begin(), filename.end());

		return wfilename;
	}

	void ModelLoader::ProcessMesh(ID3D11Device* device, const aiMesh* mesh, const aiScene* scene, StaticMesh* outMesh)
	{
		std::vector<VertexPositionColorUVNormalTangentBinormal> vertices;
		//std::vector<VertexPositionUV> vertices;
		std::vector<uint32> indices;
		std::vector<std::wstring> textures;

		vertices.reserve(static_cast<size_t>(mesh->mNumVertices));
		indices.reserve(static_cast<size_t>((mesh->mNumFaces * static_cast<size_t>(3))));
		textures.reserve(static_cast<size_t>(scene->mNumTextures));

		for (uint32 ix = 0; ix < mesh->mNumVertices; ++ix)
		{
			Vector3f position;
			LoadPosition(mesh, ix, position);

			Vector2f uv;
			LoadUV(mesh, ix, uv);

			Vector3f color = Vector3f::One;
			Vector3f normal;
			LoadNormal(mesh, ix, normal);

			Vector3f tangent;
			Vector3f binormal;
			LoadTangentAndBiNormal(mesh, ix, tangent, binormal);

			VertexPositionColorUVNormalTangentBinormal vertex(
				position, color, uv, normal, binormal, tangent
			);
			vertices.emplace_back(vertex);
			//VertexPositionUV vertex(position, uv);
			//vertices.emplace_back(vertex);
		}

		for (uint32 ix = 0; ix < mesh->mNumFaces; ++ix)
		{
			const aiFace& face = mesh->mFaces[ix];

			indices.emplace_back(face.mIndices[0]);
			indices.emplace_back(face.mIndices[1]);
			indices.emplace_back(face.mIndices[2]);
		}

		//aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		//aiString diffusePath;
		//aiGetMaterialTexture(material, aiTextureType::aiTextureType_DIFFUSE, 0, &diffusePath);

		//TransformMaterial* transformMaterial = nullptr;
		//if (diffusePath != aiString(""))
		//{
		//	textures.emplace_back(GetFileNameOnly(diffusePath));
		//	transformMaterial = new TransformMaterial();
		//	transformMaterial->AddTexture(new Texture(textures[textures.size() - 1]));
		//}

		//if (transformMaterial != nullptr)
		//{
		//	outMesh->AddMaterial(transformMaterial);
		//	transformMaterial->Initialize(device);
		//}

		//SubMesh* outMesh = new SubMesh();

		outMesh->AddSubMesh(device,
			vertices.data(), static_cast<uint32>(vertices.size()), sizeof(vertices[0]),
			indices.data(), static_cast<uint32>(indices.size())
		);

		//return outMesh;
	}
}